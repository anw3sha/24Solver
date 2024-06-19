#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <string>
#include <stdexcept>
#include <climits>

using namespace std;

vector<vector<int> > generatePermutations(int arr[], int size){
    sort(arr, arr + size);
    vector<vector<int> > perms;
    while (next_permutation(arr, arr + size)) {
        perms.push_back(vector<int>(arr, arr + size));
    }
    return perms; 
}

vector<vector<char> > generateCombinations(char ops[], int n, int r) {
    vector<vector<char> > combinations;
    vector<bool> v(n);
    fill(v.begin(), v.begin() + r, true);
    
    while (prev_permutation(v.begin(), v.end())) {
        vector<char> combination;
        for(int i = 0; i < n; ++i) {
            if (v[i]) {
                combination.push_back(ops[i]);
            }
        }
        combinations.push_back(combination);
    }
    return combinations;
}

float calculate(float a, float b, char op) {
    if (op == '+') return a + b;
    if (op == '-') return a - b;
    if (op == '*') return a * b;
    if (op == '/') {
        if (b == 0) {
            throw domain_error("Division by zero");
        } else {
            return a / b;
        }
    }
    throw invalid_argument("Invalid operator");
}

bool solve(const vector<int>& nums, const vector<char>& ops, int target, vector<string> &solutions) {
    vector<vector<int> > numPerms = generatePermutations(const_cast<int*>(&nums[0]), nums.size());
    vector<vector<char> > opCombs = generateCombinations(const_cast<char*>(&ops[0]), ops.size(), 3);

    bool foundSolution = false;

    for (const auto &n : numPerms) {
        for (const auto &o : opCombs) {
            vector<string> expressions = {
                "((" + to_string(n[0]) + " " + o[0] + " " + to_string(n[1]) + ") " + o[1] + " " + to_string(n[2]) + ") " + o[2] + " " + to_string(n[3]),
                "(" + to_string(n[0]) + " " + o[0] + " (" + to_string(n[1]) + " " + o[1] + " " + to_string(n[2]) + ")) " + o[2] + " " + to_string(n[3]),
                to_string(n[0]) + " " + o[0] + " ((" + to_string(n[1]) + " " + o[1] + " " + to_string(n[2]) + ") " + o[2] + " " + to_string(n[3]) + ")",
                "(" + to_string(n[0]) + " " + o[0] + " " + to_string(n[1]) + ") " + o[1] + " (" + to_string(n[2]) + " " + o[2] + " " + to_string(n[3]) + ")",
                to_string(n[0]) + " " + o[0] + " (" + to_string(n[1]) + " " + o[1] + " (" + to_string(n[2]) + " " + o[2] + " " + to_string(n[3]) + "))"
            };

            for (const auto &expr : expressions) {
                try {
                    // Calculate the value of the expression based on its structure
                    float result;
                    if (expr == expressions[0]) {
                        result = calculate(calculate(calculate(n[0], n[1], o[0]), n[2], o[1]), n[3], o[2]);
                    } else if (expr == expressions[1]) {
                        result = calculate(calculate(n[0], calculate(n[1], n[2], o[1]), o[0]), n[3], o[2]);
                    } else if (expr == expressions[2]) {
                        result = calculate(n[0], calculate(calculate(n[1], n[2], o[1]), n[3], o[2]), o[0]);
                    } else if (expr == expressions[3]) {
                        result = calculate(calculate(n[0], n[1], o[0]), calculate(n[2], n[3], o[2]), o[1]);
                    } else if (expr == expressions[4]) {
                        result = calculate(n[0], calculate(n[1], calculate(n[2], n[3], o[2]), o[1]), o[0]);
                    } else {
                        continue; // Invalid expression structure
                    }

                    if (fabs(result - target) < 0.0001f) {
                        solutions.push_back(expr + " = " + to_string(target));
                        foundSolution = true;
                    }
                } catch (...) {
                    continue; // Division by zero should not be an issue
                }
            }
        }
    }
    return foundSolution;
}

int main() {
    vector<int> nums(4);
    cout << "Enter four integers: ";
    for(int &num : nums) {
        cin >> num;
    }
    
    int target;
    cout << "Enter the target result: ";
    cin >> target;

    vector<char> ops;
    ops.push_back('+');
    ops.push_back('-');
    ops.push_back('*');
    ops.push_back('/');

    vector<string> solutions;

    if (solve(nums, ops, target, solutions)) {
        for (const string& s : solutions) {
            cout << s << endl;
        }
    } else {
        cout << "No solutions found." << endl;
    }

    return 0;
}