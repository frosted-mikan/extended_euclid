#include <iostream>
#include <functional>
#include <cstring>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

// Extended Euclidean Algorithm Calculator for modular inverse
// Computes the inverse a of x mod y, where ax + by = gcd(a,b) and gcd(a,b) = 1
// In other words, ax \equiv 1 mod y
// Also computes b and gcd(a,b)

// The purpose of this is to print out the steps to find the inverse

struct Data{
    int step;
    int n;
    int q;
    int x;
    int r;
    int p;
};

int main(int argc, char *argv[]){
    // Command line usage
    if (argc != 3){
        cout << "Usage: " << argv[0] << " <smaller int> <larger int> \n";
        exit(1);
    }

    int x = atoi(argv[1]);
    int mod = atoi(argv[2]);

    // Create memo and push initial data
    vector<Data> memo; 
    Data curr;
    int step = 0;
    int r = mod % x;
    curr.step = step;
    curr.n = mod;
    curr.q = mod / x;
    curr.x = x;
    curr.r = r;
    curr.p = 0;
    memo.push_back(curr);

    // Calculate further data
    while(r != 0){
        Data curr; 
        step++;
        curr.step = step;
        if (memo[step-1].p == 0){
            curr.p = 1;
        }else {
            // check order of operations? 
            curr.p = memo[step-2].p - memo[step-1].p * memo[step-2].q % mod;
            if (curr.p < 0) {
                curr.p += mod;
            }
        }
        curr.n = memo[step-1].x;
        curr.x = memo[step-1].r;
        curr.q = curr.n / curr.x;
        curr.r = curr.n % curr.x;

        memo.push_back(curr);
        
        r = curr.r;
    }

    // Print all steps out 
    cout << "Find the inverse of " << x << " mod " << mod << "\n";
    for (size_t i = 0; i < memo.size(); ++i){
        cout << "Step " << memo[i].step << ": " << memo[i].n << " = " 
             << memo[i].q << "(" << memo[i].x << ") + " << memo[i].r 
             << ", p" << memo[i].step << " = ";
        if (memo[i].p != 0 && memo[i].p != 1){
            cout << memo[i-2].p << " - " << memo[i-1].p << 
                    "(" << memo[i-2].q << ") mod " << mod << " = ";
        }
        cout << memo[i].p << "\n";
    }

    // Calculate p one more time and print
    // (this last p is the answer)    
    step++;
    int last_p = memo[step-2].p - memo[step-1].p * memo[step-2].q % mod;
    if (last_p < 0){
        last_p += mod;
    }
    cout << "Step " << step << ": p" << step << " = " << 
            memo[step-2].p << " - " << memo[step-1].p << 
            "(" << memo[step-2].q << ") mod " << mod << " = " << last_p << "\n";
    cout << "\n";

    cout << "Coefficient of smaller number: a = " << last_p << "\n";

    // Solving for b: 
    int b = (((last_p * x) - 1) / mod) * (-1);
    cout << "Coefficient of larger number: b = " << b << "\n";
    cout << "\n";

    // Computing gcd: ax + by
    int gcd = (last_p * x) + (b * mod);
    cout << "gcd(" << last_p << ", " << b << ") = " << gcd << "\n"; // should be 1 if a and b are coprime

    return 0;
}