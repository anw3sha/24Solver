#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

std::string solver(int w, int x, int y, int z){
    int nums[] = {w, x, y, z};
    std::vector<std::string> solution = {};
}

std::vector<std::vector<int>> swap(int arr[]){
    std::vector<std::vector<int>> swaps;
    for (size_t i = 0; i < 25; ++i){
        swaps[i] = std::next_permutation(arr, arr+3);
    }
}

int main(){
    int a;
    int b;
    int c;
    int d;

    std::cout << "Enter four integers separated by a space: ";
    std::cin >> a >> b >> c >> d;

    std::string solution = solver(a,b,c,d);
    std::cout << solution; 
}