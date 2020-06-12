#pragma once

namespace Gaia {

	template<typename T>
	using ResourceMap = std::map<std::string, T>;

	template<typename ... Args>
	using TupleMap = std::tuple<ResourceMap<Args>...>;

	using ResourceMaps = TupleMap<


	class ResourceManager {
	public:
		ResourceManager();

	private:

	};
}