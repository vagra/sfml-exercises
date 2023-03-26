#pragma once

#include "globals.h"

#include "../common/FontManager.h"
#include "../common/TextureManager.h"
#include "../common/ActionManager.h"
#include "../common/ActorManager.h"
#include "Sorter.h"

constexpr int FRAME_CYCLE = 100;
constexpr int MAX_ROUNDS = 10;

constexpr int MAX_RUN_SPEED = 20;
constexpr int MAX_WALK_SPEED = 10;
constexpr int MAX_STOP_SPEED = 5;
constexpr float SPEED_RATE = FRAME_CYCLE / 1000.f;


class Hero : public Actor
{
public:
    Hero(int type);

    /* override pure virtual methods */

    void play(sf::Time elapsed) override;
    void step() override;

    int getStartFrame() const override;
    int getTotalFrames() const override;
    int getCurrentFrame() const noexcept override;

    int getDirection() const override;
    sf::Vector2f getOffset() const override;

    /* public methods */

    void back(int direction) noexcept;
    void stop();
    void random();

    /* public members */

    Hero* prev = nullptr;
    Hero* next = nullptr;

private:

    /* private methods */

    sf::Vector2f genPosition();
    int genDirection();

    /* private members */

    int m_rounds{};
    int m_round{};

    int m_frame_step{};
    int m_action_id{};
    int m_direction{};

    float m_speed{};
};