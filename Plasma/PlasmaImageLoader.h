#pragma once
#include <glew.h>
#include "PlasmaTexture.h"
#include "PlasmaIO.h"
#include "picoPNG.h"

namespace Plasma {
	class ImageLoader
	{
	public:
		static Texture loadImage(std::string filePath);
	};
}

