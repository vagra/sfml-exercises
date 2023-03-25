#include "Tank.h"

Tank::Tank(int type)
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

void Tank::play(sf::Time elapsed) {

	m_frame_timer += elapsed.asMilliseconds();

	if (m_frame_timer >= FRAME_CYCLE) {
		m_frame_timer = m_frame_timer % FRAME_CYCLE;
		m_round++;

		if (m_speed > MIN_SPEED) {
			const int direction = checkRegion();
			if (direction >= 0) {
				back(direction);
			}
		}

		if (m_round >= m_rounds) {
			m_round = 0;

			random();
		}

		step();
	}

	if (m_speed > MIN_SPEED) {
		const sf::Vector2f offset = getOffset();

		sprite->move(offset);
	}

	m_prev_position = m_position;
	m_position = sprite->getPosition();
}

void Tank::step() {
    m_sprite->setRotation(m_direction * -45.f);
}

int Tank::getStartFrame() const {
	return 0;
}

int Tank::getTotalFrames() const {
	return 1;
}

int Tank::getCurrentFrame() const noexcept {
	return 0;
}

int Tank::getDirection() const {
	return m_direction;
}

sf::Vector2f Tank::getOffset() const {
	const int direction = getDirection();
	return VECTORS.at(direction) * m_speed * SPEED_RATE;
}

// ---------------------------------------------
// override virtual methods
// ---------------------------------------------

void Tank::handleBump(Actor* other) noexcept {
	bump();
}

// ---------------------------------------------
// public methods
// ---------------------------------------------

void Tank::bump() noexcept {
	const int range = rand() % (DIRECTIONS - 3) + 2;
	m_direction = (m_direction + range) % DIRECTIONS;
}

void Tank::back(int direction) noexcept {
	const int range = rand() % (DIRECTIONS - 5) + 7;
	m_direction = (direction + range) % DIRECTIONS;
}

void Tank::stop() {
	m_speed = 0.f;
}

void Tank::random() {
	m_rounds = rand() % MAX_ROUNDS + 1;

	m_speed = narrow_cast<float>(rand() % MAX_SPEED);

	if (m_speed <= MIN_SPEED) {
		m_speed = 0;
	}

	m_direction = genDirection();
}

// ---------------------------------------------
// private methods
// ---------------------------------------------

sf::Vector2f Tank::genPosition() {
	const float x = narrow_cast<float>(rand() % INIT_WIDTH);
	const float y = narrow_cast<float>(rand() % INIT_HEIGHT);

	return sf::Vector2f(x, y);
}

int Tank::genDirection() {
	return rand() % DIRECTIONS;
}