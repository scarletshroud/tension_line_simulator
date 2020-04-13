#ifndef CHARGE_HPP
#define CHARGE_HPP

#include "SFML/Graphics.hpp"

class Charge {
private:
	const int RADIUS = 5;
	int x;
	int y;
	double value;
	sf::CircleShape chargeShape;

public:
	Charge(int x, int y, float value);
	~Charge();
	int getX();
	int getY();
	int getRadius();
	float getValue();
	sf::CircleShape getShape();
};

#endif // !CHARGE_HPP
