#include "App.h"

void App::init() {

    FontManager::instance().loadFonts();
    TextureManager::instance().loadTextures(PNG_DIR);
    ActionManager::instance().loadActions(PNG_DIR, ROW_ACTIONS);
    ActorManager::instance().makeActors<Hero>(ACTORS, ACTOR_TYPES, true);

    initWindow();
    initText();
    initGrid();
    initRects();
}

void App::run() {
    
    sf::Clock clock;
    sf::Time elapsed;

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::Resized)
            {
                onResize();
            }

            if (event.type == sf::Event::KeyPressed ||
                event.type == sf::Event::KeyReleased)
            {
                onKeyboard();
            }
        }

        elapsed = clock.restart();

        ActorManager::instance().update(elapsed);
        updateText(elapsed);

        updateGrid();
        updateRects();

        window.clear(BG_COLOR);
        
        drawRects();
        drawActors();

        drawText();
        
        window.display();
    }
}

void App::onResize() {
    const sf::Vector2f win = static_cast<sf::Vector2f>(window.getSize());

    Actor::setRegion(narrow_cast<int>(win.x), narrow_cast<int>(win.y));

    sf::View view = window.getDefaultView();
    view.setCenter(win / 2.f);
    view.setSize(win);

    window.setView(view);
}

void App::onKeyboard() {
    
}

void App::initWindow() {
    window.create(sf::VideoMode(INIT_WIDTH, INIT_HEIGHT), APP_NAME);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
}

void App::initText() {
    text.setFont(*FontManager::instance().getFont(GUI_FONT));
    text.setCharacterSize(GUI_FONT_SIZE);
    text.setFillColor(GUI_COLOR);
}

void App::drawText() {
    window.draw(text);
}

void App::updateText(sf::Time elapsed) {
    int fps = narrow_cast<int>(1 / elapsed.asSeconds());
    text.setString(fmt::format("Actors: {}\nFPS: {}", ACTORS, fps));
}

void App::initGrid() {
    mp_grid = lgrid_create(
        LCELL_WIDTH, LCELL_HEIGHT, TCELL_WIDTH, TCELL_HEIGHT,
        0.f, 0.f, GRID_WIDTH, GRID_HEIGHT 
    );

    for (auto& actor : ActorManager::instance().actors)
    {
        lgrid_insert(mp_grid, actor->id,
            actor->position.x, actor->position.y, AGENT_HALFW, AGENT_HALFH
        );
    }

    lgrid_optimize(mp_grid);
}

void App::updateGrid() {

    SmallList<int> ids;

    Hero* hero = nullptr;
    Hero* other = nullptr;

    for (auto& actor : ActorManager::instance().actors)
    {
        hero = dynamic_cast<Hero*>(actor.get());

        lgrid_move(mp_grid, hero->id,
            hero->prev_position.x, hero->prev_position.y,
            hero->position.x, hero->position.y
        );

        ids = lgrid_query(mp_grid,
            actor->position.x, actor->position.y,
            AGENT_HALFW, AGENT_HALFH,
            actor->id
        );

        for (int i = 0; i < ids.size(); i++) {
            other = ActorManager::instance().getActor<Hero>(ids[i]);

            if (hero->atFront(other)) {
                hero->bump();
                break;
            }
        }
    }

    lgrid_optimize(mp_grid);
}

void App::drawActors() {
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
            // window.draw(*hero->text);

            elt_idx = elt->next;
        }
    }
}

void App::initRects() {
    initTRects();
    initLRects();
}

void App::updateRects() {
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

void App::drawRects() {
    for (int i = 0; i < mp_grid->tight.num_cells; i++) {
        window.draw(*trects.at(i));
    }

    for (int i = 0; i < mp_grid->loose.num_cells; i++) {

        if (mp_grid->loose.cells[i].head != -1) {
            window.draw(*lrects.at(i));
        }
    }
}
void App::initLRects() {
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

void App::initTRects() {
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