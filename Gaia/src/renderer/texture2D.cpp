#include "gaia_pch.h"
#include "texture2D.h"

#include <Glad/glad.h>
#include <stb_image/stb_image.h>

namespace Gaia {
	void Texture2D::submit()
	{
		reset_id();
		set_sampler_properties();

		glTexImage2D(GL_TEXTURE_2D, 0,
			(int)m_properties.internal_format,
			m_size.x, m_size.y, 0,
			(u32)m_properties.pixel_format,
			(u32)m_properties.data_type, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	bool Texture2D::load_internal()
	{
		
		return ;
	}
	bool Texture2D::unload_internal()
	{
		if (!m_id)
			return false;
		glDeleteTextures(1, &m_id);
		m_id = 0;
		return true;
	}
	void Texture2D::load_png()
	{
		stbi_set_flip_vertically_on_load(true);
		int x, y;
		u8*data = stbi_load(m_path.c_str(), &x, &y, nullptr, STBI_rgb_alpha);
		if (data)
		{

			stbi_image_free(data)
		}

	}
}
