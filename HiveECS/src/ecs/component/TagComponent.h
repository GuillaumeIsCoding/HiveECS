//
// Created by guill on 2024-10-25.
//
#pragma once
#include "IComponent.h"

namespace hive::ecs {
    struct TagComponent final : IComponent {
        std::string Tag;

        TagComponent() = default;
        explicit TagComponent(const TagComponent&) = default;
        explicit TagComponent(const std::string& tag) : Tag(std::move(tag)) {}

        ~TagComponent() override = default;

        [[nodiscard]]
        std::string toString() const override;
    };
}