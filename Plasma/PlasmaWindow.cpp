#include "PlasmaWindow.h"

namespace Plasma {
	PlasmaWindow::PlasmaWindow()
	{
	}


	PlasmaWindow::~PlasmaWindow()
	{
	}

	void PlasmaWindow::init(const char* title, float x, float y, float w, float h, unsigned int flags, std::string shaderCamera, std::string shaderTexture) {
		Error::log("Initializing a new window...");
		_shaderCamera = shaderCamera;
		_shaderTexture = shaderTexture;
		_window = nullptr;
		flags |= SDL_WINDOW_OPENGL;
		_window = SDL_CreateWindow(title, x, y, w, h, flags);
		if (_window == nullptr) {
			Error::crash("Unable to create SDL window.", 3);
		}
		SDL_GLContext context = nullptr;
		context = SDL_GL_CreateContext(_window);
		if (context == nullptr) {
			Error::crash("Unable to create GL context for SDL window.", 5);
		}
		if (glewInit() != GLEW_OK) {
			Error::warning("An error occurred while starting GLEW (not fatal)");
		}
		else {
			Error::log("GLEW done, no errors.");
		}

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		Error::log("SDL window created with no errors.");

		std::string colorVert = "in vec2 vert_Pos;\nin vec4 vert_Col;\nin vec2 vert_UV;\nout vec4 frag_Col;\nout vec2 frag_UV;\nuniform mat4 camera;\nvoid main() {\ngl_Position = camera * vec4(vert_Pos, 0.0, 1.0);\nfrag_Col = vert_Col;\nfrag_UV = vec2(vert_UV.x, 1.0 - vert_UV.y);\n}";
		std::string colorFrag = "in vec4 frag_Col;\nin vec2 frag_UV;\nout vec4 final_Col;\nvoid main() {\nfinal_Col = frag_Col;\n}";

		_colorShader.initHardcodeShader(colorVert, colorFrag);

		std::string textureVert = "in vec2 vert_Pos;\nin vec4 vert_Col;\nin vec2 vert_UV;\nout vec4 frag_Col;\nout vec2 frag_UV;\nuniform mat4 camera;\nvoid main() {\ngl_Position = camera * vec4(vert_Pos, 0.0, 1.0);\nfrag_Col = vert_Col;\nfrag_UV = vec2(vert_UV.x, 1.0 - vert_UV.y);\n}";
		std::string textureFrag = "in vec4 frag_Col;\nin vec2 frag_UV;\nout vec4 final_Col;\nuniform sampler2D textureSampler;\nvoid main() {\nfinal_Col = texture(textureSampler, frag_UV) * frag_Col;\n}";

		_textureShader.initHardcodeShader(textureVert, textureFrag);

		_init = true;
	}

	SDL_Event PlasmaWindow::processInput() {
		if (_init) {
			SDL_Event evnt;
			SDL_PollEvent(&evnt);
			return evnt;
		}
		else {
			Error::error("This window hasn't been initialized!", 4);
		}
	}
	void PlasmaWindow::update(Camera camera) {
		if (_init) {
			glClearDepth(1.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			_camera = camera;
		}
		else {
			Error::error("This window hasn't been initialized!", 4);
		}
	}

	void PlasmaWindow::swap() {
		if (_init) {
			SDL_GL_SwapWindow(_window);
		}
		else {
			Error::error("This window hasn't been initialized!", 4);
		}
	}
	char PlasmaWindow::getKeypress(Event evnt) {
		if (_init) {
			if (evnt.type == SDL_KEYDOWN) {
				return evnt.key.keysym.sym;
			}
			else {
				return NULL;
			}
		}
		else {
			Error::error("This window hasn't been initialized!", 4);
		}
	}
	bool PlasmaWindow::getExitButton(Event evnt) {
		if (_init) {
			if (evnt.type == SDL_QUIT) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			Error::error("This window hasn't been initialized!", 4);
		}
	}

	glm::vec2 PlasmaWindow::getMousePos() {
		if (_init) {
			/*if (evnt.type == SDL_MOUSEMOTION) {
				glm::vec2 screenPos(evnt.x, evnt.motion.y);
				return _camera.screenToWorld(screenPos);
			}
			else {
				//return glm::vec2(0.0f, 0.0f);
			}*/
			int x, y;
			SDL_GetMouseState(&x, &y);
			return _camera.screenToWorld(glm::vec2(x, y));
		}
		else {
			Error::error("This window hasn't been initialized!", 4);
		}
	}

	bool PlasmaWindow::getMouseclick(Event evnt) {
		if (_init) {
			if (evnt.type == SDL_MOUSEBUTTONDOWN) {
				return true;
			}
			return false;
		}
		else {
			Error::error("This window hasn't been initialized!", 4);
		}
	}

	void PlasmaWindow::draw(Sprite sprite, Shader* shader) {
		if (sprite.getType() == PLASMA_COLORSPRITE && shader == nullptr) {
			_colorShader.start();
			_colorShader.uploadCamera("camera", _camera);
		}
		else if (sprite.getType() == PLASMA_TEXTURESPRITE && shader == nullptr) {
			activeTexture(0);
			_textureShader.start();
			_textureShader.uploadTexture("textureSampler");
			_textureShader.uploadCamera("camera", _camera);
		}
		else {
			shader->start();
			shader->uploadCamera(_shaderCamera, _camera);
			if (_shaderTexture != "") {
				shader->uploadTexture(_shaderTexture);
			}
		}

		sprite.draw();

		if (sprite.getType() == PLASMA_COLORSPRITE && shader == nullptr) {
			_colorShader.end();
		}
		else if (sprite.getType() == PLASMA_TEXTURESPRITE && shader == nullptr) {
			_textureShader.end();
		}
		else {
			shader->end();
		}
	}

	void PlasmaWindow::draw(Sprite sprite, SpriteColor color, Shader* shader) {
		if (sprite.getType() == PLASMA_COLORSPRITE && shader == nullptr) {
			_colorShader.start();
			_colorShader.uploadCamera("camera", _camera);
		}
		else if (sprite.getType() == PLASMA_TEXTURESPRITE && shader == nullptr) {
			_textureShader.start();
			_textureShader.uploadTexture("textureSampler");
			_textureShader.uploadCamera("camera", _camera);
		}
		else {
			shader->start();
			shader->uploadCamera(_shaderCamera, _camera);
			if (_shaderTexture != "") {
				shader->uploadTexture(_shaderTexture);
			}
		}

		sprite.draw(color);

		if (sprite.getType() == PLASMA_COLORSPRITE && shader == nullptr) {
			_colorShader.end();
		}
		else if (sprite.getType() == PLASMA_TEXTURESPRITE && shader == nullptr) {
			_textureShader.end();
		}
		else {
			shader->end();
		}
	}
	void PlasmaWindow::draw(Sprite sprite, GLubyte r, GLubyte g, GLubyte b, GLubyte a, Shader* shader) {
		if (sprite.getType() == PLASMA_COLORSPRITE && shader == nullptr) {
			_colorShader.start();
			_colorShader.uploadCamera("camera", _camera);
		}
		else if (sprite.getType() == PLASMA_TEXTURESPRITE && shader == nullptr) {
			_textureShader.start();
			_textureShader.uploadTexture("textureSampler");
			_textureShader.uploadCamera("camera", _camera);
		}
		else {
			shader->start();
			shader->uploadCamera(_shaderCamera, _camera);
			if (_shaderTexture != "") {
				shader->uploadTexture(_shaderTexture);
			}
		}

		sprite.draw(r, g, b, a);

		if (sprite.getType() == PLASMA_COLORSPRITE && shader == nullptr) {
			_colorShader.end();
		}
		else if (sprite.getType() == PLASMA_TEXTURESPRITE && shader == nullptr) {
			_textureShader.end();
		}
		else {
			shader->end();
		}
	}
}