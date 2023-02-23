#include "GridManager.h"


GridManager::GridManager() {

}

void GridManager::init() {
    init(false);
}

void GridManager::init(bool show_rects) {
    m_show_rects = show_rects;

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

void GridManager::initActors() {

    for (auto& actor : ActorManager::actors)
    {
        lgrid_insert(mp_grid, actor->id,
            actor->position.x, actor->position.y, AGENT_HALFW, AGENT_HALFH
        );
    }

    lgrid_optimize(mp_grid);
}

void GridManager::updateActors() {

    SmallList<int> ids;

    for (auto& actor : ActorManager::actors)
    {
        lgrid_move(mp_grid, actor->id,
            actor->prev_position.x, actor->prev_position.y,
            actor->position.x, actor->position.y
        );

        ids = lgrid_query(mp_grid,
            actor->position.x, actor->position.y,
            AGENT_HALFW, AGENT_HALFH,
            actor->id
        );

        if (ids.size() == 0) {
            continue;
        }

        for (int i = 0; i < ids.size(); i++) {
            Actor* other = ActorManager::getActor(ids[i]);
            if (Actor::atFront(actor, other)) {
                actor->turn();
                break;
            }
        }
    }

    lgrid_optimize(mp_grid);
}

void GridManager::drawActors(sf::RenderWindow& window) {
    for (int i = 0; i < mp_grid->loose.num_cells; i++) {
        LGridLooseCell* lcell = &mp_grid->loose.cells[i];

        int elt_idx = lcell->head;
        while (elt_idx != -1)
        {
            const LGridElt* elt = &mp_grid->elts[elt_idx];

            window.draw(*ActorManager::getActor(elt->id)->sprite);

            elt_idx = elt->next;
        }
    }
}


void GridManager::initRects() {
    initTRects();
    initLRects();
}

void GridManager::updateRects() {
    for (int i = 0; i < mp_grid->loose.num_cells; i++) {
        LGridLooseCell* lcell = &mp_grid->loose.cells[i];

        if (lcell->head == -1) {
            continue;
        }

        lrects[i]->setSize(sf::Vector2(
            lcell->rect[2] - lcell->rect[0],
            lcell->rect[3] - lcell->rect[1]
        ));
        lrects[i]->setPosition(sf::Vector2(
            lcell->rect[0], lcell->rect[1]
        ));
    }
}

void GridManager::drawRects(sf::RenderWindow& window) {
    for (int i = 0; i < mp_grid->tight.num_cells; i++) {
        window.draw(*trects[i]);
    }

    for (int i = 0; i < mp_grid->loose.num_cells; i++) {
        if (mp_grid->loose.cells[i].head != -1) {
            window.draw(*lrects[i]);
        }
    }
}

void GridManager::initLRects() {
    for (int i = 0; i < mp_grid->loose.num_cells; i++) {
        LGridLooseCell* lcell = &mp_grid->loose.cells[i];

        sf::RectangleShape* lrect = new sf::RectangleShape(
            sf::Vector2(lcell->rect[2] - lcell->rect[0], lcell->rect[3] - lcell->rect[1])
        );
        lrect->setPosition(sf::Vector2(
            lcell->rect[0], lcell->rect[1]
        ));
        lrect->setFillColor(sf::Color::Transparent);
        lrect->setOutlineColor(LRECT_COLOR);
        lrect->setOutlineThickness(1.f);

        lrects.push_back(lrect);
    }
}

void GridManager::initTRects() {
    for (int i = 0; i < mp_grid->tight.num_rows; i++) {
        for (int j = 0; j < mp_grid->tight.num_cols; j++) {

            sf::RectangleShape* trect = new sf::RectangleShape(
                sf::Vector2f(TCELL_WIDTH, TCELL_HEIGHT)
            );
            trect->setPosition(float(TCELL_WIDTH) * j, float(TCELL_HEIGHT) * i);
            trect->setFillColor(sf::Color::Transparent);
            trect->setOutlineColor(TRECT_COLOR);
            trect->setOutlineThickness(0.5f);

            trects.push_back(trect);
        }
    }

}

GridManager::~GridManager()
{
    
}