#include "Actor.h"
#include "ActorManager.h"


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

	m_hp = MAX_HP;

	random();

	initSprite();
	initText();
	initFSM();
	
	step();

}



void Actor::initSprite() {
	m_sprite.reset();

	m_sprite = make_unique<sf::Sprite>();

	m_sprite->setTexture(*mp_texture);
	m_sprite->setScale(SCALE, SCALE);
	m_sprite->setOrigin(ORIGIN_X, ORIGIN_Y);
	m_sprite->setPosition(m_position);
}

void Actor::initText() {
	m_text.reset();

	m_text = make_unique<sf::Text>();

	m_text->setFont(*FontManager::getFont(HP_FONT));
	m_text->setCharacterSize(HP_FONT_SIZE);
	m_text->setFillColor(HP_COLOR);
	m_text->setString(to_string(m_hp));
	m_text->setOrigin(0, ORIGIN_Y);
	m_text->setPosition(m_position);
}

void Actor::initFSM() {
	m_fsm.context().actor_id = m_id;
	m_fsm.context().actor_type = m_type;
}

void Actor::random() noexcept {
	m_direction = genDirection();
}

void Actor::play(sf::Time elapsed) {

	const int ms = elapsed.asMilliseconds();

	m_frame_timer += ms;

	if (m_frame_timer >= FRAME_CYCLE) {
		m_frame_timer = m_frame_timer % FRAME_CYCLE;
		step();

		m_fsm.update();
		if (m_fsm.context().end) {
			m_direction = genDirection();
			m_fsm.randomize<Patrol>();
		}
	}

	if (isMoving()) {
		const sf::Vector2f offset = getOffset();

		m_sprite->move(offset);
		m_text->move(offset);
	}

	m_prev_position = m_position;
	m_position = m_sprite->getPosition();
}

void Actor::step() {
	const int direction = getScreenDirection(m_direction);

	m_frame.x = getStartFrame() + getCurrentFrame();
	m_frame.y = direction;

	m_area.left = m_frame.x * FRAME_WIDTH;
	m_area.top = m_frame.y * FRAME_HEIGHT;

	m_sprite->setTextureRect(m_area);
}

void Actor::turn() noexcept {
	const int range = rand() % (DIRECTIONS - 3) + 2;
	m_direction = (m_direction + range) % DIRECTIONS;
}

void Actor::battle() {
	hit();

	if (m_hp <= 0) {
		m_hp = 0;
		die();
		step();

		return;
	}

	attack();

	step();
}

void Actor::hit() noexcept {

	if (m_hits.empty()) {
		return;
	}

	do {
		m_hp -= m_hits.front();
		m_hits.pop();
	} while (!m_hits.empty());

}

void Actor::attack() noexcept {
	if (m_enemy_ids.empty()) {
		return;
	}
}

void Actor::die() noexcept {
	
}

bool Actor::isMoving() noexcept {
	return m_fsm.context().speed > 0;
}

bool Actor::isBeaten() noexcept {
	return m_fsm.isActive<Attacked>();
}

sf::Vector2f Actor::genPosition() {
	const float x = narrow_cast<float>(rand() % INIT_WIDTH);
	const float y = narrow_cast<float>(rand() % INIT_HEIGHT);

	return sf::Vector2f(x, y);
}

int Actor::genDirection() noexcept {
	const int left = region.left;
	const int top = region.top;
	const int right = region.width + region.left;
	const int bottom = region.height + region.top;

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

int Actor::getStartFrame() {
	return mp_action_set->getAction(m_fsm.context().action)->start;
}

int Actor::getCurrentFrame() {
	return min(m_fsm.context().frames - 1, m_fsm.context().frame);
}

sf::Vector2f Actor::getOffset() {
	return VECTORS.at(m_direction) * (m_fsm.context().speed / 10.f);
}


constexpr int Actor::getScreenDirection(int direction) noexcept {
	return (DIRECTIONS + INIT_DIRECTION - direction) % DIRECTIONS;
}

constexpr int Actor::getTextureDirection(int direction) noexcept {
	return (DIRECTIONS + INIT_DIRECTION - direction) % DIRECTIONS;
}