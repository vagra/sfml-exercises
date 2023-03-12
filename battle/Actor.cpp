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

	m_direction = genDirection();

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

void Actor::play(sf::Time elapsed) {

	const int ms = elapsed.asMilliseconds();

	m_frame_timer += ms;

	if (m_frame_timer >= FRAME_CYCLE) {
		m_frame_timer = m_frame_timer % FRAME_CYCLE;
		step();

		if (!isAlive()) {
			return;
		}

		m_fsm.update();

		if (inBattle()) {
			if (!m_enemy->isAlive()) {
				m_enemy = nullptr;
				m_direction = genDirection();
				m_fsm.changeTo<Patrol>();
			} else if (canAttack(m_enemy)) {
				attack(m_enemy);
				return;
			}
		} else if (inPatrol()) {
			if (m_fsm.context().end) {
				m_direction = genDirection();
				m_fsm.changeTo<Patrol>();
			}
		}
	}

	if (inMoving()) {
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

void Actor::attack(not_null<Actor*> enemy) {
	if (!canAttack(enemy)) {
		return;
	}
	
	m_enemy = enemy;
	m_direction = getOpposite(enemy);

	const Combat combat = genCombat();

	m_fsm.changeTo<Attack>();

	enemy->attackedBy(this, combat);
}

void Actor::die() {
	m_enemy = nullptr;

	m_fsm.changeTo<Death>();
}

void Actor::attackedBy(not_null<Actor*> enemy, const Combat combat) {
	m_enemy = enemy;
	m_direction = getOpposite(enemy);

	m_hp = max(0, m_hp - combat.hits);
	m_text->setString(to_string(m_hp));

	if (m_hp <= 0) {
		die();
		return;
	}

	m_fsm.react(combat);
}

bool Actor::inMoving() noexcept {
	return m_fsm.context().speed > 0;
}

bool Actor::inAttacked() noexcept {
	return m_fsm.isActive<Attacked>();
}

bool Actor::isAlive() noexcept {
	return !m_fsm.isActive<Death>();
}

bool Actor::inPatrol() {
	return m_fsm.isActive<Patrol>();
}

bool Actor::inBattle() {
	return m_fsm.isActive<Battle>();
}

bool Actor::canAttack(not_null<Actor*> enemy) {
	if (abs(position.x - enemy->position.x) > FRAME_WIDTH &&
		abs(position.x - enemy->position.y) > FRAME_WIDTH) {
		return false;
	}

	return (canAttack() && enemy->canBeAttacked());
}

bool Actor::canAttack() {
	return (m_fsm.isActive<Patrol>() ||
		m_fsm.isActive<Standby>() );
}

bool Actor::canBeAttacked() {
	return (m_fsm.isActive<Patrol>() ||
		m_fsm.isActive<Standby>() ||
		m_fsm.isActive<Stiff>());
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

int Actor::genHit() noexcept {
	return rand() % (MAX_HIT - MIN_HIT) + MIN_HIT;
}

Combat Actor::genCombat() {
	return Combat{genHit(), getStiffs()};
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

int Actor::getStiffs() {
	return ActionManager::getAction(m_type, ACTION::ATTACK)->frames;
}

int Actor::getOpposite(not_null<Actor*> enemy) noexcept {

	if (m_position.x < enemy->position.x &&
		m_position.y < enemy->position.y) return 1;
	if (m_position.x < enemy->position.x &&
		m_position.y > enemy->position.y) return 3;
	if (m_position.x > enemy->position.x &&
		m_position.y > enemy->position.y) return 5;
	if (m_position.x > enemy->position.x &&
		m_position.y < enemy->position.y) return 7;

	if (m_position.y < enemy->position.y) return 0;
	if (m_position.x < enemy->position.x) return 2;
	if (m_position.y > enemy->position.y) return 4;
	if (m_position.x > enemy->position.x) return 6;
	
	return m_direction;
}

constexpr int Actor::getScreenDirection(int direction) noexcept {
	return (DIRECTIONS + INIT_DIRECTION - direction) % DIRECTIONS;
}

constexpr int Actor::getTextureDirection(int direction) noexcept {
	return (DIRECTIONS + INIT_DIRECTION - direction) % DIRECTIONS;
}