#ifndef CELLDESTROYEVENT_H
#define CELLDESTROYEVENT_H

#include "cellupdateevent.h"

class CellDestroyEvent : public CellUpdateEvent {
public:
	CellDestroyEvent(NetworkCell* cell);
};

#endif // CELLDESTROYEVENT_H
