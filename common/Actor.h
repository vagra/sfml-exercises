#pragma once

#include "headers.h"

#include "Text.h"
#include "FontManager.h"
#include "TextureManager.h"
#include "ActionManager.h"
#include "ActorManager.h"

class Actor
{
    friend class ActorManager;

public:
    Actor(int type);

    Actor() = default;
    Actor(const Actor&) = default;
    Actor(Actor&&) noexcept = default;
    Actor& operator=(const Actor&) = default;
    Actor& operator=(Actor&&) noexcept = default;
    virtual ~Actor() = default;

    void initRegion(const sf::IntRect& region) noexcept;
    void initPosition(const sf::Vector2f& position) noexcept;
    void initSprite(const sf::Vector2f& scale, const sf::Vector2f& origin);
    void initArea(const sf::IntRect area) noexcept;
    void initText(const Text& text);

    virtual void play(sf::Time elapsed) = 0;
    virtual void step() = 0;
    
    virtual int getStartFrame() const = 0;
    virtual int getTotalFrames() const = 0;
    virtual int getCurrentFrame() const = 0;

    virtual int getDirection() const = 0;
    virtual sf::Vector2f getOffset() const = 0;

    static void setRegion(int width, int height) noexcept;

    const int& id = m_id;
    const int& type = m_type;
    const string& name = m_name;

    const sf::Vector2f& position = m_position;
    const sf::Vector2f& prev_position = m_prev_position;

    const unique_ptr<sf::Sprite>& sprite = m_sprite;
    const unique_ptr<sf::Text>& text = m_text;

protected:

    string genName();
    int checkRegion() noexcept;

    int m_id{};
    int m_type{};
    string m_name{};

    int m_frame_timer{};

    sf::Vector2i m_frame;
    sf::IntRect m_area;

    sf::Vector2f m_position;
    sf::Vector2f m_prev_position;

    unique_ptr<sf::Sprite> m_sprite;
    unique_ptr<sf::Text> m_text;

    ActionSet* m_action_set{};
    sf::Texture* m_texture{};

    static inline sf::IntRect region = sf::IntRect();
};