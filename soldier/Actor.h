#pragma once

#include "globals.h"

#include "V.h"
#include "TextureManager.h"

using namespace std;

const int DIRECTIONS = 8;
const int ACTIONS = 8;  // Attack, Block, Death, GotHit, Idle, Jump, Run, Walk
const int STEPS = 6;

const int ANIM_CYCLE = 150;
const int MAX_ACTION_CYCLE = 5000;
const float MAX_SPEED = 1.5f;
const float MAX_WALK_SPEED = 0.7f;
const float MAX_STOP_SPEED = 0.2f;

const float SQR = 0.7071f;

const V2f VECTORS[DIRECTIONS] = {
    V2f(0.0,  1.0),
    V2f(SQR,  SQR),
    V2f(1.0,  0.0),
    V2f(SQR, -SQR),
    V2f(0.0, -1.0),
    V2f(-SQR, -SQR),
    V2f(-1.0, 0.0),
    V2f(-SQR,  SQR)
};

const V2i ACTION_ORIGINS[ACTIONS] = {
    V2i(0, 0),      // 0 Attack
    V2i(6, 0),      // 1 Block
    V2i(12, 0),     // 2 Death
    V2i(18, 0),     // 3 GotHit
    V2i(0, 8),      // 4 Idle
    V2i(6, 8),      // 5 Jump
    V2i(12, 8),     // 6 Run
    V2i(18, 8),     // 7 Walk
};

const int STOPS = 5;
const int STOP_ACTIONS[STOPS] = { 0, 1, 3, 4, 5 };


class Actor
{
public:
    Actor();

    static bool zOrder(const Actor& actor1, const Actor& actor2);
    static void setRegion(int width, int height);

    static bool atFront(const Actor& actor1, const Actor& actor2);

    void random();
    void play(sf::Time elapsed);
    void turn();
    void stop();
    void step();

    int getID();
    float getX();
    float getY();
    float preX();
    float preY();

    sf::Sprite sprite;

private:

    void init();

    sf::Vector2f genPosition();
    int genDirection();
    int genStopAction();

    void changeFrame();

    int m_id;
    int m_no;
    string m_name;

    int m_anim_timer;
    int m_action_timer;
    int m_actionCycle;

    int m_step;
    int m_action;

    sf::Vector2f m_position;
    sf::Vector2f m_prev_position;
    int m_direction;

    float m_speed;
    sf::Vector2f m_vector;

    V2i m_frame;
    sf::IntRect m_area;

    sf::Texture* mp_texture;

    static inline sf::Vector2i region = sf::Vector2i(INIT_WIDTH, INIT_HEIGHT);

    static inline int counter = 0;
};