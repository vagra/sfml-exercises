#pragma once

#include "globals.h"

#include "V.h"
#include "TextureManager.h"

using namespace std;

const int DIRECTIONS = 8;

const int MAX_ACTION_CYCLE = 5000;
const float MAX_SPEED = 2.f;
const float MIN_SPEED = 0.5f;

const float SQR = 0.7071f;
const float SCALE = float(SPRITE_WIDTH) / float(PNG_WIDTH);

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

    int getID();
    float getX();
    float getY();
    float prevX();
    float prevY();

    sf::Sprite sprite;

private:

    void init();

    sf::Vector2f genPosition();
    int genDirection();

    void changeFrame();

    int m_id;
    int m_no;
    string m_name;

    int m_action_timer;
    int m_actionCycle;

    int m_step;

    sf::Vector2f m_position;
    sf::Vector2f m_prev_position;
    int m_direction;

    float m_speed;
    sf::Vector2f m_vector;

    sf::IntRect m_area;

    sf::Texture* mp_texture;

    static inline sf::Vector2i region = sf::Vector2i(INIT_WIDTH, INIT_HEIGHT);

    static inline int counter = 0;
};