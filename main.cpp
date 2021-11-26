#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include"encode.cpp"
#include"correct.cpp"
#include"gf.cpp"
#include"print.cpp"
using namespace std;
char cont[4000];
int v,erl;
char er,s[300];
int maxl[3][5];
poly p;

inline void combine()
{
	for (register int i=p.len-1;i>=0;i--)
	{
		register int ltmp=strlen(cont);
		for (register int j=ltmp;j<ltmp+8;++j)
			cont[j]='0';
		bin_code(cont,p.coe[i],ltmp+7);
	}
	return;
}

int main()
{
	maxl[1][1]=19,maxl[1][2]=16,maxl[1][3]=13,maxl[1][4]=9;
	maxl[2][1]=34,maxl[2][2]=28,maxl[2][3]=22,maxl[2][4]=16;
	printf("This generator only support string with upper case letters, numbers and space, '$', '%', '*', '+', '-', '.', '/', ':'\n");
	printf("input Version and Error correction level:");
	scanf("%d",&v);
	while (er=getchar())
	{
		if (er!='L'&&er!='M'&&er!='Q'&&er!='H')
			continue;
		else
		{
			erl=er=='L'?1:er=='M'?2:er=='Q'?3:4;
			break;
		}
	}
	printf("input string(for the version you choose you should enter no more than %d characters):",maxl[v][erl]);
	getchar();
	gets(s);
	while(strlen(s)>maxl[v][erl])
	{
		printf("the length of the string you entered is too long! Please try again!\n");
		gets(s);
	}
	encode(s,v,erl,cont);
	//printf("%s\n",cont);
	correct_code(cont,v,erl,p);
	combine();
	//printf("%s\n",cont);
	//printf("%d\n",strlen(cont));
	print(v,erl,cont);
	return 0;
}