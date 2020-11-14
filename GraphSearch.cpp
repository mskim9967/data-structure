#include <iostream>

template <typename T>
class Vertex {
public:
	T data;
	int weight;
	Vertex *link;
	Vertex(T _data) : data(_data), link(NULL) {}
	Vertex() {	Vertex(NULL);	}

	const bool operator== (const T arg) {
		return this -> data == arg;
	}
	const bool operator!= (const T arg) {
		return this -> data != arg;
	}
};


template <typename T>
class Graph {
public:
	typedef struct _Edge {
		Vertex<T> *v1Ptr, *v2Ptr;
		int weight;
	} Edge;

	const int VERTEX_MAX = 100;
	Vertex<T> **adjList;
	int vertexCnt;

	Graph() {
		vertexCnt = 0;
		adjList = new Vertex<T>*[VERTEX_MAX]();
	}

	void add_vertex(T data) {
		adjList[vertexCnt++] = new Vertex<T>(data);
	}

	int find_adjList_idx(T v) {
		int idx = 0;
		while(*adjList[idx++] != v);
		return --idx;
	}

	void add_edge(T v1, T v2) {
		int v1Pos, v2Pos;
		Vertex<T> *v1EdgePos, *v2EdgePos;

		v1Pos = find_adjList_idx(v1);
		for (v1EdgePos = adjList[v1Pos]; v1EdgePos -> link != NULL; v1EdgePos = v1EdgePos -> link);	//find position for new edge
		v1EdgePos -> link = new Vertex<T>(v2);

		v2Pos = find_adjList_idx(v2);
		for (v2EdgePos = adjList[v2Pos]; v2EdgePos -> link != NULL; v2EdgePos = v2EdgePos -> link);	//find position for new edge
		v2EdgePos -> link = new Vertex<T>(v1);


	}

	void delete_edge(T v1, T v2) {
		int v1Pos, v2Pos;
		Vertex<T> *v1EdgePos, *v2EdgePos, *delEdge;

		v1Pos = find_adjList_idx(v1);
		for (v1EdgePos = adjList[v1Pos]; *(v1EdgePos -> link) != v2; v1EdgePos = v1EdgePos -> link);	//find edge to delete
		delEdge = v1EdgePos -> link;
		v1EdgePos -> link = v1EdgePos -> link -> link;
		delete delEdge;

		v2Pos = find_adjList_idx(v2);
		for (v2EdgePos = adjList[v2Pos]; *(v2EdgePos -> link) != v1; v2EdgePos = v2EdgePos -> link);	//find edge to delete
		delEdge = v2EdgePos -> link;
		v2EdgePos -> link = v2EdgePos -> link -> link;
		delete delEdge;
	}

	void dfs(Vertex<T> *ptr) {
		bool isVisited[vertexCnt];
		for(int i = 0; i < vertexCnt; i++)
			isVisited[i] = false;
		dfs(ptr, isVisited);
	}

	void dfs(Vertex<T> *ptr, bool *isVisited) {
		isVisited[find_adjList_idx(ptr -> data)] = true;
		std::cout << ptr -> data << std::endl;

		for(ptr = ptr -> link; ptr != NULL; ptr = ptr -> link) {
			if(!isVisited[find_adjList_idx(ptr -> data)])
				dfs(adjList[find_adjList_idx(ptr -> data)], isVisited);
		}
	}

	void bfs(Vertex<T> *ptr) {
		Queue queue(vertexCnt);
		bool isVisited[vertexCnt];
		for(int i = 0; i < vertexCnt; i++)
			isVisited[i] = false;

		queue.push(ptr);
		while(!queue.isEmpty()) {
			Vertex<T> *v = queue.pop();
			if(!isVisited[find_adjList_idx(v -> data)]) {
				std::cout << v -> data << std::endl;
				isVisited[find_adjList_idx(v -> data)] = true;
				for(v = v -> link; v != NULL; v = v -> link) {
					if(!isVisited[find_adjList_idx(v -> data)])
						queue.push(adjList[find_adjList_idx(v -> data)]);
				}
			}
		}
	}

	class Queue{
	public:
		Vertex<T> **queue;
		int front, back, size;
		Queue(int _size) {
			queue = new Vertex<T>*[_size + 1];
			front = back = 0;
			size = _size;
		}

		void push(Vertex<T> *ptr) {
			queue[back] = ptr;
			back = (back + 1) % size;
		}

		Vertex<T> *pop() {
			Vertex<T> *returnVal = queue[front];
			queue[front] = NULL;
			front = (front + 1) % size;
			return returnVal;
		}

		bool isEmpty() {
			return (front == back);
		}
	};
};

int main(){
	Graph<int> graph;
	graph.add_vertex(7);
	graph.add_vertex(6);
	graph.add_vertex(5);
	graph.add_vertex(4);
	graph.add_vertex(3);
	graph.add_vertex(2);
	graph.add_vertex(1);
	graph.add_vertex(0);

	for(int i = 0; i < graph.vertexCnt; i++)
		std::cout << graph.adjList[i]->data <<std::endl;

	std::cout << "--------------------" << std::endl;

	graph.add_edge(0, 1);
	graph.add_edge(0, 2);
	graph.add_edge(1, 3);
	graph.add_edge(1, 4);
	graph.add_edge(2, 5);
	graph.add_edge(2, 6);
	graph.add_edge(3, 7);
	graph.add_edge(4, 7);
	graph.add_edge(5, 7);
	graph.add_edge(6, 7);

	for(int i = 0; i < graph.vertexCnt; i++){
		for(Vertex<int> *v = graph.adjList[i]->link;v!=NULL;v=v->link)
			std::cout << v->data;
		std::cout<<std::endl;
	}

	std::cout << "--------------------" << std::endl;

	graph.dfs(graph.adjList[0]);

	std::cout << "--------------------" << std::endl;

	graph.bfs(graph.adjList[0]);
} 
