//
// Created by guill on 2024-10-25.
//
#pragma once
#include <hvpch.h>

namespace hive::ecs {
    class System;

    class SystemManager {
    public:
        SystemManager() = default;

        ~SystemManager();

        void updateSystems(float deltaTime);

        void registerSystem(System* system, const std::string& name);
        void removeSystem(const std::string& name);

        System* getSystem(const std::string& name);
        
    private:
        std::map<std::string, System*> m_systems;
    };
}
