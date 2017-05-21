#include "Plasma.h"

namespace Plasma {
	namespace Error {
		void warning(std::string msg) {
			std::cout << PLASMA_WARNING_PREFIX << msg << std::endl;
		}
		void error(std::string msg, int code) {
			std::cout << PLASMA_ERROR_PREFIX << msg << "(" << code << ")" << std::endl;
			_getch();
		}
		void crash(std::string msg, int code) {
			std::cout << PLASMA_CRASH_PREFIX << msg << "(" << code << ")" << std::endl;
			_getch();
			exit(code);
		}
		void log(std::string msg) {
			std::cout << PLASMA_LOG_PREFIX << msg << std::endl;
		}
	}
	void init() {
		Error::log("This game was made using Plasma Engine");
		Error::log("Initializing Plasma Engine...");
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
			Error::crash("A critical error occurred while starting SDL.", 1);
		}
		else {
			Error::log("SDL done, no errors.");
		}
		Error::log("Plasma initialization completed!");
	}
	void test() {
		Error::log("Plasma is working!");
	}
	void testGFX() {
		glBegin(GL_TRIANGLES);
		{
			glColor4f(1.0f, 0.0f, 0.0f, 1.0f);

			glVertex3f(-0.5f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.5f, 0.0f);
			glVertex3f(0.5f, 0.0f, 0.0f);
		}
		glEnd();
	}
	void quit() {
		Error::log("Goodbye!");
		SDL_Quit();
		exit(0);
	}
	void pause() {
		_getch();
	}
	void changeBGColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a /*colors between 0.0 - 1.0*/) {
		glClearColor(r, g, b, a);
	}
	void activeTexture(unsigned int texture) {
		switch (texture) {
		case 0:
			glActiveTexture(GL_TEXTURE0);
			break;
		case 1:
			glActiveTexture(GL_TEXTURE1);
			break;
		case 2:
			glActiveTexture(GL_TEXTURE2);
			break;
		case 3:
			glActiveTexture(GL_TEXTURE3);
			break;
		case 4:
			glActiveTexture(GL_TEXTURE4);
			break;
		case 5:
			glActiveTexture(GL_TEXTURE5);
			break;
		case 6:
			glActiveTexture(GL_TEXTURE6);
			break;
		case 7:
			glActiveTexture(GL_TEXTURE7);
			break;
		case 8:
			glActiveTexture(GL_TEXTURE8);
			break;
		case 9:
			glActiveTexture(GL_TEXTURE9);
			break;
		case 10:
			glActiveTexture(GL_TEXTURE10);
			break;
		case 11:
			glActiveTexture(GL_TEXTURE11);
			break;
		case 12:
			glActiveTexture(GL_TEXTURE12);
			break;
		case 13:
			glActiveTexture(GL_TEXTURE13);
			break;
		case 14:
			glActiveTexture(GL_TEXTURE14);
			break;
		case 15:
			glActiveTexture(GL_TEXTURE15);
			break;
		case 16:
			glActiveTexture(GL_TEXTURE16);
			break;
		case 17:
			glActiveTexture(GL_TEXTURE17);
			break;
		case 18:
			glActiveTexture(GL_TEXTURE18);
			break;
		case 19:
			glActiveTexture(GL_TEXTURE19);
			break;
		case 20:
			glActiveTexture(GL_TEXTURE20);
			break;
		case 21:
			glActiveTexture(GL_TEXTURE21);
			break;
		case 22:
			glActiveTexture(GL_TEXTURE22);
			break;
		case 23:
			glActiveTexture(GL_TEXTURE23);
			break;
		case 24:
			glActiveTexture(GL_TEXTURE24);
			break;
		case 25:
			glActiveTexture(GL_TEXTURE25);
			break;
		case 26:
			glActiveTexture(GL_TEXTURE26);
			break;
		case 27:
			glActiveTexture(GL_TEXTURE27);
			break;
		case 28:
			glActiveTexture(GL_TEXTURE28);
			break;
		case 29:
			glActiveTexture(GL_TEXTURE29);
			break;
		case 30:
			glActiveTexture(GL_TEXTURE30);
			break;
		case 31:
			glActiveTexture(GL_TEXTURE31);
			break;
		}
	}
	void enableBlending() {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
}