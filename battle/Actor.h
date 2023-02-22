#pragma once

#include "globals.h"

#include "TextureManager.h"
#include "ActionManager.h"

using namespace std;

const int DIRECTIONS = 8;
const int INIT_DIRECTION = 6;

const float MAX_RUN_SPEED = 2.0f;
const float MAX_WALK_SPEED = 1.0f;
const float MAX_STOP_SPEED = 0.5f;

const int FRAME_CYCLE = 100;
const int MIN_ACTION_CYCLE = 1000;
const int MAX_ACTION_CYCLE = 5000;

const float SQR = 0.7071f;

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

const enum ACTION {
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

const int RUN_COUNT = 2;
const int WALK_COUNT = 2;
const int STOP_COUNT = 5;

const array<ACTION, RUN_COUNT> RUN_ACTIONS = { ACTION::RUN, ACTION::ADVANCE };
const array<ACTION, WALK_COUNT> WALK_ACTIONS = { ACTION::WALK, ACTION::JUMP };
const array<ACTION, STOP_COUNT> STOP_ACTIONS = {
    ACTION::STAND, ACTION::ATTACK, ACTION::HIT, ACTION::REST, ACTION::DEFENCE };


class Actor
{
public:
    Actor();
    Actor(int type);
    Actor(string name);

    void init(int id);
    void init(string name);
    void random();
    void play(sf::Time elapsed);
    void step();

    static void setRegion(int width, int height);

    sf::Sprite* sprite;
    const int& id = m_id;
    const int& type = m_type;
    const string& name = m_name;

private:

    void init();

    int getActionStartFrame();
    int getActionFrameCount();

    sf::Vector2f genPosition();
    int genActionCycle();
    float genSpeed();
    int genDirection();
    int genAction();

    static int getScreenDirection(int direction);
    static int getTextureDirection(int direction);

    int m_id;
    int m_type;
    string m_name;

    int m_frame_timer;
    int m_frame_step;

    int m_action_cycle;
    int m_action_timer;

    sf::Vector2i m_frame;
    sf::IntRect m_area;

    ActionSet* mp_action_set;
    sf::Texture* mp_texture;

    sf::Vector2f m_position;
    sf::Vector2f m_prev_position;

    float m_speed;

    int m_action_id = 0;
    int m_direction = 0;

    bool m_move = false;
    bool m_change = false;

    static inline sf::IntRect region = sf::IntRect(0, 0, INIT_WIDTH, INIT_HEIGHT);
};