//
// Created by guill on 2024-10-25.
//
#pragma once
#include "Registry.h"

namespace hive::ecs {
    class System;
    class SystemManager;
}

namespace hive::ecs {
    using Entity = entt::entity;
    using Registry = EntityRegistry;

    class ECS {
    public:
        static void init();
        static void shutdown();

        // System
        static void registerSystem(System* system, const std::string& name);
        static void removeSystem(const std::string& name);
        static void updateSystem(float deltaTime);

        // Entity
        template<typename Component, typename... Args>
        static void addComponent(Entity entity, Args&&... args) {
            assert(!hasComponent<Component>(entity));
            getCurrentRegistry()->addComponent<Component>(entity, args...);
        }

        template<typename Component>
        static void removeComponent(const Entity entity) {
            assert(hasComponent<Component>(entity));
            getCurrentRegistry()->removeComponent<Component>(entity);
        }

        template <typename Component>
        static Component& getComponent(const Entity entity) {
            assert(hasComponent<Component>());
            return getCurrentRegistry()->getComponent<Component>(entity);
        }

        template <typename Component>
        static bool hasComponent(const Entity entity) {
            return getCurrentRegistry()->hasComponent<Component>(entity);
        }

        static Entity createEntity() {return getCurrentRegistry()->createEntity();}

        // Other
        static Registry* getCurrentRegistry();

    private:
        static Registry* m_registry;
    };
}