#include"gf.h"
int alp[300],num_to_alp[300];
int m[3][5];
poly _c,_ct;

void ECcode_table(int v,int erl)
{
	m[1][1]=7,m[1][2]=10,m[1][3]=13,m[1][4]=17;
	m[2][1]=10,m[2][2]=16,m[2][3]=22,m[2][4]=28;
	if (v==1&&erl==1)
	{
		_c.coe[0]=alp[21];_c.coe[1]=alp[102];_c.coe[2]=alp[238];_c.coe[3]=alp[149];_c.coe[4]=alp[146];
		_c.coe[5]=alp[229];_c.coe[6]=alp[87];_c.coe[7]=alp[0];
		_c.len=8;
	}
	else if ((v==1&&erl==2)||(v==2&&erl==1))
	{
		_c.coe[0]=alp[45];_c.coe[1]=alp[32];_c.coe[2]=alp[94];_c.coe[3]=alp[64];_c.coe[4]=alp[70];
		_c.coe[5]=alp[118];_c.coe[6]=alp[61];_c.coe[7]=alp[46];_c.coe[8]=alp[67];_c.coe[9]=alp[251];_c.coe[10]=alp[0];
		_c.len=11;
	}
	else if(v==1&&erl==3)
	{
		_c.coe[0]=alp[78];_c.coe[1]=alp[140];_c.coe[2]=alp[206];_c.coe[3]=alp[218];_c.coe[4]=alp[130];
		_c.coe[5]=alp[104];_c.coe[6]=alp[106];_c.coe[7]=alp[100];_c.coe[8]=alp[86];_c.coe[9]=alp[100];
		_c.coe[10]=alp[176];_c.coe[11]=alp[152];_c.coe[12]=alp[74];_c.coe[13]=alp[0];
		_c.len=14;
	}
	else if(v==1&&erl==4)
	{
		_c.coe[0]=alp[136];_c.coe[1]=alp[163];_c.coe[2]=alp[243];_c.coe[3]=alp[39];_c.coe[4]=alp[150];
		_c.coe[5]=alp[99];_c.coe[6]=alp[24];_c.coe[7]=alp[147];_c.coe[8]=alp[214];_c.coe[9]=alp[206];
		_c.coe[10]=alp[123];_c.coe[11]=alp[239];_c.coe[12]=alp[43];_c.coe[13]=alp[78];_c.coe[14]=alp[206];
		_c.coe[15]=alp[139];_c.coe[16]=alp[43];_c.coe[17]=alp[0];
		_c.len=18;
	}
	else if(v==2&&erl==2)
	{
		_c.coe[0]=alp[120];_c.coe[1]=alp[225];_c.coe[2]=alp[194];_c.coe[3]=alp[182];_c.coe[4]=alp[169];
		_c.coe[5]=alp[147];_c.coe[6]=alp[191];_c.coe[7]=alp[91];_c.coe[8]=alp[3];_c.coe[9]=alp[76];
		_c.coe[10]=alp[161];_c.coe[11]=alp[102];_c.coe[12]=alp[109];_c.coe[13]=alp[107];_c.coe[14]=alp[104];
		_c.coe[15]=alp[120];_c.coe[16]=alp[0];
		_c.len=17;
	}
	else if(v==2&&erl==3)
	{
		_c.coe[0]=alp[231];_c.coe[1]=alp[165];_c.coe[2]=alp[105];_c.coe[3]=alp[160];_c.coe[4]=alp[134];
		_c.coe[5]=alp[219];_c.coe[6]=alp[80];_c.coe[7]=alp[98];_c.coe[8]=alp[172];_c.coe[9]=alp[8];
		_c.coe[10]=alp[74];_c.coe[11]=alp[200];_c.coe[12]=alp[53];_c.coe[13]=alp[221];_c.coe[14]=alp[109];
		_c.coe[15]=alp[14];_c.coe[16]=alp[230];_c.coe[17]=alp[93];_c.coe[18]=alp[242];_c.coe[19]=alp[247];
		_c.coe[20]=alp[171];_c.coe[21]=alp[210];_c.coe[22]=alp[0];
		_c.len=23;
	}
	else if (v==2&&erl==4)
	{
		_c.coe[0]=alp[123];_c.coe[1]=alp[9];_c.coe[2]=alp[37];_c.coe[3]=alp[242];_c.coe[4]=alp[119];
		_c.coe[5]=alp[212];_c.coe[6]=alp[195];_c.coe[7]=alp[42];_c.coe[8]=alp[87];_c.coe[9]=alp[245];
		_c.coe[10]=alp[43];_c.coe[11]=alp[21];_c.coe[12]=alp[201];_c.coe[13]=alp[232];_c.coe[14]=alp[27];
		_c.coe[15]=alp[205];_c.coe[16]=alp[147];_c.coe[17]=alp[195];_c.coe[18]=alp[190];_c.coe[19]=alp[110];
		_c.coe[20]=alp[180];_c.coe[21]=alp[108];_c.coe[22]=alp[234];_c.coe[23]=alp[224];_c.coe[24]=alp[104];
		_c.coe[25]=alp[200];_c.coe[26]=alp[223];_c.coe[27]=alp[168];_c.coe[28]=alp[0];
		_c.len=29;
	}
	return;
}

void correct_init(int v,int erl,poly &_p)
{
	_p.init();
	alp[0]=1,num_to_alp[1]=0;
	register int tmp=1;
	for (register int i=1;i<=255;++i)
	{
		tmp*=2;
		if (tmp>255)
			tmp=tmp^285;
		alp[i]=tmp;
		num_to_alp[tmp]=i;
	}
	ECcode_table(v,erl);
	return;
}

void correct_code(char _cont[],int v,int erl,poly &_p)
{
	correct_init(v,erl,_p);
	/*for (register int i=_c.len-1;i>0;i--)
		printf("%dx^%d+",_c.coe[i],i);
	printf("%d\n",_c.coe[0]);*/
	register int _l=strlen(_cont);
	for (register int i=_l-1;i>0;i-=8)
		_p.coe[_p.len++]=(_cont[i]-'0')*1+(_cont[i-1]-'0')*2+(_cont[i-2]-'0')*4+(_cont[i-3]-'0')*8+(_cont[i-4]-'0')*16+(_cont[i-5]-'0')*32+(_cont[i-6]-'0')*64+(_cont[i-7]-'0')*128;
	/*for (register int i=_p.len-1;i>0;i--)
		printf("%dx^%d+",_p.coe[i],i);
	printf("%d\n",_p.coe[0]);*/
	_p.mulx(m[v][erl]);
	/*for (register int i=_p.len-1;i>0;i--)
		printf("%dx^%d+",_p.coe[i],i);
	printf("%d\n",_p.coe[0]);*/
	while (_p.len-1>=m[v][erl])
	{
		_ct=_c;
		_ct.mulx(_p.len-_ct.len);
		for (register int i=0;i<_ct.len;i++)
		{
			//printf("%d\n",(num_to_alp[_p.coe[_p.len-1]]+num_to_alp[_ct.coe[i]])%255);
			_ct.coe[i]=_ct.coe[i]==0?0:alp[(num_to_alp[_p.coe[_p.len-1]]+num_to_alp[_ct.coe[i]])%255];
		}
		//printf("%d %d\n",_ct.len,_ct.coe[_ct.len-1]);
		for (register int i=_p.len-1;i>=0;i--)
		{
			//printf("%d xor %d = ",_p.coe[i],_ct.coe[i]);
			_p.coe[i]=(_p.coe[i]^_ct.coe[i]);
			//printf("%d\n",_p.coe[i]);
		}
		_p.clean();
		//printf("%d %d\n",_p.len,_p.coe[_p.len-1]);
	}
	/*for (register int i=_p.len-1;i>0;i--)
		printf("%dx^%d+",_p.coe[i],i);
	printf("%d\n",_p.coe[0]);*/
	return;
}