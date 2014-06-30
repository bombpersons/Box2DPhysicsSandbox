#include <Camera/Camera.hpp>

Camera::Camera() {
	pos = sf::Vector2f(0, 0);
	zoom = 1.0f;
}

Camera::~Camera() {
}

// Move the camera
void Camera::SetPosition(sf::Vector2f _pos) {
	pos = _pos;
}

const sf::Vector2f& Camera::GetPosition() {
	return pos;
}

// Zoom
void Camera::SetZoom(float _zoom) {
	zoom = _zoom;
}

float Camera::GetZoom() {
	return zoom;
}

// Get the view
sf::View Camera::GetView(sf::RenderTarget* _target) {
	// Create a view
	sf::View view = _target->getDefaultView();

	// Calculate the dimensions of the view
	float width = _target->getSize().x / zoom;
	float height = _target->getSize().y / zoom;

	// Get the points of the view.
	float left, top, right, bottom;
	left = pos.x - (width / 2.0f);
	top = pos.y - (height / 2.0f);
	right = left + width;
	bottom = top + height;

	// Make sure it is the size of the target.
	//view.setViewport(sf::FloatRect(left, top, right, bottom));
	view.setSize(width, height);
	view.setCenter(pos);

	// Return it.
	return view;
}