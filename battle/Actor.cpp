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

		if (inStandby()) {
			if (!m_enemy->isAlive()) {
				m_enemy = nullptr;
				m_direction = genDirection();
				m_fsm.changeTo<Patrol>();
			}
			else if (canAttack(m_enemy)) {
				attack(m_enemy);
			}
		}
		else if (inPatrol()) {
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
	const int direction = getScreenDirection(m_direction);

	m_frame.x = getStartFrame() + getCurrentFrame();
	m_frame.y = direction;

	m_area.left = m_frame.x * FRAME_WIDTH;
	m_area.top = m_frame.y * FRAME_HEIGHT;

	m_sprite->setTextureRect(m_area);
	m_text->setString(to_string(m_fsm.context().hp));
}

void Actor::turn() noexcept {
	const int range = rand() % (DIRECTIONS - 3) + 2;
	m_direction = (m_direction + range) % DIRECTIONS;
}

void Actor::attack(Actor* enemy) {
	if (enemy == nullptr) {
		return;
	}

	if (!canAttack(enemy)) {
		return;
	}
	
	m_enemy = enemy;
	// const int prev_direction = m_direction;
	m_direction = getOpposite(enemy);

	const pair<int, int> knockback = getKnockback(enemy);

	Combat combat = genCombat();
	combat.knockback = knockback.second;

	m_fsm.changeTo<Attack>();
	m_fsm.context().knockback = knockback.first;

	/*fmt::print("{:3d}->{:3d} att: dir {}-{} pos({:.0f}, {:.0f})\n",
		m_id, enemy->id, prev_direction, m_direction,
		m_position.x, m_position.y);*/

	enemy->attackedBy(this, combat);
}

void Actor::disable() {
	m_enemy = nullptr;

	m_disabled = true;
}

void Actor::attackedBy(Actor* enemy, const Combat combat) {

	if (enemy == nullptr) {
		return;
	}

	m_enemy = enemy;
	// const int prev_direction = m_direction;
	m_direction = getOpposite(enemy);

	/*fmt::print("{:3d}->{:3d} def: dir {}-{} pos({:.0f}, {:.0f})\n",
		enemy->id, m_id, prev_direction, m_direction,
		m_position.x, m_position.y);*/

	m_fsm.react(combat);
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

int Actor::getOpposite(const Actor* enemy) {

	if (enemy == nullptr) {
		return m_direction;
	}

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

sf::Vector2f Actor::getKnockbackOffset(const Actor* enemy) {
	if (enemy == nullptr) {
		return sf::Vector2f(0.0f, 0.0f);
	}

	const sf::Vector2f unit = VECTORS.at(m_direction);
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

constexpr int Actor::getScreenDirection(int direction) noexcept {
	return (DIRECTIONS + INIT_DIRECTION - direction) % DIRECTIONS;
}

constexpr int Actor::getTextureDirection(int direction) noexcept {
	return (DIRECTIONS + INIT_DIRECTION - direction) % DIRECTIONS;
}