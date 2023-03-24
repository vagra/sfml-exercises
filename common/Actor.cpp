#include "Actor.h"

Actor::Actor(int type)
{
	m_type = type;
	m_id = ActorManager::instance().genID();
	m_name = genName();

	m_action_set = ActionManager::instance().getActionSet(m_type);
	m_texture = TextureManager::instance().getTexture(m_type);
}

void Actor::initRegion(const sf::IntRect& region) noexcept {
	Actor::region = region;
}

void Actor::initPosition(const sf::Vector2f& position) noexcept {
	m_position = position;
	m_prev_position = position;
}

void Actor::initSprite(const sf::Vector2f& scale, const sf::Vector2f& origin) {
	m_sprite = make_unique<sf::Sprite>();

	m_sprite->setTexture(*m_texture);
	m_sprite->setTextureRect(m_area);
	m_sprite->setOrigin(origin);
	m_sprite->setScale(scale);
	m_sprite->setPosition(m_position);
}

void Actor::initArea(sf::IntRect rect) noexcept {
	m_area = rect;
}

void Actor::initText(const Text& text) {
	m_text = make_unique<sf::Text>();

	m_text->setFont(*FontManager::instance().getFont(text.font));
	m_text->setCharacterSize(text.size);
	m_text->setFillColor(text.color);
	m_text->setString(text.text);
	m_text->setOrigin(text.origin);
	m_text->setPosition(m_position);
}


bool Actor::atFront(const Actor* other) const {

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

void Actor::setRegion(int width, int height) noexcept {
	region.width = width;
	region.height = height;
}

string Actor::genName() {
	const string type_name = ActionManager::instance().getActionSetName(m_type);
	return fmt::format("{}-{}", type_name, m_id);
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