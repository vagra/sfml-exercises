#include "Hero.h"

Hero::Hero(int type)
	: Actor(type)
{
	initRegion(
		sf::FloatRect(0, 0, INIT_WIDTH, INIT_HEIGHT));
	initPosition(
		genPosition());
	initArea(
		sf::IntRect(0, 0, FRAME_WIDTH, FRAME_HEIGHT));
	initSprite(
		sf::Vector2f(SCALE, SCALE), sf::Vector2f(ORIGIN_X, ORIGIN_Y));

	random();
	
	step();
}

// ---------------------------------------------
// override pure virtual methods
// ---------------------------------------------

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

int Hero::getStartFrame() const {
	return m_action_set->getAction(m_action_id)->start;
}

int Hero::getTotalFrames() const {
	return m_action_set->getAction(m_action_id)->frames;
}

int Hero::getCurrentFrame() const noexcept {
	return m_frame_step;
}

int Hero::getDirection() const {
	return m_direction;
}

sf::Vector2f Hero::getOffset() const {
	const int direction = getDirection();
	return VECTORS.at(direction) * m_speed * SPEED_RATE;
}

// ---------------------------------------------
// override virtual methods
// ---------------------------------------------

void Hero::handleBump(Actor* other) noexcept {
	bump();
}

// ---------------------------------------------
// public methods
// ---------------------------------------------

void Hero::bump() noexcept {
	const int range = rand() % (DIRECTIONS - 3) + 2;
	m_direction = (m_direction + range) % DIRECTIONS;
}

void Hero::back(int direction) noexcept {
	const int range = rand() % (DIRECTIONS - 5) + 7;
	m_direction = (direction + range) % DIRECTIONS;
}

void Hero::stop() {
	m_speed = 0.f;
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

int Hero::getRowFrame() const {
	return m_action_set->getAction(m_action_id)->row * DIRECTIONS;
}

// ---------------------------------------------
// private methods
// ---------------------------------------------

sf::Vector2f Hero::genPosition() {
	const float x = narrow_cast<float>(rand() % INIT_WIDTH);
	const float y = narrow_cast<float>(rand() % INIT_HEIGHT);

	return sf::Vector2f(x, y);
}

int Hero::genDirection() {
	return rand() % DIRECTIONS;
}

int Hero::genStopAction() {
	const int index = rand() % STOPS;

	return at(STOP_ACTIONS, index);
}
