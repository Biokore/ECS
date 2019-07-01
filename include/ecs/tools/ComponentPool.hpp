
#pragma once

#include <vector>
#include <cassert>
#include <limits>


namespace ecs
{
    using index_t = std::size_t;
    static constexpr std::size_t invalid_index = std::numeric_limits<index_t>::max();


    struct EntityWrapper
    {
        index_t entityID{invalid_index};
    };

    template<typename ComponentType>
    struct ComponentWrapper: public EntityWrapper, public ComponentType
    {
        ComponentWrapper(): ComponentWrapper{invalid_index} {}

        template<typename ...Args>
        explicit ComponentWrapper(index_t const id, Args... args): EntityWrapper{id}, ComponentType{args...} {}
    };


    template<typename ComponentType>
    class ComponentPool
    {
    private:
        using wrapper_t = ComponentWrapper<ComponentType>;

        std::vector<wrapper_t> mData;
        std::vector<std::size_t> mIndexes;

        inline std::size_t indexOf(index_t const entityID) const {
			assert(exist(entityID));
			return mIndexes[entityID];
		}

    public:
	
	
		using iterator = typename std::vector<wrapper_t>::iterator;
		using const_iterator = typename std::vector<wrapper_t>::const_iterator;
		
		// maximum entity number : 16^6 = 16'777'216
		explicit ComponentPool(std::size_t const capacity=0xFFFFFF) {
			mData.reserve(capacity);
			mIndexes.resize(capacity, invalid_index);
		}

		~ComponentPool() = default;
		
		template<typename ...Args>
		void attach(index_t const entityID, Args ...args){
			assert(!exist(entityID));
			mData.push_back(wrapper_t{entityID, args...});
			mIndexes[entityID] = size()-1;
		}

		void detach(index_t const entityID) {
			assert(exist(entityID));
			index_t tmpID{mData[size()-1].entityID};

			std::swap(mData[indexOf(entityID)], mData[size()-1]);
			mIndexes[tmpID] = indexOf(entityID);
			mIndexes[entityID] = invalid_index;

			mData.resize(size()-1);
		}
		
		wrapper_t & get(index_t const entityID) {
			assert(exist(entityID));
			return mData[indexOf(entityID)];
		}

		wrapper_t const & get(index_t const entityID) const {
			assert(exist(entityID));
			return const_cast<wrapper_t&>(mData[indexOf(entityID)]);
		}

		wrapper_t & operator[](index_t const entityID) {
			assert(exist(entityID));
			return mData[indexOf(entityID)];
		}

		wrapper_t const & operator[](index_t const entityID) const {
			assert(exist(entityID));
			return const_cast<wrapper_t&>(mData[indexOf(entityID)]);
		}

		inline bool exist(index_t const entityID) const {
			return mIndexes[entityID] != invalid_index;
		}

		inline std::size_t size() const {
			return mData.size();
		}
		
		inline iterator begin() {
			return mData.begin();
		}
		
		inline iterator end() {
			return mData.end();
		}
		
		inline const_iterator cbegin() const {
			return mData.cbegin();
		}
		
		inline const_iterator cend() const {
			return mData.cend();
		}

    };
}