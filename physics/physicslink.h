#ifndef PHYSICSLINK_H
#define PHYSICSLINK_H

#include "physicscell.h"

class PhysicsLink {
public:
	PhysicsLink(PhysicsCell* a, PhysicsCell* b);
	~PhysicsLink();

	void update(float timestep);
	bool involves(PhysicsCell* cell) const;

	void replaceCellWith(PhysicsCell* from, PhysicsCell* to);

	bool operator ==(const PhysicsLink& other) const;

protected:
	PhysicsCell* mA;
	PhysicsCell* mB;

//	float mLength;
};

#endif // PHYSICSLINK_H
