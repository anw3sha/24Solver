#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
#include <string>
#include <stdexcept>
#include <unordered_set>
#include <fstream>

using namespace std;

vector<vector<int>> generatePermutations(int arr[], int size) {
    sort(arr, arr + size);
    vector<vector<int>> perms;
    do {
        perms.push_back(vector<int>(arr, arr + size));
    } while (next_permutation(arr, arr + size));
    return perms;
}

void generateCombinationsWithRepetition(const vector<char>& ops, int r, vector<vector<char>>& combinations, vector<char>& current) {
    if (r == 0) {
        combinations.push_back(current);
        return;
    }
    for (size_t i = 0; i < ops.size(); ++i) {
        current.push_back(ops[i]);
        generateCombinationsWithRepetition(ops, r - 1, combinations, current);
        current.pop_back();
    }
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

bool solve(const vector<int>& nums, const vector<char>& ops, int target, vector<string>& solutions) {
    vector<vector<int>> numPerms = generatePermutations(const_cast<int*>(&nums[0]), nums.size());
    
    vector<vector<char>> opCombs;
    vector<char> currentComb;
    generateCombinationsWithRepetition(ops, 3, opCombs, currentComb);

    unordered_set<string> uniqueSolutions;

    for (const auto& n : numPerms) {
        for (const auto& o : opCombs) {
            vector<string> expressions = {
                "((" + to_string(n[0]) + " " + o[0] + " " + to_string(n[1]) + ") " + o[1] + " " + to_string(n[2]) + ") " + o[2] + " " + to_string(n[3]),
                "(" + to_string(n[0]) + " " + o[0] + " (" + to_string(n[1]) + " " + o[1] + " " + to_string(n[2]) + ")) " + o[2] + " " + to_string(n[3]),
                to_string(n[0]) + " " + o[0] + " ((" + to_string(n[1]) + " " + o[1] + " " + to_string(n[2]) + ") " + o[2] + " " + to_string(n[3]) + ")",
                "(" + to_string(n[0]) + " " + o[0] + " " + to_string(n[1]) + ") " + o[1] + " (" + to_string(n[2]) + " " + o[2] + " " + to_string(n[3]) + ")",
                to_string(n[0]) + " " + o[0] + " (" + to_string(n[1]) + " " + o[1] + " (" + to_string(n[2]) + " " + o[2] + " " + to_string(n[3]) + "))"
            };

            for (const auto& expr : expressions) {
                try {
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
                        continue;
                    }

                    if (fabs(result - target) < 0.0001f) {
                        uniqueSolutions.insert(expr + " = " + to_string(target));
                    }
                } catch (const exception &e) {
                    continue;
                }
            }
        }
    }

    solutions.assign(uniqueSolutions.begin(), uniqueSolutions.end());
    return !solutions.empty();
}

int main() {
    ifstream infile("input.txt");
    if (!infile) {
        cerr << "Error opening input file." << endl;
        return 1;
    }

    int num1, num2, num3, num4, target;
    infile >> num1 >> num2 >> num3 >> num4 >> target;
    infile.close();

    vector<int> nums = {num1, num2, num3, num4};
    vector<char> ops = {'+', '-', '*', '/'};

    vector<string> solutions;
    bool found = solve(nums, ops, target, solutions);

    if (found) {
        for (const auto& solution : solutions) {
            cout << solution << endl;
        }
    } else {
        cout << "No solutions found." << endl;
    }

    return 0;
}