#include "ActorManager.h"

ActorManager::ActorManager()
{
}

void ActorManager::init() {

    cout << "init actor manager:" << endl;

    makeActors();

    cout << "init actor manager done." << endl << endl;
}

void ActorManager::update(sf::Time elapsed) {

    for (auto& actor : actors) {
        actor->play(elapsed);
    }
}

void ActorManager::draw(sf::RenderWindow& window) {

    for (auto& actor : actors) {
        window.draw(*actor->sprite);
    }
}

int ActorManager::getCount() {
    return (int)actors.size();
}

int ActorManager::genID() {
    counter++;
    return counter;
}

Actor* ActorManager::getActor(int index)
{
    return actors[index];
}

void ActorManager::makeActors() {
    cout << "make actors with texture, actions and sprite...";

    actors.clear();

    for (int i = 0; i < MAX; i++) {

        int type = rand() % ACTOR_TYPES;

        Actor* actor = new Actor(type);

        actors.push_back(actor);
    }

    cout << fmt::format("\t{} actors ready.", getCount()) << endl;

    print();
}

void ActorManager::print() {
    for (auto const& actor : actors) {
        cout << fmt::format("{}  {}",
            actor->id, actor->type) << endl;
    }
}


ActorManager::~ActorManager()
{
    for (auto const& actor : actors) {
        delete actor;
    }
}