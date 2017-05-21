#pragma once

#include <glew.h>
#include <string>
#include <iostream>
#include <conio.h>
#include <fstream>
#include <sstream>
#include "Plasma.h"
#include "PlasmaCamera.h"

namespace Plasma {
	class Shader
	{
	public:
		Shader();
		~Shader();

		void initShader(const std::string vertFilePath, const std::string fragFilePath);
		void initHardcodeShader(std::string vertFileSrc, std::string fragFileSrc);

		void start();
		void end();

		void uploadTexture(std::string name);
		void uploadCamera(std::string name, Camera camera);

		GLint getUniformLocation(std::string uniform);

	private:

		void compile();
		void compileShader(std::string path, GLuint shader);
		void compileHardcodeShader(std::string shaderSrc, GLuint shader);

		void variable(std::string attribName);

		GLint _shaderProgram;

		GLuint _vertShader;
		GLuint _fragShader;

		int _numAttribs = 0;

	};
}
