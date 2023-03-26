#include "App.h"

void App::init() {

    FontManager::instance().loadFonts();
    TextureManager::instance().loadTextures(PNG_DIR);
    ActionManager::instance().loadActions(PNG_DIR, ROW_ACTIONS);
    ActorManager::instance().makeActors<Hero>(ACTORS, ACTOR_TYPES, true);
    Sorter::instance().init();

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

        ActorManager::instance().update(elapsed);
        Sorter::instance().update();
        updateText(elapsed);

        window.clear(BG_COLOR);
        
        ActorManager::instance().draw(window);
        Sorter::instance().draw(window);
        drawText();
        
        window.display();
    }
}

void App::onResize() {
    const sf::Vector2f win = static_cast<sf::Vector2f>(window.getSize());

    Actor::setRegion(win.x, win.y);

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
    text.setFont(*FontManager::instance().getFont(gui_text.font));
    text.setCharacterSize(gui_text.size);
    text.setFillColor(gui_text.color);
}

void App::drawText() {
    window.draw(text);
}

void App::updateText(sf::Time elapsed) {
    int fps = narrow_cast<int>(1 / elapsed.asSeconds());
    text.setString(fmt::format("Actors: {}\nFPS: {}", ACTORS, fps));
}