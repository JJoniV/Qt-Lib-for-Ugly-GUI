#include <stdio.h>
	int main(){
		int n=0,m=1;
		for(int i = 0; i < 10; i++){
			printf("%d\n",n);
			int temp = n;
			n = m;
			m += temp;
		}
			
		printf("Hello");
		return 0;
	}
