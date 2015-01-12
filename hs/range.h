/* ==============================
* Author: yj
* Time：$time$
* FileName：$safeitemname$
* ===============================
*/
#ifndef RANGE_H
#define RANGE_H

#include <iostream>
#include <memory>


using namespace std;




class Range
{
public:
	enum Type
	{
		NONE,
		ALL,
		LSIDE,
		RSIDE,
		LSINGLE,
		RSINGLE,
		LPLAYER,
		RPLAYER,
		LACCOMPANY,
		RACCOMPANY,
		LSEXCEPT,
		RSEXCEPT,
		LACCEXCEPT,
		RACCEXCEPT,
		ALLEXCEPT,
	};

	Range()
	{}
		
	virtual Type getType()
	{
		return NONE;
	}
	
	virtual shared_ptr<Range> getExcept()
	{
		return nullptr;
	}

	virtual int getID()
	{
		return 0;
	}

	virtual bool isBelongTo(shared_ptr<Range> other)
	{
		return false;
	}

private:

	

};


class LSingleRange :public Range
{
public:
	LSingleRange(int id) :singleID(id)
	{
	}
	
	Type getType()
	{
		return LSINGLE;
	}


	bool isBelongTo(shared_ptr<Range> other)
	{
		if (other->getType()==LSIDE
			||(other->getType()==LSINGLE&&other->getID()==singleID)
			||other->getType()==ALL
			||(other->getType()==LSEXCEPT&&other->getExcept()->getType()==LSINGLE&&other->getExcept()->getID()!=singleID)
			|| (other->getType()==ALLEXCEPT&&other->getExcept()->getType()==LSINGLE&&other->getExcept()->getID()!=singleID))
		{
			return true;
		}
		return false;
	}

	int getID()
	{
		return singleID;
	}

private:
	int singleID;
};

class RSingleRange :public Range
{
public:
	RSingleRange(int id) :singleID(id)
	{
	}
	Type getType()
	{
		return RSINGLE;
	}



	int getID()
	{
		return singleID;
	}

	bool isBelongTo(shared_ptr<Range> other)
	{
		if (other->getType() == RSIDE
			|| (other->getType() == RSINGLE&&other->getID() == singleID)
			|| other->getType() == ALL
			|| (other->getType() == RSEXCEPT&&other->getExcept()->getType() == RSINGLE&&other->getExcept()->getID() != singleID)
			|| (other->getType() == ALLEXCEPT&&other->getExcept()->getType() == RSINGLE&&other->getExcept()->getID() != singleID))
		{
			return true;
		}
		return false;
	}

private:
	int singleID;
};


class LPlayerRange :public Range
{
public:
	LPlayerRange()
	{}

	Type getType()
	{
		return LPLAYER;
	}

	bool isBelongTo(shared_ptr<Range> other)
	{
		if (other->getType()==ALL
			||other->getType()==LSIDE
			||(other->getType()==LSEXCEPT&&other->getExcept()->getType()!=LPLAYER)
			||other->getType()==LPLAYER
			||(other->getType()==ALLEXCEPT&&other->getExcept()->getType()!=LPLAYER))
		{
			return true;
		}
		return false;
	}


};

class RPlayerRange :public Range
{
public:
	RPlayerRange()
	{}

	Type getType()
	{
		return RPLAYER;
	}
	shared_ptr<Range> getExcept()
	{
		return nullptr;
	}

	bool isBelongTo(shared_ptr<Range> other)
	{
		if (other->getType() == ALL
			|| other->getType() == RSIDE
			|| (other->getType() == RSEXCEPT&&other->getExcept()->getType() != RPLAYER)
			|| other->getType() == RPLAYER
			|| (other->getType() == ALLEXCEPT&&other->getExcept()->getType() != RPLAYER))
		{
			return true;
		}
		return false;
	}

};

class LSideRange :public Range
{
public:
	LSideRange()
	{}

	Type getType()
	{
		return LSIDE;
	}

	shared_ptr<Range> getExcept()
	{
		return nullptr;
	}
};

class RSideRange :public Range
{
public:
	Type getType()
	{
		return RSIDE;
	}

	shared_ptr<Range> getExcept()
	{
		return nullptr;
	}
};


class LAccompanyRange :public Range
{
public:
	Type getType()
	{
		return LACCOMPANY;
	}

	shared_ptr<Range> getExcept()
	{
		return nullptr;
	}
};


class RAccompanyRange :public Range
{
public:
	Type getType()
	{
		return RACCOMPANY;
	}

	shared_ptr<Range> getExcept()
	{
		return nullptr;
	}
};


class LSexceptRange :public Range
{
public:
	LSexceptRange(shared_ptr<Range> exc) :except(exc)
	{}
	Type getType()
	{
		return LSEXCEPT;
	} 

	shared_ptr<Range> getExcept()
	{
		return except;
	}


private:

	shared_ptr<Range> except;
	
}; 

class RSexceptRange :public Range
{
public:
	RSexceptRange(shared_ptr<Range> exc) :except(exc)
	{}

	Type getType()
	{
		return RSEXCEPT;
	}

	shared_ptr<Range> getExcept()
	{
		return except;
	}

private:
	shared_ptr<Range> except;
};

class RAccexceptRange :public Range
{
public:

	RAccexceptRange(shared_ptr<Range> exc) :except(exc)
	{}

	Type getType()
	{
		return RACCEXCEPT;
	}


	shared_ptr<Range> getExcept()
	{
		return except;
	}

private: 
	shared_ptr<Range> except;
};

class LAccexceptRange :public Range
{
public:

	LAccexceptRange(shared_ptr<Range> exc) :except(exc)
	{}

	Type getType()
	{
		return LACCEXCEPT;
	}

	shared_ptr<Range> getExcept()
	{
		return except;
	}

private:
	shared_ptr<Range> except;

};

class AllexceptRange :public Range
{
public:

	AllexceptRange(shared_ptr<Range> exc) :except(exc)
	{}

	Type getType()
	{
		return ALLEXCEPT;
	}
	shared_ptr<Range> getExcept()
	{
		return except;
	}

private:
	shared_ptr<Range> except;
};

class NoneRange :public Range
{
public:
	Type getType()
	{
		return NONE;
	}
};


#endif
