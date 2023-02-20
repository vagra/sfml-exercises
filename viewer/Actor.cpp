#include "Actor.h"
#include "ActorManager.h"

Actor::Actor() {
	init(0);
}

Actor::Actor(int id) {
	init(id);
}

Actor::Actor(string name) {
	init(name);
}

void Actor::init(int id) {
	m_id = id;
	m_name = ActorManager::getActorName(id);

	init();
}

void Actor::init(string name) {
	m_name = name;
	m_id = ActorManager::getActorID(name);

	init();
}

void Actor::init() {
	mp_action_set = ActionManager::getActionSet(m_name);
	mp_texture = TextureManager::getTexture(m_name);
	m_area = sf::IntRect(0, 0, FRAME_WIDTH, FRAME_HEIGHT);
	m_direction = INIT_DIRECTION;

	sprite = new sf::Sprite();

	sprite->setOrigin(ORIGIN_X, ORIGIN_Y);
	sprite->setPosition(m_position);
	sprite->setTexture(*mp_texture);
	sprite->setScale(SCALE, SCALE);
	sprite->setTextureRect(m_area);

	m_timer = 0;
	m_step = 0;
	m_move = false;
}

void Actor::play(sf::Time elapsed) {

	m_timer += elapsed.asMilliseconds();

	if (m_timer >= DURATION || m_change) {
		m_timer = m_timer % DURATION;
		m_change = false;
		step();
	}

	if (m_move) {
		int direction = getScreenDirection(m_direction);
		sf::Vector2f offset = VECTORS[direction] * SPEED;

		sprite->move(offset);

		m_position = sprite->getPosition();
	}
}

void Actor::turn(int direction) {
	m_direction = getTextureDirection(direction);
}

void Actor::change(int action_id) {
	m_action_id = action_id;
	m_step = 0;
	m_change = true;
}

void Actor::pause() {
}

void Actor::move(bool move) {
	m_move = move;
}

void Actor::step() {
	m_frame.x = getActionStartFrame() + m_step;
	m_frame.y = m_direction;

	cout << fmt::format("{} {}", m_action_id, m_frame.x) << endl;

	m_area.left = m_frame.x * FRAME_WIDTH;
	m_area.top = m_frame.y * FRAME_HEIGHT;

	sprite->setTextureRect(m_area);

	m_step = (m_step + 1) % getActionFrameCount();
}

int Actor::getActionStartFrame() {
	return mp_action_set->getAction(m_action_id)->start;
}

int Actor::getActionFrameCount() {
	return mp_action_set->getAction(m_action_id)->frames;
}

int Actor::getScreenDirection(int direction) {
	return (DIRECTIONS + INIT_DIRECTION - direction) % DIRECTIONS;
}

int Actor::getTextureDirection(int direction) {
	return (DIRECTIONS + INIT_DIRECTION - direction) % DIRECTIONS;
}