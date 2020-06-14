#pragma once
#include <components/component.h>
#include <renderer/renderable.h>
#include <renderer/model.h>

namespace Gaia {
	class MeshRenderable : public Component, public Renderable {
	public:
		void initialize()override;
		void enter()override;
		void update(float dt)override;
		void draw()const override;
		void exit()override;

	private:
		Model* m_model;
		bool m_visible;
	};
}