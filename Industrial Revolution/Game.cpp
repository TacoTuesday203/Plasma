#include "Game.h"



Game::Game()
{
}


Game::~Game()
{
}

void Game::init() {
	Plasma::test();
	Plasma::init();
	_window.init("Industrial Revolution", PLASMA_WINDOW_CENTERED, PLASMA_WINDOW_CENTERED, 1024, 768);
	_camera.init(1024, 768);
	_gameState = Plasma::Util::GameState::PLAY;
	Plasma::changeBGColor(78.0f/255.0f, 79.0f/255.0f, 81.0f/255.0f, 1.0f);
	Plasma::enableBlending();
	Item* init;
	for (int i = 0; i < sizeof(ItemType)-1; i++) {
		init = new Item(static_cast<ItemType>(i), 0.0f, 0.0f);
	}
	delete init;
	Crafting::initGrid(50.0f, 768/2 - (SLOT_HEIGHT*3+3)/2);
	registerItems();
}

void Game::gameLoop() {
	while (_gameState == Plasma::Util::GameState::PLAY) {
		_camera.update();
		Crafting::updateSlotItems(_items);
		Crafting::checkRecipes(&_items);
		processInput();
		draw();
	}
	Plasma::quit();
}

void Game::processInput() {
	Plasma::Event evnt = _window.processInput();
	if (_window.getExitButton(evnt)) {
		_gameState = Plasma::Util::GameState::EXIT;
	}
	char keypress = _window.getKeypress(evnt);
	if (keypress != NULL) {
		switch (keypress) {
		case 'e':
			spawnItem();
			break;
		case 'r':
			_items.clear();
			break;
		}
	}
	glm::vec2 mouse = _window.getMousePos();
	Slot hover = Crafting::checkSlots(mouse.x, mouse.y);
	Crafting::setHover(hover);
	bool mouseClick = _window.getMouseclick(evnt);
	bool itemHovering = false;
	if (mouseClick == true) {
		for (int i = 0; i < _items.size(); i++) {
			if (_items[i].checkHovering(mouse.x, mouse.y)) {
				if (_items[i].getMouseFollowState() == true && !canMouseToggle(hover)) {
					// what should happen if the item can't be placed?
				}
				else {
					_items[i].toggleMouseFollow();
					break;
				}
			}
		}
	}
	for (int i = 0; i < _items.size(); i++) {
		if (_items[i].getMouseFollowState()) {
			_items[i].setPos(mouse.x - 10.0f, mouse.y - 10.0f);
		}
	}
}


void Game::draw() {
	_window.update(_camera);
	Crafting::drawGrid(_window);
	for (int i = 0; i < _items.size(); i++) {
		_window.draw(_items[i]);
	}
	_window.swap();
}

void Game::spawnItem() {
	bool commandline = true;
	while (commandline) {
		std::string itemSpawn, x, y;
		std::cout << "Enter the name of an item to spawn: ";
		std::getline(std::cin, itemSpawn);
		std::cout << "X: ";
		std::getline(std::cin, x);
		std::cout << "Y: ";
		std::getline(std::cin, y);
		try {
			int X = stoi(x);
		}
		catch (std::invalid_argument& e) {
			std::cout << "Not a number, please try again." << std::endl;
			continue;
		}
		try {
			int Y = stoi(y);
		}
		catch (std::invalid_argument& e) {
			std::cout << "Not a number, please try again." << std::endl;
			continue;
		}
		if (itemSpawn == "apple") {
			_items.push_back(Item(ItemType::APPLE, std::stoi(x), std::stoi(y)));
			std::cout << "1x apple spawned" << std::endl;
			commandline = false;
			return;
		}
		if (itemSpawn == "pear") {
			_items.push_back(Item(ItemType::PEAR, std::stoi(x), std::stoi(y)));
			std::cout << "1x pear spawned" << std::endl;
			commandline = false;
			return;
		}
		if (itemSpawn == "fruitsalad") {
			_items.push_back(Item(ItemType::FRUITSALAD, std::stoi(x), std::stoi(y)));
			std::cout << "1x fruitsalad spawned" << std::endl;
			commandline = false;
			return;
		}
		else {
			std::cout << "Unknown item... try again" << std::endl;
		}
	}
}

bool Game::canMouseToggle(Slot slot) {
	switch (slot) {
	case Slot::ONE:
		if (Crafting::slotAvailable(Slot::ONE)) {
			return true;
		}
		else {
			return false;
		}
		break;
	case Slot::TWO:
		if (Crafting::slotAvailable(Slot::TWO)) {
			return true;
		}
		else {
			return false;
		}
		break;
	case Slot::THREE:
		if (Crafting::slotAvailable(Slot::THREE)) {
			return true;
		}
		else {
			return false;
		}
		break;
	case Slot::FOUR:
		if (Crafting::slotAvailable(Slot::FOUR)) {
			return true;
		}
		else {
			return false;
		}
		break;
	case Slot::FIVE:
		if (Crafting::slotAvailable(Slot::FIVE)) {
			return true;
		}
		else {
			return false;
		}
		break;
	case Slot::SIX:
		if (Crafting::slotAvailable(Slot::SIX)) {
			return true;
		}
		else {
			return false;
		}
		break;
	case Slot::SEVEN:
		if (Crafting::slotAvailable(Slot::SEVEN)) {
			return true;
		}
		else {
			return false;
		}
		break;
	case Slot::EIGHT:
		if (Crafting::slotAvailable(Slot::EIGHT)) {
			return true;
		}
		else {
			return false;
		}
		break;
	case Slot::NINE:
		if (Crafting::slotAvailable(Slot::NINE)) {
			return true;
		}
		else {
			return false;
		}
		break;
	}
}

void Game::registerItems() {
	// ORIENTATION OF GRID
	// 789
	// 456
	// 123
	// addRecipe INSTRUCTIONS
	// 1, 2, 3, 4, 5, 6, 7, 8, 9, output
	Crafting::addRecipe(Crafting::createRecipe(ItemType::NONE, ItemType::NONE, ItemType::NONE, ItemType::NONE, ItemType::NONE, ItemType::NONE, ItemType::FRUITSALAD, ItemType::NONE, ItemType::NONE, ItemType::APPLE));
	Crafting::addRecipe(Crafting::createRecipe(ItemType::NONE, ItemType::NONE, ItemType::NONE, ItemType::NONE, ItemType::NONE, ItemType::NONE, ItemType::APPLE, ItemType::PEAR, ItemType::NONE, ItemType::FRUITSALAD));
	Crafting::addRecipe(Crafting::createRecipe(ItemType::NONE, ItemType::NONE, ItemType::NONE, ItemType::NONE, ItemType::NONE, ItemType::NONE, ItemType::NONE, ItemType::FRUITSALAD, ItemType::NONE, ItemType::PEAR));

}

int main(int argc, char *argv[]) {
	std::cout << "Industrial Revolution " << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH << " beta" << std::endl;
	Game g;
	g.init();
	g.gameLoop();
	return 0;
}