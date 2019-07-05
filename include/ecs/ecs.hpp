
#pragma once

#include "Component.hpp"
#include "Entity.hpp"






namespace ecs
{
    /// ENTITY ///
    index_t create() {
        return entity::create();
    }

    bool empty(index_t const entityID) {
        return entity::empty(entityID);
    }

    void remove(index_t const entityID) {
        assert(entity::exist(entityID));
        entity::remove(entityID);
    }


    /// COMPONENT ///
    template <typename ComponentType, typename ...Args>
    void attach(index_t const entityID, Args... args) {
        assert(entity::exist(entityID));
        component::attach<ComponentType>(entityID, args...);
        entity::addFlag<ComponentType>(entityID);
    }

    template <typename ComponentType>
    void detach(index_t const entityID) {
        assert(entity::exist(entityID));
        assert(component::exist<ComponentType>(entityID));
        component::detach<ComponentType>(entityID);
        entity::popFlag<ComponentType>(entityID);
    }

    template<typename ComponentType>
    auto & get(index_t const entityID) {
        assert(entity::exist(entityID));
        assert(component::exist<ComponentType>(entityID));
        return component::get<ComponentType>(entityID);
    }

    template<typename ComponentType>
    auto & get() {
        return ecs::component::getPool<ComponentType>();
    }

    template<typename ComponentType>
    bool exist(index_t const entityID) {
    	return ecs::component::exist<ComponentType>(entityID);
    }

    void update() {
    	entity::update();
    }
}