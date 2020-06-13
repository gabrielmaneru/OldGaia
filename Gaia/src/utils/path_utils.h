#pragma once

namespace Gaia {
	std::string get_name_from_path(const std::string& path);
	std::string get_extension_from_path(const std::string& path);
	std::string read_from_file(const std::string& path);

}