#pragma once
#include <resources/resource.h>

namespace Gaia {
	class Scene;
	class Level : public Resource
	{
	public:
		using Resource::Resource;
		Extensions(e_Extension::level);

		bool load_internal()override;
		bool unload_internal()override;
		void load_level(Scene* scn)const;
		void save_level(const Scene* scn);

		static void create(const std::string& name);

		const Json::Value& get_data()const { return m_data; }

	private:
		Json::Value m_data;
	};
}