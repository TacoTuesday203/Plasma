#pragma once

#include <SDL.h>
#include <glew.h>
#include <string>
#include <conio.h>
#include <iostream>

#ifndef PLASMA_WARNING_PREFIX
#define PLASMA_WARNING_PREFIX "Plasma Engine [WARNING] "
#endif

#ifndef PLASMA_ERROR_PREFIX
#define PLASMA_ERROR_PREFIX "Plasma Engine [ERROR] "
#endif

#ifndef PLASMA_CRASH_PREFIX
#define PLASMA_CRASH_PREFIX "Plasma Engine [CRASH] "
#endif

#ifndef PLASMA_LOG_PREFIX
#define PLASMA_LOG_PREFIX "Plasma Engine [LOG] "
#endif

namespace Plasma {
	typedef SDL_Event Event;
	typedef GLubyte SpriteColor[6][4];
	namespace Util {
		enum class GameState {
			PLAY, PAUSE, EXIT, CRASH, OTHER
		};
		enum class Uniform {
			Float, Vec2f, Vec3f, Vec4f, Texture, Camera
		};
	}
	namespace Error {
		extern void warning(std::string msg);
		extern void error(std::string msg, int code);
		extern void crash(std::string msg, int code);
		extern void log(std::string msg);
	}
	extern void init();
	extern void test();
	extern void testGFX();
	extern void quit();
	extern void pause();
	extern void changeBGColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a);
	extern void activeTexture(unsigned int texture);
	extern void enableBlending();
}