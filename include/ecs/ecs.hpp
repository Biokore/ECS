
#pragma once

#include "Component.hpp"
#include "Entity.hpp"

#define tagOf(ComponentType) priv::generateUniqTag<ComponentType>()





namespace ecs
{
    namespace priv
    {
        std::size_t generateTag() {
            static index_t tag{0};
            return tag++;
        }

        template<typename ComponentType>
        std::size_t generateUniqTag() {
            static index_t utag{generateTag()};
            return utag;
        }
    }


    /// ENTITY ///
    index_t create() {
        return entity::create();
    }

    bool empty(index_t const entityID) {
        return entity::empty(entityID);
    }

    void remove(index_t const entityID) {
        assert(entity::exist(entityID));
        //TODO: pop all components from this entity !
        entity::remove(entityID);
    }


    /// COMPONENT ///
    template <typename ComponentType, typename ...Args>
    void attach(index_t const entityID, Args... args) {
        assert(entity::exist(entityID));
        component::attach<ComponentType>(entityID, args...);

        std::size_t sFlag{tagOf(ComponentType)};
        entity::addFlag(entityID, sFlag);
    }

    template <typename ComponentType>
    void detach(index_t const entityID) {
        assert(entity::exist(entityID));
        assert(component::exist<ComponentType>(entityID));
        component::detach<ComponentType>(entityID);

        std::size_t sFlag{tagOf(ComponentType)};
        entity::popFlag(entityID, sFlag);
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
}