#pragma once
#include <glew.h>

namespace Plasma {
	struct Pos {
		float x;
		float y;
		
	};

	struct Color {
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;
		
	};

	struct UV {
		float u;
		float v;
		
	};

	struct Vertex {
		Pos pos;
		Color col;
		UV uv;
		void setPos(float X, float Y) { pos.x = X; pos.y = Y; }
		void setCol(GLubyte R, GLubyte G, GLubyte B, GLubyte A) { col.r = R; col.g = G;col.b = B; col.a = A; }
		void setUV(float U, float V) { uv.u = U; uv.v = V; }
	};
}