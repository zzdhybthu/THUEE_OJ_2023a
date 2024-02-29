#include<stdio.h>

class X{
public:
    int p,n,m;
    double* a,*b,*c,*d,*e;
    double* z;
    double* y,*x;

    X(){
        scanf("%d%d%d",&p,&n,&m);
        if(p==3){
            P3();
        }else{
            P5();
        }
    }
    void P3(){
        c=new double[n];
        b=new double[n+1];
        a=new double[n+1];
        for(int i=1;i<=n-1;++i){
            scanf("%lf",&c[i]);
        }
        for(int i=1;i<=n;++i){
            scanf("%lf",&b[i]);
        }
        for(int i=2;i<=n;++i){
            scanf("%lf",&a[i]);
        }
        for(int i=2;i<=n;++i){
            a[i]/=b[i-1];
            b[i]-=c[i-1]*a[i];
        }
        z=new double[n+1];
        y=new double[n+1];
        x=new double[n+1];
        for(int i=0;i<m;++i){
            for(int j=1;j<=n;++j){
                scanf("%lf",&z[j]);
            }
            y[1]=z[1];
            for(int j=2;j<=n;++j){
                y[j]=z[j]-a[j]*y[j-1];
            }
            x[n]=y[n]/b[n];
            for(int j=n-1;j>=1;--j){
                x[j]=(y[j]-c[j]*x[j+1])/b[j];
            }
            for(int j=1;j<=n;++j){
                printf("%.4lf ",x[j]);
            }
            printf("\n");
        }
    }
    void P5(){
        e=new double[n-1];
        d=new double[n];
        c=new double[n+1];
        b=new double[n+1];
        a=new double[n+1];
        for(int i=1;i<=n-2;++i){
            scanf("%lf",&e[i]);
        }
        for(int i=1;i<=n-1;++i){
            scanf("%lf",&d[i]);
        }
        for(int i=1;i<=n;++i){
            scanf("%lf",&c[i]);
        }
        for(int i=2;i<=n;++i){
            scanf("%lf",&b[i]);
        }
        for(int i=3;i<=n;++i){
            scanf("%lf",&a[i]);
        }
        for(int i=2;i<=n-1;++i){
            b[i]/=c[i-1];
            a[i+1]/=c[i-1];
            c[i]-=d[i-1]*b[i];
            d[i]-=e[i-1]*b[i];
            b[i+1]-=d[i-1]*a[i+1];
            c[i+1]-=e[i-1]*a[i+1];
        }
        b[n]/=c[n-1];
        c[n]-=d[n-1]*b[n];
        z=new double[n+1];
        y=new double[n+1];
        x=new double[n+1];
        for(int i=0;i<m;++i){
            for(int j=1;j<=n;++j){
                scanf("%lf",&z[j]);
            }
            y[1]=z[1];
            y[2]=z[2]-b[2]*y[1];
            for(int j=3;j<=n;++j){
                y[j]=z[j]-a[j]*y[j-2]-b[j]*y[j-1];
            }
            x[n]=y[n]/c[n];
            x[n-1]=(y[n-1]-d[n-1]*x[n])/c[n-1];
            for(int j=n-2;j>=1;--j){
                x[j]=(y[j]-d[j]*x[j+1]-e[j]*x[j+2])/c[j];
            }
            for(int j=1;j<=n;++j){
                printf("%.4lf ",x[j]);
            }
            printf("\n");
        }
    }
};

int main(){
    X x;
    return 0;
}
