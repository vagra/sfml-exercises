#include "GridManager.h"

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

    for (auto& actor : ActorManager::instance().actors)
    {
        lgrid_insert(mp_grid, actor->id,
            actor->position.x, actor->position.y, AGENT_HALFW, AGENT_HALFH
        );
    }

    lgrid_optimize(mp_grid);
}

void GridManager::updateActors() {

    SmallList<int> ids;

    Hero* hero = nullptr;
    Hero* other = nullptr;

    for (auto& actor : ActorManager::instance().actors)
    {
        hero = dynamic_cast<Hero*>(actor.get());

        if (hero->disabled) {
            continue;

        } else if (hero->inDeath()) {
            lgrid_remove(mp_grid, hero->id,
                hero->position.x, hero->position.y
            );

            hero->disable();
            continue;
        }

        lgrid_move(mp_grid, hero->id,
            hero->prev_position.x, hero->prev_position.y,
            hero->position.x, hero->position.y
        );

        if (hero->inBattle()) {
            continue;
        }

        ids = lgrid_query(mp_grid,
            actor->position.x, actor->position.y,
            AGENT_HALFW, AGENT_HALFH,
            actor->id
        );

        if (ids.size() == 0) {
            continue;
        }

        for (int i = 0; i < ids.size(); i++) {
            other = ActorManager::instance().getActor<Hero>(ids[i]);

            if (hero->atFront(other)) {
                if (hero->type != other->type &&
                    hero->canAttack(other)) {
                    hero->attack(other);
                }
                else {
                    hero->bump();
                }
                break;
            }
        }
    }

    lgrid_optimize(mp_grid);
}

void GridManager::drawActors(sf::RenderWindow& window) {
    LGridLooseCell* lcell = nullptr;
    LGridElt* elt = nullptr;
    Hero* hero = nullptr;
    int elt_idx = 0;

    for (int i = 0; i < mp_grid->loose.num_cells; i++) {
        lcell = &mp_grid->loose.cells[i];

        elt_idx = lcell->head;
        while (elt_idx != -1)
        {
            elt = &mp_grid->elts[elt_idx];
            hero = ActorManager::instance().getActor<Hero>(elt->id);

            window.draw(*hero->sprite);
            if (hero->inAttacked()) {
                window.draw(*hero->text);
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

        lrects.at(i)->setPosition(sf::Vector2(
            lcell->rect[0], lcell->rect[1]
        ));
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
        lrect->setSize(
            sf::Vector2(lcell->rect[2] - lcell->rect[0], lcell->rect[3] - lcell->rect[1])
        );
        lrect->setPosition(
            sf::Vector2(lcell->rect[0], lcell->rect[1])
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
            trect->setSize(sf::Vector2f(TCELL_WIDTH, TCELL_HEIGHT));
            trect->setPosition(
                narrow_cast<float>(TCELL_WIDTH * j),
                narrow_cast<float>(TCELL_HEIGHT * i)
            );
            trect->setFillColor(sf::Color::Transparent);
            trect->setOutlineColor(TRECT_COLOR);
            trect->setOutlineThickness(0.5f);

            trects.push_back(move(trect));
        }
    }

}