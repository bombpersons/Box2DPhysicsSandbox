#include <Tools/PanTool.hpp>
#include <Game/Game.hpp>

PanTool::PanTool(Game* _game) : Tool(_game) {

}

PanTool::~PanTool() {
}

void PanTool::OnDrag(sf::Vector2f _delta, sf::Mouse::Button _button) {
	if (_button == sf::Mouse::Button::Middle) {
		// Convert the pan amount to the zoom level of the camera
		_delta.x /= game->GetCamera().GetZoom();
		_delta.y /= game->GetCamera().GetZoom();

		game->GetCamera().SetPosition(game->GetCamera().GetPosition() - _delta);
	}
}