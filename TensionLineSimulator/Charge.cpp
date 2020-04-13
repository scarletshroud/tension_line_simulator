#include "Charge.h"

Charge::Charge(int x, int y, float value) {
	this->x = x;
	this->y = y;
	this->value = value;
	chargeShape.setRadius(RADIUS);
	if (value > 0) {
		chargeShape.setFillColor(sf::Color::Red);
	}
	else {
		chargeShape.setFillColor(sf::Color::Blue);
	}
	chargeShape.setOrigin(RADIUS, RADIUS);
	chargeShape.setPosition(x, y);
}

Charge::~Charge() {}

int Charge::getX() {
	return x;
}

int Charge::getY() {
	return y;
}

int Charge::getRadius() {
	return RADIUS;
}

float Charge::getValue() {
	return value;
}

sf::CircleShape Charge::getShape() {
	return chargeShape;
}