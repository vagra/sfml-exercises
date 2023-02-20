#include "App.h"

App::App() {
    init();
}

void App::init() {

    actor_id = 0;
    action_id = 0;
    direction = 0;
    move = false;

    initWindow();
    initText();

    TextureManager::init();
    ActionManager::init();
    ActorManager::init();

    initActor(0);
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

        updateActor(elapsed);
        updateText(elapsed);

        window.clear(BG_COLOR);
        
        drawActor();
        drawText();
        
        window.display();
    }
}

void App::onResize() {
    sf::Vector2f win = static_cast<sf::Vector2f>(window.getSize());

    sf::View view = window.getDefaultView();
    view.setCenter(win / 2.f);
    view.setSize(win);

    window.setView(view);
}

void App::onKeyboard() {

    changeDirection();

    changeActor();

    changeAction();
}

void App::changeDirection() {
    int prev_direction = direction;
    bool prev_move = move;

    bool l = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    bool r = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
    bool u = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
    bool d = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);

    direction = getDirection(l, u, r, d);
    move = needMove(l, u, r, d);

    if (direction != prev_direction) {
        actor->turn(direction);
    }

    if (move != prev_move) {
        actor->move(move);
    }
}

void App::changeActor() {
    bool z = sf::Keyboard::isKeyPressed(sf::Keyboard::Z);

    if (z) {
        actor_id = (actor_id + 1) % ActorManager::getCount();

        initActor(actor_id);
    }
}

void App::changeAction() {
    bool x = sf::Keyboard::isKeyPressed(sf::Keyboard::X);

    if (x) {
        action_id = (action_id + 1) % ActionManager::getActionCount();

        actor->change(action_id);
    }
}


int App::getDirection(bool l, bool u, bool r, bool d) {

    if (l && r) {
        l = false;
        r = false;
    }

    if (u && d) {
        u = false;
        d = false;
    }

    if (l && u) {
        return 5;
    }

    if (u && r) {
        return 3;
    }

    if (r && d) {
        return 1;
    }

    if (d && l) {
        return 7;
    }

    if (l) {
        return 6;
    }

    if (u) {
        return 4;
    }

    if (r) {
        return 2;
    }

    if (d) {
        return 0;
    }

    return direction;
}

bool App::needMove(bool l, bool u, bool r, bool d) {

    if (l && r) {
        l = false;
        r = false;
    }

    if (u && d) {
        u = false;
        d = false;
    }

    if (l || u || r || d) {
        return true;
    }

    return false;
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
    text.setString(fmt::format("FPS: {}\nactor: {} {}\naction: {} {}\ndirection: {}\nmove: {}",
        fps, 
        actor_id, ActorManager::getActorName(actor_id),
        action_id, ActionManager::getActionName(action_id),
        direction,
        move
    ));
}

void App::initActor(int actor_id) {
    actor = ActorManager::getActor(actor_id);
}

void App::updateActor(sf::Time elapsed) {
    actor->play(elapsed);
}

void App::drawActor() {
    window.draw(*actor->sprite);
}
