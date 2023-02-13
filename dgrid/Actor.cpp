#include "Actor.h"

Actor::Actor() {
	init();
}

void Actor::init() {

	m_id = counter;
	counter++;

	m_no = rand() % ACTORS;
	m_name = fmt::format(ACTOR_PNG, m_no);

	m_position = genPosition();
	sprite.setPosition(m_position);

	mp_texture = TextureManager::getTexture(m_name);
	sprite.setTexture(*mp_texture);

	sprite.setOrigin(PNG_WIDTH / 2.f, PNG_HEIGHT / 2.f);
	sprite.setScale(SCALE, SCALE);

	m_area = sf::IntRect(0, 0, PNG_WIDTH, PNG_HEIGHT);

	m_action_timer = 0;

	random();
}

void Actor::random() {
	m_actionCycle = rand() % MAX_ACTION_CYCLE;
	m_speed = (rand() % int(( MAX_SPEED - MIN_SPEED) * 100.0f)) / 100.0f + MIN_SPEED;

	m_direction = genDirection();

	m_vector.x = VECTORS[m_direction].x * m_speed;
	m_vector.y = VECTORS[m_direction].y * m_speed;

	sprite.setRotation(m_direction * -45.f);
	// cout << m_direction << "  " << m_direction * -45.f<< endl;
}

void Actor::play(sf::Time elapsed) {

	m_action_timer += elapsed.asMilliseconds();

	if (m_action_timer >= m_actionCycle) {
		m_action_timer = 0;

		random();
	}

	sprite.move(m_vector);

	m_prev_position = m_position;
	m_position = sprite.getPosition();
}


void Actor::turn() {
	int range = rand() % (DIRECTIONS - 3) + 2;
	m_direction = (m_direction + range) % DIRECTIONS;

	m_vector.x = VECTORS[m_direction].x * m_speed;
	m_vector.y = VECTORS[m_direction].y * m_speed;

	sprite.setRotation(m_direction * -45.f);
}

void Actor::stop() {
	m_vector.x = 0.f;
	m_vector.y = 0.f;
}

sf::Vector2f Actor::genPosition() {
	float x = float(rand() % 1200);
	float y = float(rand() % 800);

	return sf::Vector2f(x, y);
}

int Actor::genDirection() {

	if (m_position.x < 0 && m_position.y < 0) return 1;
	if (m_position.x < 0 && m_position.y > region.y) return 3;
	if (m_position.x > region.x && m_position.y > region.y) return 5;
	if (m_position.x > region.x && m_position.y < 0) return 7;

	if (m_position.y < 0) return 0;
	if (m_position.x < 0) return 2;
	if (m_position.y > region.y) return 4;
	if (m_position.x > region.x) return 6;

	return rand() % DIRECTIONS;
}

bool Actor::zOrder(const Actor& actor1, const Actor& actor2) {
	return (actor1.sprite.getPosition().y < actor2.sprite.getPosition().y);
}

void Actor::setRegion(int width, int height) {
	region = sf::Vector2i(width, height);
}

bool Actor::atFront(const Actor& actor1, const Actor& actor2) {
	float dx = actor2.m_position.x - actor1.m_position.x;
	float dy = actor2.m_position.y - actor1.m_position.y;

	switch (actor1.m_direction) {
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

int Actor::getID() {
	return m_id;
}

float Actor::getX() {
	return m_position.x;
}

float Actor::getY() {
	return m_position.y;
}

float Actor::prevX() {
	return m_prev_position.x;
}

float Actor::prevY() {
	return m_prev_position.y;
}