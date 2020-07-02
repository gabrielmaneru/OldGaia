#include "gaia_pch.h"
#include "resource_manager.h"
#include <utils/tuple.h>
#include <utils/path_utils.h>
#include <Windows.h>

namespace Gaia {
	ResourceManager::ResourceManager()
	{
		_WIN32_FIND_DATAA file;
		std::vector<std::string> folders;
		HANDLE handle;
		folders.push_back("assets");

		// search in the folder
		for (int i = 0; i < folders.size(); i++)
		{
			handle = FindFirstFileA((LPCSTR)(folders[i] + "/*").c_str(), &file);
			if (!handle)
				continue;
			do
			{
				if (file.cFileName[0] == '.')
					continue;

				if (FILE_ATTRIBUTE_DIRECTORY & file.dwFileAttributes)
				{
					folders.push_back(folders[i] + '/' + (char *)file.cFileName);
					continue;
				}
				auto ext = strrchr((char *)file.cFileName, '.');

				if (ext != nullptr)
				{
					auto & pathname = folders[i] + '/' + file.cFileName;
					e_Extension extension = get_extension(pathname);
					if (extension != e_Extension::none)
						add_resource(pathname, extension);
				}

			} while (FindNextFileA(handle, &file));
			FindClose(handle);
		}
	}
	ResourceManager::~ResourceManager()
	{
		tuple_for_each(m_resources, [](auto& map) {
			for (auto& res : map) {
				if (res.second->is_loaded())
					res.second->unload_resource();
			}
		});
	}


#define MapElementType std::decay<decltype(map)>::type::mapped_type::element_type
	void ResourceManager::add_resource(const std::string path, const e_Extension ext)
	{
		std::string name = get_name_from_path(path);
		tuple_for_each(m_resources, [&path, &ext, &name](auto& map) {
			if (map.find(name) == map.end())
			{
				for (auto& stored_ext : MapElementType::m_extensions) {
					if (stored_ext == ext)
					{
						map[name] = new_shared<MapElementType>(path, ext);
						break;
					}
				}
			}
		});
	}
#undef MapElementType
}
