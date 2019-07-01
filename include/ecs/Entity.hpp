#pragma once

#include <bitset>

#include "tools/ComponentPool.hpp"

//TODO: add signal to kill all components from an entity...
//#include <signal/Signal.hpp>




namespace ecs
{
    using signature_t = std::bitset<64>;

    struct Signature
    {
        signature_t entityTAG{false};
    };

    // should it be a struct ? maybe...
    namespace entity
    {
        namespace priv
        {
            ComponentPool<Signature> mSignature;
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

        void addFlag(index_t const entityID, std::size_t const flag) {
            assert(exist(entityID));
            assert(!hasFlag(entityID, flag));
            priv::mSignature[entityID].entityTAG[flag] = true;
        }

        void popFlag(index_t const entityID, std::size_t const flag) {
            assert(exist(entityID));
            priv::mSignature[entityID].entityTAG[flag] = false;
        }

        signature_t const & getSignature(index_t const entityID) {
            assert(exist(entityID));
            return const_cast<signature_t&>(priv::mSignature[entityID].entityTAG);
        }

        void remove(index_t const entityID) {
            assert(exist(entityID));
            priv::mSignature.detach(entityID);
            priv::mDeleted.push_back(entityID);
        }





    }
}