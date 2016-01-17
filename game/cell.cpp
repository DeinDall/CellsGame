#include "cell.h"

unsigned int Cell::msCellIdCounter = 0;
unsigned int Cell::msCellCount = 0;

Cell::Cell() : mRadius(1.f), mMass(1.f), mDied(false) {
	mCellId = msCellIdCounter++;
	msCellCount++;

	// TODO: load cell from contents management (lua)

	mMassPrevious = mMass;
}

Cell::~Cell() {
	// Deletion of all Links
	std::list<Link*> copyList = mLinks; // a copy list is needed because link deletion affects mLinks

	for (Link* link : copyList)
		delete link;

	// Decrease cell count
	msCellCount--;
	if (msCellCount==0)
		msCellIdCounter = 0;
}

unsigned int Cell::cellId() const {
	return mCellId;
}

float Cell::radius() const {
	return mRadius;
}

float Cell::mass() const {
	return mMass;
}

void Cell::mergeWith(Cell* other) {
	// Transfering all links
	std::list<Link*> links = other->mLinks;

	for (Link* link : links) {
		Cell* linked = link->getOther(other);
		if (findLinkWith(linked)!=nullptr || linked==this) // prevents duplicate links
			delete link;
		else
			link->replaceCellWith(other, this);
	}

	// Transfering mass
	other->onMassShare(other->mMass, this);

	// Killing other cell
	other->mDied = true;
}

void Cell::update() {
	if (isDead())
		return;

	// Share mass with neighbors
	float mass = mMass, cap = massShareCap();

	for (Link* link : mLinks) {
		Cell* cell = link->getOther(this);

		if (cell->mMass < cap) {
			// TODO: condider volatility (Ediff*(sqrt(V*v)/1000);
			float m = (mass-cell->mMass)/(100.f*mLinks.size());
			onMassShare(m, cell);
		}
	}

	// Update radius if mass updated
	if (mMass != mMassPrevious) // || mDensityUpdated
		mRadius = sqrtf(mMass); // TODO: consider density (r = sqrt(M/D);)
	mMassPrevious = mMass;
}

stk::vec2 Cell::position() const {
	return mPosition;
}

stk::vec2 Cell::velocity() const {
	return stk::vec2(mPosition - mPositionPrevious);
}

stk::vec2 Cell::acceleration() const {
	return stk::vec2(mForce/mass());
}

void Cell::setForce(stk::vec2 force) {
	mForce = force;
}

void Cell::updatePhysics(float timestep) {
	// add friction
	stk::vec2 force = mForce - (mPosition - mPositionPrevious)*0.8f;

	// Verlet update
	stk::vec2 oldPos = mPosition;
	mPosition += mPosition - mPositionPrevious + (force/mass())*timestep*timestep;
	mPositionPrevious = oldPos;
}

void Cell::updateLinkPhysics(float timestep) {
	for (Link* link : mLinks)
		if (link->mA == this) // this is to prevent physics update to trigger twice (once for each cell of a link)
			link->updatePhysics(timestep);
}

void Cell::move(const stk::vec2& offset) {
	mPosition += offset;
}

void Cell::motionStop() {
	// Stop motion
	mForce = stk::vec2(0, 0);
	mPositionPrevious = mPosition;
}

Cell::Link* Cell::findLinkWith(Cell* other) const {
	for (Link* link : mLinks)
		if (link->involves(other))
			return link;
	return nullptr;
}

bool Cell::isDead() const {
	return mDied;
}

float Cell::massShareCap() const {
	return mMass*0.9f; // TODO: use lua
}

void Cell::onMassShare(float amount, Cell* to) {
	mMass -= amount;
	to->mMass += amount;
}

void Cell::onLinkWith(Cell* cell, Link* link) {
	mLinks.push_back(link);
	cell->mLinks.push_back(link);
}

void Cell::onUnlinkWith(Cell* cell, Link* link) {
	mLinks.remove(link);
	cell->mLinks.remove(link);
}

void Cell::onRelinkWith(Cell* oldcell, Cell* newcell, Link* link) {
	oldcell->mLinks.remove(link);
	newcell->mLinks.push_back(link);
}
