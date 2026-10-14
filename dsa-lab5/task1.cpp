#include <iostream>
#include <string>
using namespace std;

class CharStack {
private:
    struct Node {
        char data;
        Node* next;
        Node(char c) : data(c), next(nullptr) {}
    };
    Node* top;
    int sz;

public:
    CharStack() : top(nullptr), sz(0) {}

    ~CharStack() { clear(); }

    void push(char c) {
        Node* newNode = new Node(c);
        newNode->next = top;
        top = newNode;
        sz++;
    }

    bool pop() {
        if (!top) return false;
        Node* temp = top;
        top = top->next;
        delete temp;
        sz--;
        return true;
    }

    char topChar() const { return top ? top->data : '\0'; }

    bool isEmpty() const { return top == nullptr; }
    int  size()    const { return sz; }

    void display() const {
        if (!top) { cout << "(empty)"; return; }
        Node* cur = top;
        while (cur) {
            cout << cur->data;
            if (cur->next) cout << " -> ";
            cur = cur->next;
        }
    }

    void clear() {
        while (top) {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
        sz = 0;
    }
};

bool matches(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '[' && close == ']') ||
           (open == '{' && close == '}');
}

bool checkBalance(const string& expr, string& reason) {
    CharStack st;

    for (size_t i = 0; i < expr.size(); i++) {
        char c = expr[i];

        if (c == '(' || c == '[' || c == '{') {
            st.push(c);
        }
        else if (c == ')' || c == ']' || c == '}') {
            if (st.isEmpty()) {
                reason = "Extra closing bracket '" + string(1, c) + "' at position " + to_string(i);
                return false;
            }
            char open = st.topChar();
            if (!matches(open, c)) {
                reason = "Mismatch: '" + string(1, open) + "' vs '" + string(1, c) + "' at position " + to_string(i);
                return false;
            }
            st.pop();
        }
    }

    if (!st.isEmpty()) {
        reason = "Extra opening bracket '" + string(1, st.topChar()) + "' not closed";
        return false;
    }

    reason = "All brackets correctly matched";
    return true;
}

int main() {
    string tests[] = {
        "(A+B)",
        "{A+[B*C]}",
        "(A+B]",
        "((A+B)",
        "([A+B])"
    };

    cout << " Test Cases \n";
    for (const string& e : tests) {
        string reason;
        bool ok = checkBalance(e, reason);
        cout << e << "  -  "
             << (ok ? "Balanced" : "Not Balanced")
             << "   (" << reason << ")\n";
    }
    return 0;
}
