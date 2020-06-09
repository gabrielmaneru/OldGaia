#pragma once

namespace Gaia {
	struct TextureProperties
	{
		enum class e_InternalFormat : int;
		enum class e_PixelFormat : u32;
		enum class e_DataType : u32;
		enum class e_Wrap : int;
		enum class e_Filter : int;

		e_InternalFormat internal_format;
		e_PixelFormat pixel_format;
		e_DataType data_type;
		e_Wrap wrap;
		e_Filter min_filter;
		e_Filter mag_filter;

		TextureProperties(e_InternalFormat iForm, e_PixelFormat pForm, e_DataType type, e_Wrap wrap, e_Filter minF, e_Filter magF);

		static TextureProperties default_color;
		static TextureProperties default_depth;

		static float max_anisotropy;
	};

	class Texture2D {
	public:
		Texture2D() : m_id(0), m_properties(TextureProperties::default_color){}
		Texture2D(urect size, const TextureProperties& properties);
		~Texture2D();

		void reset();

		bool is_color()const;
		u32 get_id()const { return m_id; }

	private:
		u32 m_id;
		urect m_size;
		TextureProperties m_properties;
	};
}