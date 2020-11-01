#include <iostream>

class MaxHeap {
public:
	class Node {
	public:
		int data;
		bool isNull;
		Node(int data) {
			this -> data = data;
			isNull = false;
		}
		Node(){
			isNull = true;
		}
	};
    Node *biTree;
    int top; 
    
    MaxHeap(){
    	biTree  = new Node[100]();
    	top = 0;
    }
	
	void swap(Node &a, Node &b) {
		Node temp = a;
		a = b;
		b= temp;
	}    
	
    void push(int data) {
    	biTree[++top] = Node(data);
    	for(int idx = top; idx != 1 && biTree[idx / 2].data < biTree[idx].data; idx /= 2) 
    		swap(biTree[idx], biTree[idx / 2]);
    }
    
    int pop() {
    	swap(biTree[1], biTree[top]);
    	int returnVal = biTree[top].data;
    	biTree[top--] = Node();
    	
    	for(int i = 1; biTree[i * 2].isNull == false || biTree[i * 2 + 1] .isNull == false;) {
    		if(biTree[i * 2].isNull == true && biTree[i * 2 + 1].isNull == false) 
    			i = i * 2 + 1;
    		else if(biTree[i * 2].isNull == false && biTree[i * 2 + 1].isNull == true) 
    			i = i * 2;
    		else
    			i = biTree[i * 2].data > biTree[i * 2 + 1].data ? i * 2 : i * 2 + 1; 
    		
    		if(biTree[i / 2].data < biTree[i].data) 
    			swap(biTree[i / 2], biTree[i]);
    		else break;
    	}
    	return returnVal;
    }
        
    void print(){
    	for(int i = 1; i<=top; i++)std::cout<<biTree[i].data << " ";
    	std::cout<<std::endl;
    }
};

int main(){
	MaxHeap heap;
	heap.push(10);
	heap.push(2);
	heap.push(15);
	heap.push(-4);
	heap.push(7);
	heap.push(3);
	heap.push(0);
	heap.push(-20);
	heap.push(-3);
	heap.push(21);
	heap.push(1);
	heap.push(0);
	heap.push(21);
	heap.push(0);
	heap.push(-2);
	heap.print();
	
	heap.pop();
	heap.print();
	heap.pop();
	heap.print();
	heap.pop();
	heap.print();
	heap.pop();
	heap.print();
	heap.pop();
	heap.print();
	heap.pop();
	heap.print();
	heap.pop();
	heap.print();
	heap.pop();
	heap.print();
	heap.pop();
	heap.print();
	heap.pop();
	heap.print();
	heap.pop();
	heap.print();
	heap.pop();
	heap.print();
	heap.pop();
	heap.print();
	heap.pop();
	heap.print();
	heap.pop();
	heap.print();
	
}
