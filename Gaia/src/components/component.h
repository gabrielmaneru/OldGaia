#pragma once

namespace Gaia {
	class Entity;

	class Component{
	public:
		virtual ~Component() = default;

		virtual void initialize() {}
		virtual void enter() {}
		virtual void update(float dt) {}
		virtual void exit() {}
		template<typename T>
		void check_dependency();

		Entity* get_owner()const { return m_owner; }

		friend class Entity;
	protected:
		Entity* m_owner{ nullptr };
	};

	template<typename T>
	inline void Component::check_dependency()
	{
		if (!m_owner->get_component<T>())
			m_owner->add_component<T>();
	}
}