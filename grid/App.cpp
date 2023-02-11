#include "App.h"

App::App() {
    init();
}

void App::init() {
    initWindow();
    initText();

    TextureManager::init();

    initActors();

    initUGrid();
}

void App::run() {
    
    sf::Clock clock;
    sf::Time elapsed;
    int fps;

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

        for (auto& actor : actors)
        {
            actor.play(elapsed);
        }

        // sort(actors.begin(), actors.end(), Actor::zOrder);

        fps = int(1 / elapsed.asSeconds());
        text.setString(fmt::format("Character Number: {}\nFPS: {}", MAX, fps));

        window.clear(BG_COLOR);

        for (auto& actor : actors)
        {
            window.draw(actor.sprite);
        }

        window.draw(text);
        window.display();

        updateUGrid();
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

void App::initActors() {

    actors = vector<Actor>();

    for (int i = 0; i < MAX; i++)
    {
        Actor actor;

        actors.push_back(actor);
    }
}

void App::initUGrid() {
    mp_grid = ugrid_create(
        SPRITE_RADIUS, CELL_WIDTH, CELL_HEIGHT,
        0.f, 0.f, GRID_WIDTH, GRID_HEIGHT 
    );

    for (auto& actor : actors)
    {
        ugrid_insert(mp_grid, actor.getID(), actor.getX(), actor.getY());
    }

    ugrid_optimize(mp_grid);

    cout << fmt::format("{} {} {}", mp_grid->num_rows, mp_grid->num_cols, mp_grid->num_rows) << endl;

    /*
    for (auto& actor : actors)
    {
        cout << fmt::format("in_bound({}, {}) = {}", actor.getX(), actor.getY(), 
            ugrid_in_bounds(mp_grid, actor.getX(), actor.getY())) << endl;
    }
    */

    /*
    Actor &actor = actors[0];
    actor.sprite.setColor(sf::Color(255, 0, 0));
    cout << fmt::format("{}: {}, {}", actor.getID(), actor.getX(), actor.getY()) << endl;
    */

}

void App::updateUGrid() {

    SmallList<int> ids;

    for (auto& actor : actors)
    {
        ugrid_move(mp_grid, actor.getID(), actor.prevX(), actor.prevY(),
            actor.getX(), actor.getY());

        ids = ugrid_query(mp_grid, actor.getX(), actor.getY(), 2.f * SPRITE_RADIUS, actor.getID());

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

    ugrid_optimize(mp_grid);

}