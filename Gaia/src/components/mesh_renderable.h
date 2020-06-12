#pragma once
#include <components/component.h>
#include <renderer/renderable.h>

namespace Gaia {
	class MeshRenderable : public Component, public Renderable {
	public:
		MeshRenderable(Entity*p = nullptr) :Component(p) {}
		virtual ~MeshRenderable()=default;

		void initialize()override;
		void enter()override;
		void update(float dt)override;
		void draw()const override;
		void exit()override;

	private:
		bool m_visible;
	};
}