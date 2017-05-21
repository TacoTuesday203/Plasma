#pragma once

#include "Plasma.h"
#include "PlasmaVertex.h"
#include "PlasmaResourceManager.h"
#include <glew.h>
#include <map>

#define PLASMA_COLORSPRITE 0
#define PLASMA_TEXTURESPRITE 1

namespace Plasma {
	class Sprite
	{
	public:
		Sprite();
		~Sprite();

		void init(float x, float y, float w, float h, unsigned int type, std::string texturePath = "NONE");
		void draw(GLubyte r = 255, GLubyte g = 255, GLubyte b = 255, GLubyte a = 255);
		void draw(SpriteColor color);

		void setPos(float x, float y) { _x = x; _y = y; }
		void addPos(float x, float y) { _x += x; _y += y; }

		float getPosX() { return _x; }
		float getPosY() { return _y; }

		float getPosW() { return _w; }
		float getPosH() { return _h; }

		unsigned int getType() { return _type; }

		GLuint getVBO() { return _vbo; }

	private:
		GLuint _vbo;
		float _x;
		float _y;
		float _w;
		float _h;
		unsigned int _type;
		Texture _texture;
		bool _init;
	};


	bool operator==(Sprite& T1, Sprite& T2);

}

