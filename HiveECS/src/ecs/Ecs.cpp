//
// Created by guill on 2024-10-25.
//
#include "Ecs.h"
#include "system/System_Manager.h"

hive::ecs::SystemManager *m_systemManager = nullptr;
hive::ecs::Registry *hive::ecs::ECS::m_registry = nullptr;

void hive::ecs::ECS::init() {
    // logger
    m_registry = new Registry();
    m_systemManager = new SystemManager();
}

void hive::ecs::ECS::shutdown() {
    // logger
    delete m_systemManager;
    delete m_registry;
}

void hive::ecs::ECS::registerSystem(System *system, const std::string &name) {
    m_systemManager->registerSystem(system, name);
}

void hive::ecs::ECS::removeSystem(const std::string &name) {
    m_systemManager->removeSystem(name);
}

void hive::ecs::ECS::updateSystem(float deltaTime) {
    if(m_systemManager != nullptr) {
        m_systemManager->updateSystems(deltaTime);
    }
}

hive::ecs::Registry *hive::ecs::ECS::getCurrentRegistry() {
    return m_registry;
}







