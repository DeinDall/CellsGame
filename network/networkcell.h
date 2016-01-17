#ifndef NETWORKCELL_H
#define NETWORKCELL_H

#include "game/cell.h"
#include "gameevent.h"

class NetworkCell : public Cell {
public:
	NetworkCell();

public:
	void fillPacket(sf::Packet& packet);
	void updateFromPacket(sf::Packet& packet);
};

#endif // NETWORKCELL_H
