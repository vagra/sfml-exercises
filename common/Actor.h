#pragma once
#pragma warning(disable: 26440)

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
    virtual ~Actor() = default;

    /* public pure virtual methods */

    virtual void play(sf::Time elapsed) = 0;
    virtual void step() = 0;

    virtual int getStartFrame() const = 0;
    virtual int getTotalFrames() const = 0;
    virtual int getCurrentFrame() const = 0;

    virtual int getDirection() const = 0;
    virtual sf::Vector2f getOffset() const = 0;

    /* public virtual methods */

    virtual bool needRemove() const;
    virtual bool skipBump() const;
    virtual bool textOn() const;

    virtual void remove();
    virtual void handleBump(Actor* other);

    /* public methods */

    string getTypeName() const;
    
    void initRegion(const sf::FloatRect& region);
    void initPosition(const sf::Vector2f& position);
    void initSprite(const sf::Vector2f& scale, const sf::Vector2f& origin);
    void initArea(const sf::IntRect area);
    void initText(const Text& text);

    bool atFront(const Actor* other) const;

    /* public static methods */

    static void setRegion(float width, float height);

    /* const member accessers */

    const int& id = m_id;
    const int& type = m_type;
    const string& name = m_name;

    const bool& removed = m_removed;

    const sf::Vector2f& position = m_position;
    const sf::Vector2f& prev_position = m_prev_position;

    const unique_ptr<sf::Sprite>& sprite = m_sprite;
    const unique_ptr<sf::Text>& text = m_text;

protected:

    /* private methods */

    string genName();
    int checkRegion();

    /* private members */

    int m_id{};
    int m_type{};
    string m_name{};

    int m_frame_timer{};

    bool m_removed{};

    sf::Vector2i m_frame;
    sf::IntRect m_area;

    sf::Vector2f m_position;
    sf::Vector2f m_prev_position;

    unique_ptr<sf::Sprite> m_sprite;
    unique_ptr<sf::Text> m_text;

    ActionSet* m_action_set{};
    sf::Texture* m_texture{};

    /* private static memebers */

    static inline sf::FloatRect region = sf::FloatRect{};
};