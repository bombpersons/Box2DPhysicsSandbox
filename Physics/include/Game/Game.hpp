#ifndef PHYSICS_GAME_HPP
#define PHYSICS_GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <Gwen/Controls.h>
#include <Gwen/Renderers/SFML2.h>
#include <Gwen/Skins/TexturedBase.h>
#include <Gwen/Input/SFML.h>

#include <Box2D/Box2D.h>

#include <Camera/Camera.hpp>
#include <Entities/EntityList.hpp>
#include <Tools/Tool.hpp>

#include <Game/OnDestroyListener.hpp>

#include <Tools/ToolEvent.hpp>

#include <vector>

class UIEntity;

class Game {
public:
	// Enums
	enum Smoothing {
		NONE,
		EXTRAPOLATION,
		INTERPOLATION
	};

	// Constructor
	Game(int _width, int _height, char* _title);
	virtual ~Game();

	// Update
	void Update(float _deltatime);

	// Draw
	void Draw(float _deltatime);

	// Poll
	void PollEvents();

	// Run
	void Run();

	// Get the target (renderwindow)
	sf::RenderWindow* GetTarget();

	// Get the canvas
	Gwen::Controls::Canvas* GetCanvas();

	// Get camera
	Camera& GetCamera();

	// Get the tool list.
	const std::vector<Tool*>& GetToolList();

	// Set the current tool
	virtual void SetTool(int _i);
	virtual int GetCurrentTool();

	// Get the box2d world
	b2World* GetWorld();

	// Set the smoothing type
	void SetSmoothing(Smoothing _smooth);
	Smoothing GetSmoothing();

	// Get the physics step ratio
	float GetPhysicsStepRatio();

	// Set / Get paused physics
	void SetPhysicsActive(bool _v);
	bool GetPhysiscActive();

	// Set the physics step time
	float GetPhysicsStepTime();
	void SetPhysicsStepTime(float _time);

	// Get the entity list
	EntityList* GetEntityList();

	// Clear entities
	void ClearEntities(Entity* _entity);

	// Get UI
	UIEntity* GetUI();

	// Events
	void OnResize(int _width, int _height);

	// Get the event list.
	std::vector<ToolEvent>* GetEventList();

	// Simulate an event
	void SimulateEvent(ToolEvent event);

	// Get an object at position
	Entity* GetEntityAt(sf::Vector2f _pos);

	// Get whether or not air friction is turned on
	bool GetAirFriction();
	void SetAirFriction(bool _v);

protected:
	// The window.
	sf::RenderWindow window;

	// Timer to get frame rate and stuff.
	sf::Clock clock;

	// GWEN stuff.
	Gwen::Renderer::SFML2 gwenRenderer;
	Gwen::Skin::TexturedBase gwenSkin;
	Gwen::Controls::Canvas* gwenCanvas;
	Gwen::Input::SFML gwenInput;

	// The entity list.
	EntityList entities;

	// The ui entity
	UIEntity* ui;

	// Camera
	Camera camera;

	// Box2D stuff.
	b2World world;

	// Smoothing type
	Smoothing smoothing;

	// Ratio of physics timing
	float stepratio;

	// Whether or not air friction is turned on.
	bool airfriction;

	// Pause the physics
	bool pausedphysics;

	// How many times the physics should be updated every second
	float physicsStep;

	// Listener so that entities know when box2d has destroyed them
	OnDestroyListener destroyListener;

	// List of tools
	std::vector<Tool*> tools;
	int currentTool;
	std::vector<Tool*> passivetools;

	// Recorded events
	std::vector<ToolEvent> toolevents;
};

#endif