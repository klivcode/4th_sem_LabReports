// C++ code that simulates the behavior of a PDA for the language L={anbn:n≥1}:
// •	δ(q0,a,$)=(q0,a$) (Push 'a' onto stack)
// •	δ(q0,a,a)=(q0,aa) (Push 'a' onto stack)
// •	δ(q0,b,a)=(q1,ϵ) (Move to next state and pop 'a' from stack)
// •	δ(q1,b,a)=(q1,ϵ) (Continue to pop 'a' from stack)
// •	δ(q1,ϵ,$)=(q2,ϵ) (Accept if stack becomes empty)


#include <iostream>
#include <stack>
#include <string>

bool isLanguageAccepted(const std::string& input) {
    std::stack<char> stack;

    for (char c : input) {
        if (c == 'a') {
            stack.push('a');
        } else if (c == 'b') {
            if (stack.empty()) {
                return false; // More 'b's than 'a's
            } else {
                stack.pop();
            }
        } else {
            return false; // Invalid input character
        }
    }

    return stack.empty(); // Stack should be empty at the end
}

int main() {
    std::string input;
    std::cout << "Enter a string: ";
    std::cin >> input;

    if (isLanguageAccepted(input)) {
        std::cout << "Accepted: The string is in the language L = {a^nb^n : n >= 0}\n";
    } else {
        std::cout << "Rejected: The string is not in the language L = {a^nb^n : n >= 0}\n";
    }

    return 0;
}