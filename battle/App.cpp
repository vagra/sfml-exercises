#include "App.h"

App::App() {
    init();
}

void App::init() {

    initWindow();
    initText();

    TextureManager::init();
    ActionManager::init();
    ActorManager::init();
    GridManager::init(true);
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

        ActorManager::update(elapsed);
        updateText(elapsed);
        GridManager::update();

        window.clear(BG_COLOR);
        
        GridManager::draw(window);
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

void App::onKeyboard() {

    
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
    text.setString(fmt::format("Actors: {}\nFPS: {}", MAX, fps));
}
