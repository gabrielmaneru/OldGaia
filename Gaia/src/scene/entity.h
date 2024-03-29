#pragma once
#include <components/component.h>
#include <utils/transform3D.h>

namespace Gaia {
	class Entity : public Transform3D, public Serializable {
	public:

		Entity(const std::string& name);
		~Entity() = default;

		void enter();
		void update(float dt);
		void exit();
		void serialize(Json::Value& json)const override;
		void deserialize(const Json::Value& json)override;
		std::string get_type_name()const override { return "Entity"; }
		using ComponentMap = std::map<TypeInfo, shared<Component>>;

		template<typename T>
		shared<T> get_component();
		template<typename T>
		shared<const T> get_component()const;
		template<typename T>
		shared<T> add_component();
		const std::string& get_name()const { return m_name; }
		void set_name(const std::string& name) { m_name=name; }
		ComponentMap& get_component_map() { return m_components; }

	private:
		template<typename T, typename>
		friend struct Load;
		Entity() = default;
		bool m_alive;
		std::string m_name;
		 ComponentMap m_components;
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

		 cmp = new_shared<T>();
		 cmp->m_owner = this;
		TypeInfo type = type_of(*cmp);
		m_components[type] = cmp;

		cmp->initialize();
		return cmp;
	}
}