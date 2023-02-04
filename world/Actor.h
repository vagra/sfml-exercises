#pragma once

#include "globals.h"
#include "V.h"

using namespace std;

const int EDGE = 100;

const int DIRECTIONS = 8;
const int STEPS = 4;
const int ACTIONS = 3;  // Walk, Run, Raise
const int ACTORS = 17;

const int ANIM_CYCLE = 150;
const int MAX_ACTION_CYCLE = 5000;
const float MAX_SPEED = 2.0f;
const float MAX_WALK_SPEED = 1.0f;
const float MAX_RAISE_SPEED = 0.5f;

const float SQR = 0.7071f;
const float SCALE = 0.8f;

const string ACTOR_PNG = "../assets/characters/actor-{}-0.png";
const string SHADOW_PNG = "../assets/characters/shadow.png";

const int SHADOW_OFFX = 30;
const int SHADOW_OFFY = 80;

const V2i ANIM_STARTS[DIRECTIONS] = {
    V2i(0, 0),    // ↓
    V2i(3, 1),    // ↘
    V2i(0, 2),    // →
    V2i(3, 3),    // ↗
    V2i(0, 3),    // ↑
    V2i(3, 2),    // ↖
    V2i(0, 1),    // ←
    V2i(3, 0)     // ↙
};

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
    V2i(0, 0),     // Walk
    V2i(6, 0),     // Run
    V2i(0, 4),     // Raise
};

const int ANIM_STEPS[STEPS] = { 0, 1, 2, 1 };

class Actor
{
public:
    Actor();

    static bool zOrder(const Actor& actor1, const Actor& actor2);

    static void initTextures();
    static void setRegion(int width, int height);

    void init();
    void random();
    void play(sf::Time elapsed);
    void step();

    sf::Sprite sprite;

private:

    static void addShadow(sf::Texture& sheetTexture, sf::Texture shadowTexture);

    void changeFrame();
    int genDirection();

    int m_no;
    int m_anim_timer;
    int m_action_timer;
    int m_actionCycle;

    int m_step;
    int m_action;

    int m_direction;
    float m_speed;
    sf::Vector2f m_vector;

    V2i m_frame;
    sf::IntRect m_area;

    static inline sf::Vector2i region = sf::Vector2i(INIT_WIDTH, INIT_HEIGHT);
    static inline vector<sf::Texture> textures = vector<sf::Texture>();
    static inline sf::Texture shadow_texture = sf::Texture();
};