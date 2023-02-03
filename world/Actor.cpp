#include "Actor.h"

Actor::Actor() {
	init();
}

void Actor::init() {

	m_no = rand() % ACTORS;
	setTexture(textures[m_no]);

	m_anim_timer = 0;
	m_action_timer = 0;

	m_area = sf::IntRect(0, 0, EDGE, EDGE);
	setScale(SCALE, SCALE);

	random();
	step();
}

void Actor::random() {
	m_step = rand() % STEPS;
	m_actionCycle = rand() % MAX_ACTION_CYCLE;
	m_speed = (rand() % int(MAX_SPEED * 100.0f)) / 100.0f;

	m_direction = genDirection();

	if (m_speed > MAX_WALK_SPEED) {
		m_action = 1;	// Run
	}
	else if (m_speed > MAX_RAISE_SPEED) {
		m_action = 0;	// Walk
	}
	else {
		m_action = 2;
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

	move(m_vector);
}

void Actor::step() {
	// cout << fmt::format("step: {}, action: {}, direction: {}", m_step, m_action, m_direction) << endl;
	changeFrame();
	m_step = (m_step + 1) % STEPS;
}

void Actor::changeFrame() {

	m_frame.x = ANIM_STARTS[m_direction].x + ACTION_ORIGINS[m_action].x + ANIM_STEPS[m_step];
	m_frame.y = ANIM_STARTS[m_direction].y + ACTION_ORIGINS[m_action].y;

	m_area.left = m_frame.x * EDGE;
	m_area.top = m_frame.y * EDGE;

	// cout << fmt::format("area: ({}, {}, {}, {})", m_area.left, m_area.top, m_area.width, m_area.height) << endl;
	setTextureRect(m_area);
}

int Actor::genDirection() {
	sf::Vector2f pos = static_cast<sf::Vector2f>(getPosition());
	sf::Vector2f win = sf::Vector2f(float(App::width), float(App::height));

	// cout << fmt::format("pos: ({},{})\twin: ({},{})", pos.x, pos.y, win.x, win.y) << endl;

	if (pos.x < 0 && pos.y < 0) return 1;
	if (pos.x < 0 && pos.y > win.y) return 3;
	if (pos.x > win.x && pos.y > win.y) return 5;
	if (pos.x > win.x && pos.y < 0) return 7;

	if (pos.y < 0) return 0;
	if (pos.x < 0) return 2;
	if (pos.y > win.y) return 4;
	if (pos.x > win.x) return 6;

	return rand() % DIRECTIONS;
}

bool Actor::zOrder(const Actor& actor1, const Actor& actor2) {
	return (actor1.getPosition().y < actor2.getPosition().y);
}

void Actor::readTextures() {

	for (int i = 0; i < ACTORS; i++) {
		
		string png = fmt::format(ACTOR_PNG, i);

		if (!textures[i].loadFromFile(png))
		{
			cout << "can't read texture: " << png << endl;
		}
	}
}