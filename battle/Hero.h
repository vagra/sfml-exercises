#pragma once

#include "globals.h"

#include "../common/FontManager.h"
#include "../common/TextureManager.h"
#include "../common/ActionManager.h"
#include "../common/ActorManager.h"
#include "FSM.h"
#include "States.h"

constexpr int FRAME_CYCLE = 100;

constexpr int MAX_HP = 999;
constexpr int MIN_HIT = 50;
constexpr int MAX_HIT = 200;

const Text hp_text{
    .font = "Lato",
    .size = 16,
    .color = sf::Color::Red,
    .origin = sf::Vector2f(0, ORIGIN_Y)
};

constexpr float KNOCKBACK = 20.f;
constexpr int NEAR = 10;
constexpr int FAR = 30;

class Hero : public Actor
{
public:

    Hero(int type);

    /* override pure virtual methods */

    void play(sf::Time elapsed) override;
    void step() override;

    int getStartFrame() const override;
    int getTotalFrames() const override;
    int getCurrentFrame() const override;

    int getDirection() const override;
    sf::Vector2f getOffset() const override;

    /* override virtual methods */

    bool needRemove() const noexcept override;
    bool textOn() const noexcept override;
    bool skipBump() const noexcept override;

    void remove() noexcept override;
    void handleBump(Actor* other) override;

    /* public methods */

    void bump() noexcept;
    void back(int direction) noexcept;
    void attack(Hero* enemy);
    void attackedBy(Hero* enemy, const DefendSignl signl) noexcept;

    int getStiffs() const;

    bool inMoving() const noexcept;
    bool inKnockback() const noexcept;
    bool inAttacked() const noexcept;
    bool inFail() const noexcept;
    bool inInjured() const noexcept;
    bool inAlive() const noexcept;
    bool inDeath() const noexcept;
    bool inPatrol() const noexcept;
    bool inBattle() const noexcept;
    bool inStandby() const noexcept;

    bool canAttack(const Hero* enemy) const noexcept;
    bool canAttack() const noexcept;
    bool canBeAttacked() const noexcept;

    sf::Vector2f getKnockbackOffset(const Hero* enemy);
    pair<int, int> getKnockback(const Hero* enemy);
    pair<int, int> getOpposite(const Hero* enemy);

private:
    /* private methods */

    void initFSM();

    sf::Vector2f genPosition();
    int genHit() noexcept;

    /* private static methods */

    static constexpr int getScreenDirection(int direction) noexcept;
    static constexpr int getTextureDirection(int direction) noexcept;

    /* private members */

    Hero* m_enemy = nullptr;

    Context m_context{};
    FSM::Instance m_fsm{m_context};
};