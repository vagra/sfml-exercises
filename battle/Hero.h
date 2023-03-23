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

const string HP_FONT = "Lato";
constexpr int HP_FONT_SIZE = 16;
const sf::Color HP_COLOR = sf::Color::Red;

constexpr float KNOCKBACK = 20.f;
constexpr int NEAR = 10;
constexpr int FAR = 30;

class Hero : public Actor
{
public:

    Hero(int type);

    void play(sf::Time elapsed) override;
    void step() override;

    void bump();
    void back(int direction);
    void attack(Hero* enemy);
    void attackedBy(Hero* enemy, const DefendSignl signl);
    void disable();

    int getStartFrame() const override;
    int getTotalFrames() const override;
    int getCurrentFrame() const override;

    int getDirection() const override;
    sf::Vector2f getOffset() const override;
    int getStiffs() const;

    bool inMoving() const;
    bool inKnockback() const;
    bool inAttacked() const;
    bool inFail() const;
    bool inInjured() const;
    bool inAlive() const;
    bool inDeath() const;
    bool inPatrol() const;
    bool inBattle() const;
    bool inStandby() const;

    bool atFront(const Hero* other) const;
    bool canAttack(Hero* enemy) const;
    bool canAttack() const;
    bool canBeAttacked() const;

    sf::Vector2f getKnockbackOffset(const Hero* enemy);
    pair<int, int> getKnockback(const Hero* enemy);
    pair<int, int> getOpposite(const Hero* enemy);

    const bool& disabled = m_disabled;

private:
    void initFSM();

    sf::Vector2f genPosition();
    int genHit() noexcept;

    static constexpr int getScreenDirection(int direction) noexcept;
    static constexpr int getTextureDirection(int direction) noexcept;

    bool m_disabled{};

    Hero* m_enemy = nullptr;

    Context m_context{};
    FSM::Instance m_fsm{m_context};
};