#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <string>


using namespace std;

char Tolower(char ch)
{
	return tolower(ch);
}

int main()
{
	vector<string> vec, temp;
	string str;
	map<string, int> cnt;

	while (cin >> str, str != "#"){
		vec.push_back(str);
		transform(str.begin(), str.end(), str.begin(), Tolower);
		sort(str.begin(), str.end());
		temp.push_back(str);
	}


	for (int i=0;i<temp.size();++i)
		cnt[temp[i]]++;

	typedef vector<string>::iterator ITER;
	vector<string> out;
	for (map<string,int>::iterator iter=cnt.begin();iter!=cnt.end();++iter)
		if(iter->second==1) {
			ITER it=find(temp.begin(),temp.end(), iter->first);
			int pos=it-temp.begin();
			out.push_back(vec[pos]);
		}
	sort(out.begin(), out.end());
	for (int i=0;i<out.size();++i)
		cout << out[i]<<endl;

	return 0;
}

