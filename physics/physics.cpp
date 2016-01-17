#include "physics.h"

Physics::Physics(bool doDeleteCellsOnDestruction)
	: mPhysicsDeleteOnDestruction(doDeleteCellsOnDestruction) {
	mPhysicsTimestep = 0.1f;
}

Physics::~Physics() {
	for (PhysicsLink* link : mPhysicsLinks)
		delete link;
	if (mPhysicsDeleteOnDestruction)
		for (PhysicsCell* cell : mPhysicsCells)
			delete cell;
}

void Physics::addPhysicsCell(PhysicsCell* cell) {
	mPhysicsCells.push_back(cell);
}

void Physics::addPhysicsLink(PhysicsLink* link) {
	mPhysicsLinks.push_back(link);
}

void Physics::removePhysicsCell(PhysicsCell* cell) {
	mPhysicsCells.remove(cell);
	for (PhysicsLink* link : mPhysicsLinks)
		if (link->involves(cell))
			delete link;
}

void Physics::physicsUpdate() {
	for (PhysicsCell* cell : mPhysicsCells)
		cell->updateVerlet(mPhysicsTimestep);
	for (PhysicsLink* link : mPhysicsLinks)
		link->update(mPhysicsTimestep);

	std::list<PhysicsCell*> removedCells;

	for (PhysicsCell* cell1 : mPhysicsCells) {
		for (PhysicsCell* cell2 : mPhysicsCells) {
			if (cell1==cell2)
				continue;

			bool removed = false;
			for (PhysicsCell* c : removedCells)
				if (c == cell1 || c==cell2)
					removed = true;

			if (removed)
				continue;

			if (cell1->radius()<cell2->radius()) // FIXME: replace this with ids
				continue;

			stk::vec2 C1C2 = cell2->pos-cell1->pos;
			float r1 = cell1->radius(), r2 = cell2->radius(), distance = C1C2.lenSq();

			if (std::abs(C1C2.x)>(r1+r2)*1.5f || std::abs(C1C2.y)>(r1+r2)*1.5f)
				continue;

			if (distance<std::max(r1*r1, r2*r2)) { // Here we merge two cells
				PhysicsLink* l = cell1->findLinkWith(cell2);

				if (l!=nullptr) {
					delete l;
					mPhysicsLinks.remove(l);
				}

				cell1->mergeWith(cell2);

				if (mPhysicsDeleteOnDestruction)
					delete cell2;
				//mPhysicsCells.remove(cell2);
				removedCells.push_back(cell2);
				continue;
			}

			float radsum = (r1+r2)*(r1+r2);

			if (distance<radsum); // TODO: link two cells

			if (distance<radsum*1.44f) {
				C1C2.normalize();
				stk::vec2 pushVec = -C1C2*(0.01f/distance)*mPhysicsTimestep;

				cell1->pos += pushVec*(1.f/cell1->mass()); //
				cell2->pos -= pushVec*(1.f/cell2->mass()); //
			}
		}
	}

	for (PhysicsCell* c : removedCells)
		mPhysicsCells.remove(c);
}

const std::list<PhysicsCell*>& Physics::physicsCells() const {
	return mPhysicsCells;
}
