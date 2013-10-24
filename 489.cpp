#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int judge(string ori,string guess)
{
	char table[128]={0};
	bool visit[128]={false};
	bool correct[128]={false};
	int err_time=0;
	int corr_time=0;
	int expect=0;

	// init occurance array
	for(int i=0;i<ori.length();++i)
		table[ori[i]]=1;
	for(int i=0;i<128;++i)
		expect+=table[i];

	for(int i=0;i<guess.length();++i) {
		if(table[guess[i]]){
			if(!correct[guess[i]]){
				correct[guess[i]]=true;
				++corr_time;
				if(corr_time==expect)
					return 1;
			}
		} else if(!visit[guess[i]]){
			visit[guess[i]]=true;
			++err_time;
			if(err_time>=7)
				return -1;
		}
	}
	return 0;
}

int main()
{
	int round;
	string solution,guess;

	while(cin>>round,round!=-1){
		cin>>solution>>guess;

		int ans=judge(solution,guess);
		cout<<"Round "<<round<<endl;

		if(ans==-1)
			cout<<"You lose.\n";
		else if(ans==0)
			cout<<"You chickened out.\n";
		else
			cout<<"You win.\n";
	}
	return 0;
}

