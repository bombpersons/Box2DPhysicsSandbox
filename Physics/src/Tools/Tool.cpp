#include <Tools/Tool.hpp>

Tool::Tool(Game* _game) {
	game = _game;
}

Tool::~Tool() {
}

void Tool::OnPress(Entity* _entity, sf::Vector2f _pos, sf::Mouse::Button _button) {

}

void Tool::OnRelease(Entity* _entity, sf::Vector2f _pos, sf::Mouse::Button _button) {

}

void Tool::OnDrag(sf::Vector2f _delta, sf::Mouse::Button _button) {

}

void Tool::OnScroll(int _move) {

}

void Tool::Draw(float _deltatime) {

}

void Tool::Update(float _deltatime) {

}

// When the tool is activated
void Tool::Unequipped() {

}
void Tool::Equipped() {

}
