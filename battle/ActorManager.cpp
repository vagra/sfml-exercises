#include "ActorManager.h"


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

int ActorManager::getCount() noexcept {
    return narrow_cast<int>(actors.size());
}

int ActorManager::genID() noexcept {
    counter++;
    return counter;
}

Actor* ActorManager::getActor(int index) noexcept {
	assert(index < actors.size());
    return actors.at(index).get();
}

const vector<unique_ptr<Actor>>& ActorManager::getActors() noexcept {
	return actors;
}

void ActorManager::makeActors() {
    cout << "make actors with texture, actions and sprite..." << endl;

    actors.clear();

    int type = 0;

    for (int i = 0; i < MAX; i++) {

        type = rand() % ACTOR_TYPES;

        auto actor = make_unique<Actor>();
		actor->init(type);

        actors.push_back(move(actor));
    }

    cout << fmt::format("{} actors ready.", getCount()) << endl;

    // print();
}

void ActorManager::print() {
    for (auto const& actor : actors) {
        cout << fmt::format("{}  {}  {},{}",
            actor->id, actor->type, actor->position.x, actor->position.y) << endl;
    }
}


void ActorManager::setRegion(int width, int height) noexcept {

	const int x = width > INIT_WIDTH ? int((width - INIT_WIDTH) / 2) : 0;
	const int y = height > INIT_HEIGHT ? int((height - INIT_HEIGHT) / 2) : 0;

	Actor::region.left = x;
	Actor::region.top = y;
}

bool ActorManager::atFront(const Actor* actor1, const Actor* actor2) noexcept {
	const float dx = actor2->m_position.x - actor1->m_position.x;
	const float dy = actor2->m_position.y - actor1->m_position.y;

	switch (actor1->m_direction) {
	case 0:
		return dy > abs(dx);
	case 1:
		return dx > 0 && dy > 0;
	case 2:
		return dx > abs(dy);
	case 3:
		return dx > 0 and dy < 0;
	case 4:
		return -dy > abs(dx);
	case 5:
		return dx < 0 and dy < 0;
	case 6:
		return -dx > abs(dy);
	case 7:
		return dx < 0 and dy > 0;
	default:
		return false;
	}
}


void ActorManager::attack(Actor* actor1, Actor* actor2) {
	actor1->m_status = STATUS::BATTLE;
	actor1->m_battle_timer = 0;

	actor2->m_status = STATUS::BATTLE;
	actor2->m_battle_timer = 0;

	const int hit = genHit();

	actor2->m_hits.push(hit);

	actor1->m_enemy_ids.insert(actor2->id);
	actor2->m_enemy_ids.insert(actor1->id);

	// cout << fmt::format("{}->{}  {}  {}", actor1->id, actor2->id, actor2->hp, actor2->m_hp) << endl;
}

int ActorManager::genHit() noexcept {
	return rand() % (MAX_HIT - MIN_HIT) + MIN_HIT;
}