#pragma once
#include <renderer/texture2D.h>

namespace Gaia {
	using FramebufferProperties = std::vector<TextureProperties>;

	class Framebuffer {
	public:
		Framebuffer(urect size, const FramebufferProperties& properties);
		~Framebuffer();

		void reset();
		void resize(urect size);
		void bind();
		void free();

		u32 get_id()const { return m_id; }
		u32 get_txt_id(u32)const;

	private:
		u32 m_id;
		urect m_size;
		FramebufferProperties m_properties;
		std::vector<Texture2D*> m_draw_textures;
	};
}