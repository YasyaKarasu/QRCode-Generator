int l,alpcod[300],e,mp[3][5];

inline void encode_init()
{
	for (int i=0;i<=9;++i) alpcod[i+'0']=i;
	for (int i='A';i<='Z';++i) alpcod[i]=i-'A'+10;
	alpcod[' ']=36;alpcod['$']=37;alpcod['%']=38;alpcod['*']=39;alpcod['+']=40;alpcod['-']=41;alpcod['.']=42;alpcod['/']=43;alpcod[':']=44;
	mp[1][1]=152,mp[1][2]=128,mp[1][3]=104,mp[1][4]=72;
	mp[2][1]=272,mp[2][2]=224,mp[2][3]=176,mp[2][4]=128;
	return;
}

inline void bin_code(char a[],int cod,int ep)//转换为二进制编码
{
	while (cod)
	{	
		a[ep--]=(cod%2)==0?'0':'1';
		cod=cod/2;
	}
	return;
}

inline void _encode(char s[],char a[])
{
	register int num;
	for (register int i=0;i<=l-2;i+=2)
	{
		num=alpcod[(int)s[i]]*45+alpcod[(int)s[i+1]];
		for (register int j=e+1;j<=e+11;++j) a[j]='0';
		e+=11;
		bin_code(a,num,e);
	}
	if (l%2==1)
	{
		num=alpcod[(int)s[l-1]];
		for (register int i=e+1;i<=e+6;++i) a[i]='0';
		e+=6;
		bin_code(a,num,e);
	}
	return;
}

void encode(char s[],int v,int erl,char a[])
{
	encode_init();
	l=strlen(s);
	a[0]='0',a[1]='0',a[2]='1',a[3]='0';//Alphanumeric mode编码
	for (register int i=4;i<=12;++i) a[i]='0';//先全部填上0
	bin_code(a,l,12);//处理字符个数编码
	e=12;
	_encode(s,a);//数据串编码
	for (register int i=1;i<=4&&e+1<mp[v][erl];++i) a[++e]='0';//终止符
	if ((e+1)%8)
	{
		register int ad=8-((e+1)%8);
		for (register int i=1;i<=ad;++i) a[++e]='0';
	}
	register int f=0;
	while (e+1<mp[v][erl])
	{
		if (f==0)
		{
			for (register int i=1;i<=3;++i) a[++e]='1';
			a[++e]='0';a[++e]='1';a[++e]='1';a[++e]='0';a[++e]='0';
		}
		else
		{
			for (register int i=1;i<=3;++i) a[++e]='0';
			a[++e]='1';
			for (register int i=1;i<=3;++i) a[++e]='0';
			a[++e]='1';
		}
		f=!f;
	}
	return;
}