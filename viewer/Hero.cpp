#include "Hero.h"

Hero::Hero(int type)
	: Actor(type)
{

	initRegion(
		sf::FloatRect(0, 0, INIT_WIDTH, INIT_HEIGHT));
	initPosition(
		g_position);
	initArea(
		sf::IntRect(0, 0, FRAME_WIDTH, FRAME_HEIGHT));
	initSprite(
		sf::Vector2f(SCALE, SCALE), sf::Vector2f(ORIGIN_X, ORIGIN_Y));

	m_frame_timer = 0;
	g_frame_step = 0;
	g_direction = INIT_DIRECTION;
	g_moving = false;
	g_change_action = true;
}

void Hero::play(sf::Time elapsed) {

	m_frame_timer += elapsed.asMilliseconds();

	if (m_frame_timer >= FRAME_CYCLE || g_change_action) {
		m_frame_timer = m_frame_timer % FRAME_CYCLE;
		g_change_action = false;
		step();
	}

	if (g_moving) {
		const sf::Vector2f offset = getOffset();

		m_sprite->move(offset);

		g_position = m_sprite->getPosition();
	}
}

void Hero::step() {
	m_frame.x = getStartFrame() + g_frame_step;
	m_frame.y = g_direction;

	m_area.left = m_frame.x * FRAME_WIDTH;
	m_area.top = m_frame.y * FRAME_HEIGHT;

	m_sprite->setTextureRect(m_area);

	g_frame_step = (g_frame_step + 1) % getTotalFrames();
}

void Hero::move(bool move) noexcept {
	g_moving = move;
}

void Hero::turn(int direction) {
	g_direction = direction;
}

void Hero::changeActor() {
	m_sprite->setPosition(g_position);
}

void Hero::changeAction(int action_id) noexcept {
	g_action_id = action_id;
	g_frame_step = 0;
	g_change_action = true;
}

int Hero::getStartFrame() const {
	return m_action_set->getAction(g_action_id)->start;
}

int Hero::getTotalFrames() const {
	return m_action_set->getAction(g_action_id)->frames;
}

int Hero::getCurrentFrame() const noexcept {
	return g_frame_step;
}

int Hero::getDirection() const {
	return g_direction;
}

sf::Vector2f Hero::getOffset() const {
	const int direction = getDirection();
	return VECTORS.at(direction) * SPEED;
}