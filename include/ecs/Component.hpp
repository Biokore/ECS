
#pragma once

#ifndef MAX_ENTITY
	#define MAX_ENTITY 0xFFFF   // 65'536 entities max
#endif
#ifndef MAX_COMPONENT
	#define MAX_COMPONENT 0x3F    // 64 different components
#endif

#include "tools/ComponentPool.hpp"



namespace ecs
{
    namespace component
    {
        template<typename ComponentType>
        ComponentPool<ComponentType> & getPool() {
            static ComponentPool<ComponentType> mComponentPool{MAX_ENTITY};
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
