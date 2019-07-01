
#pragma once

#include "tools/ComponentPool.hpp"


namespace ecs
{
    namespace component
    {
        template<typename ComponentType>
        ComponentPool<ComponentType> & getPool() {
            static ComponentPool<ComponentType> mComponentPool;
            return mComponentPool;
        }


        template<typename ComponentType, typename ...Args>
        void attach(index_t const entityID, Args ... args) {
            getPool<ComponentType>().attach(entityID, args...);
        }

        template<typename ComponentType>
        void detach(index_t const entityID) {
            getPool<ComponentType>().detach(entityID);
        }

        template<typename ComponentType>
        bool exist(index_t const entityID) {
            return getPool<ComponentType>().exist(entityID);
        }

        template<typename ComponentType>
        auto & get(index_t const entityID) {
            return getPool<ComponentType>()[entityID];
        }
    }
}
