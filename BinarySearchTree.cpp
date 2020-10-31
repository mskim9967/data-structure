#include <iostream>
#include <limits> 
#define PREORDER 1

template <typename T>
class BinarySearchTree {
public:
	class Node {
	public:
		T data;
		int key;
		Node *left, *right, *parent;
		Node(T data, int key) {
			this -> data = data;
			this -> key = key;
			left = right = parent = NULL;
		}
		Node(){
			Node(NULL, NULL);
		}
		bool operator<(const int& key) const {
			return (this -> key < key);
		}
	};
	
	Node *root;
	
	BinarySearchTree() : root(NULL) {}
	
	void add_node(T data, int key) {
		if(root == NULL)	root = new Node(data, key);	//첫 노드 삽입
		else	add_node(data, key, root, NULL);
	}
	
	void add_node(T data, int key, Node *nodePtr, Node *nodeParentPtr) {
		if(nodePtr == NULL) {
			if(*nodeParentPtr < key ) {
				nodeParentPtr -> right = new Node(data, key); 
				nodeParentPtr -> right -> parent = nodeParentPtr;
			}
			else {
				nodeParentPtr -> left = new Node(data, key);
				nodeParentPtr -> left -> parent = nodeParentPtr;
			}
		}
		else {
			nodeParentPtr = nodePtr;
			nodePtr = *nodePtr < key? nodePtr -> right : nodePtr -> left;
			add_node(data, key, nodePtr, nodeParentPtr);
		}
	}
	
	Node *find_nodePtr(int key) {
		Node *curr = root;
		while(curr != NULL && key != curr -> key) 
			curr = *curr < key ? curr -> right : curr -> left;
		return curr;	//못찾으면 NULL 반환
	}
	
	void connect_parent_child(Node *parent, Node *child) {
		(parent -> left == child -> parent ? parent -> left : parent -> right) = child;
	}
	
	void disconnect_parent_itself(Node *itself) {
		(itself -> parent -> left == itself ? itself -> parent -> left : itself -> parent -> right) = NULL;
	}
	
	bool delete_node(int key) {
		Node *deletePtr = find_nodePtr(key);
		if(deletePtr == NULL)	return false;	//삭제할 노드 못찾으면 종료
	
		if(deletePtr -> right != NULL && deletePtr -> left == NULL)	//삭제할 노드에 우측자식이 있으면 부모와 우측 연결
			connect_parent_child(deletePtr -> parent, deletePtr -> right);
		
		else if(deletePtr -> right == NULL && deletePtr -> left != NULL)	//삭제할 노드에 좌측자식이 있으면 부모와 좌측 연결
			connect_parent_child(deletePtr -> parent, deletePtr -> left);
			
		else if(deletePtr -> right != NULL && deletePtr -> left != NULL) {	//삭제할 노드에 양쪽자식이 있으면
			Node *swapPtr = deletePtr-> right;	
			while(swapPtr -> left != NULL) 	//대체 노드(삭제노드보다 큰 최소값) 찾기
				swapPtr = swapPtr -> left;
			deletePtr -> data = swapPtr -> data;	//키값노드, 대체노드 교환
			deletePtr -> key = swapPtr -> key;	//키값노드, 대체노드 교환
			if(swapPtr -> right != NULL)	//대체노드에 자식이 있으면 부모와 자식 연결
				connect_parent_child(swapPtr -> parent, swapPtr -> right);
			else	//대체노드에 자식이 없으면 대체노드와 부모 연결 해제
				disconnect_parent_itself(swapPtr);
			deletePtr = swapPtr;
		}
		else {	//삭제할 노드에 자식이 없을 때
			if(deletePtr == root)	return false;	//루트값이면 종료	
			disconnect_parent_itself(deletePtr);	//삭제노드와 부모 연결 해제		
		}
		delete deletePtr;
		return true;
	}
	
	void print(int order) {
		switch(order){
			case PREORDER :
				preorder(root);
				break;
		}
		std::cout << std::endl;
	}
	void preorder(Node *ptr) {
		if(ptr) {
			std::cout << "(" << ptr -> key << ", " << ptr -> data << ") " ;
			preorder(ptr -> left); 
			preorder(ptr -> right);
		}
	}
	
};

int main() {
	BinarySearchTree<char> bst;
	bst.add_node('a', 10);
	bst.add_node('b', -10);
	bst.add_node('c', 5);
	bst.add_node('d', -2);
	bst.add_node('e', -20);
	bst.add_node('f', 32);
	bst.add_node('g', 7);
	bst.add_node('h', 3);
	bst.add_node('i', 1);
	bst.add_node('j', 4);
	bst.print(PREORDER);

	std::cout << bst.find_nodePtr(-20) -> data << std::endl;
	
	std::cout << "DELETE NODE 1"<< std::endl;	
	bst.delete_node(1);
	bst.print(PREORDER);
	std::cout << "DELETE NODE 3"<< std::endl;	
	bst.delete_node(3);
	bst.print(PREORDER);
	std::cout << "DELETE NODE 32"<< std::endl;	
	bst.delete_node(32);
	bst.print(PREORDER);
	std::cout << "DELETE NODE 1000"<< std::endl;	
	bst.delete_node(1000);
	bst.print(PREORDER);

}
