#include <math.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stack>
#include <iostream>
#include <sstream>

std::string calculate(std::string expression)
{
    int length = expression.length();
    std::stack<float> Stack;
    
    // Read each char in string
    for(int i = 0; i < length; i++)
    {
        if(expression[i] == ' ') continue;
        else if (expression[i] >= '0' && expression[i] <= '9') // If it's a valid single digit
        {
            Stack.push(expression[i] - '0');
            //printf("Pushing %d\n", expression[i] - '0');
        }
        else // Any other ASCII symbols 
        {
            // Require operands to be a valid digit
            float first, second;
            if(!Stack.empty())
            {
                first = Stack.top();
                Stack.pop();
                //printf("Popping %f\n", first);
            }
            else 
                return "Not enough operands";

            if(!Stack.empty())
            {            
                second = Stack.top();
                Stack.pop();
                //printf("Popping %f\n", second);
            }
            else
                return "Not enough operands";
            
            //printf("Performing %c\n", expression[i]);
            switch(expression[i])
            {
                // In case of operands, pop previous digits and perform operations then store back to stack
                case '+':
                    Stack.push(second + first);
                    break;
                case '-':
                    Stack.push(second - first);
                    break;
                case '*':
                    Stack.push(second * first);
                    break;
                case '/':
                    Stack.push(second / first);
                    break;
                default:
                    if(expression[i] >= 'A' && expression[i] <= 'Z') return "Invalid operand";
                    else if (expression[i] >= 'a' && expression[i] <= 'z') return "Invalid operand";
                    else return "Invalid operator";
                    break;
            }
        }
    }

    if(Stack.size() > 1) 
        return "Too many operand";
    else
        return std::to_string(Stack.top());
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */

    // Gets input from STDIN
    std::string expression;
    
    std::string input = "2 3 /\n2 3 + 4 *\n2 3 3 +\n2 + 3\n. 3 5";
    std::istringstream iss (input);

    while(getline(iss, expression, '\n'))
    {
        if(expression == "exit") break;
        
        // Print results
        std::string result;
        result = calculate(expression);
        std::cout << result << std::endl;    
    }

    return 0;
}