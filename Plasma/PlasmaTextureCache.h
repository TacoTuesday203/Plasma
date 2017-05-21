#pragma once
#include "PlasmaImageLoader.h"
#include <map>

namespace Plasma {
	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();

		Texture loadImage(std::string filePath);

	private:
		std::map<std::string, Texture> _textureMap;
	};
}