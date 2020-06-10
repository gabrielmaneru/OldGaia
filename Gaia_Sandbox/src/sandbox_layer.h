#pragma once
#include <gaia.h>
#include <core/layer.h>

class SandboxLayer : public Gaia::Layer
{
public:
	SandboxLayer()
		:Gaia::Layer("Sandbox") {}
	virtual ~SandboxLayer() = default;

	void begin()override;
	void update()override;
	void render_editor() override;
	void end() override;


private:
	 
};