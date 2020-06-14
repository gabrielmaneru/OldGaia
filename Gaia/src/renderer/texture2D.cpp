#include "gaia_pch.h"
#include "texture2D.h"

#include <Glad/glad.h>
#include <stb_image/stb_image.h>

namespace Gaia {
	void Texture2D::submit()
	{
		reset_id();
		switch (m_extension)
		{
		case Gaia::e_Extension::png:
			stb_data_load_png();
			break;
		case Gaia::e_Extension::jpg:
			stb_data_load_jpg();
			break;
		}

		if (stb_data)
		{
			set_sampler_properties();

			glTexImage2D(GL_TEXTURE_2D, 0,
				(int)m_properties.internal_format,
				m_size.x, m_size.y, 0,
				(u32)m_properties.pixel_format,
				(u32)m_properties.data_type, stb_data);
			glBindTexture(GL_TEXTURE_2D, 0);
			stb_data_free();
		}
		else
		{
			glDeleteTextures(1, &m_id);
			m_id = 0;
		}
	}
	bool Texture2D::load_internal()
	{
		submit();
		return m_id != 0;
	}
	bool Texture2D::unload_internal()
	{
		if (!m_id)
			return false;
		glDeleteTextures(1, &m_id);
		m_id = 0;
		return true;
	}
	void Texture2D::stb_data_load_png()
	{
		GAIA_EASSERT(!stb_data, "Unfree STB memory");
		stbi_set_flip_vertically_on_load(true);
		int x, y;
		stb_data = stbi_load(m_path.c_str(), &x, &y, nullptr, STBI_rgb_alpha);
		if (stb_data) {
			m_size = { (u32)x,(u32)y };
			m_properties = default_color_rgba;
		}
	}
	void Texture2D::stb_data_load_jpg()
	{
		GAIA_EASSERT(!stb_data, "Unfree STB memory");
		stbi_set_flip_vertically_on_load(true);
		int x, y;
		stb_data = stbi_load(m_path.c_str(), &x, &y, nullptr, STBI_rgb);
		m_size = { (u32)x,(u32)y };
		m_properties = default_color_rgb;
	}
	void Texture2D::stb_data_free()
	{
		GAIA_EASSERT(stb_data, "Freeing null STB memory");
		stbi_image_free(stb_data);
		stb_data = nullptr;
	}
}
