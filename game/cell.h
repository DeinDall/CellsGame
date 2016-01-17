#ifndef CELL_H
#define CELL_H

#include <list>
#include "stk/vec2.h"

class Cell {
public:
	class Link {
		friend class ::Cell;
	public:
		Link(Cell* a, Cell* b);
		~Link();

		void updatePhysics(float timestep);
		bool involves(Cell* cell) const;

		bool operator ==(const Link& other) const;

		Cell* getOther(const Cell* cell);

	protected:
		void replaceCellWith(Cell* from, Cell* to);

	protected:
		Cell* mA;
		Cell* mB;
	};
public:
	Cell();
	virtual ~Cell();

	unsigned int cellId() const;

	float mass() const;
	float radius() const;

	void mergeWith(Cell* other);

	virtual void update();

	stk::vec2 position() const;
	stk::vec2 velocity() const;
	stk::vec2 acceleration() const;

	void setForce(stk::vec2 force);

	void updatePhysics(float timestep);
	void updateLinkPhysics(float timestep);

	void move(const stk::vec2& offset);
	void motionStop();

	Link* findLinkWith(Cell* other) const;

	bool isDead() const;

protected:
	float massShareCap() const;

	virtual void onMassShare(float amount, Cell* to);
	virtual void onLinkWith(Cell* cell, Link* link);
	virtual void onUnlinkWith(Cell* cell, Link* link);
	virtual void onRelinkWith(Cell* oldcell, Cell* newcell, Link* link);

protected:
	unsigned int mCellId;

	float mRadius;
	float mMass, mMassPrevious;

	stk::vec2 mPosition, mPositionPrevious;
	stk::vec2 mForce;

	std::list<Link*> mLinks;

	bool mDied;

private:
	static unsigned int msCellIdCounter;
	static unsigned int msCellCount;
};

#endif // CELL_H
