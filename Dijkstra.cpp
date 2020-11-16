#include <iostream>
#include <vector>
#include <deque>
#define INT_MAX 9999

using namespace std;

template <typename T>
class Vertex{
public:
	int key;
	T value;
	Vertex(int _key, T _value) : key(_key), value(_value) {};
	bool operator==(const int arg) const {	return this -> key == arg;	}
	bool operator!=(const int arg) const {	return this -> key != arg;	}
	void print() {	cout << "(" << key << ", " << value << ")"; }
};

template <typename T>
class Edge{
public:
	Vertex<T> *from, *to;
	int weight;
	Edge(Vertex<T> *v1, Vertex<T> *v2, int w) : from(v1), to(v2), weight(w) {};
	void print() {	from -> print(); cout << " --- (" << weight << ") ---> "; to -> print(); cout << endl;	}
};

template <typename T>
class Graph{
public:
	vector<Vertex<T>> vertVec;
	vector<Edge<T>> edgeVec;

	void add_vert(int key, T value) {
		Vertex<T> temp(key, value);
		vertVec.push_back(temp);
	}

	void add_edge(int fromKey, int toKey, int weight) {
		Vertex<T> *from, *to;
		for(int i = 0; i < vertVec.size(); i++) {
			if(vertVec[i] == fromKey)	from = &vertVec[i];
			if(vertVec[i] == toKey)	to = &vertVec[i];
		}
		Edge<T> temp(from, to, weight);
		edgeVec.push_back(temp);
	}


	void dijkstra(int sKey) {
		int weight[vertVec.size()][vertVec.size()];
    	int prev[vertVec.size()];
		for(int i =0; i < vertVec.size(); i++)
			for(int j =0; j < vertVec.size(); j++)
				weight[i][j] = 0;
		for(int i =0; i < edgeVec.size(); i++)
			weight[edgeVec[i].from -> key][edgeVec[i].to -> key] = edgeVec[i].weight;

		vector<bool> isMin;
		vector<int> minWeight;
		vector<vector<Vertex<T>*>> minPath;
		for(int i = 0; i < vertVec.size(); i++) {
			minWeight.push_back(INT_MAX);
			minPath.push_back(vector<Vertex<T>*>());
			isMin.push_back(false);
		}

		minWeight[sKey] = 0;
        prev[sKey] = -1;
		while(1) {
			int nowKey = -1;
			for(int i = 0, min = INT_MAX; i < vertVec.size(); i++) {
				if(!isMin[i] && min > minWeight[i]) {
					min = minWeight[i];
					nowKey = i;
				}
			}
			if(nowKey == -1) break;
			isMin[nowKey] = true;

			for(int i = 0; i < vertVec.size(); i++) {
				if(weight[nowKey][i] != 0 && minWeight[i] > minWeight[nowKey] + weight[nowKey][i]) {
					minWeight[i] = minWeight[nowKey] + weight[nowKey][i];
                    prev[i] = nowKey;

				}
			}
		}

		for(int i = 0; i < minWeight.size(); i++) {
			if(minWeight[i] == INT_MAX || sKey == i)	continue;
            for(int j = i; j != -1; j = prev[j]) {
                cout << j << " ";
			}
			cout << " [" << minWeight[i] << "] " << endl;
		}
	}

	void print_vert() {	for(int i = 0; i < vertVec.size(); i++)	vertVec[i].print();	}
	void print_edge() {	for(int i = 0; i < edgeVec.size(); i++)	edgeVec[i].print();	}
};

int main() {
	Graph<char> g;

	for(int i = 0; i <= 5; i++) 
		g.add_vert(i, 'a' + i);

	g.add_edge(0, 1, 50);
	g.add_edge(0, 2, 45);
	g.add_edge(0, 3, 10);
	g.add_edge(1, 2, 10);
	g.add_edge(1, 3, 15);
	g.add_edge(2, 4, 30);
	g.add_edge(3, 0, 20);
	g.add_edge(3, 4, 15);
	g.add_edge(4, 1, 20);
	g.add_edge(4, 2, 35);
	g.add_edge(5, 4, 3);

	g.dijkstra(0);
}
