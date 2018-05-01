//
//  UIButtonScene.cpp
//  UI Demo
//
//  This module shows off a basic button.  The button is backed by a NinePatch
//  so it can resize dynamically.  It changes the text on a click.
//
//  Author: Walker White
//  Version: 1/20/18
//
#include "UIButtonScene.h"
#include <sstream>
#include <string>
#include <iostream>
#include "Components.h"
#include "ComponentType.h"
#include <algorithm>
#include <ctype.h>

using namespace cugl;

/** The unique listener id */
#define LISTENER_ID 2
/** This is adjusted by screen aspect ratio to get the height */
#define SCENE_WIDTH 1024

/**
 * Initializes the controller contents, and starts the game
 *
 * The constructor does not allocate any objects or memory.  This allows
 * us to have a non-pointer reference to this controller, reducing our
 * memory allocation.  Instead, allocation happens in this method.
 *
 * @param assets    The (loaded) assets for this game mode
 *
 * @return true if the controller is initialized properly, false otherwise.
 */
bool ButtonScene::init(const std::shared_ptr<AssetManager>& assets) {
    // Initialize the scene to a locked width
    Size dimen = Application::get()->getDisplaySize();
    dimen *= SCENE_WIDTH/dimen.width; // Lock the game to a reasonable resolution
    if (assets == nullptr) {
        return false;
    } else if (!Scene::init(dimen)) {
        return false;
    }

	CULog(("Your save directory is: " + Application::get()->getSaveDirectory()).c_str());

	{
		componentNames.push_back("DumbMovement");
		componentNames.push_back("SmartMovement");
		componentNames.push_back("ImmobileMovement");
		componentNames.push_back("TeleportMovement");
		componentNames.push_back("MeleeAttack");
		componentNames.push_back("RangeOrthoAttack");
		componentNames.push_back("RangeDiagAttack");
		componentNames.push_back("DuplicationOnTurn");
		componentNames.push_back("TileMoveOnTurn");
		componentNames.push_back("Size");
		componentNames.push_back("Idle");
		componentNames.push_back("NonIdle");
		componentNames.push_back("ExplodeOnDeath");
		componentNames.push_back("WeaknessResist");
		componentNames.push_back("StrengthResist");
		componentNames.push_back("ImmovablePlayerLimit");
		componentNames.push_back("FlyPlayerLimit");
		componentNames.push_back("SplashAttackMod");

		typeLayout["DumbMovement"] = ecs::getComponentType<DumbMovementComponent>();
		typeLayout["SmartMovement"] = ecs::getComponentType<SmartMovementComponent>();
		typeLayout["ImmobileMovement"] = ecs::getComponentType<ImmobileMovementComponent>();
		typeLayout["TeleportMovement"] = ecs::getComponentType<TeleportMovementComponent>();
		typeLayout["MeleeAttack"] = ecs::getComponentType<MeleeAttackComponent>();
		typeLayout["RangeOrthoAttack"] = ecs::getComponentType<RangeOrthoAttackComponent>();
		typeLayout["RangeDiagAttack"] = ecs::getComponentType<RangeDiagAttackComponent>();
		typeLayout["DuplicationOnTurn"] = ecs::getComponentType<DuplicationOnTurnComponent>();
		typeLayout["TileMoveOnTurn"] = ecs::getComponentType<TileMoveOnTurnComponent>();
		typeLayout["Size"] = ecs::getComponentType<SizeComponent>();
		typeLayout["Idle"] = ecs::getComponentType<IdleComponent>();
		typeLayout["NonIdle"] = ecs::getComponentType<NonIdleComponent>();
		typeLayout["ExplodeOnDeath"] = ecs::getComponentType<ExplodeOnDeathComponent>();
		typeLayout["WeaknessResist"] = ecs::getComponentType<WeaknessResistComponent>();
		typeLayout["StrengthResist"] = ecs::getComponentType<StrengthResistComponent>();
		typeLayout["ImmovablePlayerLimit"] = ecs::getComponentType<ImmovablePlayerLimitComponent>();
		typeLayout["FlyPlayerLimit"] = ecs::getComponentType<FlyPlayerLimitComponent>();
		typeLayout["SplashAttackMod"] = ecs::getComponentType<SplashAttackModComponent>();

		baseComponents["DumbMovement"] = std::make_shared<Component>(DumbMovementComponent());
		baseComponents["SmartMovement"] = std::make_shared<Component>(SmartMovementComponent());
		baseComponents["ImmobileMovement"] = std::make_shared<Component>(ImmobileMovementComponent());
		baseComponents["TeleportMovement"] = std::make_shared<Component>(TeleportMovementComponent());
		baseComponents["MeleeAttack"] = std::make_shared<Component>(MeleeAttackComponent());
		baseComponents["RangeOrthoAttack"] = std::make_shared<Component>( RangeOrthoAttackComponent());
		baseComponents["RangeDiagAttack"] = std::make_shared<Component>( RangeDiagAttackComponent());
		baseComponents["DuplicationOnTurn"] = std::make_shared<Component>( DuplicationOnTurnComponent());
		baseComponents["TileMoveOnTurn"] = std::make_shared<Component>( TileMoveOnTurnComponent());
		baseComponents["Size"] = std::make_shared<Component>( SizeComponent());
		baseComponents["Idle"] = std::make_shared<Component>( IdleComponent());
		baseComponents["NonIdle"] = std::make_shared<Component>( NonIdleComponent());
		baseComponents["ExplodeOnDeath"] = std::make_shared<Component>( ExplodeOnDeathComponent());
		baseComponents["WeaknessResist"] = std::make_shared<Component>( WeaknessResistComponent());
		baseComponents["StrengthResist"] = std::make_shared<Component>( StrengthResistComponent());
		baseComponents["ImmovablePlayerLimit"] = std::make_shared<Component>( ImmovablePlayerLimitComponent());
		baseComponents["FlyPlayerLimit"] = std::make_shared<Component>( FlyPlayerLimitComponent());
		baseComponents["SplashAttackMod"] = std::make_shared<Component>( SplashAttackModComponent());

	}

    
    _assets = assets;
    auto layer = assets->get<Node>("editor");
    layer->setContentSize(dimen);
    layer->doLayout(); // This rearranges the children to fit the screen
    addChild(layer);
	_board = Board(5, 5);

	_board.blankTexture = assets->get<Texture>("blank");
	_bgTexture = assets->get<Texture>("bg");
	bounds = Rect(0, 0, dimen.width, dimen.height);

	_currentButtons.push_back(std::dynamic_pointer_cast<Button>(assets->get<Node>("editor_buttonTemplate")));
	_currentButtons.push_back(std::dynamic_pointer_cast<Button>(assets->get<Node>("editor_buttonTemplate2")));
	_currentButtons.push_back(std::dynamic_pointer_cast<Button>(assets->get<Node>("editor_buttonTemplate3")));
	_currentButtons.push_back(std::dynamic_pointer_cast<Button>(assets->get<Node>("editor_buttonTemplate4")));
	_currentButtons.push_back(std::dynamic_pointer_cast<Button>(assets->get<Node>("editor_buttonTemplate5")));

	fileInput = std::dynamic_pointer_cast<TextField>(assets->get<Node>("editor_fileInput"));
	fileInputBG = std::dynamic_pointer_cast<TexturedNode>(assets->get<Node>("editor_fipImage"));
	fileInput->setVisible(false);
	fileInputBG->setVisible(false);

	saveButton = std::dynamic_pointer_cast<Button>(assets->get<Node>("editor_saveBoard"));
	loadButton = std::dynamic_pointer_cast<Button>(assets->get<Node>("editor_loadBoard"));

	saveButton->setListener([=](const std::string& name, bool down) {
		if (down) {
			initiateSave();
		}
	});

	loadButton->setListener([=](const std::string& name, bool down) {
		if (down) {
			initiateLoad();
		}
	});

	saveButton->activate(80);
	loadButton->activate(81);

	_infoButtons.push_back(std::dynamic_pointer_cast<Button>(assets->get<Node>("editor_minButton")));
	_infoButtons.push_back(std::dynamic_pointer_cast<Button>(assets->get<Node>("editor_minButton1")));
	_infoButtons.push_back(std::dynamic_pointer_cast<Button>(assets->get<Node>("editor_minButton2")));
	_infoButtons.push_back(std::dynamic_pointer_cast<Button>(assets->get<Node>("editor_minButton3")));
	_infoButtons.push_back(std::dynamic_pointer_cast<Button>(assets->get<Node>("editor_minButton4")));
	_infoButtons.push_back(std::dynamic_pointer_cast<Button>(assets->get<Node>("editor_minButton5")));
	_infoButtons.push_back(std::dynamic_pointer_cast<Button>(assets->get<Node>("editor_minButton6")));
	_infoButtons.push_back(std::dynamic_pointer_cast<Button>(assets->get<Node>("editor_minButton7")));

	_currentLabels.push_back(std::dynamic_pointer_cast<Label>(assets->get<Node>("editor_buttonTemplate_up_label")));
	_currentLabels.push_back(std::dynamic_pointer_cast<Label>(assets->get<Node>("editor_buttonTemplate2_up_label")));
	_currentLabels.push_back(std::dynamic_pointer_cast<Label>(assets->get<Node>("editor_buttonTemplate3_up_label")));
	_currentLabels.push_back(std::dynamic_pointer_cast<Label>(assets->get<Node>("editor_buttonTemplate4_up_label")));
	_currentLabels.push_back(std::dynamic_pointer_cast<Label>(assets->get<Node>("editor_buttonTemplate5_up_label")));

	_currentImages.push_back(std::dynamic_pointer_cast<TexturedNode>(assets->get<Node>("editor_buttonTemplate_up_img")));
	_currentImages.push_back(std::dynamic_pointer_cast<TexturedNode>(assets->get<Node>("editor_buttonTemplate2_up_img")));
	_currentImages.push_back(std::dynamic_pointer_cast<TexturedNode>(assets->get<Node>("editor_buttonTemplate3_up_img")));
	_currentImages.push_back(std::dynamic_pointer_cast<TexturedNode>(assets->get<Node>("editor_buttonTemplate4_up_img")));
	_currentImages.push_back(std::dynamic_pointer_cast<TexturedNode>(assets->get<Node>("editor_buttonTemplate5_up_img")));

	_addEnemyButton = std::dynamic_pointer_cast<Button>(assets->get<Node>("editor_addEnemy"));

	
	
	setupButtons();

    
	_boardHeight = std::dynamic_pointer_cast<TextField>(assets->get<Node>("editor_levelHeight"));
	_boardHeight->activate(LISTENER_ID);
	_boardHeight->setExitListener([=](const std::string& name, const std::string& current) {
		std::istringstream ss(current);
		int value;

		if (ss >> value) {
			if (value > 0 ? (value < 13 ? true : false) : false) {
				_boardHeight->setText(std::to_string(value));
				_board.height = value;
				_board.configure_size(_board.width, _board.height);
			}
			else {
				_boardHeight->setText(std::to_string(_board.height));
			}
		}
		else {
			_boardHeight->setText(std::to_string(_board.height));
		}
	});

	_boardWidth = std::dynamic_pointer_cast<TextField>(assets->get<Node>("editor_levelWidth"));
	_boardWidth->activate(LISTENER_ID + 1);
	_boardWidth->setExitListener([=](const std::string& name, const std::string& current) {
		std::istringstream ss(current);
		int value;

		if (ss >> value) {
			if (value > 0 ? (value < 13 ? true : false) : false) {
				_boardWidth->setText(std::to_string(value));
				_board.width = value;
				_board.configure_size(_board.width, _board.height);
			}
			else {
				_boardWidth->setText(std::to_string(_board.width));
			}
		}
		else {
			_boardWidth->setText(std::to_string(_board.width));
		}
	});

	_levelName = std::dynamic_pointer_cast<TextField>(assets->get<Node>("editor_levelName"));
	_levelName->activate(LISTENER_ID + 2);
	name = _levelName->getText();
	_levelName->setExitListener([=](const std::string& name, const std::string& current) {
		this->name = _levelName->getText();
	});

	_enemyName = std::dynamic_pointer_cast<TextField>(assets->get<Node>("editor_enemyName"));
	
	_enemyName->setExitListener([=](const std::string& name, const std::string& current) {
		if (currentEnemy != -1) {
			enemies[currentEnemy]->name = current;
			this->computeLabels();
		}
	});

	// Temp allocate random enemy
	{
		Enemy temp;
		temp.name = "Mr enemy";
		temp.addComponent<LocationComponent>(LocationComponent());
		temp.addComponent<DumbMovementComponent>(DumbMovementComponent());
		temp.addComponent<MeleeAttackComponent>(MeleeAttackComponent());
		temp.addComponent<RangeOrthoAttackComponent>(RangeOrthoAttackComponent());
		temp.opened[ecs::getComponentType<LocationComponent>()] = true;

		enemies.push_back(std::make_shared<Enemy>(temp));

		std::shared_ptr<cugl::Font> font = assets->get<Font>("mainFont20");
		for (int i = 0; i < 30; i++) {
			std::shared_ptr<Label> tempLabel = Label::alloc("Temporary", font);
			tempLabel->setName(std::to_string(i));
			tempLabel->setForeground(Color4(59, 59, 59, 255));
			tempLabel->setPositionX(768);
			tempLabel->setHorizontalAlignment(Label::HAlign::LEFT);
			tempLabel->setVerticalAlignment(Label::VAlign::MIDDLE);
			tempLabel->setVisible(false);
			enemyLabels.push_back(tempLabel);
		}

		for (int i = 0; i < 30; i++) {
			std::shared_ptr<Label> tempLabel = Label::alloc("Temporary", font);
			tempLabel->setName(std::to_string(20*i));
			tempLabel->setForeground(Color4(59, 59, 59, 255));
			tempLabel->setPositionX(795);
			tempLabel->setHorizontalAlignment(Label::HAlign::LEFT);
			tempLabel->setVerticalAlignment(Label::VAlign::MIDDLE);
			tempLabel->setVisible(false);
			_infoComponentLabels.push_back(tempLabel);
		}

		for (int i = 0; i < 30; i++) {
			std::shared_ptr<TextField> tempLabel = TextField::alloc("Temporary", font);
			tempLabel->setName(std::to_string(50*i));
			tempLabel->setForeground(Color4(196, 196, 196, 255));
			tempLabel->setBackground(Color4(59, 59, 59, 255));
			tempLabel->setHorizontalAlignment(Label::HAlign::LEFT);
			tempLabel->setVerticalAlignment(Label::VAlign::MIDDLE);
			tempLabel->setContentSize(30, 25);
			tempLabel->setVisible(false);
			_infoComponentTextfields.push_back(tempLabel);
		}
	}
	{
		Enemy temp;
		temp.name = "Mr enemy2";
		temp.addComponent<LocationComponent>(LocationComponent());
		temp.addComponent<DumbMovementComponent>(DumbMovementComponent());
		temp.addComponent<MeleeAttackComponent>(MeleeAttackComponent());

		enemies.push_back(std::make_shared<Enemy>(temp));
	}
	{
		_addEnemyButton->setListener([=](const std::string& name, bool down) {
			if (down) {
				Enemy temp;
				temp.name = "new enemy";
				temp.addComponent<LocationComponent>(LocationComponent());

				enemies.push_back(std::make_shared<Enemy>(temp));

				currentEnemy = enemies.size() - 1;
				setupButtons();
				computeLabels();
			}
		});
		_addEnemyButton->activate(65);
	}
	for (auto en = _infoComponentTextfields.begin(); en != _infoComponentTextfields.end(); en++) {
		addChild((*en));
	}


	computeLabels();
	Input::get<Mouse>()->setPointerAwareness(Mouse::PointerAwareness::ALWAYS);


	{ //Setup button inputs for tiles
		Keyboard* key = Input::get<Keyboard>();
		Mouse* m2 = Input::get<Mouse>();

		key->addKeyDownListener(50, [=](const KeyEvent& event, bool focus) {
			Mouse* m = Input::get<Mouse>();
			Vec2 loc = m->pointerPosition();
			loc.y = dimen.height - loc.y;

			if (event.keycode == KeyCode::Q) {
				_board.configureToColor(loc, 0);
			} else if (event.keycode == KeyCode::W) {
				_board.configureToColor(loc, 1);
			} else if (event.keycode == KeyCode::E) {
				_board.configureToColor(loc, 2);
			} else if (event.keycode == KeyCode::R) {
				_board.configureToColor(loc, 3);
			} else if (event.keycode == KeyCode::T) {
				_board.configureToColor(loc, 4);
			} else if (event.keycode == KeyCode::Y) {
				_board.configureToColor(loc, 5);
			}


			if (event.keycode == KeyCode::DEL || event.keycode == KeyCode::BACKSPACE) {
				Rect bound = Rect(255, 13, 200, 178);
				if (bound.contains(loc)) {
					if (currentEnemy != -1) {
						enemies.erase(enemies.begin() + currentEnemy);
						if (currentEnemyOffset <= currentEnemy && currentEnemy < currentEnemyOffset + 5)
							_currentButtons[currentEnemy - currentEnemyOffset]->deactivate();
					}
					currentEnemy = -1;
					setupButtons();
					computeLabels();
				}
			}

			if (event.keycode == KeyCode::ARROW_DOWN) {
				Rect bound = Rect(255, 13, 200, 178);
				if (bound.contains(loc)) {
					if (currentEnemyOffset + 5 < enemies.size()) {
						currentEnemyOffset++;
						setupButtons();
						computeLabels();
					}
				}

				bound = Rect(757, 246, 256, 419);
				if (bound.contains(loc)) {
					if (currentEnemy != -1) {
						int maxCount = enemies.at(currentEnemy)->components.size();
						if (yComponentOffset  < maxCount - 1) {
							yComponentOffset++;
							computeLabels();
						}
					}
				}

			}

			if (event.keycode == KeyCode::ARROW_UP) {
				Rect bound = Rect(255, 13, 200, 178);
				if (bound.contains(loc)) {
					if (currentEnemyOffset > 0) {
						currentEnemyOffset--;
						setupButtons();
						computeLabels();
					}
				}

				bound = Rect(757, 246, 256, 419);
				if (bound.contains(loc)) {
					yComponentOffset--;
					if (yComponentOffset <= 0) {
						yComponentOffset = 0;
					}

					computeLabels();
				}
			}
		});

		m2->addPressListener(55, [=](const MouseEvent& event, Uint8 clicks, bool focus) {
			Vec2 pos = event.position;
			
			Rect bounds = Rect(0, 56, 750, 430);
			if (bounds.contains(pos)) { 
				pos.y = dimen.height - pos.y;
				Vec2 gridLocation = _board.getXY(pos);
				if (gridLocation.x != -1 && gridLocation.y != -1) {
					bool hasEnemy = false;
					for (auto e = enemies.begin(); e != enemies.end(); e++) {
						Component eLoc = (*e)->components[ecs::getComponentType<LocationComponent>()];
						std::istringstream ss(eLoc.mapping["x"].second);
						int value;

						if (ss >> value) {
							std::istringstream s2(eLoc.mapping["y"].second);
							int value2;
							if (s2 >> value2) { //value x, value2 y
								if (gridLocation.x == value && gridLocation.y == value2) {
									hasEnemy = true;
									currentEnemy = e - enemies.begin();
									setupButtons();
									computeLabels();
								}
							}
						}
						if (hasEnemy) {
							break;
						}
					}

					if (!hasEnemy) {
						bool hasAlly = false;
						for (auto a = _allies.begin(); a != _allies.end(); a++) {
							if ((*a)->x == gridLocation.x && (*a)->y == gridLocation.y) {
								hasAlly = true;

								if (event.buttons.hasLeft()) {
									(*a)->isMika = !(*a)->isMika;
								}
								else if (event.buttons.hasRight()) {
									_allies.erase(a);
								}
							}
							if (hasAlly) {
								break;
							}
						}

						if (!hasAlly) {
							if (event.buttons.hasLeft()) {
								Ally newAlly;
								newAlly.x = gridLocation.x;
								newAlly.y = gridLocation.y;
								bool hasMika = false;
								for (auto a = _allies.begin(); a != _allies.end(); a++) {
									if ((*a)->isMika) {
										hasMika = true;
										break;
									}
								}
								newAlly.isMika = !hasMika;
								_allies.push_back(std::make_shared<Ally>(newAlly));
							}
						}
					}

				}

			}

		});
		

	
	}


    // XNA nostalgia
    Application::get()->setClearColor(Color4f::CORNFLOWER);
    return true;
}

/**
 * Disposes of all (non-static) resources allocated to this mode.
 */
void ButtonScene::dispose() {
    //_button = nullptr;
    //_label  = nullptr;
    _assets = nullptr;
    Scene::dispose();
}

/**
 * Sets whether the scene is currently active
 *
 * @param value whether the scene is currently active
 */
void ButtonScene::setActive(bool value) {
    _active = value;
    /*if (value && !_button->isactive()) {
        _button->activate(listener_id);
    } else if (!value && _button->isactive()) {
        _button->deactivate();
    }*/
}

void ButtonScene::draw(const std::shared_ptr<cugl::SpriteBatch>& batch) {
	batch->begin();
	batch->draw(_bgTexture, bounds);
	batch->end();
	_board.draw(batch);
	for (auto a = _allies.begin(); a != _allies.end(); a++) {
		_board.drawAlly(batch, (*a));
	}
	if (currentEnemy >= 0) {
		enemies.at(currentEnemy)->draw(batch, enemyLabels, _infoButtons, 760, 1010, 255, 583, yComponentOffset);
	}

	batch->begin();

	for (auto but = this->_currentButtons.begin(); but != _currentButtons.end(); but++) {
		if ((*but)->isVisible()) {
			(*but)->draw(batch, (*but)->getNodeToWorldTransform(), Color4::WHITE);
		}
		//CULog("Pos %d, %d, %d, %d", (*but)->getBoundingBox().getMinX(), (*but)->getBoundingBox().getMinY(), (*but)->getBoundingBox().getMaxX(), (*but)->getBoundingBox().getMaxY());
	}

	for (auto but = this->_infoComponentLabels.begin(); but != _infoComponentLabels.end(); but++) {
		if ((*but)->isVisible()) {
			(*but)->draw(batch, (*but)->getNodeToWorldTransform(), Color4::WHITE);
		}
		//CULog("Pos %d, %d, %d, %d", (*but)->getBoundingBox().getMinX(), (*but)->getBoundingBox().getMinY(), (*but)->getBoundingBox().getMaxX(), (*but)->getBoundingBox().getMaxY());
	}

	for (auto but = this->_infoComponentTextfields.begin(); but != _infoComponentTextfields.end(); but++) {
		if ((*but)->isVisible()) {
			(*but)->draw(batch, (*but)->getNodeToWorldTransform(), Color4::WHITE);
		}
		//CULog("Pos %d, %d, %d, %d", (*but)->getBoundingBox().getMinX(), (*but)->getBoundingBox().getMinY(), (*but)->getBoundingBox().getMaxX(), (*but)->getBoundingBox().getMaxY());
	}

	for (auto label = this->_boardEnemyLabels.begin(); label != _boardEnemyLabels.end(); label++) {
		if ((*label)->isVisible()) {
			(*label)->draw(batch, (*label)->getNodeToWorldTransform(), Color4::WHITE);
		}
		//CULog("Pos %d, %d, %d, %d", (*but)->getBoundingBox().getMinX(), (*but)->getBoundingBox().getMinY(), (*but)->getBoundingBox().getMaxX(), (*but)->getBoundingBox().getMaxY());
	}

	batch->end();

	render(batch);
}

void ButtonScene::update(float timestep) {
	if (currentEnemy != -1 && !_enemyName->isActive()) {
		_enemyName->activate(LISTENER_ID + 3);
		_enemyName->setText(enemies[currentEnemy]->name);
	}
	else if (currentEnemy == -1 && _enemyName->isActive()) {
		_enemyName->deactivate();
	}
	
	if (currentEnemy != -1 && enemies.at(currentEnemy)->needRedraw) {
		computeLabels();
		enemies.at(currentEnemy)->needRedraw = false;
	}

	setupBoardEnemyLabels();
	setupComponentButtons();

	if (!currentSaveLoad && !saveLoadClean) {
		fileInput->setVisible(false);
		fileInputBG->setVisible(false);
		fileInput->deactivate();
		saveLoadClean = true;
	}
}

void ButtonScene::setupButtons() {
	int val = 0;
	for (auto but = _currentButtons.begin(); but != _currentButtons.end(); but++) {
		(*but)->setVisible(false);
		(*but)->setListener([=](const std::string& name, bool down) {
			this->currentEnemy = this->currentEnemyOffset + val;
			this->computeLabels();
		});
		val++;
	}
}

void ButtonScene::computeLabels() {
	int currentDrawEnemyIndex = currentEnemyOffset;
	for (auto but = _currentButtons.begin(); but != _currentButtons.end(); but++) {
		(*but)->setVisible(false);
	}

	for (int i = 0; i < 5; i++) {
		if (currentDrawEnemyIndex < enemies.size()) {
			_currentLabels[i]->setText(enemies[currentDrawEnemyIndex]->name);
			_currentButtons[i]->setVisible(true);
			_currentButtons[i]->activate(LISTENER_ID + 4 + i);
			if (currentEnemy == currentDrawEnemyIndex) {
				_currentImages[i]->setColor(Color4(196, 196, 196, 255));
				_currentLabels[i]->setForeground(Color4(59, 59, 59, 255));
			}
			else {
				_currentImages[i]->setColor(Color4(59, 59, 59, 255));
				_currentLabels[i]->setForeground(Color4(196, 196, 196, 255));
			}
		}
		else {
			_currentButtons[i]->deactivate();
		}

		currentDrawEnemyIndex++;
	}
	if (currentEnemy != -1) {
		_enemyName->setText(enemies.at(currentEnemy)->name);
		if (yComponentOffset >= enemies.at(currentEnemy)->components.size()) {
			yComponentOffset = 0;
		}
		enemies.at(currentEnemy)->setupLabelFields(_infoComponentLabels, _infoComponentTextfields, 760, 1010, 255, 583, yComponentOffset);
	}
	else {
		_enemyName->setText("");
	}

	setupBoardEnemyLabels();
}

std::shared_ptr<Button> ButtonScene::createButton() {
	return nullptr;
}

void ButtonScene::addBoardEnemyLabel(int amount) {
	std::shared_ptr<cugl::Font> font = _assets->get<Font>("mainFont12");
	for (int i = 0; i < amount; i++) {
		std::shared_ptr<Label> tempLabel = Label::alloc("Temporary", font);
		tempLabel->setName(std::to_string(i));
		tempLabel->setForeground(Color4(59, 59, 59, 255));
		tempLabel->setPositionX(768);
		tempLabel->setHorizontalAlignment(Label::HAlign::CENTER);
		tempLabel->setVerticalAlignment(Label::VAlign::MIDDLE);
		tempLabel->setVisible(false);
		_boardEnemyLabels.push_back(tempLabel);
	}
}

void ButtonScene::setupBoardEnemyLabels() {
	if (enemies.size() > _boardEnemyLabels.size()) {
		addBoardEnemyLabel(enemies.size() - _boardEnemyLabels.size());
	}

	for (auto l = _boardEnemyLabels.begin(); l != _boardEnemyLabels.end(); l++) {
		(*l)->setVisible(false);
	}

	for (auto e = enemies.begin(); e != enemies.end(); e++) {
		std::shared_ptr<Label> ownLabel = _boardEnemyLabels.at(e - enemies.begin());
		Component eLoc = (*e)->components[ecs::getComponentType<LocationComponent>()];
		std::istringstream ss(eLoc.mapping["x"].second);
		int value;

		if (ss >> value) {
			std::istringstream s2(eLoc.mapping["y"].second);
			int value2;
			if (s2 >> value2) { //value x, value2 y
				Rect bounds = _board.getBoundsOfGrid(value, value2);
				ownLabel->setVisible(true);
				ownLabel->setPosition(bounds.origin);
				ownLabel->setContentSize(bounds.size);
				ownLabel->setText((*e)->name, true);
			}
		}
	}
}

void ButtonScene::setupComponentButtons() {
	for (auto s = componentNames.begin(); s != componentNames.end(); s++) {
		std::shared_ptr<Button> ownButton = std::dynamic_pointer_cast<Button>(_assets->get<Node>("editor_" + (*s)));
		ownButton->deactivate();
		std::shared_ptr<Label> ownLabel = std::dynamic_pointer_cast<Label>(_assets->get<Node>("editor_" + (*s) + "_up_label"));
		std::shared_ptr<TexturedNode> ownImage = std::dynamic_pointer_cast<TexturedNode>(_assets->get<Node>("editor_" + (*s) + "_up_img"));
		ownLabel->setForeground(Color4::WHITE);
		ownImage->setColor(Color4::CLEAR);
		ownLabel->setText((*s));
		if (currentEnemy != -1) {
			if (enemies[currentEnemy]->components.count(typeLayout[(*s)]) > 0) { //has
				ownLabel->setForeground(Color4::BLACK);
				ownImage->setColor(Color4::WHITE);

				ownButton->setListener([=](const std::string& name, bool down) {
					if (down) {
						enemies[currentEnemy]->components.erase(typeLayout[(*s)]);
						enemies[currentEnemy]->opened.erase(typeLayout[(*s)]);
						enemies.at(currentEnemy)->needRedraw = true;
					}
				});
			}
			else { //doesn't have
				ownButton->setListener([=](const std::string& name, bool down) {
					if (down) {
						enemies[currentEnemy]->addComponent2(typeLayout[(*s)], *baseComponents[(*s)]);
						enemies.at(currentEnemy)->needRedraw = true;
					}
				});
			}
			ownButton->activate(1500 + (s - componentNames.begin()));
		}
	}
}

void ButtonScene::initiateSave() {
	fileInput->setVisible(true);
	fileInputBG->setVisible(true);

	fileInput->setExitListener([=](const std::string& name, const std::string& current) {
		saveJson(current);
	});

	currentSaveLoad = true;
	fileInput->activate(83);
}

void ButtonScene::initiateLoad() {
	fileInput->setVisible(true);
	fileInputBG->setVisible(true);

	fileInput->setExitListener([=](const std::string& name, const std::string& current) {
		loadJson(current);
	});


	currentSaveLoad = true;
	fileInput->activate(84);
}

void ButtonScene::saveJson(std::string levelName) {
	std::shared_ptr<JsonWriter> writer = JsonWriter::alloc(levelName + ".json");
	std::shared_ptr<JsonValue> json = JsonValue::allocObject();
	std::shared_ptr<JsonValue> boardJson = JsonValue::allocObject();
	boardJson->appendChild("width", JsonValue::alloc((long)_board.width));
	boardJson->appendChild("height", JsonValue::alloc((long)_board.height));
	json->appendChild("size", boardJson);

	std::shared_ptr<JsonValue> tilesJson = JsonValue::allocArray();
	for (int x = 0; x < _board.width; x++) {
		std::shared_ptr<JsonValue> subTilesJson = JsonValue::allocArray();
		for (int y = 0; y < _board.height; y++) {
			subTilesJson->insertChild(y, JsonValue::alloc((long)_board.tiles[x][y]));
		}
		tilesJson->insertChild(x, subTilesJson);
	}
	json->appendChild("tiles", tilesJson);




	std::shared_ptr<JsonValue> enemiesJson = JsonValue::allocObject();
	for (auto e = enemies.begin(); e != enemies.end(); e++) {
		std::shared_ptr<JsonValue> enJson = JsonValue::allocObject();
		std::shared_ptr<JsonValue> compJson = JsonValue::allocObject();
		for (auto c = (*e)->components.begin(); c != (*e)->components.end(); c++) {
			std::shared_ptr<JsonValue> singleCompJson = JsonValue::allocObject();
			for (auto c1 = (*c).second.mapping.begin(); c1 != (*c).second.mapping.end(); c1++) {
				if ((*c1).second.first.compare("int") == 0) {
					std::istringstream ss((*c1).second.second);
					int value;

					if (ss >> value) {
						singleCompJson->appendChild((*c1).first, JsonValue::alloc((long)value));
					}
				}
				else if ((*c1).second.first.compare("bool") == 0) {
					std::istringstream ss((*c1).second.second);
					int value;

					if (ss >> value) {
						singleCompJson->appendChild((*c1).first, JsonValue::alloc((bool)value));
					}
				}
				else if ((*c1).second.first.compare("string") == 0) {
					singleCompJson->appendChild((*c1).first, JsonValue::alloc((*c1).second.second));
				}
			}
			compJson->appendChild((*c).second.name, singleCompJson);
		}
		enJson->appendChild("components", compJson);
		enemiesJson->appendChild((*e)->name, enJson);
	}
	json->appendChild("enemies", enemiesJson);





	std::shared_ptr<JsonValue> alliesJson = JsonValue::allocObject();

	for (auto a = _allies.begin(); a != _allies.end(); a++) {
		if ((*a)->isMika) {
			std::shared_ptr<JsonValue> mikaJson = JsonValue::allocObject();
			mikaJson->appendChild("x", JsonValue::alloc((long)(*a)->x));
			mikaJson->appendChild("y", JsonValue::alloc((long)(*a)->y));
			json->appendChild("mika", mikaJson);
		}
		else {
			std::shared_ptr<JsonValue> newAllyJson = JsonValue::allocObject();
			newAllyJson->appendChild("x", JsonValue::alloc((long)(*a)->x));
			newAllyJson->appendChild("y", JsonValue::alloc((long)(*a)->y));
			alliesJson->appendChild("ally" + std::to_string(_allies.begin() - a),newAllyJson);
		}
	}

	json->appendChild("allies", alliesJson);
	





	writer->writeJson(json);
	currentSaveLoad = false;
	saveLoadClean = false;
}

void ButtonScene::loadJson(std::string levelName) {
	try {
		std::shared_ptr<JsonReader> reader = JsonReader::alloc(levelName + ".json");
		std::shared_ptr<JsonValue> json = reader->readJson();
	} catch (...) {
		CULog("Invalid file name, check name is correct and file is in the correct location");
		return;
	}
	std::shared_ptr<JsonReader> reader = JsonReader::alloc(levelName + ".json");
	std::shared_ptr<JsonValue> json = reader->readJson();

	_board = Board();
	currentEnemy = -1;
	currentEnemyOffset = 0;
	enemies.clear();
	_allies.clear();

	std::shared_ptr<JsonValue> size = json->get("size");
	_board.configure_size(size->getInt("width"), size->getInt("height"));

	std::shared_ptr<JsonValue> tiles = json->get("tiles");
	for (int x = 0; x < size->getInt("width"); x++) {
		std::shared_ptr<JsonValue> singleRow = tiles->get(x);
		std::vector<int> values = singleRow->asIntArray();
		for (int y = 0; y < size->getInt("height"); y++) {
			_board.tiles[x][y] = values[y];
		}
	}



	std::shared_ptr<JsonValue> mika = json->get("mika");
	Ally newMika;
	newMika.isMika = true;
	newMika.x = mika->getInt("x");
	newMika.y = mika->getInt("y");
	_allies.push_back(std::make_shared<Ally>(newMika));

	std::shared_ptr<JsonValue> allies = json->get("allies");
	for (auto i = 0; i < allies->size(); i++) {
		Ally newAlly;
		newAlly.isMika = false;
		newAlly.x = allies->get(i)->getInt("x");
		newAlly.y = allies->get(i)->getInt("y");
		_allies.push_back(std::make_shared<Ally>(newAlly));
	}

	std::shared_ptr<JsonValue> enemiesJson = json->get("enemies");
	for (auto i = 0; i < enemiesJson->size(); i++) {
		Enemy newEnemy;
		LocationComponent loc;
		newEnemy.name = enemiesJson->get(i)->key();
		std::shared_ptr<JsonValue> components = enemiesJson->get(i)->get("components");
		for (auto j = 0; j < components->size(); j++) {
			std::string compName = components->get(j)->key();
			if (islower(compName.at(0))) {
				compName[0] = ((char)toupper(compName.at(0)));
			}

			if (compName.compare("Location") == 0) {
				loc.mapping["x"].second = std::to_string(components->get(j)->getInt("x"));
				loc.mapping["y"].second = std::to_string(components->get(j)->getInt("y"));
				newEnemy.addComponent<LocationComponent>(loc);
			}
			else {
				newEnemy.addComponent2(typeLayout[compName], *baseComponents[compName]);
				Component newComponent = newEnemy.components[typeLayout[compName]];
				for (auto k = 0; k < components->get(j)->size(); k++) {
					newComponent.mapping[components->get(j)->get(k)->key()].second = components->get(j)->getString(components->get(j)->get(k)->key());
				}

				newEnemy.components[typeLayout[compName]] = newComponent;
			}
		}

		enemies.push_back(std::make_shared<Enemy>(newEnemy));
	}

















	_boardHeight->deactivate();
	_boardWidth->deactivate();
	_levelName->deactivate();

	_boardHeight->setText(std::to_string(_board.height));
	_boardWidth->setText(std::to_string(_board.width));
	_levelName->setText(levelName);
	name = levelName;



	_boardHeight = std::dynamic_pointer_cast<TextField>(_assets->get<Node>("editor_levelHeight"));
	_boardHeight->activate(LISTENER_ID);
	_boardHeight->setExitListener([=](const std::string& name, const std::string& current) {
		std::istringstream ss(current);
		int value;

		if (ss >> value) {
			if (value > 0 ? (value < 13 ? true : false) : false) {
				_boardHeight->setText(std::to_string(value));
				_board.height = value;
				_board.configure_size(_board.width, _board.height);
			}
			else {
				_boardHeight->setText(std::to_string(_board.height));
			}
		}
		else {
			_boardHeight->setText(std::to_string(_board.height));
		}
	});

	_boardWidth = std::dynamic_pointer_cast<TextField>(_assets->get<Node>("editor_levelWidth"));
	_boardWidth->activate(LISTENER_ID + 1);
	_boardWidth->setExitListener([=](const std::string& name, const std::string& current) {
		std::istringstream ss(current);
		int value;

		if (ss >> value) {
			if (value > 0 ? (value < 13 ? true : false) : false) {
				_boardWidth->setText(std::to_string(value));
				_board.width = value;
				_board.configure_size(_board.width, _board.height);
			}
			else {
				_boardWidth->setText(std::to_string(_board.width));
			}
		}
		else {
			_boardWidth->setText(std::to_string(_board.width));
		}
	});

	_levelName = std::dynamic_pointer_cast<TextField>(_assets->get<Node>("editor_levelName"));
	_levelName->activate(LISTENER_ID + 2);
	name = _levelName->getText();
	_levelName->setExitListener([=](const std::string& name, const std::string& current) {
		this->name = _levelName->getText();
	});

	computeLabels();



	currentSaveLoad = false;
	saveLoadClean = false;
}