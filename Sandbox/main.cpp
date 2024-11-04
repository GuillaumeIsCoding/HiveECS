//
// Created by guill on 2024-10-25.
//
#include <iostream>
#include <ecs/HiveECS.h>

using namespace hive::ecs;

constexpr int DAG_DAMAGE = 5;
constexpr int AXE_DAMAGE = 15;
constexpr int SWORD_DAMAGE = 30;
constexpr int MINIMUM_HEALTH = 0;

enum class WEAPON_TYPE : int {
    DAG     = DAG_DAMAGE,
    AXE     = AXE_DAMAGE ,
    SWORD   = SWORD_DAMAGE
};

struct Health final : IComponent {
    int hp = 100.0;

    ~Health() override = default;

    [[nodiscard]]
    std::string toString() const override {
        return std::to_string(hp) + " HP ";
    }
};

struct Weapon final : IComponent {
    WEAPON_TYPE type;
    int damage;

    ~Weapon() override = default;

    explicit Weapon(const WEAPON_TYPE& type) : damage(static_cast<int>(type)), type(type) {}

    [[nodiscard]]
    std::string toString() const override {
        return "Attack : " + std::to_string(damage);
    }
};

void create_entity(const WEAPON_TYPE& type) {
    auto entity = ECS::createEntity();
    ECS::addComponent<Health>(entity);
    ECS::addComponent<Weapon>(entity, type);
}

class LogicSystem : public System {
public:
    void update(float deltaTime) override {
        if (!m_entities.empty()) m_entities.clear();

        auto query_health = QueryBuilder<Health>();

        for (auto [entity, health] : query_health.viewEach()) {
            if (health.hp > 0) {
                m_entities.push_back(entity);
            }
        }

        if (m_entities.size() == 1) {
            m_is_active = false;
            return ;
        }

        auto query_weapon = QueryBuilder<Weapon>();

        for (auto [entity, weapon] : query_weapon.groupEach()) {
            if (m_entities[0] == entity) idx = 1;
            else idx = 0;

            auto& health = ECS::getComponent<Health>(m_entities[idx]);
            health.hp -= weapon.damage;

            if (health.hp < MINIMUM_HEALTH) health.hp = MINIMUM_HEALTH;

            switch (weapon.type) {
                case WEAPON_TYPE::AXE:
                    std::cout << "Hit by an axe! ";
                    break;
                case WEAPON_TYPE::DAG:
                    std::cout << "Hit by a dag! ";
                    break;
                case WEAPON_TYPE::SWORD:
                    std::cout << "Hit by a sword! ";
            }

            std::cout << "Entity " << std::to_string(idx) << " has " << health.toString() << std::endl;
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

    ECS::registerSystem(new LogicSystem(), "LogicSystem");
}

void shutdown() {
    ECS::shutdown();
}

void update(float deltaTime) {
    bool is_finished = false;
    while (!is_finished) {
        ECS::updateSystem(deltaTime);
        if (ECS::getSystem("LogicSystem")->m_is_active == false) {
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

