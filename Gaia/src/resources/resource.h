#pragma once
#include <resources/extension.h>

namespace Gaia {

	class Resource
	{
		Resource(const Resource&) = delete;
	public:
		Resource(const std::string& path, e_Extension ext, bool loaded = false);

		void load_resource();
		void unload_resource();

		bool is_loaded()const { return m_loaded; }
		const std::string& get_name()const { return m_name; }
		const std::string& get_path()const { return m_path; }

		friend class ResourceManager;
	protected:

		virtual bool load_internal() { return true; }
		virtual bool unload_internal() { return true; }

		bool m_loaded;
		std::string m_path;
		std::string m_name;
		e_Extension m_extension;
	};
}