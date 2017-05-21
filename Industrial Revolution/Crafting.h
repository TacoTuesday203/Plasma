#pragma once
#include <Plasma.h>
#include <PlasmaWindow.h>
#include "Item.h"

#define SLOT_WIDTH 150.0f
#define SLOT_HEIGHT 150.0f

enum class Slot {
	ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, NONE
};

struct Recipe {
	ItemType one;
	ItemType two;
	ItemType three;
	ItemType four;
	ItemType five;
	ItemType six;
	ItemType seven;
	ItemType eight;
	ItemType nine;
	ItemType yield;
};

class Crafting
{
public:
	static void initGrid(float x, float y);
	static void drawGrid(Plasma::PlasmaWindow window);
	static Slot checkSlots(float x, float y);
	static void setHover(Slot hover);
	static void updateSlotItems(std::vector<Item> items);
	static bool slotAvailable(Slot slot);
	static void addRecipe(Recipe recipe);
	static void checkRecipes(std::vector<Item>* items);
	static Recipe createRecipe(ItemType one, ItemType two, ItemType three, ItemType four, ItemType five, ItemType six, ItemType seven, ItemType eight, ItemType nine, ItemType result);
private:
	static std::vector<Plasma::Sprite> _grid;
	static std::vector<Recipe> _recipes;
	static float _x;
	static float _y;
	static Slot _hover;
	static ItemType _slotOne;
	static ItemType _slotTwo;
	static ItemType _slotThree;
	static ItemType _slotFour;
	static ItemType _slotFive;
	static ItemType _slotSix;
	static ItemType _slotSeven;
	static ItemType _slotEight;
	static ItemType _slotNine;
	static Item* _resultItem;
	static bool eraseItem(std::vector<Item>* items);
};

