#ifndef PHYSICS_H
#define PHYSICS_H

#include "physicslink.h"
#include <list>

class Physics {
public:
	Physics(bool doDeleteCellsOnDestruction = true);
	virtual ~Physics();

	void addPhysicsCell(PhysicsCell* cell);
	void addPhysicsLink(PhysicsLink* link);

	void removePhysicsCell(PhysicsCell* cell);

	void physicsUpdate();

	const std::list<PhysicsCell*>& physicsCells() const;

private:
	std::list<PhysicsCell*> mPhysicsCells;
	std::list<PhysicsLink*> mPhysicsLinks;

	float mPhysicsTimestep;

	bool mPhysicsDeleteOnDestruction;
};

#endif // PHYSICS_H
