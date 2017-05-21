#include "PlasmaImageLoader.h"

namespace Plasma {
	Texture ImageLoader::loadImage(std::string filePath) {
		Texture tex = {};
		std::vector<unsigned char> in;
		std::vector<unsigned char> out;
		unsigned long width, height;

		if (!IO::readFileToBuffer(filePath, in)) {
			Error::warning("Image " + filePath + " not found");
			return tex;
		}

		int error = decodePNG(out, width, height, &in[0], in.size(), true);
		if (error != 0) {
			Error::crash("Corrupted PNG file: " + filePath, 10);
		}

		glGenTextures(1, &tex.id);
		glBindTexture(GL_TEXTURE_2D, tex.id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &out[0]);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

		tex.width = width;
		tex.height = height;

		return tex;
	}
}