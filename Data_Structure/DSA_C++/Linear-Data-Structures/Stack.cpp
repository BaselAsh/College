#include <cctype>
#include <iostream>
#include <string>

using namespace std;

template <typename T> class Stack {
  private:
    struct Node {
        T data;
        Node *next;
    };
    Node *topNode;
    size_t stackSize;

  public:
    Stack() : topNode(nullptr), stackSize(0) {}

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    void push(T value) {
        Node *newNode = new Node{value, topNode};
        topNode = newNode;
        stackSize++;
    }

    void pop() {
        if (isEmpty())
            return;
        Node *temp = topNode;
        topNode = topNode->next;
        delete temp;
        stackSize--;
    }

    T top() const {
        if (isEmpty())
            cout
                << "Stack Underflow: Attempted to access top of empty stack.\n";
        return topNode->data;
    }

    bool isEmpty() const { return topNode == nullptr; }

    size_t size() const { return stackSize; }
};

int getPrecedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

string infixToPostfix(string infix) {
    Stack<char> s;
    string postfix = "";

    for (int i = 0; i < infix.length(); i++) {
        char c = infix[i];

        if (isspace(c))
            continue;

        if (isdigit(c)) {
            while (i < infix.length() && isdigit(infix[i])) {
                postfix += infix[i++];
            }
            postfix += " ";
            i--;
        } else if (c == '(') {
            s.push('(');
        } else if (c == ')') {
            while (!s.isEmpty() && s.top() != '(') {
                postfix += s.top();
                postfix += " ";
                s.pop();
            }
            if (!s.isEmpty())
                s.pop();
        } else {
            while (!s.isEmpty() && getPrecedence(s.top()) >= getPrecedence(c)) {
                postfix += s.top();
                postfix += " ";
                s.pop();
            }
            s.push(c);
        }
    }

    while (!s.isEmpty()) {
        postfix += s.top();
        postfix += " ";
        s.pop();
    }
    return postfix;
}

int evaluatePostfix(string postfix) {
    Stack<int> s;

    for (int i = 0; i < postfix.length(); i++) {
        if (isspace(postfix[i]))
            continue;

        if (isdigit(postfix[i])) {
            int num = 0;
            while (i < postfix.length() && isdigit(postfix[i])) {
                num = num * 10 + (postfix[i++] - '0');
            }
            s.push(num);
            i--;
        } else {
            int val2 = s.top();
            s.pop();
            int val1 = s.top();
            s.pop();

            switch (postfix[i]) {
            case '+':
                s.push(val1 + val2);
                break;
            case '-':
                s.push(val1 - val2);
                break;
            case '*':
                s.push(val1 * val2);
                break;
            case '/':
                s.push(val1 / val2);
                break;
            }
        }
    }
    return s.top();
}

int main() {
    string input1 = "( 1 + 10 ) * ( 12 - 2 )";
    string post1 = infixToPostfix(input1);
    cout << "Input (Infix): " << input1 << endl;
    cout << "Output (Postfix): " << post1 << endl;
    cout << "Result: " << evaluatePostfix(post1) << "\n" << endl;

    string input2 = "12 10 - 9 6 + *";
    cout << "Input (Postfix): " << input2 << endl;
    cout << "Result: " << evaluatePostfix(input2) << endl;

    return 0;
}
