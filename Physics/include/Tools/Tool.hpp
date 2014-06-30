#ifndef PHYSICS_TOOL_HPP
#define PHYSICS_TOOL_HPP

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Entity;
class Game;

class Tool {
public:
	// Constructors
	Tool(Game* _game);
	virtual ~Tool();

	// Called when the tool is used.
	virtual void OnPress(Entity* _entity, sf::Vector2f _pos, sf::Mouse::Button _button);
	virtual void OnRelease(Entity* _entity, sf::Vector2f _pos, sf::Mouse::Button _button);
	virtual void OnDrag(sf::Vector2f _delta, sf::Mouse::Button _button);
	virtual void OnScroll(int _move);

	// Let the tool draw / update
	virtual void Draw(float _deltatime);
	virtual void Update(float _deltatime);

	// When the tool is activated
	virtual void Unequipped();
	virtual void Equipped();

protected:
	Game* game;
};

#endif