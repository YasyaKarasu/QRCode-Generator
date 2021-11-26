#ifndef GF_H
#define GF_H

struct poly
{
	int coe[300];
	int len;

	void init();

	void clean();

	void mulx(int m);
};

#endif