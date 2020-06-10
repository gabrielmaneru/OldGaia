#pragma once

namespace Gaia {
	class Entity {
	public:
		Entity(const std::string& name);
		~Entity() = default;

		void destoy();

	private:
		bool m_alive;
		std::string m_name;
		mat4 m_transform;
	};
}