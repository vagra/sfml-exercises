#include "App.h"

App::App() {
    init();
}

void App::init() {
    initWindow();
    initText();

    TextureManager::init();

    initActors();

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
        }

        elapsed = clock.restart();

        updateActors(elapsed);
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
    sf::Vector2f win = static_cast<sf::Vector2f>(window.getSize());

    Actor::setRegion(int(win.x), int(win.y));

    sf::View view = window.getDefaultView();
    view.setCenter(win / 2.f);
    view.setSize(win);

    window.setView(view);
}

void App::initWindow() {
    window.create(sf::VideoMode(INIT_WIDTH, INIT_HEIGHT), APP_NAME);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
}

void App::initText() {
    if (!font.loadFromFile(FONT_OTF))
    {
        cout << "can't read font: " << FONT_OTF << endl;
    }

    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Yellow);
}

void App::drawText() {
    window.draw(text);
}

void App::updateText(sf::Time elapsed) {
    int fps = int(1 / elapsed.asSeconds());
    text.setString(fmt::format("Character Number: {}\nFPS: {}", MAX, fps));
}

void App::initActors() {

    actors = vector<Actor>();

    for (int i = 0; i < MAX; i++)
    {
        Actor actor;

        actors.push_back(actor);
    }
}

void App::updateActors(sf::Time elapsed) {
    for (auto& actor : actors)
    {
        actor.play(elapsed);
    }
}

void App::drawActors() {
    for (auto& actor : actors)
    {
        window.draw(actor.sprite);
    }
}

void App::initGrid() {
    mp_grid = lgrid_create(
        LCELL_WIDTH, LCELL_HEIGHT, TCELL_WIDTH, TCELL_HEIGHT,
        0.f, 0.f, GRID_WIDTH, GRID_HEIGHT 
    );

    for (auto& actor : actors)
    {
        lgrid_insert(mp_grid, actor.getID(), actor.getX(), actor.getY(), SPRITE_HALFW, SPRITE_HALFH);
    }

    lgrid_optimize(mp_grid);

}

void App::updateGrid() {

    SmallList<int> ids;

    for (auto& actor : actors)
    {
        lgrid_move(mp_grid, actor.getID(), actor.prevX(), actor.prevY(),
            actor.getX(), actor.getY());

        ids = lgrid_query(mp_grid, actor.getX(), actor.getY(), SPRITE_HALFW, SPRITE_HALFH, actor.getID());

        if (ids.size() == 0) {
            continue;
        }

        for (int i = 0; i < ids.size(); i++) {
            Actor& other = actors[ids[i]];
            if (Actor::atFront(actor, other)) {
                actor.turn();
                break;
            }
        }
    }

    lgrid_optimize(mp_grid);
}

void App::initRects() {

    for (int i = 0; i < mp_grid->loose.num_rows; i++) {
        for (int j = 0; j < mp_grid->loose.num_cols; j++) {

            sf::RectangleShape trect(sf::Vector2f(TCELL_WIDTH, TCELL_HEIGHT));
            trect.setPosition(float(TCELL_WIDTH) * j, float(TCELL_HEIGHT) * i);
            trect.setFillColor(sf::Color::Transparent);
            trect.setOutlineColor(sf::Color(128, 0, 0, 100));
            trect.setOutlineThickness(0.5f);
            trects.push_back(trect);
        }
    }

    for (int i = 0; i < mp_grid->loose.num_cells; i++) {
        LGridLooseCell* lcell = &mp_grid->loose.cells[i];

        sf::RectangleShape lrect(sf::Vector2(
            lcell->rect[2] - lcell->rect[0],
            lcell->rect[3] - lcell->rect[1]
        ));
        lrect.setPosition(sf::Vector2(
            lcell->rect[0], lcell->rect[1]
        ));
        lrect.setFillColor(sf::Color::Transparent);
        lrect.setOutlineColor(sf::Color(0, 255, 0, 100));
        lrect.setOutlineThickness(1.f);
        lrects.push_back(lrect);
    }
}

void App::updateRects() {

    for (int i = 0; i < mp_grid->loose.num_cells; i++) {
        LGridLooseCell* lcell = &mp_grid->loose.cells[i];

        lrects[i].setSize(sf::Vector2(
            lcell->rect[2] - lcell->rect[0],
            lcell->rect[3] - lcell->rect[1]
        ));
        lrects[i].setPosition(sf::Vector2(
            lcell->rect[0], lcell->rect[1]
        ));
    }
}

void App::drawRects() {
    for (auto& trect : trects) {
        window.draw(trect);
    }

    for (auto& lrect : lrects) {
        window.draw(lrect);
    }
}