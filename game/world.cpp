#include "world.h"

World::World() {
	mPhysicsTimestep = 0.1f;
}

World::~World() {
	for (Cell* cell : mCells)
		delete cell;
}

void World::addCell(Cell* newcell) {
	onNewCell(newcell);
}

void World::removeCell(Cell* cell) {
	onDestroyCell(cell);
}

void World::updatePhysics() {
	for (Cell* cell : mCells)
		if (!cell->isDead())
			cell->updatePhysics(mPhysicsTimestep);
	for (Cell* cell : mCells)
		cell->updateLinkPhysics(mPhysicsTimestep);

	for (Cell* cell1 : mCells) {
		for (Cell* cell2 : mCells) {
			if (cell1->cellId()<=cell2->cellId()) // redundance check (includes same-cell-check)
				continue;
			if (cell1->isDead() || cell2->isDead()) // dead cell
				continue;

			stk::vec2 C1C2 = cell2->position()-cell1->position();
			float r1 = cell1->radius(), r2 = cell2->radius(), distance = C1C2.lenSq();
			float radsum = (r1+r2)*(r1+r2);

			// too far to collide, unlink if linked
			if (distance>radsum*2.f) {
				Cell::Link* link = cell1->findLinkWith(cell2);
				if (link != nullptr)
					delete link;
				continue;
			}

			// merge if overlap too much
			if (distance<std::max(r1*r1, r2*r2)) {
				if (cell1->radius()>cell2->radius())
					cell1->mergeWith(cell2);
				else
					cell2->mergeWith(cell1);

				continue;
			}

			// link if touches
			if (distance<radsum) {
				if (cell1->findLinkWith(cell2) == nullptr)
					new Cell::Link(cell1, cell2);
			}

			// push away if too close
			if (distance<radsum*1.4f) { // 1.4 for push away, and 1.44 for push towards: this is to keep a distance interval where no sqrt are computed
				stk::vec2 pushVec = C1C2.normalized()*(0.05f/distance)*mPhysicsTimestep;

				cell1->move(-pushVec*(cell2->mass()/cell1->mass()));
				cell2->move( pushVec*(cell1->mass()/cell2->mass()));
			}
		}
	}
}

void World::updateLogic() {
	for (Cell* cell : mCells)
		cell->update();
}

void World::handleDeadCells() {
	std::list<Cell*> cells = mCells; // this is to allow removals on mCells

	for (Cell* cell : cells)
		if (cell->isDead())
			onDeadCell(cell);
}

Cell* World::getNearestCell(stk::vec2 from, bool ignoreDeadCells) const {
	float distance = -1;
	Cell* c = nullptr;

	for (Cell* cell : mCells) {
		if (ignoreDeadCells && cell->isDead())
			continue;
		stk::vec2 vec = cell->position()-from;
		if (vec.lenSq()<distance || distance<0) {
			distance = vec.lenSq();
			c = cell;
		}
	}

	return c;
}

Cell* World::findCellById(unsigned int id) const {
	for (Cell* cell : mCells)
		if (cell->cellId()==id)
			return cell;
	return nullptr;
}

void World::onNewCell(Cell* cell) {
	mCells.push_back(cell);
}

void World::onDeadCell(Cell* cell) {
	onDestroyCell(cell);
}

void World::onDestroyCell(Cell* cell) {
	mCells.remove(cell);
	delete cell;
}
