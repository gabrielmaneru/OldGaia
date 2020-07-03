#pragma once

namespace Gaia {

	enum class e_InternalFormat;
	enum class e_PixelFormat;
	enum class e_DataType;
	enum class e_Wrap;
	enum class e_Filter;

	struct TextureProps
	{
		TextureProps(e_InternalFormat iForm, e_PixelFormat pForm, e_DataType type, e_Wrap wrap, e_Filter minF, e_Filter magF);

		e_InternalFormat internal_format;
		e_PixelFormat pixel_format;
		e_DataType data_type;
		e_Wrap wrap;
		e_Filter min_filter;
		e_Filter mag_filter;

		static float max_anisotropy;
	};

	class Texture {
	public:
		Texture() : m_id(0), m_properties(default_color_rgba) {}
		Texture(urect size, const TextureProps& props);
		virtual ~Texture();

		virtual void submit();
		u32 get_id()const { return m_id; }
		bool is_color()const;

		static TextureProps default_color_rgba;
		static TextureProps default_color_rgb;
		static TextureProps default_depth;

		static TextureProps gbuffer_rgb;
		static TextureProps gbuffer_rg;

	protected:
		void reset_id();
		void set_sampler_properties();

		u32 m_id;
		urect m_size;
		TextureProps m_properties;
	};
}