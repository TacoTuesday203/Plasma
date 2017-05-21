#pragma once
#include "PlasmaTextureCache.h"

namespace Plasma {
	class ResourceManager
	{
	public:
		static Texture loadImage(std::string filePath);
	private:
		static TextureCache _cache;
	};
}
