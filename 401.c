#include <stdio.h>
#include <string.h>

char* ref[4] = {
	" -- is not a palindrome.\n",
	" -- is a regular palindrome.\n",
	" -- is a mirrored string.\n",
	" -- is a mirrored palindrome.\n"
};

char mirror[128];

void init_mirror()
{
	int i;
	for(i=0;i<128;++i)
		mirror[i]=-1;

	mirror['A']='A';
	mirror['E']='3';
	mirror['H']='H';
	mirror['I']='I';
	mirror['J']='L';
	mirror['L']='J';

	mirror['M']='M';
	mirror['O']='O';
	mirror['S']='2';
	mirror['T']='T';
	mirror['U']='U';
	mirror['V']='V';
	mirror['W']='W';
	mirror['X']='X';
	mirror['Y']='Y';
	mirror['Z']='5';
	mirror['1']='1';
	mirror['2']='S';
	mirror['3']='E';
	mirror['5']='Z';
	mirror['8']='8';
}

int calc(char* str,int len)
{
	int is_regular, is_mirrored;
	int i, j;
	int ret;

	is_regular=1;
	for(i=0,j=len-1;i<j;++i,--j)
		if(str[i] != str[j]) {
			is_regular=0;
			break;
		}

	is_mirrored=1;
	for(i=0,j=len-1;i<=j;++i,--j)
		if(str[i] != mirror[str[j]]) {
			is_mirrored=0;
			break;
		}
	ret = (is_mirrored << 1) | is_regular;
	return ret;
}


int main()
{
	char str[1000];

	init_mirror();
	while (scanf("%s", str) == 1) {
		int res = calc(str, strlen(str));
		printf("%s%s\n", str, ref[res]);
	}
	return 0;
}
