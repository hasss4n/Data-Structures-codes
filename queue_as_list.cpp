// Queue as a SINGLY LINKED-LISTTTTTTTTT

#include<iostream>
using namespace std;
class Node {
private:
	int element;
	Node* next_node;
public:
	Node(int e = 0, Node* n = nullptr) : element(e), next_node(n) {}
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
	int size() const {
		int count = 0;
		for (Node* ptr = head(); ptr != nullptr; ptr = ptr->next()) {
			count = count + 1;
		}
		cout << "Size of the number is: " << count << endl;
		return count;
	}
	int count(int n) {
		int count = 0;
		for (Node* ptr = head(); ptr != nullptr; ptr = ptr->next()) {
			if (ptr->retrieve() == n) {
				count += 1;
			}
		}
		cout << "The number: " << n << " occured " << count << " times." << endl;
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
	int pop_front() {
		if (empty()) {
			throw underflow_error("List is empty");
		}
		int value = list_head->retrieve();
		Node* old_head = list_head;
		list_head = list_head->next();
		delete old_head;
		return value;
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
class Queue {
private:
	List l;
public:
	bool empty()const {
		return l.empty();
	}
	void push(int n) {
		l.push_end(n);
	}
	int pop() {
		if (empty()) {
			throw underflow_error("Empty!! ");
		}
		return l.pop_front();
	}
	int top() {
		if (empty()) {
			throw underflow_error("Empty!!");
		}
		return l.front();
	}

};
int main() {
	Queue q1;
	q1.push(8);
	q1.push(6);
	q1.push(12);
	q1.push(9);
	q1.push(4);
	q1.push(2);
	q1.pop();
	q1.pop();
	q1.pop();
	cout << "Front element: " << q1.top() << endl;
	return 0;
}