#include <iostream>
#include <cstring>

using namespace std;

int dna[10];
int dish[40+2], temp[40+2];

const char* ref = " .xW";

int main()
{
	int total_test;
	cin >> total_test;

	while (total_test-- > 0) {
		for (int i = 0; i < 10; ++i)
			cin >> dna[i];

		memset(dish, 0, sizeof(dish));
		dish[20] = 1;

		int j = 0;
		do {
			// show cur state
			for (int i = 1; i <= 40; ++i)
				cout << ref[dish[i]];
			cout << endl;

			// count
			memcpy(temp, dish, sizeof(dish));
			for (int i = 1; i <= 40; ++i) {
				int sum=temp[i-1]+temp[i]+temp[i+1];
				dish[i] = dna[sum];
			}
			++j;
		} while (j < 50);

		if (total_test != 0)
			cout << endl;
	}
	return 0;
}
