#pragma once

#include "Plasma.h"
#include "PlasmaSprite.h"
#include "PlasmaShader.h"
#include "PlasmaCamera.h"

#define PLASMA_WINDOW_CENTERED SDL_WINDOWPOS_CENTERED
#define PLASMA_FULLSCREEN SDL_WINDOW_FULLSCREEN

namespace Plasma {
	class PlasmaWindow
	{
	public:
		PlasmaWindow();
		~PlasmaWindow();

		void init(const char* title, float x, float y, float w, float h, unsigned int flags = SDL_WINDOW_OPENGL, std::string shaderCamera = "camera", std::string shaderTexture = "");
		SDL_Event processInput();
		void update(Camera camera);
		void swap();

		void draw(Sprite sprite, Shader* shader = nullptr);
		void draw(Sprite sprite, SpriteColor color, Shader* shader = nullptr);
		void draw(Sprite sprite, GLubyte r, GLubyte g, GLubyte b, GLubyte a, Shader* shader = nullptr);

		char getKeypress(Event evnt);
		bool getExitButton(Event evnt);
		glm::vec2 getMousePos();
		bool getMouseclick(Event evnt);

	private:
		SDL_Window* _window;
		Camera _camera;
		bool _init = false;
		Shader _colorShader;
		Shader _textureShader;
		
		std::string _shaderCamera;
		std::string _shaderTexture;
	};
}
