#include "gaia_pch.h"
#include "texture.h"

#include <Glad/glad.h>

namespace Gaia {

	enum class e_InternalFormat {
		R = GL_R8,
		RG = GL_RG8,
		RGB = GL_RGB8,
		RGBA = GL_RGBA8,
		hRGB = GL_RGB4,
		hRGBA = GL_RGBA4,
		Rf = GL_R32F,
		RGf = GL_RG32F,
		RGBf = GL_RGB32F,
		RGBAf = GL_RGBA32F,
		hRf = GL_R16F,
		hRGf = GL_RG16F,
		hRGBf = GL_RGB16F,
		hRGBAf = GL_RGBA16F,
		Depth = GL_DEPTH_COMPONENT
	};
	enum class e_PixelFormat {
		R = GL_RED,
		RG = GL_RG,
		RGB = GL_RGB,
		RGBA = GL_RGBA,
		Depth = GL_DEPTH_COMPONENT
	};
	enum class e_DataType {
		UnsignedByte = GL_UNSIGNED_BYTE,
		Float = GL_FLOAT,
		hFloat = GL_HALF_FLOAT
	};
	enum class e_Wrap {
		Clamp = GL_CLAMP_TO_EDGE,
		Repeat = GL_REPEAT
	};
	enum class e_Filter {
		Nearest = GL_NEAREST,
		Linear = GL_LINEAR
	};


	TextureProps::TextureProps(e_InternalFormat iForm,
		e_PixelFormat pForm, e_DataType type, e_Wrap wra,
		e_Filter minF, e_Filter magF)
		: internal_format(iForm), pixel_format(pForm), data_type(type),
		wrap(wra), min_filter(minF), mag_filter(magF) {}

	float TextureProps::max_anisotropy{ 0.f };

	Texture::Texture(urect size, const TextureProps & props)
		:m_id(0), m_size(size), m_properties(props)
	{
		submit();
	}

	Texture::~Texture()
	{
		if (m_id)
			glDeleteTextures(1, &m_id);
	}

	void Texture::submit()
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

	bool Texture::is_color() const
	{
		return m_properties.internal_format != e_InternalFormat::Depth;
	}

	void Texture::reset_id()
	{
		if (m_id)
			glDeleteTextures(1, &m_id);

		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D, m_id);
	}

	void Texture::set_sampler_properties()
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (int)m_properties.min_filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (int)m_properties.mag_filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (int)m_properties.wrap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (int)m_properties.wrap);
		glTextureParameterf(m_id, GL_TEXTURE_MAX_ANISOTROPY, m_properties.max_anisotropy);
	}

	TextureProps Texture::default_color_rgba = TextureProps(
		e_InternalFormat::RGBA,
		e_PixelFormat::RGBA,
		e_DataType::UnsignedByte,
		e_Wrap::Repeat,
		e_Filter::Nearest, e_Filter::Nearest);
	TextureProps Texture::default_color_rgb = TextureProps(
		e_InternalFormat::RGB,
		e_PixelFormat::RGB,
		e_DataType::UnsignedByte,
		e_Wrap::Repeat,
		e_Filter::Nearest, e_Filter::Nearest);
	TextureProps Texture::default_depth = TextureProps(
		e_InternalFormat::Depth,
		e_PixelFormat::Depth,
		e_DataType::Float,
		e_Wrap::Clamp,
		e_Filter::Nearest, e_Filter::Nearest);

	TextureProps Texture::gbuffer_rgb = TextureProps(
		e_InternalFormat::hRGBf,
		e_PixelFormat::RGB,
		e_DataType::hFloat,
		e_Wrap::Clamp,
		e_Filter::Nearest, e_Filter::Nearest);
	TextureProps Texture::gbuffer_rg = TextureProps(
		e_InternalFormat::hRGf,
		e_PixelFormat::RG,
		e_DataType::hFloat,
		e_Wrap::Clamp,
		e_Filter::Nearest, e_Filter::Nearest);
}
