#include <Game/Game.hpp>

#include <sstream>

#include <Entities/ShapeEntity.hpp>
#include <Entities/PhysicsEntity.hpp>
#include <Entities/UIEntity.hpp>

#include <Tools/SelectTool.hpp>
#include <Tools/RectangleTool.hpp>
#include <Tools/CircleTool.hpp>
#include <Tools/PolygonTool.hpp>
#include <Tools/RemoveTool.hpp>
#include <Tools/MoveTool.hpp>
#include <Tools/WeldTool.hpp>
#include <Tools/MotorJointTool.hpp>
#include <Tools/RotationTool.hpp>
#include <Tools/BodyTypeTool.hpp>
#include <Tools/DistanceJointTool.hpp>
#include <Tools/FrictionTool.hpp>
#include <Tools/RestitutionTool.hpp>
#include <Tools/DensityTool.hpp>

#include <Tools/PanTool.hpp>
#include <Tools/ZoomTool.hpp>

#include <Entities/EntityIDGenerator.hpp>

Game::Game(int _width, int _height, char* _title) : window(),
													entities(),
													gwenRenderer(window),
													gwenSkin(&gwenRenderer),
													gwenInput(),
													world(b2Vec2(0.0f, 9.81f)) {
	// Create the window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	window.create(sf::VideoMode(_width, _height, 32), _title, 7U, settings);

	// Initialize all the stuff here.
	// Set up the gwen skin and initialize the root panel.
	gwenSkin.Init("data/guiskins/skin.png");
	gwenSkin.SetDefaultFont(L"data/fonts/font.ttf");

	// Initialize the root panel
	gwenCanvas = new Gwen::Controls::Canvas(&gwenSkin);
	gwenCanvas->SetSize(window.getSize().x, window.getSize().y);
	gwenCanvas->SetDrawBackground(false);
	gwenCanvas->SetBackgroundColor(Gwen::Color(120, 120, 255, 255));

	// Initialize the input for gwen
	gwenInput.Initialize(gwenCanvas);

	// Set the world scale
	GetCamera().SetZoom(100.0f);
	GetCamera().SetPosition(sf::Vector2f(6.0f, 6.0f));

	// Set the physics time step.
	SetPhysicsStepTime(30.0f);

	// Set smoothing
	SetSmoothing(Game::INTERPOLATION);
	stepratio = 0.0f;

	// Turn friction on
	SetAirFriction(true);

	// Initialize the tool list
	currentTool = -1;
	tools.push_back(new SelectTool(this));
	tools.push_back(new RectangleTool(this));
	tools.push_back(new CircleTool(this));
	tools.push_back(new PolygonTool(this));
	tools.push_back(new RemoveTool(this));
	tools.push_back(new MoveTool(this));
	tools.push_back(new WeldTool(this));
	tools.push_back(new MotorJointTool(this));
	tools.push_back(new RotationTool(this));
	tools.push_back(new BodyTypeTool(this));
	tools.push_back(new DistanceJointTool(this));
	tools.push_back(new FrictionTool(this));
	tools.push_back(new RestitutionTool(this));
	tools.push_back(new DensityTool(this));

	// Add passive tools
	passivetools.push_back(new PanTool(this));
	passivetools.push_back(new ZoomTool(this));

	// Add the ondestroylistener
	world.SetDestructionListener(&destroyListener);

	// Paused physics is off
	pausedphysics = true;

	// Add some ui
	ui = new UIEntity(this);
	entities.Add(ui);
}

Game::~Game() {
	// Remove all the entities
	entities.Clear();

	// Delete the gwencanvas
	if (gwenCanvas != NULL)
		delete gwenCanvas;
}

// Update
void Game::Update(float _deltatime) {
	// Update box2d
	if (!pausedphysics) {
		if (physicsStep != 0) {
			static float time = 0.0f;
			time += _deltatime;
			if (time >= 1.0f / physicsStep) {
				world.Step(1.0f/physicsStep, 8, 3);
				time -= (1.0f / physicsStep);
				if (time > 1.0f / physicsStep)
					time = 0.0f;

				// Update entities
				entities.FixedUpdate();
			}

			stepratio = time / (1.0f / physicsStep);

		} else {
			world.Step(_deltatime, 8, 3);

			// Update entities
			entities.FixedUpdate();
		}
	}
	
	// Update all entities
	entities.Update(_deltatime);

	// Update all tools.
	if (currentTool >= 0 && currentTool < tools.size())
		tools[currentTool]->Update(_deltatime);
	for (int i = 0; i < passivetools.size(); ++i) {
		passivetools[i]->Update(_deltatime);
	}

	// Update the framerate on the window
	std::ostringstream buff;
	buff << "FPS: ";
	buff << (1.0f / _deltatime);
	buff << " Physics: ";
	buff << (physicsStep);
	buff << " Physics Ratio: ";
	buff << GetPhysicsStepRatio();
	window.setTitle(buff.str());
}

// Draw
void Game::Draw(float _deltatime) {
	// Update the view.
	window.setView(camera.GetView(&window));
	
	// Clear the window.
	window.clear();
	
	// Draw all entities
	entities.Draw(_deltatime);

	// Draw all tools.
	if (currentTool >= 0 && currentTool < tools.size())
		tools[currentTool]->Draw(_deltatime);
	for (int i = 0; i < passivetools.size(); ++i) {
		passivetools[i]->Draw(_deltatime);
	}

	// Draw the gwen stuff
	gwenCanvas->RenderCanvas();

	// Display the windows.
	window.display();
}

// Poll Events
void Game::PollEvents() {
	// For every passive tool and the current tool.
	int toolcount = passivetools.size();
	if (currentTool >= 0 && currentTool < tools.size()) toolcount++;
	Tool** tools = new Tool*[toolcount];
	for (int i = 0; i < passivetools.size(); ++i) {
		tools[i] = passivetools[i];
	}
	if (toolcount > passivetools.size())
		tools[passivetools.size()] = GetToolList()[currentTool];

	// Keep track of the last mouse position.
	static sf::Vector2i lastmousepos = sf::Mouse::getPosition(window);

	// Handle events
	sf::Event event;
	while (window.pollEvent(event)) {
		// Window closed or escape key pressed : exit
		if ((event.type == sf::Event::Closed) || 
			((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))) {
			window.close();
			break;
		} else if (event.type == sf::Event::Resized) {
			OnResize(event.size.width, event.size.height);
		}

		// Pause / Unpause physics
		if (event.type == sf::Event::KeyReleased) {
			if (event.key.code == sf::Keyboard::Space) {
				SetPhysicsActive(!GetPhysiscActive());
			}
		}

		// Process the event with gwen.
		if (!gwenInput.ProcessMessage(event)) {
			// Make sure this message is relevant.
			if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased) {
				// Figure out the position
				sf::Vector2i mousepos(event.mouseButton.x, event.mouseButton.y);

				// Convert to world coordinates.
				sf::Vector2f pos = window.mapPixelToCoords(mousepos);

				// Get entity at a position
				Entity* entity = GetEntityAt(pos);

				// Loop through each tool.
				for (int i = 0; i < toolcount; ++i) {
					// Report to the tool.
					if (event.type == sf::Event::MouseButtonPressed) {
						tools[i]->OnPress(entity, pos, event.mouseButton.button);

						// Add event.
						toolevents.push_back(ToolEvent(ToolEvent::PRESS, event.mouseButton.button, pos, currentTool));
					}
					if (event.type == sf::Event::MouseButtonReleased) {
						tools[i]->OnRelease(entity, pos, event.mouseButton.button);

						// Add event.
						toolevents.push_back(ToolEvent(ToolEvent::RELEASE, event.mouseButton.button, pos, currentTool));
					}
				}
			}

			// Detect drags
			if (event.type == sf::Event::MouseMoved) {
				for (int i = 0; i < toolcount; ++i) {
					// Get how much the mouse moved.
					sf::Vector2i delta = sf::Vector2i(event.mouseMove.x, event.mouseMove.y) - lastmousepos;
					sf::Vector2f deltaf(delta.x, delta.y);

					// Check if any mouse button is pressed.
					if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
						tools[i]->OnDrag(deltaf, sf::Mouse::Button::Left);

						// Add event.
						toolevents.push_back(ToolEvent(ToolEvent::DRAG, sf::Mouse::Button::Left, deltaf, currentTool));
					}
					if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle)) {
						tools[i]->OnDrag(deltaf, sf::Mouse::Button::Middle);

						// Add event.
						toolevents.push_back(ToolEvent(ToolEvent::DRAG, sf::Mouse::Button::Middle, deltaf, currentTool));
					}
					if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
						tools[i]->OnDrag(deltaf, sf::Mouse::Button::Right);

						// Add event.
						toolevents.push_back(ToolEvent(ToolEvent::DRAG, sf::Mouse::Button::Right, deltaf, currentTool));
					}
				}
			}

			// Detect scrolling
			if (event.type == sf::Event::MouseWheelMoved) {
				for (int i = 0; i < toolcount; ++i) {
					tools[i]->OnScroll(event.mouseWheel.delta);
				}
			}
		}
	}

	// Update the mouse pos.
	lastmousepos = sf::Mouse::getPosition(window);

	// Delete tool list
	delete tools;
}

// Run
void Game::Run() {
	while (window.isOpen()) {
		// Get the delta time
		float deltatime = clock.getElapsedTime().asSeconds();
		clock.restart();

		// Update
		Update(deltatime);

		// Draw
		Draw(deltatime);

		// Poll Events
		PollEvents();

		// Remove any entities that are dead.
		entities.RemoveDead();
	}
}


// Get / Set
sf::RenderWindow* Game::GetTarget() {
	return &window;
}

// Get the canvas
Gwen::Controls::Canvas* Game::GetCanvas() {
	return gwenCanvas;
}

// Set / Get the world scale.
Camera& Game::GetCamera() {
	return camera;
}

// Get the tool list.
const std::vector<Tool*>& Game::GetToolList() {
	return tools;
}

// Set the current tool
void Game::SetTool(int _i) {
	if (currentTool >= 0 && currentTool < tools.size())
		tools[currentTool]->Unequipped();
	currentTool = _i;
	if (currentTool >= 0 && currentTool < tools.size())
		tools[currentTool]->Equipped();
}

int Game::GetCurrentTool() {
	return currentTool;
}

// Get the box2d world
b2World* Game::GetWorld() {
	return &world;
}

// Get / Set Smoothing
void Game::SetSmoothing(Game::Smoothing _smooth) {
	smoothing = _smooth;
}
Game::Smoothing Game::GetSmoothing() {
	return smoothing;
}
float Game::GetPhysicsStepRatio() {
	return stepratio;
}

// Get / Set paused physics
void Game::SetPhysicsActive(bool _v) {
	pausedphysics = !_v;
}
bool Game::GetPhysiscActive() {
	return !pausedphysics;
}

// Set the physics step time
float Game::GetPhysicsStepTime() {
	return physicsStep;
}
void Game::SetPhysicsStepTime(float _time) {
	physicsStep = _time;
}

// Get the entity list
EntityList* Game::GetEntityList() {
	return &entities;
}

// Clear entities
void Game::ClearEntities(Entity* _entity) {
	world.SetDestructionListener(NULL);
	entities.Clear(_entity);
	world.SetDestructionListener(&destroyListener);
}

// Get the Ui
UIEntity* Game::GetUI() {
	return ui;
}

// Events
void Game::OnResize(int _width, int _height) {
	// Resize the gwen panel
	gwenCanvas->SetSize(_width, _height);
}

// Get the event list.
std::vector<ToolEvent>* Game::GetEventList() {
	return &toolevents;
}

// Simulate an event
void Game::SimulateEvent(ToolEvent event) {
	// Find the entity under the position
	Entity* entity = GetEntityAt(event.pos);

	switch (event.type) {
	case ToolEvent::PRESS:
		// Simulate the event.
		tools[event.toolid]->OnPress(entity, event.pos, event.button);

		break;
	case ToolEvent::RELEASE:
		// Simulate the event.
		tools[event.toolid]->OnRelease(entity, event.pos, event.button);

		break;

	case ToolEvent::DRAG:
		tools[event.toolid]->OnDrag(event.pos, event.button);
		break;

	default:
		break;
	}
}

Entity* Game::GetEntityAt(sf::Vector2f _pos) {
	// Find any entities underneath this point.
	class Query : public b2QueryCallback {
	public:
		Query(sf::Vector2f _pos) {
			entity = 0;
			pos = _pos;
		}
		bool ReportFixture(b2Fixture* fixture) {
			// Figure out if the point is the fixture.
			if (fixture->TestPoint(b2Vec2(pos.x, pos.y))) {
				// Get the entity
				entity = (Entity*)(fixture->GetUserData());
				return false;
			}

			return true;
		}

		Entity* entity;
		sf::Vector2f pos;
	};
	Query callback(_pos);
	b2AABB aabb;
	aabb.lowerBound.Set(_pos.x, _pos.y);
	aabb.upperBound.Set(_pos.x, _pos.y);
	world.QueryAABB(&callback, aabb);

	return callback.entity;
}

bool Game::GetAirFriction() {
	return airfriction;
}

void Game::SetAirFriction(bool _v) {
	airfriction = _v;
}
