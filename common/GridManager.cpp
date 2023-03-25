#include "GridManager.h"

// ---------------------------------------------
// public methods
// ---------------------------------------------

void GridManager::init(Grid config, bool show_rects) {
    m_config = config;
    m_show_rects = show_rects;

    mp_grid = lgrid_create(
        config.lcell_w, config.lcell_h,
        config.tcell_w, config.tcell_h,
        config.grid_l, config.grid_t,
        config.grid_r, config.grid_b
    );

    initActors();

    if (m_show_rects) {
        initRects();
    }
}

void GridManager::update() {
    updateActors();
    if (m_show_rects) {
        updateRects();
    }
}

void GridManager::draw(sf::RenderWindow& window) {
    if (m_show_rects) {
        drawRects(window);
    }
    drawActors(window);
}

// ---------------------------------------------
// private methods
// ---------------------------------------------

void GridManager::initActors() {

    for (auto& actor : ActorManager::instance().actors)
    {
        lgrid_insert(mp_grid, actor->id,
            actor->position.x, actor->position.y,
            m_config.agent_hw, m_config.agent_hh
        );
    }

    lgrid_optimize(mp_grid);
}

void GridManager::updateActors() {

    SmallList<int> ids;

    Actor* other = nullptr;

    for (auto& actor : ActorManager::instance().actors)
    {
        if (actor->removed) {
            continue;

        }
        
        if (actor->needRemove()) {
            lgrid_remove(mp_grid, actor->id,
                actor->position.x, actor->position.y
            );

            actor->remove();

            continue;
        }

        lgrid_move(mp_grid, actor->id,
            actor->prev_position.x, actor->prev_position.y,
            actor->position.x, actor->position.y
        );

        if (actor->skipBump()) {
            continue;
        }

        ids = lgrid_query(mp_grid,
            actor->position.x, actor->position.y,
            m_config.agent_hw, m_config.agent_hh,
            actor->id
        );

        if (ids.size() == 0) {
            continue;
        }

        for (int i = 0; i < ids.size(); i++) {
            other = ActorManager::instance().getActor(ids[i]);
            Ensures(other);

            if (actor->atFront(other)) {
                actor->handleBump(other);

                break;
            }
        }
    }

    lgrid_optimize(mp_grid);
}

void GridManager::drawActors(sf::RenderWindow& window) {
    LGridLooseCell* lcell = nullptr;
    LGridElt* elt = nullptr;
    Actor* actor = nullptr;
    int elt_idx = 0;

    for (int i = 0; i < mp_grid->loose.num_cells; i++) {
        lcell = &mp_grid->loose.cells[i];

        elt_idx = lcell->head;
        while (elt_idx != -1)
        {
            elt = &mp_grid->elts[elt_idx];
            actor = ActorManager::instance().getActor(elt->id);
            Ensures(actor);

            window.draw(*actor->sprite);
            if (actor->textOn()) {
                window.draw(*actor->text);
            }

            elt_idx = elt->next;
        }
    }
}

void GridManager::initRects() {
    initTRects();
    initLRects();
}

void GridManager::updateRects() {
    LGridLooseCell* lcell = nullptr;

    for (int i = 0; i < mp_grid->loose.num_cells; i++) {
        lcell = &mp_grid->loose.cells[i];

        if (lcell->head == -1) {
            continue;
        }

        lrects.at(i)->setSize(sf::Vector2(
            lcell->rect[2] - lcell->rect[0],
            lcell->rect[3] - lcell->rect[1]
        ));

        lrects.at(i)->setPosition(
            lcell->rect[0], lcell->rect[1]
        );
    }
}

void GridManager::drawRects(sf::RenderWindow& window) {
    for (int i = 0; i < mp_grid->tight.num_cells; i++) {
        window.draw(*trects.at(i));
    }

    for (int i = 0; i < mp_grid->loose.num_cells; i++) {
        if (mp_grid->loose.cells[i].head != -1) {
            window.draw(*lrects.at(i));
        }
    }
}

void GridManager::initLRects() {
    LGridLooseCell* lcell = nullptr;

    lrects.clear();

    for (int i = 0; i < mp_grid->loose.num_cells; i++) {
        lcell = &mp_grid->loose.cells[i];

        auto lrect = make_unique<sf::RectangleShape>();
        lrect->setSize(sf::Vector2(
            lcell->rect[2] - lcell->rect[0],
            lcell->rect[3] - lcell->rect[1]
        ));
        lrect->setPosition(
            lcell->rect[0], lcell->rect[1]
        );
        lrect->setFillColor(sf::Color::Transparent);
        lrect->setOutlineColor(LRECT_COLOR);
        lrect->setOutlineThickness(1.f);

        lrects.push_back(move(lrect));
    }
}

void GridManager::initTRects() {
    trects.clear();

    for (int i = 0; i < mp_grid->tight.num_rows; i++) {
        for (int j = 0; j < mp_grid->tight.num_cols; j++) {

            auto trect = make_unique<sf::RectangleShape>();
            trect->setSize(
                sf::Vector2f(m_config.tcell_w, m_config.tcell_h)
            );
            trect->setPosition(
                m_config.tcell_w * j, m_config.tcell_h * i
            );
            trect->setFillColor(sf::Color::Transparent);
            trect->setOutlineColor(TRECT_COLOR);
            trect->setOutlineThickness(0.5f);

            trects.push_back(move(trect));
        }
    }
}
