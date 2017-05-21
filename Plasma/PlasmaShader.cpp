#include "PlasmaShader.h"

namespace Plasma {
	Shader::Shader()
	{
	}


	Shader::~Shader()
	{
	}

	void Shader::initShader(const std::string vertFilePath, const std::string fragFilePath) {

		Error::log("Creating shaders...");

		_shaderProgram = glCreateProgram();

		_vertShader = glCreateShader(GL_VERTEX_SHADER);
		_fragShader = glCreateShader(GL_FRAGMENT_SHADER);

		compileShader(vertFilePath, _vertShader);
		compileShader(fragFilePath, _fragShader);

		variable("vert_Pos");
		variable("vert_Col");
		variable("vert_UV");

		compile();


		Error::log("Created a new shader.");

	}

	void Shader::initHardcodeShader(std::string vertFileSrc, std::string fragFileSrc) {

		Error::log("Creating shaders...");

		_shaderProgram = glCreateProgram();

		_vertShader = glCreateShader(GL_VERTEX_SHADER);
		_fragShader = glCreateShader(GL_FRAGMENT_SHADER);

		compileHardcodeShader(vertFileSrc, _vertShader);
		compileHardcodeShader(fragFileSrc, _fragShader);

		variable("vert_Pos");
		variable("vert_Col");
		variable("vert_UV");

		compile();


		Error::log("Created a new shader.");

	}

	void Shader::compile() {

		glAttachShader(_shaderProgram, _vertShader);
		glAttachShader(_shaderProgram, _fragShader);

		glLinkProgram(_shaderProgram);

		GLchar* programInfoLog;
		int programIsCompiled = 0;

		glGetProgramiv(_shaderProgram, GL_LINK_STATUS, (int*)&programIsCompiled);
		if (programIsCompiled == 0) {
			int maxLength;
			glGetProgramiv(_shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);

			programInfoLog = (char*)malloc(maxLength);

			glGetProgramInfoLog(_shaderProgram, maxLength, &maxLength, programInfoLog);
			std::cout << programInfoLog << std::endl << std::endl;
			Error::crash("Please fix all shader issues and restart the program.", 7);

		}

		glDetachShader(_shaderProgram, _vertShader);
		glDetachShader(_shaderProgram, _fragShader);
	}

	void Shader::compileShader(std::string path, GLuint shader) {

		std::string shaderSrc;
		std::string line;

		std::ifstream loadShader(path);
		if (loadShader.fail()) {
			Error::crash("Unable to find shader: " + path, 9);
		}

		while (!loadShader.eof()) {
			std::getline(loadShader, line);
			shaderSrc += line + "\n";
		}

		const char* shaderSrcPtr = shaderSrc.c_str();

		glShaderSource(shader, 1, &shaderSrcPtr, nullptr);
		glCompileShader(shader);

		GLchar* infoLog;
		int isCompiled = 0;

		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == 0) {
			int maxLength;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			infoLog = (char*)malloc(maxLength);

			glGetShaderInfoLog(shader, maxLength, &maxLength, infoLog);

			Error::log("Shader " + path + " has experienced an issue: ");
			std::cout << infoLog << std::endl;
		}
	}

	void Shader::compileHardcodeShader(std::string shaderSrc, GLuint shader) {
		const char* shaderSrcPtr = shaderSrc.c_str();

		glShaderSource(shader, 1, &shaderSrcPtr, nullptr);
		glCompileShader(shader);

		GLchar* infoLog;
		int isCompiled = 0;

		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == 0) {
			int maxLength;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			infoLog = (char*)malloc(maxLength);

			glGetShaderInfoLog(shader, maxLength, &maxLength, infoLog);

			Error::log("Hardcoded Shader has experienced an issue: ");
			std::cout << infoLog << std::endl;
			Error::log("If you're seeing this, you've encountered a bug. Please download the latest version of Plasma.");
		}
	}

	GLint Shader::getUniformLocation(std::string uniform) {
		GLint location = glGetUniformLocation(_shaderProgram, uniform.c_str());
		if (location == GL_INVALID_INDEX) {
			Error::error("Could not find uniform in shader: " + uniform, 8);
		}
		return location;
	}

	void Shader::variable(std::string attribName) {
		glBindAttribLocation(_shaderProgram, _numAttribs++, attribName.c_str());
	}

	void Shader::start() {
		glUseProgram(_shaderProgram);
	}

	void Shader::end() {
		glUseProgram(0);
	}

	void Shader::uploadTexture(std::string name) {
		glUniform1i(getUniformLocation(name), 0);
	}

	void Shader::uploadCamera(std::string name, Camera camera) {
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &camera.getCameraMatrix()[0][0]);
	}
}