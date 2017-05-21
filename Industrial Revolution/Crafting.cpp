#include "Crafting.h"

std::vector<Plasma::Sprite> Crafting::_grid;
std::vector<Recipe> Crafting::_recipes;
float Crafting::_x;
float Crafting::_y;
Slot Crafting::_hover;

ItemType Crafting::_slotOne = ItemType::NONE;
ItemType Crafting::_slotTwo = ItemType::NONE;
ItemType Crafting::_slotThree = ItemType::NONE;
ItemType Crafting::_slotFour = ItemType::NONE;
ItemType Crafting::_slotFive = ItemType::NONE;
ItemType Crafting::_slotSix = ItemType::NONE;
ItemType Crafting::_slotSeven = ItemType::NONE;
ItemType Crafting::_slotEight = ItemType::NONE;
ItemType Crafting::_slotNine = ItemType::NONE;

Item* Crafting::_resultItem = nullptr;

void Crafting::initGrid(float x, float y) {
	_hover = Slot::NONE;
	int Y = 0;
	for (int j = 0; j < 3; j++) {
		int X = 0;
		if (j != 0) { Y += SLOT_HEIGHT+1; }
		for (int i = 0; i < 3; i++) {
			if (i != 0) { X += SLOT_WIDTH+1; }
			_grid.push_back(Plasma::Sprite());
			_grid.back().init(x + X, y + Y, SLOT_WIDTH, SLOT_HEIGHT, PLASMA_COLORSPRITE);
		}
	} 
	_grid.push_back(Plasma::Sprite());
	_grid.back().init(x + SLOT_WIDTH * 4, y + SLOT_HEIGHT, SLOT_WIDTH, SLOT_HEIGHT, PLASMA_COLORSPRITE);
	_x = x; _y = y;
}

void Crafting::drawGrid(Plasma::PlasmaWindow window) {
	if (_hover == Slot::ONE) {
		window.draw(_grid[0], 239, 242, 247, 255);
	}
	else {
		window.draw(_grid[0], 206, 213, 224, 255);
	}
	if (_hover == Slot::TWO) {
		window.draw(_grid[1], 239, 242, 247, 255);
	}
	else {
		window.draw(_grid[1], 206, 213, 224, 255);
	}
	if (_hover == Slot::THREE) {
		window.draw(_grid[2], 239, 242, 247, 255);
	}
	else {
		window.draw(_grid[2], 206, 213, 224, 255);
	}
	if (_hover == Slot::FOUR) {
		window.draw(_grid[3], 239, 242, 247, 255);
	}
	else {
		window.draw(_grid[3], 206, 213, 224, 255);
	}
	if (_hover == Slot::FIVE) {
		window.draw(_grid[4], 239, 242, 247, 255);
	}
	else {
		window.draw(_grid[4], 206, 213, 224, 255);
	}
	if (_hover == Slot::SIX) {
		window.draw(_grid[5], 239, 242, 247, 255);
	}
	else {
		window.draw(_grid[5], 206, 213, 224, 255);
	}
	if (_hover == Slot::SEVEN) {
		window.draw(_grid[6], 239, 242, 247, 255);
	}
	else {
		window.draw(_grid[6], 206, 213, 224, 255);
	}
	if (_hover == Slot::EIGHT) {
		window.draw(_grid[7], 239, 242, 247, 255);
	}
	else {
		window.draw(_grid[7], 206, 213, 224, 255);
	}
	if (_hover == Slot::NINE) {
		window.draw(_grid[8], 239, 242, 247, 255);
	}
	else {
		window.draw(_grid[8], 206, 213, 224, 255);
	}
	if (_hover == Slot::TEN) {
		window.draw(_grid[9], 239, 242, 247, 255);
	}
	else {
		window.draw(_grid[9], 206, 213, 224, 255);
	}
}

Slot Crafting::checkSlots(float x, float y) {
	if (x > _x && x < _x + SLOT_WIDTH && y > _y && y < _y + SLOT_HEIGHT) {
		return Slot::ONE;
	}
	else if (x > _x + SLOT_WIDTH + 1 && x < _x + SLOT_WIDTH * 2 + 1 && y > _y && y < _y + SLOT_HEIGHT) {
		return Slot::TWO;
	}
	else if (x > _x + SLOT_WIDTH * 2 + 1 && x < _x + SLOT_WIDTH * 3 + 1 && y > _y && y < _y + SLOT_HEIGHT) {
		return Slot::THREE;
	}
	else if (x > _x && x < _x + SLOT_WIDTH && y + SLOT_HEIGHT + 1 > _y && y < _y + SLOT_HEIGHT * 2 + 1) {
		return Slot::FOUR;
	}
	else if (x > _x + SLOT_WIDTH + 1 && x < _x + SLOT_WIDTH * 2 + 1 && y + SLOT_HEIGHT + 1 > _y && y < _y + SLOT_HEIGHT * 2 + 1) {
		return Slot::FIVE;
	}
	else if (x > _x + SLOT_WIDTH * 2 + 1 && x < _x + SLOT_WIDTH * 3 + 1 && y + SLOT_HEIGHT + 1 > _y && y < _y + SLOT_HEIGHT * 2 + 1) {
		return Slot::SIX;
	}
	else if (x > _x && x < _x + SLOT_WIDTH && y + SLOT_HEIGHT*2 + 1 > _y && y < _y + SLOT_HEIGHT * 3 + 1) {
		return Slot::SEVEN;
	}
	else if (x > _x + SLOT_WIDTH + 1 && x < _x + SLOT_WIDTH * 2 + 1 && y + SLOT_HEIGHT*2 + 1 > _y && y < _y + SLOT_HEIGHT * 3 + 1) {
		return Slot::EIGHT;
	}
	else if (x > _x + SLOT_WIDTH * 2 + 1 && x < _x + SLOT_WIDTH * 3 + 1 && y + SLOT_HEIGHT*2 + 1 > _y && y < _y + SLOT_HEIGHT * 3 + 1) {
		return Slot::NINE;
	}
	else if (x > _x + SLOT_WIDTH * 4 && x < _x + SLOT_WIDTH * 5 && y > _y + SLOT_HEIGHT && y < _y + SLOT_HEIGHT * 2) {
		return Slot::TEN;
	}
	else {
		return Slot::NONE;
	}
}

void Crafting::updateSlotItems(std::vector<Item> items) {
	bool one = false, two = false, three = false, four = false, five = false, six = false, seven = false, eight = false, nine = false;
	for (int i = 0; i < items.size(); i++) {
		Slot slot = checkSlots(items[i].getPosX(), items[i].getPosY());
		if (!items[i].getMouseFollowState()) {
			if (slot == Slot::ONE) {
				_slotOne = items[i].getItemType();
				one = true;
			}
			if (slot == Slot::TWO) {
				_slotTwo = items[i].getItemType();
				two = true;
			}
			if (slot == Slot::THREE) {
				_slotThree = items[i].getItemType();
				three = true;
			}
			if (slot == Slot::FOUR) {
				_slotFour = items[i].getItemType();
				four = true;
			}
			if (slot == Slot::FIVE) {
				_slotFive = items[i].getItemType();
				five = true;
			}
			if (slot == Slot::SIX) {
				_slotSix = items[i].getItemType();
				six = true;
			}
			if (slot == Slot::SEVEN) {
				_slotSeven = items[i].getItemType();
				seven = true;
			}
			if (slot == Slot::EIGHT) {
				_slotEight = items[i].getItemType();
				eight = true;
			}
			if (slot == Slot::NINE) {
				_slotNine = items[i].getItemType();
				nine = true;
			}
		}
		if (one == false) {
			_slotOne = ItemType::NONE;
		}
		if (two == false) {
			_slotTwo = ItemType::NONE;
		}
		if (three == false) {
			_slotThree = ItemType::NONE;
		}
		if (four == false) {
			_slotFour = ItemType::NONE;
		}
		if (five == false) {
			_slotFive = ItemType::NONE;
		}
		if (six == false) {
			_slotSix = ItemType::NONE;
		}
		if (seven == false) {
			_slotSeven = ItemType::NONE;
		}
		if (eight == false) {
			_slotEight = ItemType::NONE;
		}
		if (nine == false) {
			_slotNine = ItemType::NONE;
		}
	}
}

bool Crafting::slotAvailable(Slot slot) {
	switch (slot) {
	case Slot::ONE:
		if (_slotOne != ItemType::NONE) {
			return false;
		}
		else {
			return true;
		}
		break;
	case Slot::TWO:
		if (_slotTwo != ItemType::NONE) {
			return false;
		}
		else {
			return true;
		}
		break;
	case Slot::THREE:
		if (_slotThree != ItemType::NONE) {
			return false;
		}
		else {
			return true;
		}
		break;
	case Slot::FOUR:
		if (_slotFour != ItemType::NONE) {
			return false;
		}
		else {
			return true;
		}
		break;
	case Slot::FIVE:
		if (_slotFive != ItemType::NONE) {
			return false;
		}
		else {
			return true;
		}
		break;
	case Slot::SIX:
		if (_slotSix != ItemType::NONE) {
			return false;
		}
		else {
			return true;
		}
		break;
	case Slot::SEVEN:
		if (_slotSeven != ItemType::NONE) {
			return false;
		}
		else {
			return true;
		}
		break;
	case Slot::EIGHT:
		if (_slotEight != ItemType::NONE) {
			return false;
		}
		else {
			return true;
		}
		break;
	case Slot::NINE:
		if (_slotNine != ItemType::NONE) {
			return false;
		}
		else {
			return true;
		}
		break;
	}
}

void Crafting::setHover(Slot hover) {
	_hover = hover;
}

void Crafting::addRecipe(Recipe recipe) {
	_recipes.push_back(recipe);
}

void Crafting::checkRecipes(std::vector<Item>* items) {
	bool noRecipes = true;
	for (int i = 0; i < _recipes.size(); i++) {
		if (_slotOne == _recipes[i].one && _slotTwo == _recipes[i].two && _slotThree == _recipes[i].three && _slotFour == _recipes[i].four && _slotFive == _recipes[i].five && _slotSix == _recipes[i].six && _slotSeven == _recipes[i].seven && _slotEight == _recipes[i].eight && _slotNine == _recipes[i].nine) {
			noRecipes = false;
			if (_resultItem == nullptr) {
				items->push_back(Item(_recipes[i].yield, _x + SLOT_WIDTH * 4, _y + SLOT_HEIGHT));
				_resultItem = &items->back();
			}
			if (_resultItem->getMouseFollowState()) {
				_resultItem = nullptr;
			}
			for (int i = 0; i <= items->size(); i++) {
				if (_resultItem == nullptr) {
					if (eraseItem(items) != true) {
						break;
					}
				}
			}
		}
	}
	if (noRecipes == true) {
		std::cout << ".";
		for (int i = 0; i < items->size(); i++) {
			int x = (*items)[i].getPosX();
			int y = (*items)[i].getPosY();
			if (checkSlots(x, y) == Slot::TEN && (*items)[i].getMouseFollowState() == false) {
				std::cout << "TRUE" << std::endl;
				items->erase(items->begin() + i);
				break;
			}
		}
	}
}

Recipe Crafting::createRecipe(ItemType one, ItemType two, ItemType three, ItemType four, ItemType five, ItemType six, ItemType seven, ItemType eight, ItemType nine, ItemType result) {
	Recipe r;
	r.one = one;
	r.two = two;
	r.three = three;
	r.four = four;
	r.five = five;
	r.six = six;
	r.seven = seven;
	r.eight = eight;
	r.nine = nine;
	r.yield = result;
	return r;
}

// The eraseItem function is kind of a buggy function that erases the first item in a vector that meets a certain condition
bool Crafting::eraseItem(std::vector<Item>* items) {
	for (int i = 0; i < items->size(); i++) {
		int x = (*items)[i].getPosX();
		int y = (*items)[i].getPosY();
		if (checkSlots(x, y) != Slot::NONE && checkSlots(x, y) != Slot::TEN) {
			items->erase(items->begin() + i);
			return true;
		}
	}
	return false;
}