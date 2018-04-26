//
//  UIButtonScene.h
//  UI Demo
//
//  This module shows off a basic button.  The button is backed by a NinePatch
//  so it can resize dynamically.  It changes the text on a click.
//
//  Author: Walker White
//  Version: 1/20/18
//
#ifndef __UI_BUTTON_SCENE_H__
#define __UI_BUTTON_SCENE_H__
#include <cugl/cugl.h>
#include "Board.h"
#include "ally.h"

/**
 * A scene for demoing a simple button
 */
class ButtonScene : public cugl::Scene {
public:
    /** The asset manager for this game mode. */
    std::shared_ptr<cugl::AssetManager> _assets;

    std::shared_ptr<cugl::Button> _button;
	std::shared_ptr<cugl::Button> _addEnemyButton;
    std::shared_ptr<cugl::Label> _label;

	bool currentSaveLoad = false;
	bool saveLoadClean = false;

	std::shared_ptr<cugl::Button> _infoTemplate;
	std::shared_ptr<cugl::Node> _upTemplate;
	std::shared_ptr<cugl::Texture> _bgTexture;
	cugl::Rect bounds;
	
	std::vector <std::string> componentNames;
	std::unordered_map<std::string, ComponentType> typeLayout;
	std::unordered_map<std::string, std::shared_ptr<Component>> baseComponents;
	

	std::shared_ptr<cugl::TextField> fileInput;
	std::shared_ptr<cugl::TexturedNode> fileInputBG;

	std::shared_ptr<cugl::Button> saveButton;
	std::shared_ptr<cugl::Button> loadButton;

	std::shared_ptr<cugl::TextField> _boardHeight;
	std::shared_ptr<cugl::TextField> _boardWidth;
	std::vector <std::shared_ptr<cugl::Label>> _infoLabels;
	std::vector <std::shared_ptr<cugl::Button>> _currentButtons;
	std::vector <std::shared_ptr<cugl::TexturedNode>> _currentImages;
	std::vector <std::shared_ptr<cugl::Label>> _currentLabels;
	std::vector <std::shared_ptr<cugl::Label>> _infoComponentLabels;
	std::vector <std::shared_ptr<cugl::TextField>> _infoComponentTextfields;
	std::vector <std::shared_ptr<cugl::Button>> _infoButtons;
	std::vector <std::shared_ptr<Ally>> _allies;

	std::vector <std::shared_ptr<cugl::Label>> _boardEnemyLabels;

	std::shared_ptr<cugl::TextField> _levelName;
	std::shared_ptr<cugl::TextField> _enemyName;

	std::vector<std::shared_ptr<Enemy>> enemies;
	std::vector<std::shared_ptr<cugl::Label>> enemyLabels;

	int currentEnemy = 0;
	int currentEnemyOffset = 0;
	int yComponentOffset = 0;
	

	std::string name = "";


	Board _board;
    int _counter;
    
//public:
#pragma mark -
#pragma mark Constructors
    /**
     * Creates a new scene with the default values.
     *
     * This constructor does not allocate any objects or start the controller.
     * This allows us to use a controller without a heap pointer.
     */
    ButtonScene() : _counter(0), enemies(), enemyLabels(), _infoLabels(), _currentButtons(), _infoComponentLabels(), _infoComponentTextfields(), _infoButtons(), _currentLabels(), _currentImages(){}
    
    /**
     * Disposes of all (non-static) resources allocated to this mode.
     *
     * This method is different from dispose() in that it ALSO shuts off any
     * static resources, like the input controller.
     */
    ~ButtonScene() { dispose(); }
    
    /**
     * Disposes of all (non-static) resources allocated to this mode.
     */
    virtual void dispose() override;
    
	void setupButtons();
	void addBoardEnemyLabel(int amount);
	void setupBoardEnemyLabels();
	void setupComponentButtons();

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
    bool init(const std::shared_ptr<cugl::AssetManager>& assets);
    
    static std::shared_ptr<ButtonScene> alloc(const std::shared_ptr<cugl::AssetManager>& assets) {
        std::shared_ptr<ButtonScene> result = std::make_shared<ButtonScene>();
        return (result->init(assets) ? result : nullptr);
    }
    
    /**
     * Sets whether the scene is currently active
     *
     * @param value whether the scene is currently active
     */
    virtual void setActive(bool value) override;

	void draw(const std::shared_ptr<cugl::SpriteBatch>& batch);

	virtual void update(float timestep) override;

	void computeLabels();

	std::shared_ptr<cugl::Button> createButton();

	void initiateSave();
	void initiateLoad();

	void loadJson(std::string levelName);
	void saveJson(std::string levelName);
};

#endif /* __UI_BUTTON_SCENE_H__ */
