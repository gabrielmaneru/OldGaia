#include "gaia_pch.h"
#include "shader.h"

#include <Glad/glad.h>

namespace Gaia {
	enum class Shader::e_Type : u32 {
		frag = GL_FRAGMENT_SHADER,
		vert = GL_VERTEX_SHADER,
		geom = GL_GEOMETRY_SHADER,
		tese = GL_TESS_EVALUATION_SHADER,
		tesc = GL_TESS_CONTROL_SHADER
	};

	Shader::Shader(const std::string& name, const std::vector<std::string>& paths)
		:m_id(0), m_name(name), m_paths(paths)
	{
		reload();
	}
	void Shader::compile(std::unordered_map<e_Type, std::string>& sources)
	{
		if (m_id)
			glDeleteProgram(m_id);

		u32 program = glCreateProgram();
		std::vector<u32> shader_ids;
		for (auto& key : sources)
		{
			u32 type = (u32)key.first;
			std::string& source = key.second;

			u32 shader_id = glCreateShader(type);
			const char* cstr = source.c_str();
			glShaderSource(shader_id, 1, &cstr, 0);
			glCompileShader(shader_id);

			int compiled{0};
			glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compiled);
			if (compiled == GL_FALSE)
			{
				int log_length = 0;
				glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);

				std::vector<char> log(log_length);
				glGetShaderInfoLog(shader_id, log_length, &log_length, &log[0]);
				glDeleteShader(shader_id);

				GAIA_ELOG_ERROR("Shader compilation failed:\n{0}", &log[0]);
				GAIA_EASSERT(false, "Shader compilation failed");
			}
			glAttachShader(program, shader_id);
			shader_ids.push_back(shader_id);
		}

		glLinkProgram(program);

		int linked{ 0 };
		glGetProgramiv(program, GL_LINK_STATUS, &linked);
		if (linked == GL_FALSE)
		{
			int log_length = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);

			std::vector<char> log(log_length);
			glGetProgramInfoLog(program, log_length, &log_length, &log[0]);
			glDeleteProgram(program);
			for (auto id : shader_ids)
				glDeleteShader(id);

			GAIA_ELOG_ERROR("Shader linking failed:\n{0}", &log[0]);
			GAIA_EASSERT(false, "Shader linking failed");
		}

		for (auto id : shader_ids)
			glDetachShader(program, id);

		m_id = program;
	}
	void Shader::reload()
	{
		std::unordered_map<e_Type, std::string> sources;
		for (auto path : m_paths)
		{
			std::string source = read_from_file(path);
			GAIA_EASSERT(!source.empty(), "Could not load shader!");

			e_Type type = get_type(get_extension_from_path(path));
			GAIA_EASSERT(sources.find(type) == sources.end(),
				"Multiple sources of same shader type");

			sources[type] = source;
		}

		compile(sources);

	}
	void Shader::bind()
	{
		if (m_id)
			glUseProgram(m_id);
	}
	Shader::e_Type Shader::get_type(const std::string & extension)
	{
		if (extension == "frag")
			return Shader::e_Type::frag;
		if (extension == "vert")
			return Shader::e_Type::vert;
		if (extension == "geom")
			return Shader::e_Type::geom;
		if (extension == "tese")
			return Shader::e_Type::tese;
		if (extension == "tesc")
			return Shader::e_Type::tesc;

		GAIA_EASSERT(false, "Invalid Extension");
		return {};
	}
}
