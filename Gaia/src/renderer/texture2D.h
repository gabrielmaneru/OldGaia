#pragma once
#include <renderer/texture.h>
#include <resources/resource.h>

namespace Gaia {

	class Texture2D : public Texture, public Resource {
	public:
		Texture2D(const std::string& path)
			: Resource(path){}

		bool load_internal()override;
		bool unload_internal()override;

	private:
		void submit()override;
		void load_png();

		u8* data{ nullptr };
	};
}