#include <iostream>
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

    Node* next() const {
        return next_node;
    }

    friend class List;
    friend class Stack;
};

class List {
private:
    Node* list_head;

public:
    List() {
        list_head = nullptr;
    }

    Node* head() const {
        return list_head;
    }

    bool empty() const {
        return (list_head == nullptr);
    }

    int size() const {
        int count = 0;
        for (Node* ptr = head(); ptr != nullptr; ptr = ptr->next()) {
            count++;
        }
        cout << "Size of the number is: " << count << endl;
        return count;
    }

    int count(int n) {
        int count = 0;
        for (Node* ptr = head(); ptr != nullptr; ptr = ptr->next()) {
            if (ptr->retrieve() == n)
                count++;
        }
        cout << "The number: " << n << " occured " << count << " times." << endl;
        return count;
    }

    int front() const {
        if (empty()) throw underflow_error("List is empty");
        return list_head->retrieve();
    }

    int end() const {
        if (empty()) throw underflow_error("List is empty");

        Node* ptr = list_head;
        while (ptr->next_node != nullptr)
            ptr = ptr->next_node;

        return ptr->retrieve();
    }

    void push_front(int n) {
        list_head = new Node(n, list_head);
    }

    void pop_front() {
        if (empty()) throw underflow_error("List is empty");
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
        while (ptr->next_node != nullptr)
            ptr = ptr->next_node;

        ptr->next_node = newNode;
    }

    void pop_end() {
        if (empty()) throw underflow_error("List is empty");

        if (list_head->next_node == nullptr) {
            delete list_head;
            list_head = nullptr;
            return;
        }

        Node* prev = list_head;
        Node* curr = list_head->next_node;

        while (curr->next_node != nullptr) {
            prev = curr;
            curr = curr->next_node;
        }

        prev->next_node = nullptr;
        delete curr;
    }

    int erase(int n) {
        if (empty()) throw underflow_error("List is empty");

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

class Stack {
private:
    Node* top_node;   

public:
    Stack() {
        top_node = nullptr;
    }

    bool empty() const {
        return (top_node == nullptr);
    }

    void push(int x) {
        top_node = new Node(x, top_node);
    }

    int top() const {
        if (empty()) throw underflow_error("Stack is empty");
        return top_node->retrieve();
    }

    void pop() {
        if (empty()) throw underflow_error("Stack is empty");

        Node* temp = top_node;
        top_node = top_node->next();
        delete temp;
    }

    void display() const {
        Node* ptr = top_node;
        cout << "Stack (top → bottom): ";
        while (ptr != nullptr) {
            cout << ptr->retrieve() << " ";
            ptr = ptr->next();
        }
        cout << endl;
    }
};

int main() {

    cout << "List" << endl;
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
    l1.erase(10);
    l1.display();
    cout << endl << endl;

    cout << "Stack" << endl;
    Stack s1;
    s1.push(10);
    s1.push(20);
    s1.push(30);
    s1.display();

    cout << "Top: " << s1.top() << endl;

    s1.pop();
    s1.display();

    return 0;
}
