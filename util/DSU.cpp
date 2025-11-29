#include "DSU.h"
#include <vector>
DSU::DSU(int size) {
	parent.resize(size);
	for (int i = 0; i < size; i++) {
		parent[i] = i;
	}
}
void DSU::setParent(int x, int p) {
	parent[x] = p;
}

void DSU::merge(int x, int y) {
	int px = findParent(x);
	int py = findParent(y);
	if (px != py) {
		setParent(px, py);
	}
}
int DSU::findParent(int x) {
	if (parent[x] != x) {
		parent[x] = findParent(parent[x]);
	}
	return parent[x];
}
