#pragma once
#include <renderer/texture2D.h>

namespace Gaia {

	template<typename T>
	using ResourceMap = std::map<std::string, shared<T>>;

	template<typename ... Args>
	using TupleMap = std::tuple<ResourceMap<Args>...>;

	using ResourceMaps = TupleMap<
		Texture2D
	>;


	class ResourceManager {
	public:
		ResourceManager();
		~ResourceManager();

		template<typename T>
		shared<T> get(const std::string& name);
		template<typename T>
		ResourceMap<T>& get_map();


	private:
		void add_resource(const std::string path, const e_Extension);

		ResourceMaps m_resources;
	};
	template<typename T>
	inline shared<T> ResourceManager::get(const std::string & name)
	{
		ResourceMap<T>& resource_map = get_map<T>();
		auto key = resource_map.find(name);
		if (key == resource_map.end())
			return nullptr;

		if (!key->second->is_loaded())
			key->second->load();
		return shared<T>{key->second};
	}
	template<typename T>
	inline ResourceMap<T>& ResourceManager::get_map()
	{
		return std::get<ResourceMap<T>>(m_resources);
	}
}