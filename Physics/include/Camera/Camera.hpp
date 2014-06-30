#ifndef PHYSICS_CAMERA_HPP
#define PHYSICS_CAMERA_HPP

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Camera {
public:
	// Constructor
	Camera();
	~Camera();

	// Move the camera
	void SetPosition(sf::Vector2f _pos);
	const sf::Vector2f& GetPosition();

	void SetZoom(float _zoom);
	float GetZoom();

	// Get the sfml view
	sf::View GetView(sf::RenderTarget* _target);

private:
	// How zoomed in we are.
	float zoom;
	sf::Vector2f pos;
};

#endif