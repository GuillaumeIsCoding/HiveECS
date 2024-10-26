//
// Created by guill on 2024-10-25.
//
#pragma once
#include <hvpch.h>
#include "Ecs.h"

namespace hive::ecs {

    template<typename... Components>
    class QueryBuilder {
    public:
        QueryBuilder() = default;

        /**
         * 
         * @return Iterator of type <hive::ecs::Entity, Components...>
         */
        auto each() const {
            auto m_view = ECS::getCurrentRegistry()->m_registry.view<Components...>();
            return m_view.each();
        }
    };
}