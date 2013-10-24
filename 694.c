#include <stdio.h>
#include <stdint.h>

int64_t solve(int64_t st, int64_t limit)
{
	int64_t ret=1;

	while (st>1&&st<=limit) {
		if(st%2==0)
			st/=2;
		else
			st=3*st+1;
		++ret;
	}
	if(st>limit)
		--ret;
	return ret;
}

int main()
{
	int64_t a,limit;
	int64_t round=0;
	int64_t ans;

	while(scanf("%ld%ld",&a,&limit),a!=-1&&limit!=-1){
		printf("Case %ld: A = %ld, limit = %ld, number of terms = ", ++round, a, limit);
		ans=solve(a,limit);
		printf("%ld\n", ans);
	}
	return 0;
}

