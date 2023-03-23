#pragma once

#include "globals.h"

#include "../common/TextureManager.h"
#include "../common/ActionManager.h"
#include "../common/ActorManager.h"

constexpr int INIT_DIRECTION = 6;
constexpr float SPEED = 2.0f;
constexpr int DURATION = 100;

class Hero : public Actor
{
public:
    Hero(int type);

    void play(sf::Time elapsed) override;
    void step() override;

    void move(bool move);
    void turn(int direction);
    void change(int action_id);

    bool inMoving();

private:
    int getTotalFrames() override;
    int getStartFrame() override;

    int getDirection() override;
    sf::Vector2f getOffset() override;

    static constexpr int getScreenDirection(int direction);
    static constexpr int getTextureDirection(int direction);

    static inline int m_frame_step = 0;
    static inline int m_action_id = 0;
    static inline int m_direction = 0;
    static inline bool m_move = false;
    static inline bool m_change = false;
};