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
};

class List {
private:
    Node* list_head;
public:
    List() {
        list_head = nullptr;
    }

    bool empty() const {
        return (list_head == nullptr);
    }

    Node* head() const {
        return list_head;
    }

    void push_front(int n) {
        Node* newNode = new Node(n);
        if (empty()) {
            list_head = newNode;
            newNode->next_node = list_head; // points to itself
        } else {
            Node* ptr = list_head;
            while (ptr->next_node != list_head) {
                ptr = ptr->next_node;
            }
            ptr->next_node = newNode;
            newNode->next_node = list_head;
            list_head = newNode;
        }
    }

    void push_end(int n) {
        Node* newNode = new Node(n);
        if (empty()) {
            list_head = newNode;
            newNode->next_node = list_head;
        } else {
            Node* ptr = list_head;
            while (ptr->next_node != list_head) {
                ptr = ptr->next_node;
            }
            ptr->next_node = newNode;
            newNode->next_node = list_head;
        }
    }

    void pop_front() {
        if (empty()) {
            throw underflow_error("List is empty");
        }

        if (list_head->next_node == list_head) {
            delete list_head;
            list_head = nullptr;
            return;
        }

        Node* ptr = list_head;
        while (ptr->next_node != list_head) {
            ptr = ptr->next_node;
        }

        Node* old_head = list_head;
        list_head = list_head->next_node;
        ptr->next_node = list_head;
        delete old_head;
    }

    void pop_end() {
        if (empty()) {
            throw underflow_error("List is empty");
        }

        if (list_head->next_node == list_head) {
            delete list_head;
            list_head = nullptr;
            return;
        }

        Node* ptr = list_head;
        Node* prev = nullptr;
        while (ptr->next_node != list_head) {
            prev = ptr;
            ptr = ptr->next_node;
        }

        prev->next_node = list_head;
        delete ptr;
    }

    int erase(int n) {
        if (empty()) {
            throw underflow_error("List is empty");
        }

        int count = 0;
        Node* curr = list_head;
        Node* prev = nullptr;

        // handle head nodes with matching value
        while (curr->retrieve() == n) {
            if (curr->next_node == list_head) {
                delete curr;
                list_head = nullptr;
                count++;
                cout << "The number " << n << " was erased " << count << " times" << endl;
                return count;
            }

            // find last node to reconnect circularly
            Node* last = list_head;
            while (last->next_node != list_head) {
                last = last->next_node;
            }

            list_head = curr->next_node;
            last->next_node = list_head;
            delete curr;
            curr = list_head;
            count++;
        }

        // remove remaining nodes
        prev = curr;
        curr = curr->next_node;

        while (curr != list_head) {
            if (curr->retrieve() == n) {
                prev->next_node = curr->next_node;
                delete curr;
                curr = prev->next_node;
                count++;
            } else {
                prev = curr;
                curr = curr->next_node;
            }
        }

        cout << "The number " << n << " was erased " << count << " times" << endl;
        return count;
    }

    int size() const {
        if (empty()) {
            cout << "The size of the list is: 0" << endl;
            return 0;
        }

        int count = 0;
        Node* ptr = list_head;
        do {
            count++;
            ptr = ptr->next_node;
        } while (ptr != list_head);

        cout << "The size of the list is: " << count << endl;
        return count;
    }

    void display() const {
        if (empty()) {
            cout << "List is empty" << endl;
            return;
        }

        Node* ptr = list_head;
        do {
            cout << ptr->retrieve() << " ";
            ptr = ptr->next_node;
        } while (ptr != list_head);
        cout << endl;
    }
};

int main() {
    List l1;
    l1.push_front(10);
    l1.push_front(5);
    l1.push_end(15);
    l1.push_front(20);
    l1.push_end(25);

    l1.display();
    l1.size();
    l1.erase(15);
    l1.display();
    l1.pop_front();
    l1.display();
    l1.pop_end();
    l1.display();
}
