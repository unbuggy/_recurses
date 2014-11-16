#include "std.hpp"

using namespace std;

int main() {

    string skippers = "!@#$%^&|*,?:;+~{}";
    auto const b = begin(skippers), e = end(skippers);

    for (string s; getline(cin, s);) {
        cout << s;
        if (!s.empty() && find(b, e, s.back()) == e) cout << ';';
        cout << '\n';
    }

}
