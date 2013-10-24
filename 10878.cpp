#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main()
{
    string str;

    getline(cin, str);
    while (getline(cin, str), str != "___________") {
	int res = 0;
	for (int i = 2; i <= 5; ++i)
	    res = 2 * res + (str[i] == 'o');
	for (int i = 7; i <= 9; ++i)
	    res = 2 * res + (str[i] == 'o');
	cout << (char)res;
    }

    return 0;
}
