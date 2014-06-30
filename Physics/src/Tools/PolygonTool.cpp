#include <Tools/PolygonTool.hpp>
#include <Entities/Entity.hpp>
#include <Entities/PhysicsEntity.hpp>
#include <Game/Game.hpp>

PolygonTool::PolygonTool(Game* _game) : Tool(_game) {
}

PolygonTool::~PolygonTool() {
}

void PolygonTool::OnPress(Entity* _entity, sf::Vector2f _pos, sf::Mouse::Button _button) {
	if (_button == sf::Mouse::Button::Left) {
		// Check if this is an ending point..
		if (vertices.size() > 2) {
			sf::Vector2f diff = (vertices[0] - _pos);
			float length = sqrt((diff.x * diff.x) - (diff.y * diff.y));
			if (IntersectingOnShape(vertices[vertices.size()-1], _pos) == 0) {
				// If this isn't convex, then stop here.
				if (IsConvex()) {
					// Get the average center of these points.
					sf::Vector2f total(0, 0);
					for (int i = 0; i < vertices.size(); ++i) {
						total += vertices[i];
					}
					total.x /= vertices.size();
					total.y /= vertices.size();

					// Re-center the points.
					for (int i = 0; i < vertices.size(); ++i) {
						vertices[i] -= total;
					}

					// Create the shape with the points it has now.
					PhysicsEntity* entity = new PhysicsEntity(game);

					// Set the points.
					entity->SetPosition(total);
					entity->SetVertices(vertices.data(), vertices.size());

					// Add it to the entity list.
					game->GetEntityList()->Add(entity);
				}

				// Reset the vertices
				vertices.clear();

				// Return so that we don't accidentally put down a vertice after this.
				return;
			}
		}

		// Add the point if we can
		if (vertices.size() < 2)
			vertices.push_back(_pos);
		else if (IntersectingOnShape(vertices[vertices.size() - 1], _pos) < 0)
			vertices.push_back(_pos);
	}
}

void PolygonTool::OnRelease(Entity* _entity, sf::Vector2f _pos, sf::Mouse::Button _button) {
}

void PolygonTool::Equipped() {
	Tool::Equipped();

	vertices.clear();
}

void PolygonTool::Draw(float _deltatime) {
	sf::VertexArray array(sf::PrimitiveType::LinesStrip, vertices.size() + 1);
	for (int i = 0; i < vertices.size(); ++i) {
		array[i] = sf::Vertex(vertices[i], sf::Color::White);
	}

	array[vertices.size()] = sf::Vertex(game->GetTarget()->mapPixelToCoords(sf::Mouse::getPosition(*game->GetTarget())), sf::Color::White);
	game->GetTarget()->draw(array);
}

bool PolygonTool::IsConvex() {
	bool sign = Cross(vertices[0] - vertices[1], vertices[1] - vertices[2]) > 0;
	for (int i = 0; i < vertices.size(); ++i) {
		if (Cross(vertices[i] - vertices[(i+1) % vertices.size()], vertices[(i+1) % vertices.size()] - vertices[(i+2) % vertices.size()]) > 0 != sign) {
			return false;
		}
	}
	return true;
}

int PolygonTool::IntersectingOnShape(sf::Vector2f _linea, sf::Vector2f _lineb) {
	// Loop through each line and check if it is intersecting.
	for (int i = 0; i < (int)vertices.size() - 2; ++i) {
		sf::Vector2f point;
		if (AreLinesIntersecting(_linea, _lineb, vertices[i], vertices[i+1], &point)) {
			return i;
		}
	}
	return -1;
}

bool PolygonTool::AreLinesIntersecting(sf::Vector2f _line1a, sf::Vector2f _line1b, sf::Vector2f _line2a, sf::Vector2f _line2b, sf::Vector2f* _out) {
    float cross = Cross((_line2b - _line2a), (_line1b - _line1a));
    if (cross == 0)
    {
        // Pararell or colinear
        return false;
    }

    float t, s;
    t = Cross(_line1a - _line2a, _line2b - _line2a) / cross;
    s = Cross(_line1a - _line2a, _line1b - _line1a) / cross;

    // Check if the lines intersected
    if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
    {
        *_out = _line1a + (_line1b - _line1a) * t;
        return true;
    }
    else
    {
        // No intersect
        return false;
    }
}

float PolygonTool::Cross(sf::Vector2f _one, sf::Vector2f _two) {
	return (_one.x * _two.y) - (_two.x * _one.y);
}