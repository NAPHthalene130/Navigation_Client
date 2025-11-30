#ifndef NAVIGATION_UTIL_DSU_H_
#define NAVIGATION_UTIL_DSU_H_
#include <vector>
class DSU {
private:
	std::vector<int> parent;
public:
	DSU(int size);
	int findParent(int x);
	void setParent(int x, int p);
	void merge(int x,int y);
};

#endif
