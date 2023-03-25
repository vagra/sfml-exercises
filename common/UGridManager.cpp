#include "UGridManager.h"

// ---------------------------------------------
// public methods
// ---------------------------------------------

void UGridManager::init(Grid config, bool show_rects) {
    m_config = config;
    m_show_rects = show_rects;

    mp_grid = ugrid_create(
        config.agent_r, config.cell_w, config.cell_h,
        config.grid_l, config.grid_t,
        config.grid_r, config.grid_b
    );

    initActors();

    if (m_show_rects) {
        initRects();
    }
}

void UGridManager::update() {
    updateActors();
}

void UGridManager::draw(sf::RenderWindow& window) {
    if (m_show_rects) {
        drawRects(window);
    }
    drawActors(window);
}

// ---------------------------------------------
// private methods
// ---------------------------------------------

void UGridManager::initActors() {

    for (auto& actor : ActorManager::instance().actors)
    {
        ugrid_insert(mp_grid, actor->id,
            actor->position.x, actor->position.y
        );
    }

    ugrid_optimize(mp_grid);
}

void UGridManager::updateActors() {

    SmallList<int> ids;

    Actor* other = nullptr;

    for (auto& actor : ActorManager::instance().actors)
    {
        if (actor->removed) {
            continue;

        }
        
        if (actor->needRemove()) {
            ugrid_remove(mp_grid, actor->id,
                actor->position.x, actor->position.y
            );

            actor->remove();

            continue;
        }

        ugrid_move(mp_grid, actor->id,
            actor->prev_position.x, actor->prev_position.y,
            actor->position.x, actor->position.y
        );

        if (actor->skipBump()) {
            continue;
        }

        ids = ugrid_query(mp_grid,
            actor->position.x, actor->position.y,
            m_config.agent_r, actor->id
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

    ugrid_optimize(mp_grid);
}

void UGridManager::drawActors(sf::RenderWindow& window) {
    UGridRow* row = nullptr;
    UGridElt* elt = nullptr;
    Actor* actor = nullptr;
    int elt_idx = 0;

    for (int i = 0; i < mp_grid->num_rows; i++) {
        row = &mp_grid->rows[i];
        Ensures(row);

        for (int j = 0; j < mp_grid->num_cols; j++) {
            elt_idx = row->cells[j];

            while (elt_idx != -1){
                elt = &row->elts[elt_idx];

                actor = ActorManager::instance().getActor(elt->id);
                Ensures(actor);

                window.draw(*actor->sprite);

                if (actor->textOn()) {
                    window.draw(*actor->text);
                }
                
                elt_idx = row->elts[elt_idx].next;
            }
        }
    }
}

void UGridManager::initRects() {
    for (int i = 0; i < mp_grid->num_rows; i++) {

        for (int j = 0; j < mp_grid->num_cols; j++) {

            auto rect = make_unique<sf::RectangleShape>();
            
            rect->setSize(
                sf::Vector2f(m_config.cell_w, m_config.cell_h)
            );
            rect->setPosition(
                m_config.cell_w * j, m_config.cell_h * i
            );
            rect->setFillColor(sf::Color::Transparent);
            rect->setOutlineColor(RECT_COLOR);
            rect->setOutlineThickness(1.0f);

            rects.push_back(move(rect));
        }
    }
}

void UGridManager::drawRects(sf::RenderWindow& window) {
    UGridRow* row = nullptr;
    int* cell = nullptr;

    for (int r = 0, i = 0; i < mp_grid->num_rows; i++) {
        row = &mp_grid->rows[i];
        Ensures(row);

        for (int j = 0; j < mp_grid->num_cols; j++) {
            cell = &row->cells[j];
            Ensures(cell);

            if (*cell != -1) {
                window.draw(*rects.at(r));
            }
            r++;
        }
    }
}