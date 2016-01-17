#include "physicscell.h"
#include "physicslink.h"

PhysicsCell::PhysicsCell() {
	mPhysicalDeath = false;
}

void PhysicsCell::updateVerlet(float timestep) {
	mForce = -(pos - mPositionPrevious)*timestep*5.f;

	stk::vec2 oldPos = pos;
	pos += pos - mPositionPrevious + (mForce/mass())*timestep*timestep;
	mPositionPrevious = oldPos;
}

void PhysicsCell::stopMotion() {
	mForce = stk::vec2(0, 0);
	mPositionPrevious = pos;
}

void PhysicsCell::mergeWith(CoreCell* cell) {
	PhysicsCell* c = dynamic_cast<PhysicsCell*>(cell);

	for (PhysicsLink* l : c->mLinks)
		l->replaceCellWith(c, this);

	c->mLinks.clear();
	c->mPhysicalDeath = true;
}

/*
void PhysicsCell::unlink() {
	std::list<PhysicsLink*> copyList = mLinks;

	// a copy list is needed because link deletion affects mLinks
	for (PhysicsLink* link : copyList)
		delete link;
} //*/

PhysicsLink* PhysicsCell::findLinkWith(PhysicsCell* cell) const {
	for (PhysicsLink* link : mLinks)
		if (link->involves(cell))
			return link;
	return nullptr;
}

bool PhysicsCell::isPhysicsDead() const {
	return mPhysicalDeath;
}
