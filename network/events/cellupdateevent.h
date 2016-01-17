#ifndef CELLUPDATEEVENT_H
#define CELLUPDATEEVENT_H

#include "network/gameevent.h"
#include "network/networkcell.h"

class CellUpdateEvent : public GameEvent {
public:
	CellUpdateEvent(NetworkCell* cell);

	void pack(sf::Packet& packet);
	void unpack(sf::Packet& packet);

private:
	NetworkCell* mCell;
};

#endif // CELLUPDATEEVENT_H
