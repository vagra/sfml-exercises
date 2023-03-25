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
		static_assert(std::is_base_of<Actor, T>::value, "T must be a subclass of Actor");

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

	template <typename T>
	T* getActor(int index) {
		static_assert(std::is_base_of<Actor, T>::value, "T must be a subclass of Actor");
		assert(index < m_actors.size());
		return dynamic_cast<T*>(m_actors.at(index).get());
	}

	/* public methods */
	
	void update(sf::Time elapsed);
	void draw(sf::RenderWindow& window);

	int getCount();
	int genID();

	/* const member accessers */

	const vector<unique_ptr<Actor>>& actors = m_actors;

private:

	/* private methods */

	void print();

	/* private members */

	int counter = -1;
	vector<unique_ptr<Actor>> m_actors;
};