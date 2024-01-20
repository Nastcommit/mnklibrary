#include <iostream>
#include <math.h>
#include "mnk.h"
#include "GnuP.h"
#include <fstream>
using namespace std;

int main(int argc, char **argv)
{
	cout<<"Вариант 3:\n\n";
	
	double *x,*y,*g;
	int n,i,st;
	FILE *f;
	f=fopen("PRIMER","rb");
	fread(&n,sizeof(int),1,f);
	fread(&st,sizeof(int),1,f);
	x=new double[n];
	y=new double[n];
	fread(x,sizeof(double),n,f);
	fread(y,sizeof(double),n,f);
	fclose(f);
	
	g=new double [st];
	g=exponent(x,y);
	cout<<"Коэффициенты функциональной зависимости\n";
	for(i=0;i<st;i++)
	cout<<g[i]<<"\n";
	
	double *Y;
	Y=new double[n];
	for (i=0;i<n;i++)
	Y[i]=g[0]*exp(x[i]*g[1]);
	
	double *cor;
	cor=new double [2];
	cor=correlation(y,x,Y);
	cout<<"Коэффициент корреляции: "<<cor[0]<<"\n";
	cout<<"Индекс корреляции: "<<cor[1]<<"\n";
	
	double *osh;
	osh=new double [3];
	osh=fault(y,Y);
	cout<<"Квадратичная ошибка: "<<osh[0]<<"\n";
	cout<<"Средняя ошибка: "<<osh[1]<<"\n";
	cout<<"Относительная ошибка: "<<osh[2]<<"\n";
	cout<<"Критерий стьюдента: "<< kritstudent(y,x,Y)<<"\n";
	if(student(kritstudent(y,x,Y),0.95,n-2)) cout<<"Критерий стьюдента значительно отличен от нуля\n";
	else cout<<"Критерий стьюдента незначительно отличен от нуля\n";
	GnuP p;
	p.plotArrayPar(n,x,y,1,0,15);
	p.plotArrayPar(n,x,Y,0,0,2);
	p.plot();
	return 0;
}

