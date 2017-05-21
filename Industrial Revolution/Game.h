#pragma once

#include <Plasma.h>
#include <PlasmaWindow.h>
#include <PlasmaSprite.h>
#include <PlasmaShader.h>
#include "Crafting.h"
#include "Item.h"

#define VERSION_MAJOR 1
#define VERSION_MINOR 2
#define VERSION_PATCH 2

class Game
{
public:
	Game();
	~Game();

	void init();
	void gameLoop();
	void processInput();
	void draw();
private:
	Plasma::PlasmaWindow _window;
	Plasma::Camera _camera;
	Plasma::Util::GameState _gameState;
	std::vector<Item> _items;
	void spawnItem();
	bool canMouseToggle(Slot slot);
	void registerItems();
};

