#include <iostream>

class Node {
public:

	int key, runNum;
	Node(int _key, int _run) : key(_key), runNum(_run){};
	Node(){
		key = INT_MAX;
	};
	bool operator<(const Node& arg) const{
		return this -> key < arg.key;
	}
};


class LoserTree {
public:

	const int RUNMAX = 100;

	Node **run, **tree;
	int *runTop, runCount;

	LoserTree(int _runCount) {
		runCount = _runCount;
		tree = new Node*[runCount * 2]();
		run = new Node*[runCount]();
		runTop = new int[runCount];
		for(int i = 0; i < runCount; i++) {
			run[i] = new Node[RUNMAX]();
			run[i][0] = Node(INT_MAX, i);
			runTop[i] = 0;
		}
	}

	void addKey(int _run, int _key) {
		run[_run][++runTop[_run]] = Node(_key, _run);
	}

	void setTree() {
		Node **winTree = new Node*[runCount * 2]();
		for(int i = 0; i < runCount; i++)
			winTree[i + runCount] = tree[i + runCount] = &run[i][runTop[i]--];

		for(int i = runCount - 1; i > 0; i--) {
			winTree[i] = *(winTree[i * 2]) < *(winTree[i * 2 + 1]) ? winTree[i * 2] : winTree[i * 2 + 1];
			tree[i] = *(winTree[i * 2]) < *(winTree[i * 2 + 1]) ? winTree[i * 2 + 1] : winTree[i * 2];
		}
		tree[0] = winTree[1];
		delete[] winTree;
	}

	Node* popTree() {
		Node* returnVal = tree[0];
		int changedRun = tree[0] -> runNum;
		tree[0] = tree[runCount + changedRun] = &run[changedRun][runTop[changedRun]--];
		for(int i = (runCount + changedRun) / 2; i > 0; i /= 2) {
			if(*tree[i] < *tree[0]) {
				Node* temp = tree[0];
				tree[0] = tree[i];
				tree[i] = temp;
			}
		}
		return returnVal;
	}
};

int main() {
	std::cout << "---------------------------------------" << std::endl;
	LoserTree lt(8);

	lt.addKey(0, 16);	lt.addKey(0, 15);	lt.addKey(0, 10);
	lt.addKey(1, 38);	lt.addKey(1, 20);	lt.addKey(1, 9);
	lt.addKey(2, 30);	lt.addKey(2, 20);	lt.addKey(2, 20);
	lt.addKey(3, 28);	lt.addKey(3, 25);	lt.addKey(3, 15);	lt.addKey(3, 6);
	lt.addKey(4, 50);	lt.addKey(4, 15);	lt.addKey(4, 8);
	lt.addKey(5, 16);	lt.addKey(5, 11);	lt.addKey(5, 9);
	lt.addKey(6, 99);	lt.addKey(6, 95);	lt.addKey(6, 90);
	lt.addKey(7, 20);	lt.addKey(7, 18);	lt.addKey(7, 17);

	lt.setTree();
	for(int popVal = lt.popTree() -> key; popVal != INT_MAX; popVal = lt.popTree() -> key) {
		std::cout << popVal << std::endl;
	}

	std::cout << "---------------------------------------" << std::endl;
}
