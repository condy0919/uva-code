#include <iostream>

using namespace std;

void draw_wave(int h)
{
	int i,j;
	for(i=1;i<=h;++i,cout<<endl)
		for(j=0;j<i;++j)
			cout<<i;
	for(i=h-1;i>=1;--i,cout<<endl)
		for(j=0;j<i;++j)
			cout<<i;
}

int main()
{
	int total_test;
	int amplitude, freq;

	cin>>total_test;
	while(total_test-->0){
		cin.ignore();
		cin>>amplitude>>freq;
		
		for(int i=0;i<freq;++i){
			draw_wave(amplitude);
			if(i!=freq-1||total_test!=0)
				cout<<endl;
		}
	}
	return 0;
}
