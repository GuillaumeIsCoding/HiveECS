//
// Created by guill on 2024-10-25.
//
#pragma once
#include <string>

namespace hive::ecs {
    struct IComponent {
        virtual ~IComponent() = default;
        [[nodiscard]]
        virtual std::string toString() const = 0;
    };
}