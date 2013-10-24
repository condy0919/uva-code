#include <stdio.h>
int a[50];
int main()
{
	int n,i,s,ave;
	int round=1;
	while (scanf("%d",&n)==1) {
		if (n==0)
			break;
		s=0;
		for (i=0;i<n;++i){
			scanf("%d",&a[i]);
			s+=a[i];
		}
		ave=s/n;
		s=0;
		for(i=0;i<n;++i)
			if(a[i]>ave)
				s+=a[i]-ave;
		printf("Set #%d\n",round++);
		printf("The minimum number of moves is %d.\n\n",s);
	}
	return 0;
}
