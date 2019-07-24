#include <iostream>
#include <string>
using std::endl;

int main() {
    std::string s("12345");
    std::cout << *(s.end()) << endl;
    std::cout << *(s.end()-1) << endl;
    return 0;
}