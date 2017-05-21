#include "PlasmaSprite.h"

namespace Plasma {
	Sprite::Sprite()
	{
	}


	Sprite::~Sprite()
	{
	}

	void Sprite::init(float x, float y, float w, float h, unsigned int type, std::string texturePath) {
		_type = type;
		if (_type < 0 || _type > 1) {
			Plasma::Error::error("Sprite type is invalid!", 6);
		}
		if (texturePath == "NONE" && type == PLASMA_TEXTURESPRITE) {
			Error::warning("No texture path provided!");
			return;
		}
		else if (texturePath != "NONE" && type == PLASMA_TEXTURESPRITE) {
			_texture = ResourceManager::loadImage(texturePath);
		}
		_x = x;
		_y = y;
		_w = w;
		_h = h;
		glGenBuffers(1, &_vbo);
		_init = true;
	}

	void Sprite::draw(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
		if (_init) {
			Vertex vertex[6];

			vertex[0].setPos(_x, _y);
			vertex[0].setUV(0.0f, 0.0f);

			vertex[1].setPos(_x, _y + _h);
			vertex[1].setUV(0.0f, 1.0f);

			vertex[2].setPos(_x + _w, _y);
			vertex[2].setUV(1.0f, 0.0f);

			vertex[3].setPos(_x + _w, _y);
			vertex[3].setUV(1.0f, 0.0f);

			vertex[4].setPos(_x + _w, _y + _h);
			vertex[4].setUV(1.0f, 1.0f);

			vertex[5].setPos(_x, _y + _h);
			vertex[5].setUV(0.0f, 1.0f);

			for (int i = 0; i < 6; i++) {
				vertex[i].setCol(r, g, b, a);
			}

			glBindBuffer(GL_ARRAY_BUFFER, _vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

			if (_type == PLASMA_TEXTURESPRITE) {
				glBindTexture(GL_TEXTURE_2D, _texture.id);
			}

			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);

			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
			glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, col));
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

			glDrawArrays(GL_TRIANGLES, 0, 6);

			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(2);

			if (_type == PLASMA_TEXTURESPRITE) {
				glBindTexture(GL_TEXTURE_2D, 0);
			}

			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		else {
			Error::error("This sprite hasn't been initialized!", 11);
		}
	}

	void Sprite::draw(SpriteColor color) {
		if (_init) {
			Vertex vertex[6];

			vertex[0].setPos(_x, _y);
			vertex[0].setUV(0.0f, 0.0f);

			vertex[1].setPos(_x, _y + _h);
			vertex[1].setUV(0.0f, 1.0f);

			vertex[2].setPos(_x + _w, _y);
			vertex[2].setUV(1.0f, 0.0f);

			vertex[3].setPos(_x + _w, _y);
			vertex[3].setUV(1.0f, 0.0f);

			vertex[4].setPos(_x + _w, _y + _h);
			vertex[4].setUV(1.0f, 1.0f);

			vertex[5].setPos(_x, _y + _h);
			vertex[5].setUV(0.0f, 1.0f);

			for (int i = 0; i < 6; i++) {
				vertex[i].setCol(color[i][0], color[i][1], color[i][2], color[i][3]);
			}

			glBindBuffer(GL_ARRAY_BUFFER, _vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

			if (_type == PLASMA_TEXTURESPRITE) {
				glBindTexture(GL_TEXTURE_2D, _texture.id);
			}

			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);

			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
			glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, col));
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

			glDrawArrays(GL_TRIANGLES, 0, 6);

			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(2);

			if (_type == PLASMA_TEXTURESPRITE) {
				glBindTexture(GL_TEXTURE_2D, 0);
			}

			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		else {
			Error::error("This sprite hasn't been initialized!", 11);
		}
	}

	bool operator==(Sprite& T1, Sprite& T2) {
		if (T1.getVBO() == T2.getVBO()) {
			return true;
		}
		else {
			return false;
		}
	}

}