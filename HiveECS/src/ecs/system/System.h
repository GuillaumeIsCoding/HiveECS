//
// Created by guill on 2024-10-25.
//
#pragma once

namespace hive::ecs {
    class System {
    public:
        virtual ~System() = default;

        virtual void init() = 0;
        virtual void update(float deltaTime) = 0;

        bool is_active = true;

    private:
        friend class SystemManager;
    };
}
