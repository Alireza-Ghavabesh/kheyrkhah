#include <iostream>
#include <stack>
#include <bits/stdc++.h>
using namespace std;

class infix_to_postfix_app
{
public:
    // Function to return precedence of operators
    int prec(char c)
    {
        if (c == '^')
            return 3;
        else if (c == '/' || c == '*')
            return 2;
        else if (c == '+' || c == '-')
            return 1;
        else
            return -1;
    }

    // The main function to convert infix expression
    // to postfix expression
    string infixToPostfix(string s)
    {

        stack<char> st; // For stack operations, we are using
                        // C++ built in stack
        string result;

        for (int i = 0; i < s.length(); i++)
        {
            char c = s[i];

            // If the scanned character is
            // an operand, add it to output string.
            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
                result += c;

            // If the scanned character is an
            // ‘(‘, push it to the stack.
            else if (c == '(')
                st.push('(');

            // If the scanned character is an ‘)’,
            // pop and to output string from the stack
            // until an ‘(‘ is encountered.
            else if (c == ')')
            {
                while (st.top() != '(')
                {
                    result += st.top();
                    st.pop();
                }
                st.pop();
            }

            // If an operator is scanned
            else
            {
                while (!st.empty() && prec(s[i]) <= prec(st.top()))
                {
                    result += st.top();
                    st.pop();
                }
                st.push(c);
            }
        }

        // Pop all the remaining elements from the stack
        while (!st.empty())
        {
            result += st.top();
            st.pop();
        }

        return result;
    }
};

class infix_to_prefix_app
{
public:
    bool isOperator(char c)
    {
        return (!isalpha(c) && !isdigit(c));
    }

    int getPriority(char C)
    {
        if (C == '-' || C == '+')
            return 1;
        else if (C == '*' || C == '/')
            return 2;
        else if (C == '^')
            return 3;
        return 0;
    }

    string infixToPostfix(string infix)
    {
        infix = '(' + infix + ')';
        int l = infix.size();
        stack<char> char_stack;
        string output;

        for (int i = 0; i < l; i++)
        {

            // If the scanned character is an
            // operand, add it to output.
            if (isalpha(infix[i]) || isdigit(infix[i]))
                output += infix[i];

            // If the scanned character is an
            // ‘(‘, push it to the stack.
            else if (infix[i] == '(')
                char_stack.push('(');

            // If the scanned character is an
            // ‘)’, pop and output from the stack
            // until an ‘(‘ is encountered.
            else if (infix[i] == ')')
            {
                while (char_stack.top() != '(')
                {
                    output += char_stack.top();
                    char_stack.pop();
                }

                // Remove '(' from the stack
                char_stack.pop();
            }

            // Operator found
            else
            {
                if (isOperator(char_stack.top()))
                {
                    if (infix[i] == '^')
                    {
                        while (getPriority(infix[i]) <= getPriority(char_stack.top()))
                        {
                            output += char_stack.top();
                            char_stack.pop();
                        }
                    }
                    else
                    {
                        while (getPriority(infix[i]) < getPriority(char_stack.top()))
                        {
                            output += char_stack.top();
                            char_stack.pop();
                        }
                    }

                    // Push current Operator on stack
                    char_stack.push(infix[i]);
                }
            }
        }
        while (!char_stack.empty())
        {
            output += char_stack.top();
            char_stack.pop();
        }
        return output;
    }

    string infixToPrefix(string infix)
    {
        /* Reverse String
         * Replace ( with ) and vice versa
         * Get Postfix
         * Reverse Postfix * */
        int l = infix.size();

        // Reverse infix
        reverse(infix.begin(), infix.end());

        // Replace ( with ) and vice versa
        for (int i = 0; i < l; i++)
        {

            if (infix[i] == '(')
            {
                infix[i] = ')';
            }
            else if (infix[i] == ')')
            {
                infix[i] = '(';
            }
        }

        string prefix = infixToPostfix(infix);

        // Reverse postfix
        reverse(prefix.begin(), prefix.end());

        return prefix;
    }
};

class postfix_to_infix_app
{
public:
    bool isOperand(char x)
    {
        return (x >= 'a' && x <= 'z') ||
               (x >= 'A' && x <= 'Z');
    }

    // Get Infix for a given postfix
    // expression
    string getInfix(string exp)
    {
        stack<string> s;

        for (int i = 0; exp[i] != '\0'; i++)
        {
            // Push operands
            if (isOperand(exp[i]))
            {
                string op(1, exp[i]);
                s.push(op);
            }

            // We assume that input is
            // a valid postfix and expect
            // an operator.
            else
            {
                string op1 = s.top();
                s.pop();
                string op2 = s.top();
                s.pop();
                s.push("(" + op2 + exp[i] +
                       op1 + ")");
            }
        }

        // There must be a single element
        // in stack now which is the required
        // infix.
        return s.top();
    }
};

class prefix_to_infix_app
{
public:
    // function to check if character is operator or not
    bool isOperator(char x)
    {
        switch (x)
        {
        case '+':
        case '-':
        case '/':
        case '*':
        case '^':
        case '%':
            return true;
        }
        return false;
    }

    // Convert prefix to Infix expression
    string preToInfix(string pre_exp)
    {
        stack<string> s;

        // length of expression
        int length = pre_exp.size();

        // reading from right to left
        for (int i = length - 1; i >= 0; i--)
        {

            // check if symbol is operator
            if (isOperator(pre_exp[i]))
            {

                // pop two operands from stack
                string op1 = s.top();
                s.pop();
                string op2 = s.top();
                s.pop();

                // concat the operands and operator
                string temp = "(" + op1 + pre_exp[i] + op2 + ")";

                // Push string temp back to stack
                s.push(temp);
            }

            // if symbol is an operand
            else
            {

                // push the operand to the stack
                s.push(string(1, pre_exp[i]));
            }
        }

        // Stack now contains the Infix expression
        return s.top();
    }
};

// Driver's code
int main()
{
    infix_to_postfix_app infix_to_postfix_obj;
    infix_to_prefix_app infix_to_prefix_obj;
    postfix_to_infix_app postfix_to_infix_obj;
    prefix_to_infix_app prefix_to_infix_obj;
    while (true)
    {
        string input_type_exp;
        string output_type_exp;
        string input_expression;
        cout << "input type:";
        cin >> input_type_exp;
        cout << "output type:";
        cin >> output_type_exp;
        if (input_type_exp == "infix" && output_type_exp == "prefix")
        {
            cout << "Enter input expression:";
            cin >> input_expression;
            cout << "\n";
            string result = infix_to_prefix_obj.infixToPrefix(input_expression);
            cout << "result: " << result;
            break;
        }
        else if (input_type_exp == "infix" && output_type_exp == "postfix")
        {
            cout << "Enter input expression:";
            cin >> input_expression;
            cout << "\n";
            string result = infix_to_postfix_obj.infixToPostfix(input_expression);
            cout << "result: " << result;
            break;
        }
        else if (input_type_exp == "prefix" && output_type_exp == "infix")
        {
            cout << "Enter input expression:";
            cin >> input_expression;
            cout << "\n";
            string result = prefix_to_infix_obj.preToInfix(input_expression);
            cout << "result: " << result;
            break;
        }
        else if (input_type_exp == "postfix" && output_type_exp == "infix")
        {
            cout << "Enter input expression:";
            cin >> input_expression;
            cout << "\n";
            string result = postfix_to_infix_obj.getInfix(input_expression);
            cout << "result: " << result;
            break;
        }
        else if (input_type_exp == "prefix" && output_type_exp == "postfix")
        {
            cout << "Enter input expression:";
            cin >> input_expression;
            cout << "\n";
            string infix_expression = prefix_to_infix_obj.preToInfix(input_expression);
            string result = infix_to_postfix_obj.infixToPostfix(infix_expression);
            cout << "result: " << result;
            break;
        }
        else if (input_type_exp == "postfix" && output_type_exp == "prefix")
        {
            cout << "Enter input expression:";
            cin >> input_expression;
            cout << "\n";
            string infix_expression = postfix_to_infix_obj.getInfix(input_expression);
            string result = infix_to_prefix_obj.infixToPrefix(infix_expression);
            cout << "result: " << result;
            break;
        }
        else
        {
            cout << "input expression is wrong!"
                 << "\n";
            cout << "try again..."
                 << "\n\n";
            continue;
        }
    }
    // // infix to postfix test
    // string infix_exp = "a+b*(c^d-e)^(f+g*h)-i";
    // string result = infix_to_postfix_obj.infixToPostfix(infix_exp);
    // cout << result << "\n";

    // // infix to prefix test
    // string s = ("x+y*z/w+u");
    // cout << "\n\n\nresult:"
    //      << infix_to_prefix_obj.infixToPrefix(s) << std::endl;

    // // postfix to infix test
    // string exp = "ab*c+";
    // cout << postfix_to_infix_obj.getInfix(exp) << "\n";

    // // prefix to infix test
    // string pre_exp = "*-A/BC-/AKL";
    // cout << "Infix : " << pretfix_to_infix_obj.preToInfix(pre_exp);

    return 0;
}
