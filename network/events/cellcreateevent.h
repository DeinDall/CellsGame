#ifndef CELLCREATEEVENT_H
#define CELLCREATEEVENT_H

#include "cellupdateevent.h"

class CellCreateEvent : public CellUpdateEvent {
public:
	CellCreateEvent(NetworkCell* cell);
};

#endif // CELLCREATEEVENT_H
