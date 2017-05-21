#include "PlasmaCamera.h"

namespace Plasma {
	Camera::Camera()
	{
	}


	Camera::~Camera()
	{
	}

	void Camera::init(float screenWidth, float screenHeight) {
		Error::log("Initializing 2D camera...");

		_x = 0.0f;
		_y = 0.0f;

		_cameraMatrix = glm::mat4(1.0f);
		_scale = 1.0f;
		_needsUpdate = true;

		_screenWidth = screenWidth;
		_screenHeight = screenHeight;

		_ortho = glm::ortho(0.0f, _screenWidth, 0.0f, _screenHeight);
		
		Error::log("2D camera created.");
	}

	void Camera::update() {
		if (_needsUpdate) {
			glm::vec3 translation(-_x, -_y, 0.0f);
			_cameraMatrix = glm::translate(_ortho, translation);

			glm::vec3 scale(_scale, _scale, 0.0f);
			_cameraMatrix = glm::scale(glm::mat4(1.0), scale) * _cameraMatrix;
			_needsUpdate = false;
		}
	}
	glm::vec2 Camera::screenToWorld(glm::vec2 screen) {
		glm::vec2 newCoords = screen;
		newCoords.y = _screenHeight - screen.y;
		//newCoords -= glm::vec2(_screenWidth, _screenHeight);
		newCoords /= _scale;
		newCoords += glm::vec2(_x, _y);

		return newCoords;
	}
}