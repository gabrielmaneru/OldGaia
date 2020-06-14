#pragma once
#include <renderer/texture.h>
#include <resources/resource.h>

namespace Gaia {

	class Texture2D : public Texture, public Resource {
	public:
		Texture2D(const std::string& path, const e_Extension ext)
			: Texture(), Resource(path, ext) {}
		Extensions(e_Extension::png, e_Extension::jpg);

		bool load_internal()override;
		bool unload_internal()override;

	private:
		void submit()override;
		void stb_data_load_png();
		void stb_data_load_jpg();
		void stb_data_free();

		u8* stb_data{ nullptr };
	};
}