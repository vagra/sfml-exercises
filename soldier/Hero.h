#pragma once

#include "globals.h"

#include "../common/FontManager.h"
#include "../common/TextureManager.h"
#include "../common/ActionManager.h"
#include "../common/ActorManager.h"


constexpr int FRAME_CYCLE = 100;
constexpr int MAX_ROUNDS = 10;

constexpr int MAX_RUN_SPEED = 20;
constexpr int MAX_WALK_SPEED = 10;
constexpr int MAX_STOP_SPEED = 5;
constexpr float SPEED_RATE = FRAME_CYCLE / 1000.f;

constexpr int STOPS = 5;
constexpr int STOP_ACTIONS[STOPS] = { 0, 1, 3, 4, 5 };


class Hero : public Actor
{
public:
    Hero(int type);

    void play(sf::Time elapsed) override;
    void step() override;
	
    void bump();
    void back(int direction);
    void stop();
    void random();

    int getStartFrame() const override;
    int getTotalFrames() const override;
    int getCurrentFrame() const noexcept override;
    int getRowFrame() const;

    int getDirection() const override;
    sf::Vector2f getOffset() const override;

private:
    sf::Vector2f genPosition();
    int genDirection();
    int genStopAction();

    int m_rounds{};
    int m_round{};

    int m_frame_step{};
    int m_action_id{};
    int m_direction{};

    float m_speed{};
};