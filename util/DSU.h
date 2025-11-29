#ifndef NAVIGATION_UTIL_DSU_H_
#define NAVIGATION_UTIL_DSU_H_
#include <vector>
class DSU {
private:
	DSU(int size);
public:
	std::vector<int> parent;
	int findParent(int x);
	void setParent(int x, int p);
	void merge(int x,int y);
};

#endif
