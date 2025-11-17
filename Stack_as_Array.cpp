#include <iostream>
using namespace std;

class Stack {
private:
    int stack_size;      // Number of elements currently in stack
    int array_capacity;  // Total capacity of the array
    int* array;          // Pointer to dynamically allocated array

public:
    // Constructor
    Stack(int capacity = 10) {
        array_capacity = capacity;        // set capacity
        array = new int[array_capacity];  // allocate array dynamically
        stack_size = 0;                   // stack is initially empty
    }

    // Destructor (to free memory)
    ~Stack() {
        delete[] array;
    }

    // Check if stack is empty
    bool empty() const {
        return stack_size == 0;
    }

    // Return top element without removing it
    int top() const {
        if (empty()) {
            throw underflow_error("Stack is empty!");
        }
        return array[stack_size - 1];  // last inserted element
    }

    // Push a new element on top of stack
    void push(int value) {
        if (stack_size == array_capacity) {
            cout << "Stack Overflow! Cannot push " << value << endl;
            return;
        }
        array[stack_size] = value;   // add at top
        stack_size++;                // increase size
        cout << value << " pushed onto stack." << endl;
    }

    // Pop (remove) top element and return it
    int pop() {
        if (empty()) {
            throw underflow_error("Stack Underflow! Cannot pop.");
        }
        stack_size--;                // reduce size
        int value = array[stack_size];  // get last element
        cout << value << " popped from stack." << endl;
        return value;
    }
};

int main() {
    Stack s(5);  // create stack with capacity 5

    s.push(10);
    s.push(20);
    s.push(30);

    cout << "Top element is: " << s.top() << endl;

    s.pop();
    s.pop();

    if (s.empty()) {
        cout << "Stack is empty now." << endl;
    } else {
        cout << "Stack still has elements." << endl;
    }

    return 0;
}
