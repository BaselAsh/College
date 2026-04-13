#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T> class CircularDeque {
  private:
    T *arr;
    int head;
    int tail;
    int capacity;
    int count;

  public:
    CircularDeque(int size) : capacity(size), count(0) {
        arr = new T[capacity];
        head = 0;
        tail = capacity - 1;
    }

    ~CircularDeque() { delete[] arr; }

    bool isFull() const { return count == capacity; }
    bool isEmpty() const { return count == 0; }

    void pushFront(T val) {
        if (isFull())
            throw runtime_error("Deque Overflow");

        head = (head - 1 + capacity) % capacity;
        arr[head] = val;
        count++;
    }

    void pushBack(T val) {
        if (isFull())
            throw runtime_error("Deque Overflow");

        tail = (tail + 1) % capacity;
        arr[tail] = val;
        count++;
    }

    void popFront() {
        if (isEmpty())
            throw runtime_error("Deque Underflow");
        head = (head + 1) % capacity;
        count--;
    }

    void popBack() {
        if (isEmpty())
            throw runtime_error("Deque Underflow");
        tail = (tail - 1 + capacity) % capacity;
        count--;
    }

    T getFront() const {
        if (isEmpty())
            throw runtime_error("Deque is empty");
        return arr[head];
    }

    T getBack() const {
        if (isEmpty())
            throw runtime_error("Deque is empty");
        return arr[tail];
    }

    void display() const {
        if (isEmpty()) {
            cout << "Deque is empty." << endl;
            return;
        }

        cout << "Deque elements: ";
        for (int i = 0; i < count; i++) {
            // Calculate the actual index using modulo
            int index = (head + i) % capacity;
            cout << arr[index] << " ";
        }
        cout << endl;
    }
};

int main() {
    CircularDeque<int> q(10);
    q.pushBack(3);
    q.display();
    q.pushBack(5);
    q.display();
    q.pushBack(9);
    q.display();
    q.popFront();
    q.display();
    q.pushFront(23);
    q.display();
    q.popFront();
    q.display();
    q.popFront();
    q.display();
}
