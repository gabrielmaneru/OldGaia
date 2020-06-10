#pragma once
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <array>
#include <vector>

#include <glm/glm.hpp>

#include <core/definitions.h>
#include <debug/log_manager.h>

namespace Gaia {
	std::string get_name_from_path(const std::string& path);
	std::string get_extension_from_path(const std::string& path);
	std::string read_from_file(const std::string& path);
}
