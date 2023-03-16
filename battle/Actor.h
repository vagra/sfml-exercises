#pragma once

#include "globals.h"

#include "FontManager.h"
#include "TextureManager.h"
#include "ActionManager.h"
#include "FSM.h"
#include "States.h"

constexpr int DIRECTIONS = 8;
constexpr int INIT_DIRECTION = 6;

constexpr int FRAME_CYCLE = 100;

constexpr int MAX_HP = 999;
constexpr int MIN_HIT = 50;
constexpr int MAX_HIT = 200;

const string HP_FONT = "Lato";
constexpr int HP_FONT_SIZE = 16;
const sf::Color HP_COLOR = sf::Color::Red;

constexpr float SQR = 0.7071f;

const array<sf::Vector2f, DIRECTIONS> VECTORS = {
    sf::Vector2f(0.0,   1.0),   // 0
    sf::Vector2f(SQR,   SQR),   // 1
    sf::Vector2f(1.0,   0.0),   // 2
    sf::Vector2f(SQR,  -SQR),   // 3
    sf::Vector2f(0.0,  -1.0),   // 4
    sf::Vector2f(-SQR, -SQR),   // 5
    sf::Vector2f(-1.0,  0.0),   // 6
    sf::Vector2f(-SQR,  SQR)    // 7
};

constexpr float KNOCKBACK = 20.f;

class Actor
{
public:

    void init(int id);
    void init(string name);

    void play(sf::Time elapsed);
    void step();
    void turn() noexcept;

    void attack(Actor* enemy);
    void disable();

    bool inMoving() noexcept;
    bool inKnockback() noexcept;
    bool inAttacked() noexcept;
    bool inFail() noexcept;
    bool inInjured() noexcept;
    bool isAlive() noexcept;
    bool isDeath() noexcept;

    bool inPatrol();
    bool inBattle();
    bool inStandby();
    bool canAttack(Actor* enemy);
    bool canAttack();
    bool canBeAttacked();

    int getOpposite(const Actor* enemy);
    sf::Vector2f getKnockback(const Actor* enemy);

    const int& id = m_id;
    const int& type = m_type;
    const string& name = m_name;
    const bool& disabled = m_disabled;

    const int& direction = m_direction;
    const sf::Vector2f& position = m_position;
    const sf::Vector2f& prev_position = m_prev_position;

    const unique_ptr<sf::Sprite>& sprite = m_sprite;
    const unique_ptr<sf::Text>& text = m_text;

    friend class ActorManager;

private:

    void init();

    void initSprite();
    void initText();
    void initFSM();

    int getStartFrame();
    int getCurrentFrame();

    sf::Vector2f getOffset();
    int getStiffs();

    sf::Vector2f genPosition();
    int genDirection() noexcept;
    int genHit() noexcept;

    Combat genCombat();

    void attackedBy(Actor* enemy, const Combat combat);

    static constexpr int getScreenDirection(int direction) noexcept;
    static constexpr int getTextureDirection(int direction) noexcept;

    int m_id{};
    int m_type{};
    string m_name{};
    bool m_disabled{};

    int m_frame_timer{};

    int m_direction{};

    sf::Vector2i m_frame;
    sf::IntRect m_area;

    sf::Vector2f m_position;
    sf::Vector2f m_prev_position;

    unique_ptr<sf::Sprite> m_sprite;
    unique_ptr<sf::Text> m_text;

    ActionSet* mp_action_set = nullptr;
    sf::Texture* mp_texture = nullptr;

    Actor* m_enemy = nullptr;

    Context m_context{};
    FSM::Instance m_fsm{m_context};

    static inline sf::IntRect region = sf::IntRect(0, 0, INIT_WIDTH, INIT_HEIGHT);
};