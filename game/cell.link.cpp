#include "cell.h"

Cell::Link::Link(Cell* a, Cell* b) : mA(a), mB(b) {
	mA->onLinkWith(mB, this);
}

Cell::Link::~Link() {
	mA->onUnlinkWith(mB, this);
}

void Cell::Link::updatePhysics(float timestep) {
	stk::vec2 AB = mB->mPosition-mA->mPosition;

	float ABlen = AB.lenSq();

	float len = mB->radius()+mA->radius();
	len *= len*1.44f;

	if (ABlen<=len)
		return;

	stk::vec2 pushVec = AB.normalized()*(ABlen-len)*0.01f*timestep;

	mA->move( pushVec*(mB->mass()/mA->mass()));
	mB->move(-pushVec*(mA->mass()/mB->mass()));
}

bool Cell::Link::involves(Cell* cell) const {
	return mA==cell || mB==cell;
}

Cell* Cell::Link::getOther(const Cell* cell) {
	if (mA==cell)
		return mB;
	if (mB==cell)
		return mA;
	return nullptr;
}

void Cell::Link::replaceCellWith(Cell* from, Cell* to) {
	if (mA == from) {
		mA = to;
		mB->onRelinkWith(from, to, this);
	} else if (mB == from) {
		mB = to;
		mA->onRelinkWith(from, to, this);
	}
}

bool Cell::Link::operator ==(const Cell::Link& other) const {
	return ((mA==other.mA) && (mB==other.mB))
		|| ((mB==other.mA) && (mA==other.mB));
}
