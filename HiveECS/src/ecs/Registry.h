//
// Created by guill on 2024-10-25.
//
#pragma once
#include <hvpch.h>

namespace hive::ecs {
    class EntityRegistry {
    public:
        using Entity = entt::entity;

        EntityRegistry() = default;

        Entity createEntity() {
            return m_registry.create();
        }

        template<typename  Component, typename... Args>
        void addComponent(Entity entity, Args&&...args) {
            m_registry.emplace<Component>(entity, std::forward<Args>(args)...);
        }

        template<typename Component>
        bool hasComponent(Entity entity) const {
            return m_registry.all_of<Component>(entity);
        }

        template<typename Component>
        Component& getComponent(Entity entity) {
            return m_registry.get<Component>(entity);
        }

        template<typename Component>
        void removeComponent(Entity entity) {
            m_registry.remove<Component>(entity);
        }

    protected:
        template <typename... Component>
        friend class QueryBuilder;
        entt::registry m_registry;
    };
}