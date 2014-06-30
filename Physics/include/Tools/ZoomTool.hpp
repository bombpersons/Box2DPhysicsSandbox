#ifndef PHYSICS_ZOOMTOOL_HPP
#define PHYSICS_ZOOMTOOL_HPP

#include <Tools/Tool.hpp>

class ZoomTool : public Tool {
public:
	ZoomTool(Game* _game);
	~ZoomTool();

	virtual void OnScroll(int _move);

private:

};

#endif