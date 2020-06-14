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
		void set_uniform(const char *name, bool val) const;
		void set_uniform(const char *name, int val) const;
		void set_uniform(const char *name, float val) const;
		void set_uniform(const char *name, const vec2 & v) const;
		void set_uniform(const char *name, const vec3 & v) const;
		void set_uniform(const char *name, const vec4 & v) const;
		void set_uniform(const char *name, const mat3 & m) const;
		void set_uniform(const char *name, const mat4 & m) const;

		u32 get_id()const { return m_id; }

		static e_Type get_type(const std::string& extension);

	private:
		u32 m_id;
		std::string m_name;
		std::vector<std::string> m_paths;
	};
}