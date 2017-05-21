#include "Item.h"



Item::Item(ItemType item, float x, float y)
{
	_itemType = item;
	switch (item) {
	case ItemType::APPLE:
		init(x, y, 50.0f, 50.0f, PLASMA_TEXTURESPRITE, "textures/apple.png");
		break;
	case ItemType::PEAR:
		init(x, y, 50.0f, 50.0f, PLASMA_TEXTURESPRITE, "textures/pear.png");
		break;
	case ItemType::FRUITSALAD:
		init(x, y, 50.0f, 50.0f, PLASMA_TEXTURESPRITE, "textures/fruitsalad.png");
		break;
	default:
		Plasma::Error::crash("Unknown item type!", -1);
	}
}


Item::~Item()
{
}

bool Item::checkHovering(float mouseX, float mouseY) {
	float x = getPosX();
	float y = getPosY();
	float w = getPosW();
	float h = getPosH();
	if (mouseX > x && mouseX < x + w && mouseY > y && mouseY < y + h) {
		return true;
	}
	else {
		return false;
	}
}