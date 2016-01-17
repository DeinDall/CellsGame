#ifndef WORLD_H
#define WORLD_H

#include "cell.h"

class World {
public:
	World();
	virtual ~World();

	void addCell(Cell* newcell);
	void removeCell(Cell* cell);

	void updatePhysics();
	void updateLogic();
	void handleDeadCells();

	Cell* getNearestCell(stk::vec2 from, bool ignoreDeadCells = true) const;

	Cell* findCellById(unsigned int id) const;

protected:
	virtual void onNewCell(Cell* cell);
	virtual void onDeadCell(Cell* cell);
	virtual void onDestroyCell(Cell* cell);

protected:
	std::list<Cell*> mCells;

private:
	float mPhysicsTimestep;
};

#endif // WORLD_H
