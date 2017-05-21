#include "PlasmaTextureCache.h"

namespace Plasma {
	TextureCache::TextureCache()
	{
	}


	TextureCache::~TextureCache()
	{
	}

	Texture TextureCache::loadImage(std::string filePath) {
		auto mit = _textureMap.find(filePath);
		if (mit == _textureMap.end()) {
			Texture newTex = ImageLoader::loadImage(filePath);
			_textureMap.insert(make_pair(filePath, newTex));
			return newTex;
		}
		return mit->second;
	}
}