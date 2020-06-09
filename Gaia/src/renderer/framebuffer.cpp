#include "gaia_pch.h"
#include "framebuffer.h"

#include <Glad/glad.h>

namespace Gaia {
	Framebuffer::Framebuffer(urect size, const FramebufferProperties& properties)
		:m_id(0), m_size(size), m_properties(properties)
	{
		reset();
	}
	Framebuffer::~Framebuffer()
	{
		free();
	}
	void Framebuffer::reset()
	{
		if (m_id)
			free();

		for (auto t : m_properties)
			m_draw_textures.push_back(new Texture2D(m_size, t));

		glGenFramebuffers(1, &m_id);
		glBindFramebuffer(GL_FRAMEBUFFER, m_id);

		std::vector<u32> draw_buffers;
		for (u32 i = 0; i <m_draw_textures.size(); ++i)
		{
			Texture2D& t = *m_draw_textures[i];
			if (t.is_color())
			{
				u32 color_attach = GL_COLOR_ATTACHMENT0 + (u32)draw_buffers.size();
				glFramebufferTexture(GL_FRAMEBUFFER, color_attach, t.get_id(), 0);
				draw_buffers.push_back(color_attach);
			}
			else
			{
				glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, t.get_id(), 0);
			}
		}

		if (draw_buffers.size() > 0)
			glDrawBuffers((int)draw_buffers.size(), draw_buffers.data());

		GAIA_EASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}
	void Framebuffer::resize(urect size)
	{
		if (m_size == size)
			return;
		m_size = size;

		reset();
	}
	void Framebuffer::bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_id);
		glViewport(0, 0, m_size.x, m_size.y);
	}
	void Framebuffer::free()
	{
		for (auto pT : m_draw_textures)
			delete pT;
		m_draw_textures.clear();
		if (m_id)
			glDeleteFramebuffers(1, &m_id);
	}
	u32 Framebuffer::get_txt_id(u32 idx) const
	{
		if(idx < m_draw_textures.size())
			return m_draw_textures[idx]->get_id();

		GAIA_EASSERT(false, "Invalid Texture Access!")
		return 0;
	}
}
