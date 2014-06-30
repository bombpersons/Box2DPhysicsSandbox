#include <Tools/ZoomTool.hpp>
#include <Game/Game.hpp>

ZoomTool::ZoomTool(Game* _game) : Tool(_game) {
}

ZoomTool::~ZoomTool() {

}

void ZoomTool::OnScroll(int _move) {
	// Zoom in 20% every scroll
	float zoom = game->GetCamera().GetZoom();
	zoom += zoom * (0.2 * _move);
	game->GetCamera().SetZoom(zoom);
}