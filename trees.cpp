#include <iostream>
#include <algorithm> // Added for std::max usage in height() if needed, though usually included in iostream implementation-dependently
using namespace std;

template <typename T>
class node {
protected:
    T element;
    node<T>* next_node;

public:
    node(T e = T(), node<T>* n = nullptr) : element(e), next_node(n) {}

    T retrieve() const {
        return element;
    }

    node<T>* next() const {
        return next_node;
    }

    template <typename U>
    friend class list;
};

template <typename T>
class list {
private:
    node<T>* list_head;

public:
    list() : list_head(nullptr) {}

    node<T>* head() const {
        return list_head;
    }

    bool empty() const {
        return list_head == nullptr;
    }

    int size() {
        int count = 0;
        for (node<T>* ptr = head(); ptr != nullptr; ptr = ptr->next()) {
            count++;
        }
        return count;
    }

    int count(T n) {
        int c = 0;
        for (node<T>* ptr = head(); ptr != nullptr; ptr = ptr->next()) {
            if (ptr->retrieve() == n) {
                c++;
            }
        }
        return c;
    }

    void display() {
        for (node<T>* ptr = head(); ptr != nullptr; ptr = ptr->next()) {
            cout << ptr->retrieve() << " ";
        }
    }

    void push_front(T a) {
        list_head = new node<T>(a, list_head);
    }

    void push_end(T n) {
        node<T>* new_node = new node<T>(n, nullptr);

        if (empty()) {
            list_head = new_node;
            return;
        }

        node<T>* ptr = list_head;
        while (ptr->next() != nullptr) {
            ptr = ptr->next_node;
        }
        ptr->next_node = new_node;
    }

    T pop_end() {
        if (empty()) {
            throw underflow_error("list is empty");
        }
        T e;
        if (list_head->next_node == nullptr) {
            e = list_head->retrieve();
            delete list_head;
            list_head = nullptr;
            return e;
        }

        node<T>* last = list_head;
        node<T>* curr = list_head->next_node;

        while (curr->next_node != nullptr) {
            last = curr;
            curr = curr->next_node;
        }

        last->next_node = nullptr;
        T a = curr->retrieve();
        delete curr;
        return a;
    }

    T pop_front() {
        if (empty()) {
            throw underflow_error("List is empty!");
        }

        node<T>* old_head = list_head;
        T value = old_head->retrieve();
        list_head = old_head->next();
        delete old_head;
        return value;
    }

    void erase(T n) {
        if (empty()) {
            cout << "list is empty";
            return;
        }
        while (list_head && list_head->retrieve() == n) {
            node<T>* old_head = list_head;
            list_head = old_head->next();
            delete old_head;
        }
        node<T>* curr = list_head;
        node<T>* prev = list_head;
        while (curr != nullptr) {
            if (curr->retrieve() == n) {
                prev->next_node = curr->next_node;
                delete curr;
                curr = prev;
            }
            prev = curr;
            curr = curr->next();
        }
    }


    T front() const {
        if (empty()) {
            throw underflow_error("List is empty!");
        }
        return list_head->retrieve();
    }
};

template <typename T>
class stack {
protected:
    list<T> l;

public:
    stack() = default;

    void push(T x) {
        l.push_front(x);
    }

    void pop() {
        l.pop_front();
    }

    void displaystack() {
        l.display();
    }
};
template<typename T>
class que {
protected:
    list<T> l;
public:
    que() = default;
    void pushq(T a) {
        l.push_front(a);
    }
    T popq() {
        return l.pop_end();
    }
    void displayque() {
        l.display();
    }
    bool emptyq() {
        return l.empty();
    }
};

template<typename T>
class simple_tree {
protected:
    T element;
    simple_tree* parent_node;
    list<simple_tree*> children;
public:

    simple_tree(T const& obj = T(), simple_tree* p = nullptr) {
        element = obj;
        parent_node = p;
    }

    simple_tree<T>* parent() {
        return parent_node;
    }

    T retrieve() {
        return element;
    }

    bool is_root() {
        return (parent() == nullptr);
    }

    // --- FIX APPLIED HERE ---
    // Changed to 0-based indexing to match your main() usage
    simple_tree<T>* child(int n) {
        if (n < 0 || n >= degree()) { // Changed from (n<=0 || n>degree())
            return nullptr;
        }
        node<simple_tree*>* ptr = children.head();
        int index = 0; // Changed from 1 to 0
        while (ptr != nullptr) {
            if (index == n) {
                return ptr->retrieve();
            }
            ptr = ptr->next();
            index++;
        }
        return nullptr;
    }
    // ------------------------

    int degree() {
        return children.size();
    }

    bool is_leaf() {
        return (degree() == 0);
    }

    void insert(T const& obj) {
        children.push_end(new simple_tree(obj, this));
    }

    int size() {
        int s = 1;
        for (node<simple_tree*>* ptr = children.head(); ptr != nullptr; ptr = ptr->next()) {
            s += ptr->retrieve()->size();
        }
        return s;
    }

    int height() {
        int h = 0;
        for (node<simple_tree*>* ptr = children.head(); ptr != nullptr; ptr = ptr->next()) {
            h = std::max(h, 1 + ptr->retrieve()->height());
        }
        return h;
    }

    void detach() {
        if (is_root()) {
            return;
        }
        parent()->children.erase(this);
        parent_node = nullptr;
    }

    void attach(simple_tree<T>* tree) {
        if (!tree->is_root()) {
            tree->detach();
        }
        tree->parent_node = this;
        children.push_end(tree);
    }

    void depth_first_traversal() {
        cout << retrieve() << "\t";
        for (node<simple_tree*>* ptr = children.head(); ptr != nullptr; ptr = ptr->next()) {
            ptr->retrieve()->depth_first_traversal();
        }
    }
    void breadth_first_traversal() {
        que<simple_tree*> q;
        q.pushq(this);
        while (!q.emptyq()) {
            simple_tree* p = q.popq();
            cout << p->retrieve() << "\t";
            for (node<simple_tree*>* ptr = children.head(); ptr != nullptr; ptr = ptr->next()) {
                q.pushq(ptr->retrieve());
            }


        }
    }
};

int main() {
    simple_tree<char> s1;
    simple_tree<char>* root = new simple_tree<char>('H');

    root->insert('a'); // Index 0
    root->insert('s'); // Index 1

    simple_tree<char>* root2 = new simple_tree<char>('s');
    root2->insert('a');
    root2->insert('n');

    if (root->child(1) != nullptr) {
        root->child(1)->attach(root2);
    }
    
    root->depth_first_traversal();
    cout << endl;

    cout << "The hieght of the tree is: ";
    cout << root->height();
    cout << endl;
    cout << "the size of the tree is :";

    cout << root->size();

    return 0;
}