#include"gf.h"
#include"svpng.inc"
#define INF 0x3f3f3f3f
#define min(a,b) ((a)<(b)?(a):(b))
int QRCode[30][30];
int nochange[30][30];
//0 for ¡õ and 1 for ¡ö
//QRCode[ÁÐ][ÐÐ]

void _print(int v)
{
	/*for (register int i=0;i<(v-1)*4+21;++i)
	{
		for (register int j=0;j<(v-1)*4+21;++j)
		{
			mp[j][i]?printf("¡ö"):printf("¡õ");
		}
		printf("\n");
	}*/
	/*printf("--------------------------\n");
	for (register int i=0;i<(v-1)*4+21;++i)
	{
		for (register int j=0;j<(v-1)*4+21;++j)
		{
			printf("%d",nochange[j][i]);
		}
		printf("\n");
	}
	printf("------------------------------\n");
	printf("------------------------------\n");*/
	register int siz=v*4+17;
	unsigned char rgb[siz*siz*225*3],*p=rgb;
	FILE *fp = fopen("QRCode.png", "wb");
	for (register int y=0;y<siz;y++)
		for (register int m=1;m<=15;++m)
			for (register int x=0;x<siz;x++)
				for (register int n=1;n<=15;++n)
				{
					*p++=QRCode[x][y]?0:255;
					*p++=QRCode[x][y]?0:255;
					*p++=QRCode[x][y]?0:255;
				}
	svpng(fp,siz*15,siz*15,rgb,0);
	fclose(fp);
	printf("The QRCode image has been successfully generated.\n");
	return;
}

void print_init(int v)
{
	memset(QRCode,0,sizeof(QRCode));
	for (register int i=0;i<7;++i)
	{
		QRCode[i][0]=1;nochange[i][0]=1;
		QRCode[i][6]=1;nochange[i][6]=1;
		QRCode[(v-1)*4+14+i][0]=1;nochange[(v-1)*4+14+i][0]=1;
		QRCode[(v-1)*4+14+i][6]=1;nochange[(v-1)*4+14+i][6]=1;
		QRCode[i][(v-1)*4+14]=1;nochange[i][(v-1)*4+14]=1;
		QRCode[i][(v-1)*4+20]=1;nochange[i][(v-1)*4+20]=1;
	}
	for (register int i=1;i<=5;++i)
	{
		QRCode[0][i]=1;nochange[0][i]=1;
		QRCode[6][i]=1;nochange[6][i]=1;
		QRCode[0][(v-1)*4+14+i]=1;nochange[0][(v-1)*4+14+i]=1;
		QRCode[6][(v-1)*4+14+i]=1;nochange[6][(v-1)*4+14+i]=1;
		QRCode[(v-1)*4+14][i]=1;nochange[(v-1)*4+14][i]=1;
		QRCode[(v-1)*4+20][i]=1;nochange[(v-1)*4+20][i]=1;
	}
	for (register int i=0;i<3;++i)
		for (register int j=0;j<3;++j)
		{
			QRCode[2+i][2+j]=1;nochange[2+i][2+j]=1;
			QRCode[(v-1)*4+16+i][2+j]=1;nochange[(v-1)*3+16+i][2+j]=1;
			QRCode[2+i][(v-1)*4+16+j]=1;nochange[2+i][(v-1)*4+16+j]=1;
		}
	for (register int i=0;i<8;++i)
	{
		nochange[7][i]=1;
		nochange[(v-1)*4+13][i]=1;
		nochange[7][(v-1)*4+13+i]=1;
	}
	for (register int i=0;i<7;++i)
	{
		nochange[i][7]=1;
		nochange[(v-1)*4+14+i][7]=1;
		nochange[i][(v-1)*4+13]=1;
	}
	for (register int i=0;i<5;++i)
		for (register int j=0;j<5;++j)
		{
			nochange[1+i][1+j]=1;
			nochange[1+i][(v-1)*4+15+j]=1;
			nochange[(v-1)*4+15+i][1+j]=1;
		}
	if (v==2)
	{
		for (register int i=0;i<5;++i)
			QRCode[16+i][16]=1,QRCode[16+i][20]=1;
		for (register int i=0;i<3;++i)
			QRCode[16][17+i]=1,QRCode[20][17+i]=1;
		for (register int i=16;i<=20;++i)
			for (register int j=16;j<=20;++j)
				nochange[i][j]=1;
		QRCode[18][18]=1;nochange[18][18]=1;
	}
	register int f=1;
	for (register int i=0;i<(v==1?5:9);++i)
	{
		QRCode[8+i][6]=f;nochange[8+i][6]=1;
		QRCode[6][8+i]=f;nochange[6][8+i]=1;
		f=!f;
	}
	QRCode[8][4*v+9]=1;nochange[8][4*v+9]=1;
	for (register int i=0;i<9;++i)
	{
		nochange[i][8]=1;
		nochange[8][i]=1;
	}
	for (register int i=0;i<8;++i)
	{
		nochange[8][(v-1)*4+13+i]=1;
		nochange[(v-1)*4+13+i][8]=1;
	}
	//_print(QRCode,v);
	return;
}

void nxtp(int &xx,int &yy,int &c,int &r,int v,int &f)
{
	xx+=c;
	if (f) yy+=r;
	if (yy<0||yy>=(v-1)*4+21)
	{
		yy-=r;
		xx-=c;
		r=-r;
		xx-=c;
		if (xx==6) xx-=c;
	}
	c=-c;
	f=!f;
	//printf("(%d,%d),c=%d,r=%d,f=%d\n",xx,yy,c,r,f);
	return;
}

int calc(int mp[][30],int v,int erl,int idt)
{
	register int sum=0,siz=v*4+17;
	poly mc;
	mc.init();
	switch (erl)
	{
		case 1:
			mc.coe[14]=0;
			mc.coe[13]=1;
			break;
		case 2:
			mc.coe[14]=0;
			mc.coe[13]=0;
			break;
		case 3:
			mc.coe[14]=1;
			mc.coe[13]=1;
			break;
		case 4:
			mc.coe[14]=1;
			mc.coe[13]=0;
			break;
	}
	for (register int i=0;i<13;++i)
		mc.coe[i]=0;
	mc.len=15;
	register int p=10,_id=idt;
	while (_id)
	{
		mc.coe[p++]=_id%2;
		_id/=2;
	}
	mc.clean();
	poly c,ct;
	c.init();ct.init();
	c.len=11;
	c.coe[0]=1,c.coe[1]=1,c.coe[2]=1,c.coe[4]=1,c.coe[5]=1,c.coe[8]=1,c.coe[10]=1;
	while (mc.len>10)
	{
		ct=c;
		ct.mulx(mc.len-ct.len);
		for (register int i=mc.len-1;i>=0;i--)
		{
			mc.coe[i]=mc.coe[i]^ct.coe[i];
			//printf("%d ",mc.coe[i]);
		}
		//printf("\n");
		mc.clean();
	}
	while (mc.len<10)
		mc.coe[mc.len++]=0;
	switch (erl)
	{
		case 1:
			mc.coe[14]=0;
			mc.coe[13]=1;
			break;
		case 2:
			mc.coe[14]=0;
			mc.coe[13]=0;
			break;
		case 3:
			mc.coe[14]=1;
			mc.coe[13]=1;
			break;
		case 4:
			mc.coe[14]=1;
			mc.coe[13]=0;
			break;
	}
	for (register int i=10;i<13;++i)
		mc.coe[i]=0;
	mc.len=15;
	p=10;
	while (idt)
	{
		mc.coe[p++]=idt%2;
		idt/=2;
	}
	int fmtcode[20]={0,1,0,0,1,0,0,0,0,0,1,0,1,0,1};
	for (register int i=0;i<15;++i)
		fmtcode[i]^=mc.coe[i];
	for (register int i=0;i<=6;++i)
	{
		register int b=fmtcode[i];
		fmtcode[i]=fmtcode[14-i];
		fmtcode[14-i]=b;
	}
	for (register int i=0;i<=6;++i)
	{
		mp[i+(i>5?1:0)][8]=fmtcode[i];
		mp[8][siz-1-i]=fmtcode[i];
	}
	for (register int i=0;i<=7;++i)
	{
		mp[8][8-i-(i>1?1:0)]=fmtcode[7+i];
		mp[siz-8+i][8]=fmtcode[7+i];
	}
	for (register int i=0;i<siz;++i)
	{
		register int tmp=1;
		for (register int j=1;j<siz;++j)
		{
			if (mp[i][j]==mp[i][j-1])
				tmp++;
			else
			{
				sum+=tmp<5?0:tmp-2;
				tmp=1;
			}
		}
	}
	for (register int i=0;i<siz;++i)
	{
		register int tmp=1;
		for (register int j=1;j<siz;++j)
		{
			if (mp[j][i]==mp[j-1][i])
				tmp++;
			else
			{
				sum+=tmp<5?0:tmp-2;
				tmp=1;
			}
		}
	}
	for (register int i=0;i<siz-1;++i)
		for (register int j=0;j<siz-1;++j)
			if (mp[i][j]==mp[i+1][j]&&mp[i][j]==mp[i][j+1]&&mp[i][j]==mp[i+1][j+1])
				sum+=3;
	for (register int i=0;i<siz-1;++i)
		for (register int j=0;j<siz-10;++j)
			if (mp[i][j]&&!mp[i][j+1]&&mp[i][j+2]&&mp[i][j+3]&&mp[i][j+4]&&!mp[i][j+5]&&mp[i][j+6]&&!mp[i][j+7]&&!mp[i][j+8]&&!mp[i][j+9]&&!mp[i][j+10])
				sum+=40;
	for (register int i=0;i<siz-1;++i)
		for (register int j=0;j<siz-10;++j)
			if (!mp[i][j]&&!mp[i][j+1]&&!mp[i][j+2]&&!mp[i][j+3]&&mp[i][j+4]&&!mp[i][j+5]&&mp[i][j+6]&&mp[i][j+7]&&mp[i][j+8]&&!mp[i][j+9]&&mp[i][j+10])
				sum+=40;
	for (register int i=0;i<siz-1;++i)
		for (register int j=0;j<siz-10;++j)
			if (mp[j][i]&&!mp[j+1][i]&&mp[j+2][i]&&mp[j+3][i]&&mp[j+4][i]&&!mp[j+5][i]&&mp[j+6][i]&&!mp[j+7][i]&&!mp[j+8][i]&&!mp[j+9][i]&&!mp[j+10][i])
				sum+=40;
	for (register int i=0;i<siz-1;++i)
		for (register int j=0;j<siz-10;++j)
			if (!mp[j][i]&&!mp[j+1][i]&&!mp[j+2][i]&&!mp[j+3][i]&&mp[j+4][i]&&!mp[j+5][i]&&mp[j+6][i]&&mp[j+7][i]&&mp[j+8][i]&&!mp[j+9][i]&&mp[j+10][i])
				sum+=40;
	register int blk=0;
	for (register int i=0;i<siz;++i)
		for (register int j=0;j<siz;++j)
			blk+=mp[i][j];
	register double rate=(double)blk/(siz*siz);
	rate*=100;
	register int cnt=((int)rate)/5;
	sum+=min(abs(cnt*5-50),abs(cnt*5-45))*2;
	//printf("score is %d\n",sum);
	return sum;
}

int mask_code(int v,int erl)
{
	int tmp[30][30],_qrcode[30][30],cur,choice;
	int scr=INF,id;
	memcpy(_qrcode,QRCode,sizeof(QRCode));
	memcpy(tmp,_qrcode,sizeof(_qrcode));
	register int siz=v*4+17;
	for (register int i=0;i<siz;++i)
		for (register int j=0;j<siz;++j)
			if (!nochange[i][j])
				if (!((i+j)%2))
					tmp[i][j]=!tmp[i][j];
	cur=calc(tmp,v,erl,0);
	//printf("score for #0 is %d\n",cur);
	//_print(tmp,v);
	if (cur<scr)
	{
		scr=cur,id=0;
		memcpy(QRCode,tmp,sizeof(tmp));
	}
	memcpy(tmp,_qrcode,sizeof(_qrcode));
	for (register int i=0;i<siz;++i)
		for (register int j=0;j<siz;++j)
			if (!nochange[i][j])
				if (!(j%2))
					tmp[i][j]=!tmp[i][j];
	cur=calc(tmp,v,erl,1);
	//printf("score for #1 is %d\n",cur);
	//_print(tmp,v);
	if (cur<scr)
	{
		scr=cur,id=1;
		memcpy(QRCode,tmp,sizeof(tmp));
	}
	memcpy(tmp,_qrcode,sizeof(_qrcode));
	for (register int i=0;i<siz;++i)
		for (register int j=0;j<siz;++j)
			if (!nochange[i][j])
				if (!(i%3))
					tmp[i][j]=!tmp[i][j];
	cur=calc(tmp,v,erl,2);
	//printf("score for #2 is %d\n",cur);
	//_print(tmp,v);
	if (cur<scr)
	{
		scr=cur,id=2;
		memcpy(QRCode,tmp,sizeof(tmp));
	}
	memcpy(tmp,_qrcode,sizeof(_qrcode));
	for (register int i=0;i<siz;++i)
		for (register int j=0;j<siz;++j)
			if (!nochange[i][j])
				if (!((i+j)%3)) 
					tmp[i][j]=!tmp[i][j];
	cur=calc(tmp,v,erl,3);
	//printf("score for #3 is %d\n",cur);
	//_print(tmp,v);
	if (cur<scr)
	{
		scr=cur,id=3;
		memcpy(QRCode,tmp,sizeof(tmp));
	}
	memcpy(tmp,_qrcode,sizeof(_qrcode));
	for (register int i=0;i<siz;++i)
		for (register int j=0;j<siz;++j)
			if (!nochange[i][j])
				if (!((j/2+i/3)%2))
					tmp[i][j]=!tmp[i][j];
	cur=calc(tmp,v,erl,4);
	//printf("score for #4 is %d\n",cur);
	//_print(tmp,v);
	if (cur<scr)
	{
		scr=cur,id=4;
		memcpy(QRCode,tmp,sizeof(tmp));
	}
	memcpy(tmp,_qrcode,sizeof(_qrcode));
	for (register int i=0;i<siz;++i)
		for (register int j=0;j<siz;++j)
			if (!nochange[i][j])
				if (!((i*j)%2+(i*j)%3))
					tmp[i][j]=!tmp[i][j];
	cur=calc(tmp,v,erl,5);
	//printf("score for #5 is %d\n",cur);
	//_print(tmp,v);
	if (cur<scr)
	{
		scr=cur,id=5;
		memcpy(QRCode,tmp,sizeof(tmp));
	}
	memcpy(tmp,_qrcode,sizeof(_qrcode));
	for (register int i=0;i<siz;++i)
		for (register int j=0;j<siz;++j)
			if (!nochange[i][j])
				if (!(((i*j)%2+(i*j)%3)%2))
					tmp[i][j]=!tmp[i][j];
	cur=calc(tmp,v,erl,6);
	//printf("score for #6 is %d\n",cur);
	//_print(tmp,v);
	if (cur<scr)
	{
		scr=cur,id=6;
		memcpy(QRCode,tmp,sizeof(tmp));
	}
	memcpy(tmp,_qrcode,sizeof(_qrcode));
	for (register int i=0;i<siz;++i)
		for (register int j=0;j<siz;++j)
			if (!nochange[i][j])
				if (!(((i+j)%2+(i*j)%3)%2))
					tmp[i][j]=!tmp[i][j];
	cur=calc(tmp,v,erl,7);
	//printf("score for #7 is %d\n",cur);
	//_print(tmp,v);
	if (cur<scr)
	{
		scr=cur,id=7;
		memcpy(QRCode,tmp,sizeof(tmp));
	}
	choice=id;
	poly mc;
	mc.init();
	switch (erl)
	{
		case 1:
			mc.coe[14]=0;
			mc.coe[13]=1;
			break;
		case 2:
			mc.coe[14]=0;
			mc.coe[13]=0;
			break;
		case 3:
			mc.coe[14]=1;
			mc.coe[13]=1;
			break;
		case 4:
			mc.coe[14]=1;
			mc.coe[13]=0;
			break;
	}
	for (register int i=0;i<13;++i)
		mc.coe[i]=0;
	mc.len=15;
	register int p=10,_id=id;
	while (_id)
	{
		mc.coe[p++]=_id%2;
		_id/=2;
	}
	mc.clean();
	poly c,ct;
	c.init();ct.init();
	c.len=11;
	c.coe[0]=1,c.coe[1]=1,c.coe[2]=1,c.coe[4]=1,c.coe[5]=1,c.coe[8]=1,c.coe[10]=1;
	while (mc.len>10)
	{
		ct=c;
		ct.mulx(mc.len-ct.len);
		for (register int i=mc.len-1;i>=0;i--)
		{
			mc.coe[i]=mc.coe[i]^ct.coe[i];
			//printf("%d ",mc.coe[i]);
		}
		//printf("\n");
		mc.clean();
	}
	while (mc.len<10)
		mc.coe[mc.len++]=0;
	switch (erl)
	{
		case 1:
			mc.coe[14]=0;
			mc.coe[13]=1;
			break;
		case 2:
			mc.coe[14]=0;
			mc.coe[13]=0;
			break;
		case 3:
			mc.coe[14]=1;
			mc.coe[13]=1;
			break;
		case 4:
			mc.coe[14]=1;
			mc.coe[13]=0;
			break;
	}
	for (register int i=10;i<13;++i)
		mc.coe[i]=0;
	mc.len=15;
	p=10;
	//printf("%d\n",id);
	while (id)
	{
		mc.coe[p++]=id%2;
		id/=2;
	}
	/*for (register int i=14;i>=0;i--)
		printf("%d ",mc.coe[i]);
	printf("\n");*/
	int fmtcode[20]={0,1,0,0,1,0,0,0,0,0,1,0,1,0,1};
	for (register int i=0;i<15;++i)
		fmtcode[i]^=mc.coe[i];
	for (register int i=0;i<=6;++i)
	{
		register int b=fmtcode[i];
		fmtcode[i]=fmtcode[14-i];
		fmtcode[14-i]=b;
	}
	/*for (register int i=0;i<=14;++i)
		printf("%d ",fmtcode[i]);
	printf("\n");*/
	for (register int i=0;i<=6;++i)
	{
		QRCode[i+(i>5?1:0)][8]=fmtcode[i];
		QRCode[8][siz-1-i]=fmtcode[i];
	}
	for (register int i=0;i<=7;++i)
	{
		QRCode[8][8-i-(i>1?1:0)]=fmtcode[7+i];
		QRCode[siz-8+i][8]=fmtcode[7+i];
	}
	return choice;
}

void print(int v,int erl,char _cont[])
{
	print_init(v);
	register int c=-1,r=-1;
	register int x=(v-1)*4+20,y=(v-1)*4+20,f=0;
	register int _l=strlen(_cont),i=0;
	for (i=0;i<_l;++i)
	{
		//printf("cont[%d]=%c  ",i,_cont[i]);
		//printf("now at (%d,%d)\n",x,y);
		while (nochange[x][y])
		{
			//printf("QRCode[%d][%d] can't change.\n",x,y);
			nxtp(x,y,c,r,v,f);
			//printf("Jump to QRCode[%d][%d].\n",x,y);
		}
		//printf("now at (%d,%d),c=%d,r=%d,f=%d\n",x,y,c,r,f);
		QRCode[x][y]=_cont[i]-'0';
		nxtp(x,y,c,r,v,f);
	}
	//_print(v);
	mask_code(v,erl);
	_print(v);
	return;
}