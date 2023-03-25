#include "ActorManager.h"

// ---------------------------------------------
// public methods
// ---------------------------------------------

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

int ActorManager::getCount() {
    return narrow_cast<int>(m_actors.size());
}

int ActorManager::genID() {
    counter++;
    return counter;
}

Actor* ActorManager::getActor(int index) {
    assert(index < m_actors.size());
    return m_actors.at(index).get();
}

// ---------------------------------------------
// private methods
// ---------------------------------------------

void ActorManager::print() {
    for (auto const& actor : m_actors) {
        fmt::print("{}  {}  {}  {}  {},{}\n",
            actor->id, actor->type, 
            actor->getTypeName(), actor->name,
            actor->position.x, actor->position.y);
    }
}