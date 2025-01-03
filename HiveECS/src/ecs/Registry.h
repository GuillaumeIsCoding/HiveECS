//
// Created by guill on 2024-10-25.
//
#pragma once
#include <hvpch.h>

namespace hive::ecs
{
    class EntityRegistry
    {
    public:
        using Entity = entt::entity;
    public:
        EntityRegistry() = default;

        /**
         * Creates an Entity
         * @return Entity : A new Entity with zero Component attach to it
         */
        Entity createEntity();

        /**
         * Adds a Component to an Entity
         * @tparam Component : A Component
         * @param entity Entity : The Entity that will receive the Component
         * @param args Args : Args to give to the Component
         */
        template<typename  Component, typename... Args>
        void addComponent(Entity entity, Args&&...args);

        /**
         * Checks if an Entity has a specific Component
         * @tparam Component : A Component
         * @param entity Entity : The Entity that will be checks
         * @returns bool : False if the Entity does not have the Component and True if it does have it
         */
        template<typename Component>
        [[nodiscard]]
        bool hasComponent(Entity entity) const;

        /**
         * Gets a specific Component from the Entity
         * @tparam Component : A Component
         * @param entity Entity : The Entity that we will get the Component from
         * @return Component : None if the Entity has not the Component and The Component if the Entity has the Component
         */
        template<typename Component>
        Component& getComponent(Entity entity);

        /**
         * Removes a specific Component from the Entity
         * @tparam Component : A Component
         * @param entity Entity : The Entity we will remove the Component from
         */
        template<typename Component>
        void removeComponent(Entity entity);
    protected:
        template <typename... Component>
        friend class QueryBuilder;
        entt::registry m_registry;
    };

    template<typename Component, typename... Args>
    void EntityRegistry::addComponent(Entity entity, Args &&... args)
    {
        m_registry.emplace<Component>(entity, std::forward<Args>(args)...);
    }

    template<typename Component>
    bool EntityRegistry::hasComponent(Entity entity) const
    {
        return m_registry.all_of<Component>(entity);
    }

    template<typename Component>
    Component &EntityRegistry::getComponent(Entity entity)
    {
        return m_registry.get<Component>(entity);
    }

    template<typename Component>
    void EntityRegistry::removeComponent(Entity entity)
    {
        m_registry.remove<Component>(entity);
    }
}