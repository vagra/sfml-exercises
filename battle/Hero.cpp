#include "Hero.h"

Hero::Hero(int type) 
	: Actor(type)
{

	initRegion(
		sf::IntRect(0, 0, INIT_WIDTH, INIT_HEIGHT));
	initPosition(
		genPosition());
	initArea(
		sf::IntRect(0, 0, FRAME_WIDTH, FRAME_HEIGHT));
	initSprite(
		sf::Vector2f(SCALE, SCALE), sf::Vector2f(ORIGIN_X, ORIGIN_Y));
	initText(
		Text{ HP_FONT, "", HP_FONT_SIZE, HP_COLOR, sf::Vector2f(0, ORIGIN_Y) });

	initFSM();
	
	step();
}

void Hero::play(sf::Time elapsed) {

	if (inDeath()) {
		return;
	}

	const int ms = elapsed.asMilliseconds();

	m_frame_timer += ms;

	if (m_frame_timer >= FRAME_CYCLE) {
		m_frame_timer = m_frame_timer % FRAME_CYCLE;
		step();

		m_fsm.update();

		if (inPatrol()) {
			const int direction = checkRegion();
			if (direction >=0) {
				back(direction);
			}
		}

		if (inStandby()) {
			if (!m_enemy->inAlive()) {
				m_enemy = nullptr;
				m_fsm.changeTo<Patrol>();
			}
			else if (canAttack(m_enemy)) {
				attack(m_enemy);
			}
		}
	}
	
	if (inMoving()) {
		const sf::Vector2f offset = getOffset();

		m_sprite->move(offset);
		m_text->move(offset);
	}
	else if (inKnockback()) {
		const sf::Vector2f offset = 
			narrow_cast<float>(m_fsm.context().knockback) * getKnockbackOffset(m_enemy);

		m_sprite->move(offset);
		m_text->move(offset);

		m_fsm.context().knockback = 0;
	}
	
	m_prev_position = m_position;
	m_position = m_sprite->getPosition();
}

void Hero::step() {
	const int direction = getScreenDirection(getDirection());

	m_frame.x = getStartFrame() + getCurrentFrame();
	m_frame.y = direction;

	m_area.left = m_frame.x * FRAME_WIDTH;
	m_area.top = m_frame.y * FRAME_HEIGHT;

	m_sprite->setTextureRect(m_area);
	m_text->setString(to_string(m_fsm.context().hp));
}

void Hero::bump() {
	m_fsm.react(BumpTurnSignl());
}

void Hero::back(int direction) {
	m_fsm.react(BackTurnSignl{direction});
}

void Hero::attack(Hero* enemy) {
	if (enemy == nullptr) {
		return;
	}

	if (!canAttack(enemy)) {
		return;
	}
	
	m_enemy = enemy;

	const pair<int, int> knockback = getKnockback(enemy);
	const pair<int, int> opposite = getOpposite(enemy);

	const AttackSignl att_signl = AttackSignl{
		knockback.first, opposite.first };

	const DefendSignl def_signl = DefendSignl{
		genHit(), getStiffs(), knockback.second, opposite.second };

	m_fsm.react(att_signl);

	enemy->attackedBy(this, def_signl);
}

void Hero::attackedBy(Hero* enemy, DefendSignl signl) {

	if (enemy == nullptr) {
		return;
	}

	m_enemy = enemy;

	m_fsm.react(signl);
}

void Hero::disable() {
	m_enemy = nullptr;
	m_disabled = true;
}

int Hero::getStartFrame() const {
	return m_action_set->getAction(m_fsm.context().action)->start;
}

int Hero::getTotalFrames() const {
	return m_action_set->getAction(m_fsm.context().action)->frames;
}

int Hero::getCurrentFrame() const {
	return min(m_fsm.context().frames - 1, m_fsm.context().frame);
}

int Hero::getDirection() const {
	return m_fsm.context().direction;
}

sf::Vector2f Hero::getOffset() const {
	return VECTORS.at(getDirection()) * (m_fsm.context().speed / 10.f);
}

int Hero::getStiffs() const {
	return ActionManager::instance().getAction(m_type, ACTION::ATTACK)->frames;
}

bool Hero::inMoving() const {
	return m_fsm.context().speed > 0;
}

bool Hero::inKnockback() const {
	return m_fsm.context().knockback != 0;
}

bool Hero::inAttacked() const {
	return m_fsm.isActive<Attacked>();
}

bool Hero::inFail() const {
	return m_fsm.isActive<Fail>();
}

bool Hero::inInjured() const {
	return m_fsm.isActive<Injure>();
}

bool Hero::inAlive() const {
	return !m_fsm.isActive<Death>() && !m_fsm.isActive<Fail>();
}

bool Hero::inDeath() const {
	return m_fsm.isActive<Death>();
}

bool Hero::inPatrol() const {
	return m_fsm.isActive<Patrol>();
}

bool Hero::inBattle() const {
	return m_fsm.isActive<Battle>();
}

bool Hero::inStandby() const {
	return m_fsm.isActive<Standby>();
}

bool Hero::atFront(const Hero* other) const {

	if (other == nullptr) {
		return false;
	}

	const float dx = other->position.x - m_position.x;
	const float dy = other->position.y - m_position.y;

	switch (getDirection()) {
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

bool Hero::canAttack(Hero* enemy) const {

	if (enemy == nullptr) {
		return false;
	}

	return (canAttack() && enemy->canBeAttacked());
}

bool Hero::canAttack() const {
	return (m_fsm.isActive<Patrol>() ||
		m_fsm.isActive<Standby>());
}

bool Hero::canBeAttacked() const {
	return (m_fsm.isActive<Patrol>() ||
		m_fsm.isActive<Standby>() ||
		m_fsm.isActive<Stiff>());
}

void Hero::initFSM() {
	m_fsm.context().actor_id = m_id;
	m_fsm.context().actor_type = m_type;
	m_fsm.context().hp = MAX_HP;
}

sf::Vector2f Hero::genPosition() {
	const float x = narrow_cast<float>(rand() % INIT_WIDTH);
	const float y = narrow_cast<float>(rand() % INIT_HEIGHT);

	return sf::Vector2f(x, y);
}

int Hero::genHit() noexcept {
	return rand() % (MAX_HIT - MIN_HIT) + MIN_HIT;
}

sf::Vector2f Hero::getKnockbackOffset(const Hero* enemy) {
	if (enemy == nullptr) {
		return sf::Vector2f(0.0f, 0.0f);
	}

	const sf::Vector2f unit = VECTORS.at(getDirection());
	const sf::Vector2f offset = sf::Vector2f(unit.x * KNOCKBACK, unit.y * KNOCKBACK);
	// fmt::print("{},{}\n", offset.x, offset.y);

	return offset;
}

pair<int, int> Hero::getKnockback(const Hero* enemy) {
	if (enemy == nullptr) {
		return make_pair(0, 0);
	}

	const float abx = abs(m_position.x - enemy->position.x);
	const float aby = abs(m_position.y - enemy->position.y);

	if (abx < NEAR && aby < NEAR) {
		return make_pair(0, -1);
	}

	if (abx > FAR || aby > FAR) {
		return make_pair(1, 0);
	}

	return make_pair(1, -1);
}

pair<int, int> Hero::getOpposite(const Hero* enemy) {

	const int direction = getDirection();

	if (enemy == nullptr) {
		return make_pair(direction, 0);
	}

	if (m_position.x < enemy->position.x &&
		m_position.y < enemy->position.y) {
		return make_pair(1, 5);
	}
	if (m_position.x < enemy->position.x &&
		m_position.y > enemy->position.y) {
		return make_pair(3, 7);
	}
	if (m_position.x > enemy->position.x &&
		m_position.y > enemy->position.y) {
		return make_pair(5, 1);
	}
	if (m_position.x > enemy->position.x &&
		m_position.y < enemy->position.y) {
		return make_pair(7, 3);
	}

	if (m_position.y < enemy->position.y) {
		return make_pair(0, 4);
	}
	if (m_position.x < enemy->position.x) {
		return make_pair(2, 6);
	}
	if (m_position.y > enemy->position.y) {
		return make_pair(4, 0);
	}
	if (m_position.x > enemy->position.x) {
		return make_pair(6, 2);
	}

	return make_pair(direction, enemy->getDirection());
}

constexpr int Hero::getScreenDirection(int direction) noexcept {
	return (DIRECTIONS + INIT_DIRECTION - direction) % DIRECTIONS;
}

constexpr int Hero::getTextureDirection(int direction) noexcept {
	return (DIRECTIONS + INIT_DIRECTION - direction) % DIRECTIONS;
}