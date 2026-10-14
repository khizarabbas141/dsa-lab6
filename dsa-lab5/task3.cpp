#include <iostream>
#include <string>
#include <cctype>
#include <sstream>
#include <vector>
using namespace std;

class Stack {
private:
    struct Node {
        string data;
        Node* next;
        Node(const string& s) : data(s), next(nullptr) {}
    };
    Node* top;

public:
    Stack() : top(nullptr) {}
    ~Stack() { clear(); }

    void push(const string& s) {
        Node* n = new Node(s);
        n->next = top;
        top = n;
    }

    string pop() {
        if (!top) return "";
        Node* t = top;
        string v = t->data;
        top = top->next;
        delete t;
        return v;
    }

    string topVal() const { return top ? top->data : ""; }
    bool isEmpty() const { return top == nullptr; }

    void clear() {
        while (top) { Node* t = top; top = top->next; delete t; }
    }
};

int precedence(const string& op) {
    if (op == "*" || op == "/" || op == "%") return 3;
    if (op == "+" || op == "-")              return 2;
    return 0;
}

bool isOperator(const string& t) {
    return t == "+" || t == "-" || t == "*" || t == "/" || t == "%";
}

vector<string> tokenize(const string& expr) {
    vector<string> tokens;
    string num;
    for (char c : expr) {
        if (isdigit(c)) num += c;
        else if (isspace(c)) {
            if (!num.empty()) { tokens.push_back(num); num.clear(); }
        } else {
            if (!num.empty()) { tokens.push_back(num); num.clear(); }
            tokens.push_back(string(1, c));
        }
    }
    if (!num.empty()) tokens.push_back(num);
    return tokens;
}

bool infixToPostfix(const vector<string>& tokens, vector<string>& postfix, string& error) {
    Stack ops;
    for (const string& t : tokens) {
        if (t == "(") {
            ops.push(t);
        } else if (t == ")") {
            while (!ops.isEmpty() && ops.topVal() != "(") {
                postfix.push_back(ops.pop());
            }
            if (ops.isEmpty()) {
                error = "Mismatched parentheses: extra ')'";
                return false;
            }
            ops.pop(); 
        } else if (isOperator(t)) {
            while (!ops.isEmpty() && ops.topVal() != "(" &&
                   precedence(ops.topVal()) >= precedence(t)) {
                postfix.push_back(ops.pop());
            }
            ops.push(t);
        } else {
            postfix.push_back(t); 
        }
    }
    while (!ops.isEmpty()) {
        if (ops.topVal() == "(") {
            error = "Mismatched parentheses: unclosed '('";
            return false;
        }
        postfix.push_back(ops.pop());
    }
    return true;
}

bool evalPostfix(const vector<string>& postfix, double& result, string& error) {
    Stack s;
    for (const string& t : postfix) {
        if (isOperator(t)) {
            if (s.isEmpty()) { error = "Invalid expression"; return false; }
            string bStr = s.pop();
            if (s.isEmpty()) { error = "Invalid expression"; return false; }
            string aStr = s.pop();

            double a = stod(aStr);
            double b = stod(bStr);
            double val = 0;

            if (t == "+") val = a + b;
            else if (t == "-") val = a - b;
            else if (t == "*") val = a * b;
            else if (t == "/") {
                if (b == 0) { error = "Division by zero"; return false; }
                val = a / b;
            }
            else if (t == "%") {
                if ((int)b == 0) { error = "Modulus by zero"; return false; }
                val = (int)a % (int)b;
            }
            s.push(to_string(val));
        } else {
            s.push(t);
        }
    }
    if (s.isEmpty()) { error = "Invalid empty expression"; return false; }
    string res = s.pop();
    if (!s.isEmpty()) { error = "Invalid expression (leftover values)"; return false; }
    result = stod(res);
    return true;
}

void testExpression(const string& expr) {
    cout << "Infix    : \"" << expr << "\"\n";

    vector<string> tokens = tokenize(expr);
    if (tokens.empty()) {
        cout << "Result   : Invalid — empty expression\n";
        return;
    }

    vector<string> postfix;
    string error;

    if (!infixToPostfix(tokens, postfix, error)) {
        cout << "Result   : Invalid — " << error << "\n";
        return;
    }

    cout << "Postfix  : ";
    for (const string& p : postfix) cout << p << " ";
    cout << "\n";

    double result;
    if (!evalPostfix(postfix, result, error)) {
        cout << "Result   : Invalid — " << error << "\n";
        return;
    }
    cout << "Result   : " << result << "\n";
}

int main() {

    testExpression("2 + 3 * 4");
    testExpression("(2 + 3) * 4");
    testExpression("10 + 2 * 6");
    testExpression("(10 + 2) * (6 - 3)");
    testExpression("20 / 5 + 3");

    testExpression("(1 + 2) * ((3 + 4) * 5)");
    testExpression("20 / 0");                 
    testExpression("(1 + 2))");               
    testExpression("((1 + 2)");             
    testExpression("");                    
    testExpression("10 % 3 + 1");            

    return 0;
}