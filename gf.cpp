#include"gf.h"

void poly::init()
{
	for (register int i=0;i<300;++i)
		coe[i]=0;
	len=0;
	return;
}

void poly::clean()
{
	while (!coe[len-1]&&len>=1) len--;
	return;
}

void poly::mulx(int m)
{
	if (m==0)
		return;
	for (register int i=len;i>=0;i--)
	{
		coe[i+m]=coe[i];
		coe[i]=0;
	}
	len+=m;
	return;
}