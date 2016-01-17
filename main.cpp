#include "client/clientworld.h"

int main(int, char**) {
	sf::RenderWindow window(sf::VideoMode(854, 480), "Game", sf::Style::Default, sf::ContextSettings(0, 0, 16));
	sf::Event ev;

	window.setFramerateLimit(60);
	window.setView(sf::View(sf::Vector2f(0, 0), sf::Vector2f(64, 36)));

	ClientWorld world;

	{
		ClientCell* cell = new ClientCell;
		world.addCell(cell);
	}

	sf::CircleShape shape(1);
	shape.setFillColor(sf::Color(255, 192, 192, 64));
	shape.setOrigin(1, 1);

	while (window.isOpen()) {
		while (window.pollEvent(ev)) {
			if (ev.type==sf::Event::Closed)
				window.close();
			else if (ev.type==sf::Event::MouseButtonPressed) {
				ClientCell* cell = new ClientCell;
				cell->move(shape.getPosition());
				cell->motionStop();

				world.addCellConnectedTo(cell, world.getNearestCell(window.mapPixelToCoords(sf::Mouse::getPosition(window))));
			}
		}

		world.update();

		{
			stk::vec2 vec = window.mapPixelToCoords(sf::Mouse::getPosition(window));
			Cell* cell = world.getNearestCell(vec);

			shape.setPosition(cell->position()+stk::vec2(vec-cell->position()).normalized()*(cell->radius()+1.f));
		}

		window.clear();

		world.draw(window);
		window.draw(shape);

		window.display();
	}

	return 0;
}
