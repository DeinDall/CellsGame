#include "networkcell.h"

NetworkCell::NetworkCell() {}

void NetworkCell::fillPacket(sf::Packet& packet) {
	packet << mMass << mPosition.x << mPosition.y << mPositionPrevious.x << mPositionPrevious.y << mForce.x << mForce.y;
}

void NetworkCell::updateFromPacket(sf::Packet& packet) {
	packet >> mMass >> mPosition.x >> mPosition.y >> mPositionPrevious.x >> mPositionPrevious.y >> mForce.x >> mForce.y;
}
