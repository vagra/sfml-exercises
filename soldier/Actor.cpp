#include "Actor.h"

Actor::Actor() {
	init();
}

void Actor::init() {

	m_no = rand() % ACTORS;
	m_name = fmt::vformat(ACTOR_PNG, fmt::make_format_args(m_no));

	m_position = genPosition();
	sprite.setPosition(m_position);

	mp_texture = TextureManager::getTexture(m_name);
	sprite.setTexture(*mp_texture);

	sprite.setScale(SCALE, SCALE);

	m_area = sf::IntRect(0, 0, FRAME_WIDTH, FRAME_HEIGHT);

	m_anim_timer = 0;
	m_action_timer = 0;

	random();

	step();
}

void Actor::random() {
	m_step = rand() % STEPS;
	m_actionCycle = rand() % MAX_ACTION_CYCLE;
	m_speed = (rand() % int(MAX_SPEED * 100.0f)) / 100.0f;

	m_direction = genDirection();

	if (m_speed > MAX_WALK_SPEED) {
		m_action = 6;	// Run
	}
	else if (m_speed > MAX_STOP_SPEED) {
		m_action = 7;	// Walk
	}
	else {
		m_action = genStopAction();	// Attack, Block, Idle, Jump
	}

	m_vector.x = VECTORS[m_direction].x * m_speed;
	m_vector.y = VECTORS[m_direction].y * m_speed;
}

void Actor::play(sf::Time elapsed) {

	m_anim_timer += elapsed.asMilliseconds();
	m_action_timer += elapsed.asMilliseconds();

	// cout << fmt::format("anim_timer{}, elapsed: {}", m_anim_timer, elapsed.asMilliseconds()) << endl;

	if (m_action_timer >= m_actionCycle) {
		m_action_timer = 0;

		random();
	}

	if (m_anim_timer >= ANIM_CYCLE) {
		m_anim_timer = m_anim_timer % ANIM_CYCLE;

		step();
	}

	sprite.move(m_vector);

	m_position = sprite.getPosition();
}

void Actor::step() {
	// cout << fmt::format("step: {}, action: {}, direction: {}", m_step, m_action, m_direction) << endl;

	changeFrame();

	sprite.setTextureRect(m_area);

	m_step = (m_step + 1) % STEPS;
}

int Actor::genStopAction() {
	int index = rand() % STOPS;

	return STOP_ACTIONS[index];
}

sf::Vector2f Actor::genPosition() {
	float x = float(rand() % 1200);
	float y = float(rand() % 800);

	return sf::Vector2f(x, y);
}

int Actor::genDirection() {
	// cout << fmt::format("position: ({},{})\tregion: ({},{})", m_position.x, m_position.y, region.x, region.y) << endl;

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

void Actor::changeFrame() {

	m_frame.x = ACTION_ORIGINS[m_action].x + m_step;
	m_frame.y = ACTION_ORIGINS[m_action].y + m_direction;

	m_area.left = m_frame.x * FRAME_WIDTH;
	m_area.top = m_frame.y * FRAME_HEIGHT;

	// cout << fmt::format("area: ({}, {}, {}, {})", m_area.left, m_area.top, m_area.width, m_area.height) << endl;
}

bool Actor::zOrder(const Actor& actor1, const Actor& actor2) {
	return (actor1.sprite.getPosition().y < actor2.sprite.getPosition().y);
}

void Actor::setRegion(int width, int height) {
	region = sf::Vector2i(width, height);
}
