#include "calculate.h"
#include "stdlib.h"

void LU(int n,double *a,double *b,double *c,double d,double e,double *pointx,double *pointy)
{
	double *f=calloc(n+1,sizeof(double));//动态数组，可根据n决定数组大小
	double *g=calloc(n+1,sizeof(double));
	double *h=calloc(n+1,sizeof(double));
	double *k=calloc(n+1,sizeof(double));
	
	double gk_sum=0;
	
	double *y=calloc(n+1,sizeof(double));
	double *x=calloc(n+1,sizeof(double));
		
	double gx_sum=0,gy_sum=0;
	
	double *px=calloc(n+2,sizeof(double));
	double *py=calloc(n+2,sizeof(double));
	int i=0;
	//LU矩阵存储，L由数组f和g存储，U由数值h和k存储
	h[1]=b[1];
	for(i=1;i<n-1;i++)
	{
		f[i]=a[i]/h[i];
		h[i+1]=b[i+1]-f[i]*c[i];
	}
	
	g[1]=d/h[1];
	for(i=1;i<n-2;i++)
	{
		g[i+1]=-g[i]*c[i]/h[i+1];
	}
	f[n-1]=(a[n-1]-g[n-2]*c[n-2])/h[n-1];

	k[1]=e;
	for(i=1;i<n-2;i++)
	{
		k[i+1]=-f[i]*k[i];
	}
	k[n-1]=c[n-1]-f[n-2]*k[n-2];
	

	for(i=1;i<n-1;i++)
	{
		gk_sum=gk_sum+g[i]*k[i];
	}
	h[n]=b[n]-gk_sum-f[n-1]*c[n-1];

	x[0]=6*pointx[n-1];
	y[0]=6*pointy[n-1];
	for(i=0;i<n-2;i++)
	{
		x[i+1]=6*pointx[i]-f[i+1]*x[i];
		y[i+1]=6*pointy[i]-f[i+1]*y[i];
	}

	for(i=0;i<n-2;i++)
	{
		gx_sum=gx_sum+g[i+1]*x[i];
		gy_sum=gy_sum+g[i+1]*y[i];
	}
	x[n-1]=6*pointx[n-2]-gx_sum-f[n-1]*x[n-2];
	y[n-1]=6*pointy[n-2]-gy_sum-f[n-1]*y[n-2];

	px[n-1]=x[n-1]/h[n];
	px[n-2]=(x[n-2]-k[n-1]*px[n-1])/h[n-1];
	py[n-1]=y[n-1]/h[n];
	py[n-2]=(y[n-2]-k[n-1]*py[n-1])/h[n-1];
	
	for(i=n-3;i>=0;i--)
	{
		px[i]=(x[i]-c[i+1]*px[i+1]-k[i+1]*px[n-1])/h[i+1];
		py[i]=(y[i]-c[i+1]*py[i+1]-k[i+1]*py[n-1])/h[i+1];
	}
//  边界条件，即闭合曲线的两控制点，非闭合曲线可不用
//	px[n]=px[0];px[n+1]=px[1];
//	py[n]=py[0];py[n+1]=py[1];

}
void Equalication()
{

  int inum=12;
  double pointx[12]={-10,-50,-50,-10,-20,20,10,50,50,10,20,-20};
  double pointy[12]={10,20,-20,-10,-50,-50,-10,-20,20,10,50,50};

	double *a=calloc(inum,sizeof(double));
	double *b=calloc(inum,sizeof(double));
	double *c=calloc(inum,sizeof(double));
	
	int d=1,e=1;
	int i=0;
	for( i=1;i<=inum;i++)
	{
		b[i]=4;
		if((i+1)<=inum)
		{
			a[i]=1;c[i]=1;
		}
	}
	LU(inum,a,b,c,d,e,pointx,pointy);
}

/*
还需基函数算法,基函数为二维数组，B[i,deg(t)],i表示第几个元素，deg(t)表示阶数
节点表采用顺序方法。例如，曲线有6个控制点，阶数为3，则节点表的大小为6+3+1=10
knot(i)，即节点为0，1/9，2/9，3/9，4/9，5/9，6/9，7/9，8/9，1；
B[i,deg(t)]=[(t-knot(i))/knot(i+deg)-knot(i)]*B[i,deg-1(t)]
            +[(knot(i+deg+1)-t)/knot(i+deg+1)-knot(i+1)*B[i,deg-1(t)]
递归deg次以后回退到0阶，B[i,0]
if(knot(i)<=t<=knot(i+1)) B[i,0]=1
if(t<knot(i)||t>knot(i+1)) B[i,0]=0
最终计算C(t)=连乘(i=0,n-1) B[i,deg(t)]*P(i) 即C(3)
*/

