#pragma once

#include "globals.h"

#include "TextureManager.h"
#include "ActionManager.h"

using namespace std;

const int DIRECTIONS = 8;
const int INIT_DIRECTION = 6;
const float SPEED = 2.0f;

const int DURATION = 100;

const float SQR = 0.7071f;

const array<sf::Vector2f, DIRECTIONS> VECTORS= {
    sf::Vector2f(0.0,   1.0),
    sf::Vector2f(SQR,   SQR),
    sf::Vector2f(1.0,   0.0),
    sf::Vector2f(SQR,  -SQR),
    sf::Vector2f(0.0,  -1.0),
    sf::Vector2f(-SQR, -SQR),
    sf::Vector2f(-1.0,  0.0),
    sf::Vector2f(-SQR,  SQR)
};

class Actor
{
public:
    Actor();
    Actor(int id);
    Actor(string name);

    void init(int id);
    void init(string name);
    void play(sf::Time elapsed);
    void pause();
    void step();
    void move(bool move);

    void turn(int direction);
    void change(int action_id);

    sf::Sprite* sprite;

private:

    void init();

    int getActionStartFrame();
    int getActionFrameCount();

    static int getScreenDirection(int direction);
    static int getTextureDirection(int direction);

    int m_id;
    string m_name;

    int m_timer;
    int m_step;

    sf::Vector2i m_frame;
    sf::IntRect m_area;

    ActionSet* mp_action_set;
    sf::Texture* mp_texture;

    static inline sf::Vector2f m_position = sf::Vector2f(INIT_WIDTH / 2, INIT_HEIGHT / 2);
    static inline int m_action_id = 0;
    static inline int m_direction = 0;
    static inline bool m_move = false;
    static inline bool m_change = false;
};