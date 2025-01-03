//
// Created by guill on 2024-10-25.
//
#include "Registry.h"

namespace hive::ecs
{
    EntityRegistry::Entity EntityRegistry::createEntity()
    {
        return m_registry.create();
    }




}