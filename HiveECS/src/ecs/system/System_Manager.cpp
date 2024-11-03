//
// Created by guill on 2024-10-25.
//
#include "System_Manager.h"
#include "System.h"

hive::ecs::SystemManager::~SystemManager() {
    for (const auto& [name, system] : m_systems) {
        delete system;
    }
}

void hive::ecs::SystemManager::updateSystems(float deltaTime) {
    for (auto& system_pair : m_systems) {
        const std::string name = system_pair.first;
        auto system = system_pair.second;

        if(system->m_is_active) {
            system->update(deltaTime);
        }
    }
}

void hive::ecs::SystemManager::registerSystem(System *system, const std::string &name) {
    m_systems[name] = system;
    system->init();
}

void hive::ecs::SystemManager::removeSystem(const std::string &name) {
    m_systems.erase(name);
}

hive::ecs::System *hive::ecs::SystemManager::getSystem(const std::string &name) {
    return m_systems.at(name);
}



