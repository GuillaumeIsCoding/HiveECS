//
// Created by guill on 2024-10-25.
//
#include <iostream>
#include "ecs/Ecs.h"
#include "ecs/Query_Builder.h"
#include "ecs/system/System.h"
#include "ecs/component/IComponent.h"

using namespace hive::ecs;

constexpr int DAG_DAMAGE = 5;
constexpr int AXE_DAMAGE = 15;
constexpr int SWORD_DAMAGE = 30;
constexpr int MINIMUM_HEALTH = 0;

enum class WEAPON_TYPE : uint8_t{
    DAG,
    AXE,
    SWORD
};

struct Health final : IComponent {
    int hp = 100.0;

    ~Health() override = default;

    [[nodiscard]]
    std::string toString() const override {
        return std::to_string(hp) + " HP ";
    }
};

struct Weapon : IComponent {
    int damage;

    ~Weapon() override = default;

    explicit Weapon(const int& damage) : damage(damage) {}

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

void create_entity(const WEAPON_TYPE& type) {
    auto entity = ECS::createEntity();
    ECS::addComponent<Health>(entity);
    switch (type) {
        case WEAPON_TYPE::DAG:
            ECS::addComponent<Dag>(entity);
            break;
        case WEAPON_TYPE::AXE:
            ECS::addComponent<Axe>(entity);
            break;
        case WEAPON_TYPE::SWORD:
            ECS::addComponent<Sword>(entity);
            break;
    }
}

class LSystem : public System {
public:
    void update(float deltaTime) override {
        if (!m_entities.empty()) m_entities.clear();

        auto query_health = QueryBuilder<Health>();

        for (auto [entity, health] : query_health.each()) {
            if (health.hp > 0) {
                m_entities.push_back(entity);
            }
        }

        if (m_entities.size() == 1) {
            is_active = false;
            return ;
        }

        auto query_dag = QueryBuilder<Dag>();

        for (auto [entity, dag] : query_dag.each()) {
            if (m_entities[0] == entity)  idx = 1;
            else idx = 0;

            auto& health = ECS::getComponent<Health>(m_entities[idx]);
            health.hp -= dag.damage;

            if (health.hp < MINIMUM_HEALTH) health.hp = MINIMUM_HEALTH;

            std::cout << "Hit by a dag! Entity " << std::to_string(idx) << " has " << health.toString() << std::endl;
        }

        auto query_axe = QueryBuilder<Axe>();

        for (auto [entity, axe] : query_axe.each()) {
            if (m_entities[0] == entity)  idx = 1;
            else idx = 0;

            auto& health = ECS::getComponent<Health>(m_entities[idx]);
            health.hp -= axe.damage;

            if (health.hp < MINIMUM_HEALTH) health.hp = MINIMUM_HEALTH;

            std::cout << "Hit by an axe! Entity " << std::to_string(idx) << " has " << health.toString() << std::endl;
        }

        auto query_sword = QueryBuilder<Sword>();

        for (auto [entity, sword] : query_sword.each()) {
            if (m_entities[0] == entity)  idx = 1;
            else idx = 0;

            auto& health = ECS::getComponent<Health>(m_entities[idx]);
            health.hp -= sword.damage;

            if (health.hp < MINIMUM_HEALTH) health.hp = MINIMUM_HEALTH;

            std::cout << "Hit by a sword! Entity " << std::to_string(idx) << " has " << health.toString() << std::endl;
        }


    }

    void init() override {}
private:
    int idx = 0;
    std::vector<entt::entity> m_entities;
};

void setupEcs() {
    ECS::init();

    // Entity 1
    create_entity(WEAPON_TYPE::SWORD);

    // Entity 2
    create_entity(WEAPON_TYPE::AXE);

    ECS::registerSystem(new LSystem(), "LogicSystem");
}

void shutdown() {
    ECS::shutdown();
}

void update(float deltaTime) {
    bool is_finished = false;
    while (!is_finished) {
        ECS::updateSystem(deltaTime);
        if (ECS::getSystem("LogicSystem")->is_active == false) {
            is_finished = true;
        }
    }
}

void init() {
    setupEcs();
}

int main() {
    init();
    update(1.0);
    shutdown();
    return 0;
}

