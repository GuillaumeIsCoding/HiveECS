//
// Created by guill on 2024-10-25.
//
#include "ecs/Ecs.h"
#include "ecs/Query_Builder.h"
#include "ecs/system/System.h"
#include "ecs/component/IComponent.h"

using namespace hive::ecs;

constexpr int DAG_DAMAGE = 5;
constexpr int AXE_DAMAGE = 15;
constexpr int SWORD_DAMAGE = 30;

struct Health final : IComponent {
    uint8_t hp = 100.0;

    ~Health() override = default;

    [[nodiscard]]
    std::string toString() const override {
        return "HP : " + std::to_string(hp);
    }
};

struct Weapon : IComponent {
    uint8_t damage;

    ~Weapon() override = default;

    explicit Weapon(const uint8_t& damage) : damage(damage) {}

    [[nodiscard]]
    std::string toString() const override {
        return "Attack : " + std::to_string(damage);
    }
};

struct Dag final : Weapon {
    ~Dag() override = default;

    Dag() : Weapon(DAG_DAMAGE) {}
};

struct Axe final : Weapon {
    ~Axe() override = default;

    Axe() : Weapon(AXE_DAMAGE) {}
};

struct Sword final : Weapon {
    ~Sword() override = default;

    Sword() : Weapon(SWORD_DAMAGE) {}
};



int main() {
    return 0;
}

