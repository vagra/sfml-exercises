#include "Actor.h"
#include "ActorManager.h"

Actor::Actor() {
	init(0);
}

Actor::Actor(int type) {
	init(type);
}

Actor::Actor(string name) {
	init(name);
}

void Actor::init(int type) {
	m_type = type;
	m_name = ActionManager::getActionSetName(type);

	init();
}

void Actor::init(string name) {
	m_name = name;
	m_type = ActionManager::getActionSetIndex(name);

	init();
}

void Actor::init() {

	m_id = ActorManager::genID();

	mp_action_set = ActionManager::getActionSet(m_name);
	mp_texture = TextureManager::getTexture(m_name);
	m_area = sf::IntRect(0, 0, FRAME_WIDTH, FRAME_HEIGHT);

	m_position = genPosition();
	m_prev_position = m_position;

	random();

	sprite = new sf::Sprite();

	sprite->setOrigin(ORIGIN_X, ORIGIN_Y);
	sprite->setPosition(m_position);
	sprite->setTexture(*mp_texture);
	sprite->setScale(SCALE, SCALE);
	
	step();
}


void Actor::random() {
	m_frame_timer = 0;
	m_frame_step = 0;
	m_action_timer = 0;

	m_action_cycle = genActionCycle();
	m_speed = genSpeed();
	m_direction = genDirection();
	m_action_id = genAction();
}


void Actor::play(sf::Time elapsed) {

	m_action_timer += elapsed.asMilliseconds();
	m_frame_timer += elapsed.asMilliseconds();

	if (m_action_timer >= m_action_cycle) {
		m_action_timer = 0;
		random();
	}

	if (m_frame_timer >= FRAME_CYCLE || m_change) {
		m_frame_timer = m_frame_timer % FRAME_CYCLE;
		m_change = false;
		step();
	}

	if (m_move) {
		sf::Vector2f offset = VECTORS[m_direction] * m_speed;

		sprite->move(offset);
	}

	m_prev_position = m_position;
	m_position = sprite->getPosition();
}

void Actor::step() {
	int direction = getScreenDirection(m_direction);

	m_frame.x = getActionStartFrame() + m_frame_step;
	m_frame.y = direction;

	m_area.left = m_frame.x * FRAME_WIDTH;
	m_area.top = m_frame.y * FRAME_HEIGHT;

	sprite->setTextureRect(m_area);

	m_frame_step = (m_frame_step + 1) % getActionFrameCount();
}

void Actor::turn() {
	int range = rand() % (DIRECTIONS - 3) + 2;
	m_direction = (m_direction + range) % DIRECTIONS;
}


void Actor::setRegion(int width, int height) {

	int x = width > INIT_WIDTH ? int((width - INIT_WIDTH) / 2) : 0;
	int y = height > INIT_HEIGHT ? int((height - INIT_HEIGHT) / 2) : 0;

	region.left = x;
	region.top = y;
}

bool Actor::atFront(const Actor* actor1, const Actor* actor2) {
	float dx = actor2->m_position.x - actor1->m_position.x;
	float dy = actor2->m_position.y - actor1->m_position.y;

	switch (actor1->m_direction) {
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


int Actor::genActionCycle() {
	return rand() % (MAX_ACTION_CYCLE - MIN_ACTION_CYCLE) + MIN_ACTION_CYCLE;
}

float Actor::genSpeed() {
	float speed = rand() % int(MAX_RUN_SPEED * 100) / 100.0f;

	if (speed < MAX_STOP_SPEED) {
		speed = 0;
		m_move = false;
	} 
	else {
		m_move = true;
	}

	return speed;
}

sf::Vector2f Actor::genPosition() {
	float x = float(rand() % INIT_WIDTH);
	float y = float(rand() % INIT_HEIGHT);

	return sf::Vector2f(x, y);
}

int Actor::genDirection() {
	int left = region.left;
	int top = region.top;
	int right = region.width + region.left;
	int bottom = region.height + region.top;

	if (m_position.x < left && m_position.y < top) return 1;
	if (m_position.x < left && m_position.y > bottom) return 3;
	if (m_position.x > right && m_position.y > bottom) return 5;
	if (m_position.x > right &&	m_position.y < top) return 7;

	if (m_position.y < top) return 0;
	if (m_position.x < left) return 2;
	if (m_position.y > bottom) return 4;
	if (m_position.x > right) return 6;

	return rand() % DIRECTIONS;
}

int Actor::genAction() {

	int action_id = m_action_id;

	if (m_speed > MAX_WALK_SPEED) {
		action_id = RUN_ACTIONS[ rand() % RUN_COUNT ];
	}
	else if (m_speed > MAX_STOP_SPEED) {
		action_id = WALK_ACTIONS[rand() % WALK_COUNT];
	}
	else {
		action_id = STOP_ACTIONS[rand() % STOP_COUNT];
	}

	if (m_action_id == action_id) {
		m_frame_step = 0;
		m_change = true;
	}

	return action_id;
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