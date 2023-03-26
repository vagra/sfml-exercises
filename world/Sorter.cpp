#include "Sorter.h"

void Sorter::init() {

	Hero* hero = nullptr;

	int row = 0;
	for (auto& actor : ActorManager::instance().actors)
	{
		hero = dynamic_cast<Hero*>(actor.get());

		row = getRow(hero);

		moveTo(hero, row);
	}

	// print();
}

void Sorter::update() {

	Hero* hero = nullptr;

	for (auto& actor : ActorManager::instance().actors)
	{
		hero = dynamic_cast<Hero*>(actor.get());

		move(hero);
	}
}

void Sorter::draw(sf::RenderWindow& window) {

	Hero* hero = nullptr;

	for (auto& head : rows)
	{
		hero = head;

		while (hero != nullptr) {
			window.draw(*hero->sprite);

			hero = hero->next;
		}
	}
	
}

void Sorter::move(Hero* hero) {

	const int prev_row = getPrevRow(hero);
	const int row = getRow(hero);

	if (row == prev_row) {
		return;
	}

	removeFrom(hero, prev_row);
	moveTo(hero, row);
}

void Sorter::removeFrom(Hero* hero, int row) {

	Hero* prev = nullptr;
	Hero* next = nullptr;

	if (hero->prev != nullptr) {
		prev = hero->prev;
	}

	if (hero->next != nullptr) {
		next = hero->next;
		next->prev = prev;
	}

	if (prev != nullptr) {
		prev->next = next;
	}
	else {
		rows.at(row) = next;
	}
}

void Sorter::moveTo(Hero* hero, int row) {

	Hero* head = nullptr;

	hero->prev = nullptr;

	if (rows.at(row) != nullptr) {
		head = rows.at(row);
		head->prev = hero;
	}
	
	hero->next = head;

	rows.at(row) = hero;
}

int Sorter::getRow(const Hero* hero) {
	const int row = narrow_cast<int>(hero->position.y / ROW_HEIGHT);

	return min(ROWS - 1, row);
}

int Sorter::getPrevRow(const Hero* hero) {
	const int row = narrow_cast<int>(hero->prev_position.y / ROW_HEIGHT);

	return min(ROWS - 1, row);
}

void Sorter::print() {

	Hero* hero = nullptr;

	int r = 0;
	for (auto& head : rows)
	{
		if (head == nullptr) {
			continue;
		}

		fmt::print("{}:", r);

		hero = head;
		while (hero != nullptr) {
			

			fmt::print(" ({},{})", hero->position.x, hero->position.y);

			hero = hero->next;
		}

		fmt::print("\n");

		r++;
	}
}
