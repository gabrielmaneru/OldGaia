#pragma once
#include <components/component.h>
#include <renderer/renderable.h>
#include <renderer/model.h>
#include <renderer/material.h>

namespace Gaia {
	class MeshRenderable : public Component, public Renderable {
		DECL_COMP(MeshRenderable)
	public:
		void initialize()override;
		void enter()override;
		void update(float dt)override;
		void draw(Shader * shader)const override;
		void render_editor()override;
		void exit()override;
		void serialize(Json::Value& json)const override;
		void deserialize(const Json::Value& json)override;
		std::string get_type_name()const override { return "MeshRenderable"; }

	private:
		shared<Material> m_material;
		Model* m_model;
		bool m_visible;
	};
}