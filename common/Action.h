#pragma once

#include "headers.h"

constexpr int DIRECTIONS = 8;
constexpr float SQR = 0.7071f;

const array<sf::Vector2f, DIRECTIONS> VECTORS = {
	sf::Vector2f(0.0,   1.0),
	sf::Vector2f(SQR,   SQR),
	sf::Vector2f(1.0,   0.0),
	sf::Vector2f(SQR,  -SQR),
	sf::Vector2f(0.0,  -1.0),
	sf::Vector2f(-SQR, -SQR),
	sf::Vector2f(-1.0,  0.0),
	sf::Vector2f(-SQR,  SQR)
};

struct Action
{
	string name;
	int frames{};
	int start{};
	int row{};
};

struct ActionSet
{
	string name;
	unordered_map<string, unique_ptr<Action>> actions;
	vector<string> names;

	Action* getAction(string name) {
		if (actions.find(name) != actions.end()) {
			return actions[name].get();
		}

		throw runtime_error(
			fmt::format("no action named '{}'.", name)
		);
	}

	Action* getAction(int index) {
		assert(index < names.size());
		return getAction(names.at(index));
	}
};