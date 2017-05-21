#pragma once
#include "Plasma.h"
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>

namespace Plasma {
	class Camera
	{
	public:
		Camera();
		~Camera();

		void init(float screenWidth, float screenHeight);
		void update();

		void setPos(float x, float y) { _x = x; _y = y; _needsUpdate = true; }
		void addPos(float x, float y) { _x += x; _y += y; _needsUpdate = true; }

		float getX() { return _x; }
		float getY() { return _y; }

		void setScale(float scale) { _scale = scale; _needsUpdate = true; }
		void addScale(float scale) { _scale += scale; _needsUpdate = true; }

		glm::mat4 getCameraMatrix() { return _cameraMatrix; }

		glm::vec2 screenToWorld(glm::vec2 screen);

	private:
		float _x;
		float _y;

		glm::mat4 _cameraMatrix;
		glm::mat4 _ortho;

		float _scale;
		bool _needsUpdate;
		float _screenWidth;
		float _screenHeight;

	};
}
