#include "clientcell.h"

ClientCell::ClientCell() {
	mClientDeath = false;
	mGraphicalLife = 1.f;
	mGraphicalRadius = 0.5f;
}

float ClientCell::graphicalLife() const {
	return mGraphicalLife;
}

float ClientCell::graphicalRadius() const {
	return mGraphicalRadius;
}

sf::Vector2f ClientCell::graphicsPosition() const {
	return position();
}

void ClientCell::update() {
	Cell::update();

	if (isDead()) {
		mGraphicalLife -= 0.01f;
		mRadius = 0;
		if (mGraphicalLife<0.f)
			mClientDeath = true;
	}

	if (mGraphicalRadius < mRadius-0.01f || mGraphicalRadius > mRadius+0.01f)
		mGraphicalRadius += (mRadius-mGraphicalRadius)/16.f;
}

void ClientCell::kill() {
	mDied = true;
}

bool ClientCell::isClientDead() const {
	return mClientDeath;
}
