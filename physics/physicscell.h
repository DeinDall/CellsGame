#ifndef PHYSICSCELL_H
#define PHYSICSCELL_H

#include "game/corecell.h"
#include <list>

class PhysicsLink;

class PhysicsCell : public virtual CoreCell {
public:
	PhysicsCell();

	void updateVerlet(float timestep);
	void stopMotion();

	void mergeWith(CoreCell* cell);
//	void unlink();

	PhysicsLink* findLinkWith(PhysicsCell* cell) const;

	bool isPhysicsDead() const;

protected:
	stk::vec2 mForce; // acceleration
	std::list<PhysicsLink*> mLinks;

	friend class PhysicsLink;

private:
	stk::vec2 mPositionPrevious;
	bool mPhysicalDeath;
};

#endif // PHYSICSCELL_H
