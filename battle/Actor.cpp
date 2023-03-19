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
	m_text->setString(to_string(m_fsm.context().hp));
	m_text->setOrigin(0, ORIGIN_Y);
	m_text->setPosition(m_position);
}

void Actor::initFSM() {
	m_fsm.context().actor_id = m_id;
	m_fsm.context().actor_type = m_type;
	m_fsm.context().hp = MAX_HP;
}

void Actor::play(sf::Time elapsed) {

	if (isDeath()) {
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
			if (!m_enemy->isAlive()) {
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

void Actor::step() {
	const int direction = getScreenDirection(getDirection());

	m_frame.x = getStartFrame() + getCurrentFrame();
	m_frame.y = direction;

	m_area.left = m_frame.x * FRAME_WIDTH;
	m_area.top = m_frame.y * FRAME_HEIGHT;

	m_sprite->setTextureRect(m_area);
	m_text->setString(to_string(m_fsm.context().hp));
}

void Actor::bump() {
	m_fsm.react(BumpTurnSignl());
}

void Actor::back(int direction) {
	m_fsm.react(BackTurnSignl{direction});
}

void Actor::attack(Actor* enemy) {
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

void Actor::disable() {
	m_enemy = nullptr;
	m_disabled = true;
}

void Actor::attackedBy(Actor* enemy, DefendSignl signl) {

	if (enemy == nullptr) {
		return;
	}

	m_enemy = enemy;

	m_fsm.react(signl);
}

bool Actor::inMoving() noexcept {
	return m_fsm.context().speed > 0;
}

bool Actor::inKnockback() noexcept {
	return m_fsm.context().knockback != 0;
}

bool Actor::inAttacked() noexcept {
	return m_fsm.isActive<Attacked>();
}

bool Actor::inFail() noexcept {
	return m_fsm.isActive<Fail>();
}

bool Actor::inInjured() noexcept {
	return m_fsm.isActive<Injure>();
}

bool Actor::isAlive() noexcept {
	return !m_fsm.isActive<Death>() && !m_fsm.isActive<Fail>();
}

bool Actor::isDeath() noexcept {
	return m_fsm.isActive<Death>();
}

bool Actor::inPatrol() {
	return m_fsm.isActive<Patrol>();
}

bool Actor::inBattle() {
	return m_fsm.isActive<Battle>();
}

bool Actor::inStandby() {
	return m_fsm.isActive<Standby>();
}

bool Actor::canAttack(Actor* enemy) {

	if (enemy == nullptr) {
		return false;
	}

	return (canAttack() && enemy->canBeAttacked());
}

bool Actor::canAttack() {
	return (m_fsm.isActive<Patrol>() ||
		m_fsm.isActive<Standby>());
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

int Actor::checkRegion() noexcept {
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

	return -1;
}

int Actor::genHit() noexcept {
	return rand() % (MAX_HIT - MIN_HIT) + MIN_HIT;
}

int Actor::getStartFrame() {
	return mp_action_set->getAction(m_fsm.context().action)->start;
}

int Actor::getCurrentFrame() {
	return min(m_fsm.context().frames - 1, m_fsm.context().frame);
}

sf::Vector2f Actor::getOffset() {
	return VECTORS.at(getDirection()) * (m_fsm.context().speed / 10.f);
}

int Actor::getStiffs() {
	return ActionManager::getAction(m_type, ACTION::ATTACK)->frames;
}

int Actor::getDirection() const {
	return m_fsm.context().direction;
}

sf::Vector2f Actor::getKnockbackOffset(const Actor* enemy) {
	if (enemy == nullptr) {
		return sf::Vector2f(0.0f, 0.0f);
	}

	const sf::Vector2f unit = VECTORS.at(getDirection());
	const sf::Vector2f offset = sf::Vector2f(unit.x * KNOCKBACK, unit.y * KNOCKBACK);
	// fmt::print("{},{}\n", offset.x, offset.y);

	return offset;
}

pair<int, int> Actor::getKnockback(const Actor* enemy) {
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

pair<int, int> Actor::getOpposite(const Actor* enemy) {

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

constexpr int Actor::getScreenDirection(int direction) noexcept {
	return (DIRECTIONS + INIT_DIRECTION - direction) % DIRECTIONS;
}

constexpr int Actor::getTextureDirection(int direction) noexcept {
	return (DIRECTIONS + INIT_DIRECTION - direction) % DIRECTIONS;
}