#pragma once
#include <scene/component.h>

namespace Gaia {
	class Entity {
	public:
		Entity(const std::string& name);
		~Entity() = default;

		template<typename T> shared<T> get_component();
		template<typename T> shared<const T> get_component()const;
		template<typename T> shared<T> add_component();
		void destroy();

	private:
		bool m_alive;
		std::string m_name;
		mat4 m_transform;
		std::map<TypeInfo, shared<Component>> m_components;
	};

	template<typename T>
	inline shared<T> Entity::get_component()
	{
		TypeInfo type = type_of<T>();
		auto res = m_components.find(type);
		if (res != m_components.end())
			return std::dynamic_pointer_cast<T>(res->second);
		return nullptr;
	}
	template<typename T>
	inline shared<const T> Entity::get_component() const
	{
		TypeInfo type = type_of<T>();
		auto res = m_components.find(type);
		if (res != m_components.end())
			return std::dynamic_pointer_cast<T>(res->second);
		return nullptr;
	}
	template<typename T>
	inline shared<T> Entity::add_component()
	{
		shared<T> cmp = get_component<T>();
		if (cmp != nullptr)
		{
			GAIA_ELOG_WARN("Adding same component twice");
			return cmp;
		}

		 cmp = new_shared<T>(this);
		TypeInfo type = type_of(*cmp);

		cmp->initialize();
		m_components[type] = cmp;
		return cmp;
	}
}