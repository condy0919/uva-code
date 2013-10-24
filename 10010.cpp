#include<iostream>
#include<cctype>
#include<string>

using namespace std;


char mat[50][50];

struct xy_t{
	int x,y;

	xy_t() {}
	xy_t(int _x,int _y): x(_x),y(_y) {}
};

bool cmp(string& str,int tx,int ty,int dx,int dy,int row,int col)
{
	int i,j;
	int op=0;
	for(i=tx,j=ty;op<str.length()&&i<row&&i>=0&&j<col&&j>=0;i+=dx,j+=dy)
		if(mat[i][j]!=str[op++])
			return false;
	return op==str.length();
}

xy_t search_str(string& str,int row,int col)
{
	int i,j;

	static int dx[8]={-1,-1,0,1,1,1,0,-1},
			   dy[8]={0,1,1,1,0,-1,-1,-1};

	for(i=0;i<row;++i){
		int k;
		for(k=i,j=0;k>=0&&j<col;++j,--k){
			int tx=k,ty=j;
			for(int dir=0;dir<8;++dir)
				if(cmp(str,tx,ty,dx[dir],dy[dir],row,col))
					return xy_t(tx,ty);
		}
	}
	i=row-1;
	for(j=1;j<col;++j){
		int tx=i,ty=j;
		for(;tx>=0&&tx<row&&ty<col&&ty>=0;++ty,--tx)
			for(int dir=0;dir<8;++dir)
				if(cmp(str,tx,ty,dx[dir],dy[dir],row,col))
					return xy_t(tx,ty);
	}
	return xy_t(-2,-2);
}

int main()
{
	int total_test;
	int row, col;
	int k;

	cin>>total_test;
	while (total_test-->0){
		cin>>row>>col;
		cin.ignore();
		for(int i=0;i<row;++i,cin.ignore())
			for(int j=0;j<col;++j){
				cin>>mat[i][j];
				mat[i][j]=tolower(mat[i][j]);
			}
		cin>>k;
		cin.ignore();
		while(k-->0){
			string str;
			cin>>str;
			for(int t=0;t<str.length();++t)
				str[t]=tolower(str[t]);

			xy_t ans=search_str(str,row,col);
			cout<<ans.x+1<<' '<<ans.y+1<<endl;
		}
		if(total_test!=0)
			cout<<endl;
	}
	return 0;
}
