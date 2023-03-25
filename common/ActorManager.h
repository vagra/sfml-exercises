#pragma once
#pragma warning(disable: 26440)

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

	/* public template methods */

	template <typename T>
	void makeActors(int count, int types, bool random) {
		static_assert(derived_from<T, Actor>, "T must be a subclass of Actor");

		cout << "make actors with texture, actions and sprite..." << endl;

		m_actors.clear();

		for (int type = 0, i = 0; i < count; i++) {

			if (random) {
				type = rand() % types;
			}
			else {
				type = i % types;
			}

			auto actor = make_unique<T>(type);

			m_actors.push_back(move(actor));
		}

		fmt::print("{} actors ready.\n", getCount());

		// print();
	}

	/* public methods */
	
	void update(sf::Time elapsed);
	void draw(sf::RenderWindow& window);

	int getCount();
	int genID();
	Actor* getActor(int index);

	/* const member accessers */

	const vector<unique_ptr<Actor>>& actors = m_actors;

private:

	/* private methods */

	void print();

	/* private members */

	int counter = -1;
	vector<unique_ptr<Actor>> m_actors;
};