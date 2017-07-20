
#ifndef LINESRLIST_H
#define LINEARLIST_H

//=========================================================================
//the abstract class of linear list

template<class T>
class LinearList{
public:
	virtual ~LinearList() {};
	virtual bool empty() const = 0;
	virtual int size() const = 0;
	virtual T& get(int theIndex) const = 0;
	virtual int indexOf(const T& theElem) const = 0;
	virtual void erase(int theIndex) = 0;
	virtual void insert(int theIndex , const T& theElem) = 0;
	virtual void pushBack(const T &theElem) = 0;
	virtual void show(std::ostream& out) const = 0;

};

#endif
