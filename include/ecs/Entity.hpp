#pragma once

#include <bitset>
#include <functional>

#include "tools/ComponentPool.hpp"
#include "Tags.hpp"


namespace ecs
{
    using signature_t = std::bitset<MAX_COMPONENT>;

    struct Signature
    {
        signature_t entityTAG{false};
    };

    struct Eraser {
    	std::function<void(index_t)> destroy;
    };

    namespace entity
    {
        namespace priv
        {
            ComponentPool<Signature> mSignature{MAX_ENTITY};
            ComponentPool<Eraser> mEraser{MAX_COMPONENT};

            std::vector<index_t> mDeletedBuffer;
            std::vector<index_t> mDeleted;

            index_t generateIndex() {
                static index_t gid{0};
                return gid++;
            }
        }


        index_t create() {
            index_t tmpID{invalid_index};

            if(!priv::mDeleted.empty()) {
                tmpID = priv::mDeleted.back();
                priv::mDeleted.pop_back();
            } else {
                tmpID = priv::generateIndex();
            }

            priv::mSignature.attach(tmpID, false);

            return tmpID;
        }

        bool exist(index_t const entityID) {
            return priv::mSignature.exist(entityID);
        }

        bool empty(index_t const entityID) {
            return priv::mSignature[entityID].entityTAG.none();
        }

        bool hasFlag(index_t const entityID, std::size_t const flag) {
            assert(exist(entityID));
            return priv::mSignature[entityID].entityTAG[flag] == true;
        }

        template<typename ComponentType>
	    bool hasFlag(index_t const entityID) {
		    assert(exist(entityID));
		    return hasFlag(entityID, tagOf(ComponentType));
	    }

        template<typename ComponentType>
        void addFlag(index_t const entityID) {
            assert(exist(entityID));
            index_t cid{tagOf(ComponentType)};

            priv::mSignature[entityID].entityTAG[cid] = true;

            if(!priv::mEraser.exist(cid)) {
            	priv::mEraser.attach(cid, component::detach<ComponentType>);
            }
        }

        template<typename ComponentType>
        void popFlag(index_t const entityID) {
            assert(exist(entityID));
	        priv::mSignature[entityID].entityTAG[tagOf(ComponentType)] = false;
        }

        signature_t const & getSignature(index_t const entityID) {
            assert(exist(entityID));
            return const_cast<signature_t&>(priv::mSignature[entityID].entityTAG);
        }

        void remove(index_t const entityID) {
            assert(exist(entityID));
            priv::mDeletedBuffer.push_back(entityID);
        }

        void update() {
			for(auto & e:priv::mDeletedBuffer) {
				for(auto & f:priv::mEraser) {
					if(hasFlag(e, f.entityID)) {
						f.destroy(e);
					}
				}
				priv::mDeleted.push_back(e);
				priv::mSignature.detach(e);
			}
	        priv::mDeletedBuffer.clear();
        }





    }
}