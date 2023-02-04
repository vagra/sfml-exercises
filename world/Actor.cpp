#include "Actor.h"

Actor::Actor() {
	init();
}

void Actor::init() {

	m_no = rand() % ACTORS;
	sprite.setTexture(textures[m_no]);

	m_anim_timer = 0;
	m_action_timer = 0;

	m_area = sf::IntRect(0, 0, EDGE, EDGE);
	sprite.setScale(SCALE, SCALE);

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

	sprite.move(m_vector);
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
	sprite.setTextureRect(m_area);
}

int Actor::genDirection() {
	sf::Vector2f pos = static_cast<sf::Vector2f>(sprite.getPosition());

	// cout << fmt::format("pos: ({},{})\tregion: ({},{})", pos.x, pos.y, region.x, region.y) << endl;

	if (pos.x < 0 && pos.y < 0) return 1;
	if (pos.x < 0 && pos.y > region.y) return 3;
	if (pos.x > region.x && pos.y > region.y) return 5;
	if (pos.x > region.x && pos.y < 0) return 7;

	if (pos.y < 0) return 0;
	if (pos.x < 0) return 2;
	if (pos.y > region.y) return 4;
	if (pos.x > region.x) return 6;

	return rand() % DIRECTIONS;
}

bool Actor::zOrder(const Actor& actor1, const Actor& actor2) {
	return (actor1.sprite.getPosition().y < actor2.sprite.getPosition().y);
}

void Actor::setRegion(int width, int height) {
	region = sf::Vector2i(width, height);
}

void Actor::readTextures() {
	textures.clear();

	for (int i = 0; i < ACTORS; i++) {
		string png = fmt::format(ACTOR_PNG, i);

		sf::Texture texture;

		if (!texture.loadFromFile(png)) {
			cout << "can't read texture: " << png << endl;
		}
		else {
			textures.push_back(texture);
		}
	}
}