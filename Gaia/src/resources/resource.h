#pragma once
#include <resources/extension.h>

namespace Gaia {

	class Resource
	{
	public:
		Resource(const Resource&) = delete;
		Resource(const std::string& path, const e_Extension);

		void load();
		void unload();

		bool is_loaded()const { return m_loaded; }
		const std::string& get_name()const { return m_name; }
		const std::string& get_path()const { return m_path; }

	protected:

		virtual bool load_internal() { return true; }
		virtual bool unload_internal() { return true; }

		bool m_loaded;
		std::string m_path;
		std::string m_name;
		e_Extension m_extension;
	};
}