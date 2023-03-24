#include "App.h"

void App::init()
{
    actor_id = 0;
    action_id = 0;
    direction = 0;
    move = false;

    FontManager::instance().loadFonts();
    TextureManager::instance().loadTextures(PNG_DIR);
    ActionManager::instance().loadActions(PNG_DIR, ROW_ACTIONS);
    ActorManager::instance().makeActors<Hero>(ACTORS, ACTOR_TYPES, false);

    initWindow();
    initText();

    changeActor(0);
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
    const sf::Vector2f win = static_cast<sf::Vector2f>(window.getSize());

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
    const int prev_direction = direction;
    const bool prev_move = move;

    const bool l = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    const bool r = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
    const bool u = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
    const bool d = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);

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
    const bool z = sf::Keyboard::isKeyPressed(sf::Keyboard::Z);

    if (z) {
        actor_id = (actor_id + 1) % ActorManager::instance().getCount();

        changeActor(actor_id);
    }
}

void App::changeAction() {
    const bool x = sf::Keyboard::isKeyPressed(sf::Keyboard::X);

    if (x) {
        action_id = (action_id + 1) % ActionManager::instance().getActionCount();

        actor->changeAction(action_id);
    }
}


int App::getDirection(bool l, bool u, bool r, bool d) noexcept {

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

bool App::needMove(bool l, bool u, bool r, bool d) noexcept {

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
    text.setFont(*FontManager::instance().getFont(GUI_FONT));
    text.setCharacterSize(GUI_FONT_SIZE);
    text.setFillColor(GUI_COLOR);
}

void App::drawText() {
    window.draw(text);
}

void App::updateText(sf::Time elapsed) {
    int fps = narrow_cast<int>(1 / elapsed.asSeconds());
    text.setString(fmt::format("FPS: {}\nactor: {}\naction: {} {}\ndirection: {}\nmove: {}",
        fps, 
        actor_id,
        action_id, ActionManager::instance().getActionName(action_id),
        direction,
        move
    ));
}

void App::changeActor(int actor_id) {
    actor = ActorManager::instance().getActor<Hero>(actor_id);
    actor->changeActor();
}

void App::updateActor(sf::Time elapsed) {
    actor->play(elapsed);
}

void App::drawActor() {
    window.draw(*actor->sprite);
}
