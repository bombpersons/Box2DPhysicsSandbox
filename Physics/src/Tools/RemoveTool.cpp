#include <Tools/RemoveTool.hpp>
#include <Game/Game.hpp>

RemoveTool::RemoveTool(Game* _game) : Tool(_game) {
}

RemoveTool::~RemoveTool() {
}

void RemoveTool::OnPress(Entity* _entity, sf::Vector2f _pos, sf::Mouse::Button _button) {
}

void RemoveTool::OnRelease(Entity* _entity, sf::Vector2f _pos, sf::Mouse::Button _button) {
	if (_button == sf::Mouse::Button::Left) {
		if (_entity != NULL) {
			game->GetEntityList()->Remove(_entity);
			game->GetEntityList()->RemoveDead();
			game->GetEntityList()->RemoveDead();
		}
	}
}