#include <set>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

vector<vector<int> > swap1(int arr[]){
    vector<vector<int> > swaps;
    for (size_t i = 0; i < 24; ++i){ // 4! = 24
        next_permutation(arr, arr+4);
        swaps.push_back(vector<int>(arr, arr+4));
    }
    return swaps; 
}

vector<vector<char> > swap2(char ops[], int n, int r) {
    vector<vector<char> > combinations;
    vector<char> combination(r);
    int index[r];

    for (int i = 0; i < r; i++)
        index[i] = 0;

    while (true) {
        for (int i = 0; i < r; i++)
            combination[i] = ops[index[i]];
        combinations.push_back(combination);

        int next = r - 1;
        while (next >= 0 && (index[next] + 1 >= n))
            next--;

        if (next < 0)
            return combinations;

        index[next]++;

        for (int i = next + 1; i < r; i++)
            index[i] = 0;
    }
}

int calculateResult(int a, int b, char op) {
    if (op == '+') {
        return a + b;
    } else if (op == '-') {
        return a - b;
    } else if (op == '*') {
        return a * b;
    } else if (op == '/') {
        if (b != 0) {
            return a / b;
        } else {
            return INT_MIN;
        }
    } else {
        return INT_MIN;
    }
}

set<string> solver(int v, int w, int x, int y, int z){
    int nums[] = {v, w, x, y};
    char ops[] = {'+', '-', '*', '/'};
    set<string> solution;
    vector<vector<int> > numbers = swap1(nums);
    vector<vector<char> > operations = swap2(ops, 4, 3); // 4 operations, 3 slots

    for (size_t i = 0; i < numbers.size(); ++i){
        for (size_t j = 0; j < operations.size(); ++j){
            int result = numbers[i][0];
            result = calculateResult(result, numbers[i][1], operations[j][0]);
            result = calculateResult(result, numbers[i][2], operations[j][1]);
            result = calculateResult(result, numbers[i][3], operations[j][2]);
            if (result == INT_MIN) {continue;}
            if (result == z){
                string s = to_string(numbers[i][0]) + string(1, operations[j][0]) + 
                to_string(numbers[i][1]) + string(1, operations[j][1]) + 
                to_string(numbers[i][2]) + string(1, operations[j][2]) + 
                to_string(numbers[i][3]);

                solution.insert(s); // Use insert instead of push_back
            }
        }
    }

    return solution;

}

int main(){
    int a;
    int b;
    int c;
    int d;
    int target;

    cout << "Enter four integers and then your target separated by a space: ";
    cin >> a >> b >> c >> d >> target;

    set<string> solutions = solver(a,b,c,d,target);
    string solution = "";
    for (const string& s : solutions) {
        solution += s + "\n";
    }
    vector<string> unique_solutions(solutions.begin(), solutions.end());
    for (const string& s : unique_solutions) {
        cout << s << endl;
    }
}