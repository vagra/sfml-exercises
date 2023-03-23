#include "App.h"

void App::init() {

    FontManager::init();
    TextureManager::init(PNG_DIR);
    ActionManager::init(PNG_DIR);
    ActorManager::init();
    GridManager::init(true);

    initWindow();
    initText();
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
    const sf::Vector2f win = static_cast<sf::Vector2f>(window.getSize());

    ActorManager::setRegion(narrow_cast<int>(win.x), narrow_cast<int>(win.y));

    sf::View view = window.getDefaultView();
    view.setCenter(win / 2.f);
    view.setSize(win);

    window.setView(view);
}

void App::onKeyboard() noexcept {

    
}

void App::initWindow() {
    window.create(sf::VideoMode(INIT_WIDTH, INIT_HEIGHT), APP_NAME);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
}

void App::initText() {
    text.setFont(*FontManager::getFont(GUI_FONT));
    text.setCharacterSize(GUI_FONT_SIZE);
    text.setFillColor(GUI_COLOR);
}

void App::drawText() {
    window.draw(text);
}

void App::updateText(sf::Time elapsed) {
    int fps = narrow_cast<int>(1 / elapsed.asSeconds());
    text.setString(fmt::format("Actors: {}\nFPS: {}", MAX, fps));
}
