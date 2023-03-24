#include "Hero.h"

Hero::Hero(int type)
	: Actor(type)
{
	initRegion(
		sf::IntRect(0, 0, INIT_WIDTH, INIT_HEIGHT));
	initPosition(
		genPosition());
	initArea(
		sf::IntRect(0, 0, FRAME_WIDTH, FRAME_HEIGHT));
	initSprite(
		sf::Vector2f(SCALE, SCALE), sf::Vector2f(ORIGIN_X, ORIGIN_Y));

	random();
	
	step();
}

void Hero::random() {
	m_rounds = rand() % MAX_ROUNDS + 1;

	m_speed = narrow_cast<float>(rand() % MAX_RUN_SPEED);

	m_direction = genDirection();

	if (m_speed > MAX_WALK_SPEED) {
		m_action_id = 6;	// Run
	}
	else if (m_speed > MAX_STOP_SPEED) {
		m_action_id = 7;	// Walk
	}
	else {
		m_action_id = genStopAction();	// Attack, Block, Idle, Jump
	}
}

void Hero::play(sf::Time elapsed) {

	m_frame_timer += elapsed.asMilliseconds();

	if (m_frame_timer >= FRAME_CYCLE) {
		m_frame_timer = m_frame_timer % FRAME_CYCLE;
		m_frame_step++;

		if (m_frame_step >= getTotalFrames()) {
			m_frame_step = 0;
			m_round++;

			if (m_round >= m_rounds) {
				m_round = 0;

				random();
			}
		}

		step();
	}

	if (m_speed > MAX_STOP_SPEED) {
		const sf::Vector2f offset = getOffset();

		sprite->move(offset);
	}

	m_prev_position = m_position;
	m_position = sprite->getPosition();
}

void Hero::step() {
	m_frame.x = getStartFrame() + getCurrentFrame();
	m_frame.y = getRowFrame() + m_direction;

	m_area.left = m_frame.x * FRAME_WIDTH;
	m_area.top = m_frame.y * FRAME_HEIGHT;

	m_sprite->setTextureRect(m_area);
}

void Hero::bump() {
	const int range = rand() % (DIRECTIONS - 3) + 2;
	m_direction = (m_direction + range) % DIRECTIONS;
}

void Hero::back(int direction) {
	const int range = rand() % (DIRECTIONS - 5) + 7;
	m_direction = (direction + range) % DIRECTIONS;
}

void Hero::stop() {
	m_speed = 0.f;
}

int Hero::getStartFrame() const {
	return m_action_set->getAction(m_action_id)->start;
}

int Hero::getTotalFrames() const {
	return m_action_set->getAction(m_action_id)->frames;
}

int Hero::getCurrentFrame() const noexcept {
	return m_frame_step;
}

int Hero::getRowFrame() const {
	return m_action_set->getAction(m_action_id)->row * DIRECTIONS;
}

int Hero::getDirection() const {
	return m_direction;
}

sf::Vector2f Hero::getOffset() const {
	const int direction = getDirection();
	return VECTORS.at(direction) * m_speed * SPEED_RATE;
}

bool Hero::atFront(const Hero* other) const {

	if (other == nullptr) {
		return false;
	}

	const float dx = other->position.x - m_position.x;
	const float dy = other->position.y - m_position.y;

	switch (getDirection()) {
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

sf::Vector2f Hero::genPosition() {
	const float x = narrow_cast<float>(rand() % INIT_WIDTH);
	const float y = narrow_cast<float>(rand() % INIT_HEIGHT);

	return sf::Vector2f(x, y);
}

int Hero::genDirection() {
	return rand() % DIRECTIONS;
}

int Hero::genStopAction() {
	int index = rand() % STOPS;

	return at(STOP_ACTIONS, index);
}