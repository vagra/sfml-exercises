#pragma once

#include "globals.h"

#include "../common/FontManager.h"
#include "../common/TextureManager.h"
#include "../common/ActionManager.h"
#include "../common/ActorManager.h"


constexpr int FRAME_CYCLE = 100;
constexpr int MAX_ROUNDS = 50;

constexpr int MAX_SPEED = 20;
constexpr int MIN_SPEED = 5;
constexpr float SPEED_RATE = FRAME_CYCLE / 1000.f;


class Tank : public Actor
{
public:
    Tank(int type);

    /* override pure virtual methods */

    void play(sf::Time elapsed) override;
    void step() override;

    int getStartFrame() const override;
    int getTotalFrames() const override;
    int getCurrentFrame() const noexcept override;

    int getDirection() const override;
    sf::Vector2f getOffset() const override;

    /* override virtual methods */

    void handleBump(Actor* other) noexcept override;
	
    /* public methods */

    void bump() noexcept;
    void back(int direction) noexcept;
    void stop();
    void random();

private:

    /* private methods */

    sf::Vector2f genPosition();
    int genDirection();

    /* private members */

    int m_rounds{};
    int m_round{};

    int m_direction{};

    float m_speed{};
};