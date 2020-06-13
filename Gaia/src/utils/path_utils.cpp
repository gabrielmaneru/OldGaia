#include "gaia_pch.h"
#include "path_utils.h"

namespace Gaia {
	std::string get_name_from_path(const std::string & path)
	{
		size_t found; std::string name;
		found = path.find_last_of("/\\");
		name = found != std::string::npos ? path.substr(found + 1) : path;
		found = name.find_last_of(".");
		name = found != std::string::npos ? name.substr(0, found) : name;
		return name;
	}
	std::string get_extension_from_path(const std::string & path)
	{
		size_t found = path.find_last_of(".");
		return found != std::string::npos ? path.substr(found + 1) : "";
	}
	std::string read_from_file(const std::string & path)
	{
		std::string output;
		std::ifstream in(path, std::ios::in | std::ios::binary);
		if (!in)
			return "";
		in.seekg(0, std::ios::end);
		output.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&output[0], output.size());
		in.close();
		return output;
	}
}