#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
using namespace std;

class FormulaEvaluator {
private:
    // Store the right-hand side of each formula
    // Example: "a = b + 3" -> formulas["a"] = "b + 3"
    unordered_map<string, string> formulas;
    
    // Cache: store calculated values to avoid recalculating
    unordered_map<string, int> cache;
    
    // Track which variables we're currently evaluating (for cycle detection)
    unordered_map<string, bool> visiting;

public:
    // Parse input formulas and store them
    void parseFormulas(vector<string>& input) {
        for (string& formula : input) {
            // Find the '=' sign
            int equalPos = formula.find('=');
            
            // Extract variable name (left side of '=')
            string varName = formula.substr(0, equalPos);
            // Remove spaces
            varName.erase(remove(varName.begin(), varName.end(), ' '), varName.end());
            
            // Extract expression (right side of '=')
            string expression = formula.substr(equalPos + 1);
            
            formulas[varName] = expression;
        }
    }
    
    // Main evaluation function - uses recursion + memoization
    int evaluate(string varName) {
        // Remove any spaces from variable name
        varName.erase(remove(varName.begin(), varName.end(), ' '), varName.end());
        
        // STEP 1: Check cache (memoization)
        if (cache.find(varName) != cache.end()) {
            return cache[varName];  // Already calculated!
        }
        
        // STEP 2: Check for cycles
        if (visiting[varName]) {
            throw runtime_error("Cyclic dependency detected for variable: " + varName);
        }
        
        // STEP 3: Check if variable exists
        if (formulas.find(varName) == formulas.end()) {
            throw runtime_error("Variable not defined: " + varName);
        }
        
        // STEP 4: Mark as currently visiting (for cycle detection)
        visiting[varName] = true;
        
        // STEP 5: Evaluate the expression
        string expression = formulas[varName];
        int result = evaluateExpression(expression);
        
        // STEP 6: Cache the result
        cache[varName] = result;
        
        // STEP 7: Unmark visiting
        visiting[varName] = false;
        
        return result;
    }
    
    // Evaluate an expression like "b + 3" or "5"
    int evaluateExpression(string expr) {
        stringstream ss(expr);
        string token;
        int result = 0;
        char operation = '+';  // Start with addition
        
        while (ss >> token) {
            int value;
            
            // Check if token is a number
            if (isdigit(token[0]) || (token[0] == '-' && token.length() > 1)) {
                value = stoi(token);  // Convert string to integer
            }
            // Check if it's an operator
            else if (token == "+" || token == "-") {
                operation = token[0];
                continue;
            }
            // Otherwise, it's a variable - recursively evaluate it!
            else {
                value = evaluate(token);  // Recursive call!
            }
            
            // Apply the operation
            if (operation == '+') {
                result += value;
            } else {
                result -= value;
            }
        }
        
        return result;
    }
    
    // Get all variable values
    unordered_map<string, int> evaluateAll() {
        // Evaluate each variable
        for (auto& pair : formulas) {
            if (cache.find(pair.first) == cache.end()) {
                evaluate(pair.first);
            }
        }
        return cache;
    }
};

// Main function to demonstrate
int main() {
    FormulaEvaluator evaluator;
    
    // Example 1: Simple case
    cout << "=== Example 1 ===" << endl;
    vector<string> formulas1 = {"a = b + 3", "b = 5"};
    evaluator.parseFormulas(formulas1);
    
    auto results = evaluator.evaluateAll();
    for (auto& pair : results) {
        cout << pair.first << " = " << pair.second << endl;
    }
    
    // Example 2: More complex
    cout << "\n=== Example 2 ===" << endl;
    FormulaEvaluator evaluator2;
    vector<string> formulas2 = {
        "x = y + 2",
        "y = z - 1", 
        "z = 10"
    };
    evaluator2.parseFormulas(formulas2);
    
    results = evaluator2.evaluateAll();
    for (auto& pair : results) {
        cout << pair.first << " = " << pair.second << endl;
    }
    
    // Example 3: Cyclic dependency (error case)
    cout << "\n=== Example 3 (Cyclic) ===" << endl;
    try {
        FormulaEvaluator evaluator3;
        vector<string> formulas3 = {
            "a = b + 1",
            "b = a + 1"
        };
        evaluator3.parseFormulas(formulas3);
        evaluator3.evaluateAll();
    } catch (exception& e) {
        cout << "Error caught: " << e.what() << endl;
    }
    
    return 0;
}