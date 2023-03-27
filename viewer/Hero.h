#pragma once

#include "globals.h"

#include "../common/TextureManager.h"
#include "../common/ActionManager.h"
#include "../common/ActorManager.h"

constexpr int FRAME_CYCLE = 100;
constexpr float SPEED = 2.0f;

class Hero : public Actor
{
public:
    Hero(int type);

    void play(sf::Time elapsed) override;
    void step() override;

    void move(bool move) noexcept;
    void turn(int direction);
    void changeActor();
    void changeAction(int action_id) noexcept;

    int getStartFrame() const override;
    int getTotalFrames() const override;
    int getCurrentFrame() const noexcept override;

    int getDirection() const override;
    sf::Vector2f getOffset() const override;

private:

    static inline sf::Vector2f g_position = sf::Vector2f(INIT_WIDTH / 2, INIT_HEIGHT / 2);
    static inline int g_frame_step = 0;
    static inline int g_action_id = 0;
    static inline int g_direction = 0;
    static inline bool g_moving = false;
    static inline bool g_change_action = true;
};