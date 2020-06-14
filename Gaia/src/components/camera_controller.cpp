#include "gaia_pch.h"
#include "camera_controller.h"
#include <scene/entity.h>
#include <components/camera.h>

namespace Gaia {
	void CameraController::initialize()
	{
		check_dependency<Camera>();
	}

	void CameraController::enter()
	{
	}

	void CameraController::update(float dt)
	{
		
	}

	void CameraController::exit()
	{
	}
}
