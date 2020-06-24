#pragma once

namespace Gaia {
	class Entity;

	class Component : public Serializable{
	public:
		virtual ~Component() = default;

		virtual void initialize() {}
		virtual void enter() {}
		virtual void update(float dt) {}
		virtual void exit() {}
		template<typename T>
		void check_dependency();
		std::string get_type_name()const override { return "Component"; }

		Entity* get_owner()const { return m_owner; }

		friend class Entity;
		friend class ComponentFactory;
	protected:
		Entity* m_owner{ nullptr };
		virtual Component* create()const { return nullptr; }
	};

	template<typename T>
	inline void Component::check_dependency()
	{
		if (!m_owner->get_component<T>())
			m_owner->add_component<T>();
	}

	class ComponentFactory {
	public:
		static const ComponentFactory& get();
		Component* create(const std::string& name)const;
	private:
		ComponentFactory();
		~ComponentFactory();
		void register_bp(const Component*);
		std::map<std::string, const Component*> m_blueprints;
	};
#define DECL_COMP(DERIVED) Component* create()const override{return new DERIVED{};}
}