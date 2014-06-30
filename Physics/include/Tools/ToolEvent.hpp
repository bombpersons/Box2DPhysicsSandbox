#ifndef PHYSICS_TOOLEVENT_HPP
#define PHYSICS_TOOLEVENT_HPP

class ToolEvent {
public:
	// Classes
	enum EventType { 
		DRAG = 0,
		PRESS,
		RELEASE,
	};

	// Constructors
	ToolEvent(EventType _type, sf::Mouse::Button _button, sf::Vector2f _pos, int _toolid) {
		type = _type;
		button = _button;
		pos = _pos;
		toolid = _toolid;
	}
	ToolEvent() {
	}
	~ToolEvent() {
	}

	// Buttons / Position (the entity pointer will be calculated whe the event is processed)
	sf::Mouse::Button button;
	sf::Vector2f pos;
	int toolid;
	EventType type;

private:

};

#endif