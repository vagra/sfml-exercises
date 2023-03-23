#pragma once

#include "headers.h"
#include "Actor.h"

class Actor;

class ActorManager
{

public:

	static ActorManager& instance() {
		static ActorManager instance;
		return instance;
	}

	template <typename T>
	void makeActors(int count, int types) {
		cout << "make actors with texture, actions and sprite..." << endl;

		m_actors.clear();

		int type = 0;

		for (int i = 0; i < count; i++) {

			type = rand() % types;

			auto actor = make_unique<T>(type);

			m_actors.push_back(move(actor));
		}

		fmt::print("{} actors ready.\n", getCount());

		// print();
	}
	
	void update(sf::Time elapsed);
	void draw(sf::RenderWindow& window);

	int genID() noexcept;

	int getCount() noexcept;
	Actor* getActor(int index) noexcept;

	const vector<unique_ptr<Actor>>& actors = m_actors;

private:
	void print();

	int counter = -1;
	vector<unique_ptr<Actor>> m_actors;
};