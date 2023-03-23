#include "Hero.h"

Hero::Hero(int type) : Actor(type) {

	initRegion(
		sf::IntRect(0, 0, INIT_WIDTH, INIT_HEIGHT));
	initPosition(
		sf::Vector2f(INIT_WIDTH / 2, INIT_HEIGHT / 2));
	initArea(
		sf::IntRect(0, 0, FRAME_WIDTH, FRAME_HEIGHT));
	initSprite(
		sf::Vector2f(SCALE, SCALE), sf::Vector2f(ORIGIN_X, ORIGIN_Y));

	m_frame_timer = 0;
	m_frame_step = 0;
	m_direction = INIT_DIRECTION;
	m_move = false;
	m_change = false;
}

void Hero::play(sf::Time elapsed) {

	m_frame_timer += elapsed.asMilliseconds();

	if (m_frame_timer >= DURATION || m_change) {
		m_frame_timer = m_frame_timer % DURATION;
		m_change = false;
		step();
	}

	if (inMoving()) {
		const sf::Vector2f offset = getOffset();

		m_sprite->move(offset);

		m_position = m_sprite->getPosition();
	}
}

void Hero::step() {
	m_frame.x = getStartFrame() + m_frame_step;
	m_frame.y = m_direction;

	m_area.left = m_frame.x * FRAME_WIDTH;
	m_area.top = m_frame.y * FRAME_HEIGHT;

	m_sprite->setTextureRect(m_area);

	m_frame_step = (m_frame_step + 1) % getTotalFrames();
}

void Hero::turn(int direction) {
	m_direction = getTextureDirection(direction);
}

void Hero::change(int action_id) {
	m_action_id = action_id;
	m_frame_step = 0;
	m_change = true;
}

void Hero::move(bool move) {
	m_move = move;
}

bool Hero::inMoving() {
	return m_move;
}

int Hero::getStartFrame() {
	return m_action_set->getAction(m_action_id)->start;
}

int Hero::getTotalFrames() {
	return m_action_set->getAction(m_action_id)->frames;
}

int Hero::getDirection() {
	return getScreenDirection(m_direction);
}

sf::Vector2f Hero::getOffset() {
	const int direction = getDirection();
	return VECTORS.at(direction) * SPEED;
}

constexpr int Hero::getScreenDirection(int direction) {
	return (DIRECTIONS + INIT_DIRECTION - direction) % DIRECTIONS;
}

constexpr int Hero::getTextureDirection(int direction) {
	return (DIRECTIONS + INIT_DIRECTION - direction) % DIRECTIONS;
}