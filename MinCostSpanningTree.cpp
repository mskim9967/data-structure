#include <iostream>
#define VERT_MAX 100

template <typename T>
class Vertex {
public:
	T value;
	int key;
	Vertex(int _key, T _value) : key(_key), value(_value) {};
	void print(){
		std::cout << "(" << key << ", " << value << ")" << std::endl;
	}
	bool operator>(const Vertex<T> arg) const {
		return this -> key > arg.key;
	}
	bool operator>(const int arg) const {
		return this -> key > arg;
	}
	bool operator<(const Vertex<T> arg) const {
		return this -> key < arg.key;
	}
	bool operator<(const int arg) const {
		return this -> key < arg;
	}
	bool operator==(const Vertex<T> arg) const {
		return this -> key == arg.key;
	}
	bool operator==(const int arg) const {
		return this -> key == arg;
	}
};

template <typename T>
class Edge {
public:
	Vertex<T> *vert1, *vert2;
	int weight;
	Edge(Vertex<T> *_vert1, Vertex<T> *_vert2, int _weight) : vert1(_vert1), vert2(_vert2), weight(_weight) {};
	bool operator<(const Edge<T> arg) const {
		return this -> weight < arg.weight;
	}
	bool operator>(const Edge<T> arg) const {
		return this -> weight > arg.weight;
	}
	void print(){
		std::cout << "(" << vert1 -> key << ", " << vert1 -> value << ")--" << weight << "--(" << vert2 -> key << ", " << vert2 -> value << ")" << std::endl;
	}
};

class Set {
public:
	int arr[VERT_MAX], vertCnt;

	Set(){
		for(int i = 0; i < VERT_MAX; i++)	arr[i] = -1;
		vertCnt = 0;
	}

	void add_vert() {
		arr[vertCnt++] = vertCnt;
	}

	void uni(int vert1, int vert2) {
		if(vert1 < vert2)	arr[vert2] = vert1;
		else	arr[vert1] = vert2;
	}

	int find(int vert) {
		if(arr[vert] == vert)	return vert;
		else	return find(arr[vert]);
	}
};

template <typename T>
class MinHeap {
public:
	class Node {
	public:
		T *data;
		Node *left, *right;
		Node(T *_data) : data(_data), left(NULL), right(NULL) {};
		bool operator<(const Node arg) const {
			return *(this -> data) < *(arg.data);
		}
		bool operator>(const Node arg) const {
			return *(this -> data) > *(arg.data);
		}
	};

	Node **tree;
	int nodeCnt;

	MinHeap() {
		nodeCnt = 0;
		tree = new Node*[VERT_MAX];
	}
	~MinHeap(){
		for(int i = 0; i < nodeCnt; i++)	delete tree[i];
		delete tree;
	}

	void swap_node(Node **n1, Node **n2) {
		Node *temp = *n1;
		*n1 = *n2;
		*n2 = temp;
	}

	void push(T *data) {
		tree[++nodeCnt] = new Node(data);
		for(int selfIdx = nodeCnt, parentIdx = selfIdx / 2; parentIdx != 0 && *tree[selfIdx] < *tree[parentIdx]; selfIdx /= 2, parentIdx /= 2)
			swap_node(&tree[selfIdx], &tree[parentIdx]);
	}

	T *pop() {
		T *returnVal = tree[1] -> data;
		swap_node(&tree[1], &tree[nodeCnt]);
		tree[nodeCnt--] = NULL;
		for(int selfIdx = 1, lIdx = selfIdx * 2, rIdx = selfIdx * 2 + 1;;lIdx = selfIdx * 2, rIdx = selfIdx * 2 + 1) {
			if(tree[lIdx] != NULL && tree[rIdx] != NULL) {	//if both child have data
				if(*tree[selfIdx] < *tree[lIdx] && *tree[selfIdx] < *tree[rIdx])	//if tree is MinHeap
					break;
				swap_node(&tree[selfIdx], &(*tree[lIdx] < *tree[rIdx] ? tree[lIdx] : tree[rIdx]));	//swap itself and smaller child
				selfIdx = *tree[lIdx] < *tree[rIdx] ? lIdx : rIdx;
			}
			else if(tree[lIdx] != NULL) {	//if left child has data
				if(*tree[selfIdx] < *tree[lIdx])
					break;
				swap_node(&tree[selfIdx], &tree[lIdx]);
				selfIdx = lIdx;
			}
			else if(tree[rIdx] != NULL) {	//if right child has data
				if(*tree[selfIdx] < *tree[rIdx])
					break;
				swap_node(&tree[selfIdx], &tree[rIdx]);
				selfIdx = rIdx;
			}
			else	//if no child
				break;
		}
		return returnVal;
	}

	bool isEmpty() {
		return !nodeCnt;
	}

	void print() {
		for(int i = 1; i <= nodeCnt; i++)
			tree[i] -> data -> print();
	}

};

template <typename T>
class Graph {
public:
	Edge<T> **edgeList;
	Vertex<T> **vertList;
	int edgeCnt, vertCnt;

	Graph() {
		edgeList = new Edge<T>*[VERT_MAX * VERT_MAX];
		vertList = new Vertex<T>*[VERT_MAX];
		edgeCnt = vertCnt = 0;
	}
	~Graph(){
		for(int i = 0; i < edgeCnt; i++)	delete edgeList[i];
		for(int i = 0; i < vertCnt; i++)	delete vertList[i];
		delete edgeList;
		delete vertList;
	}

	void add_vert(int key, T value) {
		vertList[vertCnt++] = new Vertex<T>(key, value);
	}

	void add_edge(Vertex<T> *vert1, Vertex<T> *vert2, int weight) {
		edgeList[edgeCnt++] = new Edge<T>(vert1, vert2, weight);
	}

	void add_edge(int key1, int key2, int weight) {
		edgeList[edgeCnt++] = new Edge<T>(vertList[key1], vertList[key2], weight);
	}

	void copy_to(Graph<T>& cp) {	//deepcopy itself to cp
		cp.vertCnt = cp.edgeCnt = 0;
		for(int i = 0; i < vertCnt; i++)
			cp.add_vert(vertList[i] -> key, vertList[i] -> value);
		for(int i = 0; i < edgeCnt; i++)
			cp.add_edge(cp.vertList[edgeList[i] -> vert1 -> key],
				cp.vertList[edgeList[i] -> vert2 -> key], edgeList[i] -> weight);
	}

	void make_kruskal_to(Graph<T>& mst) {	//make min spanning tree to mst
		this -> copy_to(mst);

		Set vertSet;
		for(int i = 0; i < vertCnt; i++)
			vertSet.add_vert();

		MinHeap<Edge<T>> heap;
		for(int i = 0; i < edgeCnt; i++) {
			heap.push(mst.edgeList[i]);
			mst.edgeList[i] = NULL;
		}
		mst.edgeCnt = 0;

		for(Edge<T> *minEdge = heap.pop(); !heap.isEmpty(); minEdge = heap.pop()) {
			if(vertSet.find(minEdge -> vert1 -> key) != vertSet.find(minEdge -> vert2 -> key)) {	//if no cycle
				vertSet.uni(minEdge -> vert1 -> key, minEdge -> vert2 -> key);
				mst.add_edge(minEdge -> vert1, minEdge -> vert2, minEdge -> weight);
			}
		}
	}

	void make_prim_to(Graph<T>& mst) {
		this -> copy_to(mst);

		Set vertSet;
		for(int i = 0; i < vertCnt; i++)
			vertSet.add_vert();

		Edge<T> *primEdgeList[VERT_MAX * VERT_MAX];
		int primEdgeCnt = 0;
		MinHeap<Edge<T>> heap;

		for(int i = 0; i < edgeCnt; i++) {
			if(*(mst.edgeList[i] -> vert1) == 0 || *(mst.edgeList[i] -> vert2) == 0) {	//start with 0
				heap.push(mst.edgeList[i]);
				mst.edgeList[i] = NULL;
			}
		}

		for(Edge<T> *pop = heap.pop(); !heap.isEmpty(); pop = heap.pop()) {
			if(vertSet.find(pop -> vert1 -> key) != vertSet.find(pop -> vert2 -> key)) {	//if no cycle
				vertSet.uni(pop -> vert1 -> key, pop -> vert2 -> key);
				primEdgeList[primEdgeCnt++] = pop;
				for(int i = 0; i < edgeCnt; i++) {
					if(mst.edgeList[i] != NULL && (*(mst.edgeList[i] -> vert1) == *(pop -> vert1)
 						|| *(mst.edgeList[i] -> vert2) == *(pop -> vert1)
						|| *(mst.edgeList[i] -> vert1) == *(pop -> vert2)
						|| *(mst.edgeList[i] -> vert2) == *(pop -> vert2))) {
						heap.push(mst.edgeList[i]);
						mst.edgeList[i] = NULL;
					}
				}
			}
		}

		for(int i = 0; i < primEdgeCnt; i++)
			mst.edgeList[i] = primEdgeList[i];
		mst.edgeCnt = primEdgeCnt;
	}

};

int main() {
	Graph<char> graph, mstGraph;
	for(int i = 0; i < 7; i++)
		graph.add_vert(i, 'a' + i);

	graph.add_edge(0, 1, 28);
	graph.add_edge(0, 5, 10);
	graph.add_edge(1, 6, 14);
	graph.add_edge(1, 2, 16);
	graph.add_edge(2, 3, 12);
	graph.add_edge(3, 4, 22);
	graph.add_edge(3, 6, 18);
	graph.add_edge(4, 6, 24);
	graph.add_edge(4, 5, 25);

	graph.make_kruskal_to(mstGraph);
	for(int i = 0; i < mstGraph.edgeCnt; i++)
		(mstGraph.edgeList[i]) -> print();

	std::cout << "----------------------" << std::endl;

	graph.make_prim_to(mstGraph);
	for(int i = 0; i < mstGraph.edgeCnt; i++)
		(mstGraph.edgeList[i]) -> print();

/*
	for(int i = 0; i < g.vertCnt; i++)
		(g.vertList[i]) -> print();

	for(int i = 0; i < g.edgeCnt; i++)
		(g.edgeList[i]) -> print();

	MinHeap<Edge<char>> m;
	m.push(g.edgeList[0]);
	m.push(g.edgeList[1]);
	m.push(g.edgeList[2]);
	m.push(g.edgeList[3]);
	m.push(g.edgeList[4]);

	m.print();
	std::cout<<"pop: ";
	m.pop() -> print();

	m.print();
	*/
}
