
#pragma once

#define tagOf(ComponentType) tag::generateUniqTag<ComponentType>()


namespace ecs {
	using index_t = size_t; // TODO : define it only once in a "god header" ?
	namespace tag {
		std::size_t generateTag() {
			static index_t gtag{0};
			return gtag++;
		}

		template<typename ComponentType>
		std::size_t generateUniqTag() {
			static index_t utag{generateTag()};
			return utag;
		}
	}
}