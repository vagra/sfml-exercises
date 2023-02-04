#include "App.h"

App::App() {
    init();
}

void App::init() {

    initWindow();

    initText();

    initActors();
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

        sort(actors.begin(), actors.end(), Actor::zOrder);

        fps = int(1 / elapsed.asSeconds());
        text.setString(fmt::format("Character Number: {}\nFPS: {}", MAX, fps));

        window.clear();

        for (auto& actor : actors)
        {
            window.draw(actor.sprite);
        }

        window.draw(text);
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

    // cout << fmt::format("win: ({}, {})", win.x, win.y) << endl;
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

    Actor::readTextures();

    actors = vector<Actor>();

    for (int i = 0; i < MAX; i++)
    {
        Actor actor;

        float x = float(rand() % 1200);
        float y = float(rand() % 800);
        actor.sprite.setPosition(x, y);

        actors.push_back(actor);
    }
}