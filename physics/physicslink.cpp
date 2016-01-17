#include "physicslink.h"

PhysicsLink::PhysicsLink(PhysicsCell* a, PhysicsCell* b) : mA(a), mB(b) {
	mA->mLinks.push_back(this);
	mB->mLinks.push_back(this);
}

PhysicsLink::~PhysicsLink() {
	mA->mLinks.remove(this);
	mB->mLinks.remove(this);
}

void PhysicsLink::update(float timestep) {
	stk::vec2 AB = mB->pos-mA->pos;

	float ABlen = AB.lenSq();
	float len = mB->radius()+mA->radius();

	len *= len*1.44f;

	if (ABlen<=len)
		return;

	AB.normalize();

	stk::vec2 pushVec = AB*(ABlen-len)*0.01f*timestep;

	mA->pos += pushVec*(1.f/mA->mass()); //
	mB->pos -= pushVec*(1.f/mB->mass()); //
}

bool PhysicsLink::involves(PhysicsCell* cell) const {
	return mA==cell || mB==cell;
}

void PhysicsLink::replaceCellWith(PhysicsCell* from, PhysicsCell* to) {
	if (mA == from) {
		mA = to;
		mA->mLinks.push_back(this);
	}
	else if (mB == from) {
		mB = to;
		mB->mLinks.push_back(this);
	}
}

bool PhysicsLink::operator ==(const PhysicsLink& other) const {
	return ((mA==other.mA) && (mB==other.mB))
		|| ((mB==other.mA) && (mA==other.mB));
}
