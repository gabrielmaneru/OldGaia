#include "gaia_pch.h"
#include "extension.h"
#include <utils/path_utils.h>

namespace Gaia {
	e_Extension operator++(e_Extension & x)
	{
		return x=(e_Extension)(std::underlying_type<e_Extension>::type(x)+1);
	}
	e_Extension get_extension(const std::string & path)
	{
		const std::string cur_ext = get_extension_from_path(path);
		if (!cur_ext.empty())
		{
			for (auto ext = e_Extension::begin; ext < e_Extension::end; ++ext)
			{
				std::string ext_name;
				switch (ext)
				{
				default:
					GAIA_EASSERT(false, "Incomplete Extension Name");
				case e_Extension::begin:
					continue;
				case e_Extension::e_png:
					ext_name = "png";
					break;
				case e_Extension::e_jpg:
					ext_name = "jpg";
					break;
				}

				if (cur_ext == ext_name)
					return ext;
			}
		}
		return e_Extension::none;
	}
}
