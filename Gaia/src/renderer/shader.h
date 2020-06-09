#pragma once

namespace Gaia {
	class Shader {
	public:
		Shader() = default;
		Shader(const std::string& name, const std::vector<std::string>& paths);
		enum class e_Type : u32;

		void compile(std::unordered_map<e_Type, std::string>& sources);
		void reload();
		void bind();

		u32 get_id()const { return m_id; }

		static e_Type get_type(const std::string& extension);

	private:
		u32 m_id;
		std::string m_name;
		std::vector<std::string> m_paths;
	};
}