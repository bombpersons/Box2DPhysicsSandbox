#ifndef PHYSICS_PANTOOL_HPP
#define PHYSICS_PANTOOL_HPP

#include <Tools/Tool.hpp>

class PanTool : public Tool {
public:
	PanTool(Game* _game);
	~PanTool();

	// Detect the object to select
	virtual void OnDrag(sf::Vector2f _delta, sf::Mouse::Button _button);

private:

};

#endif