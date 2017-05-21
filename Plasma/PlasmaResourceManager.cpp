#include "PlasmaResourceManager.h"

namespace Plasma {

	TextureCache ResourceManager::_cache;

	Texture ResourceManager::loadImage(std::string filePath) {
		return _cache.loadImage(filePath);
	}
}