#include <iostream>
#include <SFML/Graphics.hpp>
#include "Charge.h"
#include "Math.h"
#include <vector>

void calculateTension(sf::RenderWindow& window);
void drawTension(sf::RenderWindow& window, float x, float y, float tension_x, float tension_y);

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const float SCALE = 1;

std::vector<Charge> charges;

int main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Tension lines");

	Charge chargeP(170, 170, 0.000000008);
	Charge chargeM(230, 170, -0.000000008);
	Charge chargeM2(170, 230, -0.000000008);
	Charge charge1(230, 230, 0.000000008);

	charges.push_back(chargeP);
	charges.push_back(chargeM);
	charges.push_back(chargeM2);
	charges.push_back(charge1);

	bool changed = true;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (changed) {
			window.clear(sf::Color::Black);
			for (auto it = std::begin(charges); it != std::end(charges); ++it) {
				window.draw(it->getShape());
			}
			calculateTension(window);
			window.display();
			changed = false;
		}
	}
}

void calculateTension(sf::RenderWindow& window) {
	const long k = 9000000000.l;
	bool endLine = false;
	float x;
	float y;
	for (auto it = std::begin(charges); it != std::end(charges); ++it) {
		if (it->getValue() > 0) {
			for (int phi = 0; phi <= 360; phi += 5) {
				endLine = false;
				x = it->getX() + it->getRadius() * cos(phi);
				y = it->getY() + it->getRadius() * sin(phi);
				float res_tension_x = 0;
				float res_tension_y = 0;
				int j = 0;
				while (!endLine) {
					if (x >= SCREEN_WIDTH || x <= 0 || y >= SCREEN_HEIGHT || y <= 0) {
						endLine = true;
					}
					else {
						for (auto itr = std::begin(charges); itr != std::end(charges); ++itr) {
							const float dx = x - itr->getX();
							const float dy = y - itr->getY();
							const double distance = sqrt(dx * dx + dy * dy);
							if (itr->getValue() < 0 && itr->getRadius() >= distance) {
								endLine = true;
								break;
							}
							else {
								const double tension = (k * (double)itr->getValue()) / (distance * distance);
								const float tension_x = tension * dx / distance;
								const float tension_y = tension * dy / distance;
								res_tension_x += tension_x;
								res_tension_y += tension_y;
							}
						}
						drawTension(window, x, y, res_tension_x, res_tension_y);
						j++;
						x += res_tension_x * SCALE;
						y += res_tension_y * SCALE;
					}
				}
			}
		}
	}
}

void drawTension(sf::RenderWindow& window, float x, float y, float tension_x, float tension_y) {
	sf::VertexArray line(sf::Lines, 2);
	line[0].position = sf::Vector2f(x, y);
	line[0].color = sf::Color::Yellow;
	line[1].position = sf::Vector2f(x + tension_x * SCALE, y + tension_y * SCALE);
	line[1].color = sf::Color::Yellow;
	window.draw(line);
}
