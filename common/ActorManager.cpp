#include "ActorManager.h"

void ActorManager::update(sf::Time elapsed) {

    for (auto& actor : m_actors) {
        actor->play(elapsed);
    }
}

void ActorManager::draw(sf::RenderWindow& window) {

    for (auto& actor : m_actors) {
        window.draw(*actor->sprite);
    }
}

int ActorManager::getCount() noexcept {
    return narrow_cast<int>(m_actors.size());
}

int ActorManager::genID() noexcept {
    counter++;
    return counter;
}

void ActorManager::print() {
    for (auto const& actor : m_actors) {
        fmt::print("{}  {}  {},{}\n",
            actor->id, actor->type, actor->position.x, actor->position.y);
    }
}