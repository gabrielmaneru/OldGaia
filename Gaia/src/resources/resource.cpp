#include "gaia_pch.h"
#include "resource.h"
#include <utils/path_utils.h>

namespace Gaia {

	Resource::Resource(const std::string & path, const e_Extension ext)
		: m_loaded(false), m_path(path),
		m_name(get_name_from_path(path)),
		m_extension(ext) {}
	void Resource::load()
	{
		if (m_loaded)
			GAIA_ELOG_WARN("Loading twice {0} at {1}", m_name, m_path);
		else
			m_loaded = load_internal();

		if(!m_loaded)
			GAIA_ELOG_WARN("Couldn't load {0} at {1}", m_name, m_path);
	}
	void Resource::unload()
	{
		if (!m_loaded)
			GAIA_ELOG_WARN("Unloading twice {0} at {1}", m_name, m_path);
		else
			m_loaded = !unload_internal();

		if (m_loaded)
			GAIA_ELOG_WARN("Couldn't unload {0} at {1}", m_name, m_path);
	}
}
