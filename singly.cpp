#include <iostream>
using namespace std;

class Node {
private:
	int element;
	Node* next_node;
public:
	Node(int e = 0, Node* n = nullptr) : element(e), next_node(n){}
	int retrieve() const {
		return element;
	}
	Node* next()const {
		return next_node;
	}
	friend class List;
};

class List {
private:
	Node* list_head;
public:
	List() {
		list_head = nullptr;
	}
	Node* head()const {
		return list_head;
	}
	// TO check if the List is empty
	bool empty()const {
		return (list_head == nullptr);
	}
	int size() const{
		int count = 0;
		for (Node* ptr = head(); ptr != nullptr; ptr = ptr->next()) {
			count = count + 1;
		}
		cout << "Size of the number is: " << count << endl;
		return count;
	}
	int count(int n){
		int count = 0;
		for (Node* ptr = head(); ptr != nullptr; ptr = ptr->next()) {
			if (ptr->retrieve() == n) {
				count += 1;
			}
		}
		cout << "The number: " << n << " occured " << count << " times."<< endl;
		return count;
	}
	int front() const {
		if (empty()) {
			throw underflow_error("List is empty");
		}
		return list_head->retrieve();
	}
	int end()const {
		if (empty()) {
			throw underflow_error("List is Empty");
		}
		Node* ptr = list_head;
		while (ptr->next_node != nullptr) {
			ptr = ptr->next_node;
		}
		return ptr->retrieve();
	}
	void push_front(int n) {
		if (empty()) {
			list_head = new Node(n, nullptr);
		}
		else {
			list_head = new Node(n, head());
		}
	}
	void pop_front() {
		if (empty()) {
			throw underflow_error("List is empty");
		}

		Node* old_head = list_head;          
		list_head = list_head->next();     
		delete old_head;                      

	}
	void push_end(int z) {
		Node* newNode = new Node(z, nullptr);
		if (empty()) {
			list_head = newNode;
			return;
		}
		Node* ptr = list_head;
		while (ptr->next_node != nullptr) {
			ptr = ptr->next_node;
		}
		ptr->next_node = newNode;
	}

	void pop_end() {
		if (empty()) {
			throw underflow_error("List is empty!");
		}

		// Case 1 only one node
		if (list_head->next_node == nullptr) {
			delete list_head;
			list_head = nullptr;
			return;
		}

		// Otherwise, find the last node and its previous node
		Node* prev = list_head;
		Node* curr = list_head->next_node;
		while (curr->next_node != nullptr) {
			prev = curr;
			curr = curr->next_node;
		}

		// current is last node; previous is node before last
		prev->next_node = nullptr;
		delete curr;
	}

	int erase(int n) {
		if (empty()) {
			throw underflow_error("List is empty");
		}
		if (list_head->next_node == nullptr) {
			if (list_head->retrieve() == n) { // if the only node matches
				delete list_head;
				list_head = nullptr;
				return 1; // one node deleted
			}
			return 0; // value not found
		}

		int count = 0;
		while (list_head != nullptr && list_head->retrieve() == n) {
			Node* temporary = list_head;
			list_head = list_head->next();
			delete temporary;
			++count;
		}
		Node* ptr = list_head;
		while (ptr != nullptr && ptr->next() != nullptr) {
			if (ptr->next()->retrieve() == n) {
				Node* temp = ptr->next();
				ptr->next_node = ptr->next()->next();
				delete temp;
				++count;
			}
			else {
				ptr = ptr->next();
			}
		}
		cout << "Number of nodes deleted: " << count << endl;
		return count;
	}
	void display() {
		for (Node* ptr = list_head; ptr != nullptr; ptr = ptr->next()) {
			cout << ptr->retrieve() << " ";
		}
	}
};
int main() {
	List l1;
	l1.push_front(10);
	l1.push_front(5);
	l1.pop_front();
	l1.pop_front();
	l1.push_front(15);
	l1.push_front(10);
	l1.push_end(25);
	l1.push_end(20);
	l1.push_end(30);
	l1.pop_end();
	l1.push_end(10);
	l1.push_front(10);
	l1.size();
	//l1.count(10);
	l1.erase(10);
	l1.display();
}