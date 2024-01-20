#include <math.h>
#include <fstream>
bool student(double t,double pr, int N)
{
	int n,m,i,j;
	double **a;
	FILE *h;
	h=fopen("student","rb");
	fread(&n,sizeof(int),1,h);
	fread(&m,sizeof(int),1,h);
	a=new double *[n];
	for(i=0;i<n;i++)
	a[i]=new double[m];
	for(i=0;i<n;i++)
	fread(a[i],sizeof(double),m,h);
	fclose(h);
	
	for(i=0;i<m;i++)
	if(a[0][i]==pr) j=i;
	
	if (N>=1 && N<=30)
	{
		if (a[N][j]>t) return 0;
	}
	else if (N==40)
	{
		if (a[31][j]>t) return 0;
	}
	else if (N==60)
	{
		if (a[32][j]>t) return 0;
	}
	else if (N==120)
	{
		if (a[33][j]>t) return 0;
	}
	else if(N>120)
	{
		if (a[34][j]>t) return 0;
	}
	return 1;
}
double *fault(double *y,double *Y)
{
	int i,n;
	double *bug,My;
	n=sizeof(y);
	bug=new double[3];
	for(bug[0]=i=0;i<n;i++)
	bug[0]=bug[0]+pow(y[i]-Y[i],2);//квадратичная ошибка

	bug[1]=sqrt(bug[0])/n;//средняя ошибка в точке

	for(My=i=0;i<n;i++)
	My=My+y[i];
	My=My/n;
	bug[2]=bug[1]/My;//относительная ошибка
	return bug;	
}
double *correlation(double *y,double *x,double *Y)
{
	int i,n;
	n=sizeof(y);
	double *kor,My,Mx,s1,s2,s3;
	kor=new double[2];
	for(Mx=i=0;i<n;i++)
	Mx=Mx+x[i];
	Mx=Mx/n;
	
	for(My=i=0;i<n;i++)
	My=My+y[i];
	My=My/n;
	for(s1=i=0;i<n;i++)
	s1+=(x[i]-Mx)*(y[i]-My);
	
	for(s2=i=0;i<n;i++)
	s2+=(x[i]-Mx)*(x[i]-Mx);
	
	for(s3=i=0;i<n;i++)
	s3+=(y[i]-My)*(y[i]-My);
	kor[0]=s1/sqrt(s2*s3);//Коэффициент корреляции
	
	for(s1=i=0;i<n;i++)
	s1=s1+pow(y[i]-Y[i],2);
	
	for(s2=i=0;i<n;i++)
	s2=s2+(y[i]-My)*(y[i]-My);
	kor[1]=sqrt(1-s1/s2);//Индекс корреляции
	return kor;
}
double kritstudent(double *y,double *x,double *Y)
{
	double *krits;
	int n;
	n=sizeof(y);
	krits=new double[2];
	krits=correlation(y,x,Y);
	double r=krits[0];
	return (sqrt(r*r*(n-2)/(1-r*r)));
}
bool gause(double **A,double *B,double *x,int n)
{
	double *b,**a,maxn,M,s,f;
	int i,j,maxi,k;
	
	b=(double *)calloc(n,sizeof(double));
	for(i=0;i<n;i++)
	b[i]=B[i];
	a=(double **)calloc(n,sizeof(double *));
	for(i=0;i<n;i++) a[i]=(double *)calloc(n,sizeof(double));
	for(i=0;i<n;i++)
	for(j=0;j<n;j++)
	a[i][j]=A[i][j];
		for(k=0;k<n;k++)
		{
			maxi=k;
			maxn=fabs(a[k][k]);
			for(i=k+1;i<n;i++)
			if(fabs(a[i][k])>maxn)
			{
				maxn=fabs(a[i][k]);
				maxi=i;
			}
			
			for(i=k;i<n;i++)
			{
				f=a[k][i];
				a[k][i]=a[maxi][i];
				a[maxi][i]=f;
			};
			f=b[maxi];
			b[maxi]=b[k];
			b[k]=f;
			for(i=k+1;i<n;i++)
				{
					M=a[i][k]/a[k][k];
					for(j=k;j<n;j++)
					a[i][j]-=M*a[k][j];
					b[i]-=M*b[k];
				}
		}
		if(a[n-1][n-1]==0)
		{
			return 0;
		}
		else
		{
			for(i=n-1;i>-1;i--)
			{
				for(s=0,j=i+1;j<n;j++)
				s+=a[i][j]*x[j];
				x[i]=(b[i]-s)/a[i][i];
			}
		}
	return 1;
}
double znach(double *P,double x)
{
	double b;
	int n=sizeof(P);
	int i;
	b=P[0];
	for (i=1;i<n;i++)
	b=P[i]+x*b;
	return b;
}
double* parabolan(double *x,double *y,int st)
{
	double **C,*g,s;
	int i,j,k;
	int n=sizeof(x);
	st=st+1;
	bool pr;
	for(i=1;i<n;i++)
	{
		for(pr=false,j=0;j<n-i;j++)
		if(x[j]>x[j+1]) 
		{
		s=x[j];
		x[j]=x[j+1];
		x[j+1]=s;
		pr=true;
		s=y[j];
		y[j]=y[j+1];
		y[j+1]=s;
		}
		if(!pr) break;
	}
	C=(double **)calloc(st,sizeof(double *));
	for(i=0;i<st;i++) C[i]=(double *)calloc(st,sizeof(double));
	for(i=0;i<st;i++)
	for(j=0;j<st;j++)
	{
		s=0;
		for(k=0;k<n;k++)
		s=s+pow(x[k],(i+j));
		C[i][j]=s;
	}
	g=new double[st];
	for(i=0;i<st;i++)
	{
		s=0;
		for(k=0;k<n;k++)
		s=s+y[k]*pow(x[k],i);
		g[i]=s;
	}
	
	if (gause(C,g,g,st))
	{
		for(i=0;i<st/2;i++)
		{
		s=g[i];
		g[i]=g[st-i-1];
		g[st-i-1]=s;
		}
	}
	return g;
}
double* drob(double *x,double *y,int st)
{
	double **C,*g,s,*Y1;
	int i,j,k;
	bool pr;
		int n=sizeof(x);
	for(i=1;i<n;i++)
	{
		for(pr=false,j=0;j<n-i;j++)
		if(x[j]>x[j+1]) 
		{
		s=x[j];
		x[j]=x[j+1];
		x[j+1]=s;
		pr=true;
		s=y[j];
		y[j]=y[j+1];
		y[j+1]=s;
		}
		if(!pr) break;
	}
	
	st=st+1;
	Y1=new double[n];
	for(i=0;i<n;i++)
	Y1[i]=1/y[i];
	
	C=(double **)calloc(st,sizeof(double *));
	for(i=0;i<st;i++) C[i]=(double *)calloc(st,sizeof(double));
	for(i=0;i<st;i++)
	for(j=0;j<st;j++)
	{
		s=0;
		for(k=0;k<n;k++)
		s=s+pow(x[k],(i+j));
		C[i][j]=s;
	}
	g=new double[st];
	for(i=0;i<st;i++)
	{
		s=0;
		for(k=0;k<n;k++)
		s=s+Y1[k]*pow(x[k],i);
		g[i]=s;
	}
	if(gause(C,g,g,st))
	for(i=0;i<st/2;i++)
		{
		s=g[i];
		g[i]=g[st-i-1];
		g[st-i-1]=s;
		}
	return g;
}
double *gybrid(double *x,double *y)
{
	int i,kol=3,j,c,d,k;
	double **C,s;
	double *Y;
	bool pr;
	int n=sizeof(x);
	for(i=1;i<n;i++)
	{
		for(pr=false,j=0;j<n-i;j++)
		if(x[j]>x[j+1]) 
		{
		s=x[j];
		x[j]=x[j+1];
		x[j+1]=s;
		pr=true;
		s=y[j];
		y[j]=y[j+1];
		y[j+1]=s;
		}
		if(!pr) break;
	}
	Y=new double[n];
	for(i=0;i<n;i++)
	Y[i]=log(y[i]);
	
	C=new double*[kol];
	for(i=0;i<kol;i++) C[i]=new double[kol];
	double LN;
	for(i=0;i<kol;i++)
	for(j=0;j<kol;j++)
	{
	s=0;
		if (j==1 || i==1)
		{
		if (j==1 && i==1) c=2;
		else c=1;
	}
		else c=0;
  
	if(j==2 || i==2)
	{
	if(j==2 && i==2)
	d=2;
	else d=1;
		}
  else d=0;
  
  
  for(k=0;k<n;k++)
  {
   LN=log(x[k]);
  s=s+pow(LN,c)*pow(x[k],d);
 }
  C[i][j]=s;
 }
 double *g;
 g=new double[kol];
 for (i=0;i<kol;i++)
 {
  if (i==1)
  {
   c=1;
   d=0;
  }
  else if (i==2)
  {
   c=0;
   d=1;
  }
  else c=d=0;
  s=0;
  for(k=0;k<n;k++)
  s+=Y[k]*pow(log(x[k]),c)*pow(x[k],d);
  g[i]=s;
 } 
 if(!gause(C,g,g,kol)) return 0;
 g[0]=exp(g[0]);
 return g;
}
 double *exponent(double *x,double *y)
{
	int i,k,kol=2,j;
	double *s,*K,**C,S,*g,*K1,s1;
	bool pr;
		int n=sizeof(x);
	for(i=1;i<n;i++)
	{
		for(pr=false,j=0;j<n-i;j++)
		if(x[j]>x[j+1]) 
		{
		s1=x[j];
		x[j]=x[j+1];
		x[j+1]=s1;
		pr=true;
		s1=y[j];
		y[j]=y[j+1];
		y[j+1]=s1;
		}
		if(!pr) break;
	}
	s=new double[n];
	K=new double[n];
	for(i=0;i<n;i++)
	{
		s[i]=x[i];
		K[i]=y[i];
	}
	
	C=(double **)calloc(kol,sizeof(double*));
	for(i=0;i<kol;i++) C[i]=(double *)calloc(kol,sizeof(double));
	
	for(i=0;i<kol;i++)
	for(j=0;j<kol;j++)
	{
		S=0;
		for(k=0;k<n;k++)
		S+=pow(s[k],i+j);
		C[i][j]=S;
	}
	K1=new double[n];
	for(i=0;i<n;i++)
	K1[i]=log(K[i]);
	
	g=new double[kol];
	for(i=0;i<kol;i++)
	{
		S=0;
		for(k=0;k<n;k++)
		S+=K1[k]*pow(s[k],i);
		g[i]=S;
	}
	if(!gause(C,g,g,kol)) return 0;
	g[0]=exp(g[0]);
	return g;
}
double S1(double *a, int n)
{
	int i;
	double S;
	for (S=i=0;i<n;i++)
	S+=a[i];
	return S;
}
double S2(double *a, double *b, int n)
{
	int i;
	double S;
	for (S=i=0;i<n;i++)
	S+=a[i]*b[i];
	return S;
}
 double *stepen(double *x,double *y)
{
	int i,j;
	double *z,*g,s1,*x1,a,b;
	bool pr;
		int n=sizeof(x);
	for(i=1;i<n;i++)
	{
		for(pr=false,j=0;j<n-i;j++)
		if(x[j]>x[j+1]) 
		{
		s1=x[j];
		x[j]=x[j+1];
		x[j+1]=s1;
		pr=true;
		s1=y[j];
		y[j]=y[j+1];
		y[j+1]=s1;
		}
		if(!pr) break;
	}
	g=new double[2];
	z=new double[n];
	x1=new double[n];
	for (i=0;i<n;i++)
	{
		z[i]=log(y[i]);
		x1[i]=log(x[i]);
	}
    b=((n*S2(x1,z,n))-(S1(z,n)*S1(x1,n)))/((n*S2(x1,x1,n))-(S1(x1,n)*S1(x1,n)));
    a=(1./n)*(S1(z,n)-b*S1(x1,n));
    a=exp(a);
    g[0]=a;
    g[1]=b;
	return g;
}	
