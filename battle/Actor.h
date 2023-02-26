#pragma once

#include "globals.h"

#include "FontManager.h"
#include "TextureManager.h"
#include "ActionManager.h"

constexpr int DIRECTIONS = 8;
constexpr int INIT_DIRECTION = 6;

constexpr float MAX_RUN_SPEED = 2.0f;
constexpr float MAX_WALK_SPEED = 1.0f;
constexpr float MAX_STOP_SPEED = 0.5f;

constexpr int FRAME_CYCLE = 100;
constexpr int MIN_ACTION_CYCLE = 1000;
constexpr int MAX_ACTION_CYCLE = 5000;

constexpr int MIN_BATTLE_CYCLE = 500;
constexpr int MAX_BATTLE_CYCLE = 1000;

constexpr int MAX_HP = 999;

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

enum ACTION {
    WALK = 0,
    RUN = 1,
    SIT = 2,
    FAIL = 3,
    STAND = 4,
    ADVANCE = 5,
    ATTACK = 6,
    HIT = 7,
    JUMP = 8,
    REST = 9,
    DEFENCE = 10
};

constexpr int RUN_COUNT = 2;
constexpr int WALK_COUNT = 2;
constexpr int STOP_COUNT = 5;

constexpr array<ACTION, RUN_COUNT> RUN_ACTIONS = { ACTION::RUN, ACTION::ADVANCE };
constexpr array<ACTION, WALK_COUNT> WALK_ACTIONS = { ACTION::WALK, ACTION::JUMP };
constexpr array<ACTION, STOP_COUNT> STOP_ACTIONS = {
    ACTION::STAND, ACTION::ATTACK, ACTION::HIT, ACTION::REST, ACTION::DEFENCE };

class Actor
{
public:
    Actor() = default;

    void init(int id);
    void init(string name);
    void random() noexcept;
    void play(sf::Time elapsed);
    void step();
    void turn() noexcept;

    unique_ptr<sf::Sprite> sprite;
    unique_ptr<sf::Text> text;

    const int& id = m_id;
    const int& type = m_type;
    const string& name = m_name;
    const int& hp = m_hp;
    const bool& battle = m_battle;
    const sf::Vector2f& position = m_position;
    const sf::Vector2f& prev_position = m_prev_position;

    friend class ActorManager;

private:

    void init();

    void initSprite();
    void initText();

    int getActionStartFrame();
    int getActionFrameCount();

    sf::Vector2f genPosition();
    int genActionCycle() noexcept;
    int genBattleCycle() noexcept;
    float genSpeed() noexcept;
    int genDirection() noexcept;
    int genAction() noexcept;

    static constexpr int getScreenDirection(int direction) noexcept;
    static constexpr int getTextureDirection(int direction) noexcept;

    int m_id{};
    int m_type{};
    string m_name{};

    int m_hp{};

    int m_frame_timer{};
    int m_frame_step{};

    int m_action_cycle{};
    int m_action_timer{};

    int m_battle_cycle{};
    int m_battle_timer{};

    sf::Vector2i m_frame;
    sf::IntRect m_area;

    ActionSet* mp_action_set = nullptr;
    sf::Texture* mp_texture = nullptr;

    sf::Vector2f m_position;
    sf::Vector2f m_prev_position;

    float m_speed{};

    int m_action_id{};
    int m_direction{};

    bool m_move{};
    bool m_change{};
    bool m_battle{};

    unique_ptr<Actor> m_target;
    vector<unique_ptr<Actor>> m_enemies;

    static inline sf::IntRect region = sf::IntRect(0, 0, INIT_WIDTH, INIT_HEIGHT);
};