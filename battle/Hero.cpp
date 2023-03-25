#include "Hero.h"

Hero::Hero(int type) 
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
	initText(hp_text);

	initFSM();
	
	step();
}

// ---------------------------------------------
// override pure virtual methods
// ---------------------------------------------

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
		const sf::Vector2f offset = getKnockbackOffset(m_enemy);

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

// ---------------------------------------------
// override virtual methods
// ---------------------------------------------

bool Hero::needRemove() const noexcept {
	return inDeath();
}

bool Hero::textOn() const noexcept {
	return inAttacked();
}

bool Hero::skipBump() const noexcept {
	return inBattle();
}

void Hero::remove() noexcept {
	m_enemy = nullptr;
	m_removed = true;
}

void Hero::handleBump(Actor* other) {
	Hero* hero = dynamic_cast<Hero*>(other);

	if (canAttack(hero)) {
		attack(hero);
	}
	else {
		bump();
	}
}

// ---------------------------------------------
// public methods
// ---------------------------------------------

void Hero::bump() noexcept {
	m_fsm.react(BumpTurnSignl());
}

void Hero::back(int direction) noexcept {
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

void Hero::attackedBy(Hero* enemy, DefendSignl signl) noexcept {

	if (enemy == nullptr) {
		return;
	}

	m_enemy = enemy;

	m_fsm.react(signl);
}

int Hero::getStiffs() const {
	return ActionManager::instance().getAction(m_type, ACTION::ATTACK)->frames;
}

bool Hero::inMoving() const noexcept {
	return m_fsm.context().speed > 0;
}

bool Hero::inKnockback() const noexcept {
	return m_fsm.context().knockback != 0;
}

bool Hero::inAttacked() const noexcept {
	return m_fsm.isActive<Attacked>();
}

bool Hero::inFail() const noexcept {
	return m_fsm.isActive<Fail>();
}

bool Hero::inInjured() const noexcept {
	return m_fsm.isActive<Injure>();
}

bool Hero::inAlive() const noexcept {
	return !m_fsm.isActive<Death>() && !m_fsm.isActive<Fail>();
}

bool Hero::inDeath() const noexcept {
	return m_fsm.isActive<Death>();
}

bool Hero::inPatrol() const noexcept {
	return m_fsm.isActive<Patrol>();
}

bool Hero::inBattle() const noexcept {
	return m_fsm.isActive<Battle>();
}

bool Hero::inStandby() const noexcept {
	return m_fsm.isActive<Standby>();
}

bool Hero::canAttack(Hero* enemy) const noexcept {

	if (enemy == nullptr) {
		return false;
	}

	if (enemy->type == m_type) {
		return false;
	}

	return (canAttack() && enemy->canBeAttacked());
}

bool Hero::canAttack() const noexcept {
	return (m_fsm.isActive<Patrol>() ||
		m_fsm.isActive<Standby>());
}

bool Hero::canBeAttacked() const noexcept {
	return (m_fsm.isActive<Patrol>() ||
		m_fsm.isActive<Standby>() ||
		m_fsm.isActive<Stiff>());
}

sf::Vector2f Hero::getKnockbackOffset(const Hero* enemy) {
	if (enemy == nullptr) {
		return sf::Vector2f(0.0f, 0.0f);
	}

	const sf::Vector2f unit = VECTORS.at(getDirection());
	const sf::Vector2f offset = sf::Vector2f(unit.x * KNOCKBACK, unit.y * KNOCKBACK);

	return narrow_cast<float>(m_fsm.context().knockback)* offset;
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


// ---------------------------------------------
// private methods
// ---------------------------------------------

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


// ---------------------------------------------
// private static methods
// ---------------------------------------------

constexpr int Hero::getScreenDirection(int direction) noexcept {
	return (DIRECTIONS + INIT_DIRECTION - direction) % DIRECTIONS;
}

constexpr int Hero::getTextureDirection(int direction) noexcept {
	return (DIRECTIONS + INIT_DIRECTION - direction) % DIRECTIONS;
}