#pragma once

#include <Plasma.h>
#include <PlasmaSprite.h>

enum class ItemType {
	APPLE, PEAR, FRUITSALAD, NONE
};

class Item : public Plasma::Sprite
{
public:
	Item(ItemType item, float x, float y);
	~Item();

	void toggleMouseFollow() {
		if (!_shouldFollowMouse) { 
			_shouldFollowMouse = true;
		}
		else {
			_shouldFollowMouse = false;
		}
	}

	bool getMouseFollowState() { return _shouldFollowMouse; }

	ItemType getItemType() { return _itemType; }

	bool checkHovering(float mouseX, float mouseY);

private:
	bool _shouldFollowMouse = false;
	ItemType _itemType;
};

