# include<stdio.h>

class Y{
public:
Y(){
    scanf("%d%d",&N,&M);
    t=new double[N];
    x=new double[N];
    y=new double[N];
    xx=new double[N];
    yy=new double[N];
    for(int i=0;i<N;++i){
        scanf("%lf%lf",&xx[i],&yy[i]);
    }
    length=0;
    for(int i=0;i<N;++i){
        double xi,yi;
        // xi=xx[i];
        // yi=yy[i];
        xi=xx[N-1-i];
        yi=yy[N-1-i];
        bool flag=true;
        for(int j=0;j<length;++j){
            if(x[j]-xi<=0.000001&&xi-x[j]<=0.000001){
                flag=false;
                break;
            }
        }
        if(!flag){
            continue;
        }
        double mul_y=1;
        double result_y=0;
        for(int j=0;j<length;++j){
            result_y+=t[j]*mul_y;
            mul_y*=(xi-x[j]);
        }
        if(result_y-yi<=0.00000000005&&yi-result_y<=0.00000000005){
            break;
        }
        t[length]=(yi-result_y)/mul_y;
        x[length]=xi;
        y[length]=yi;
        ++length;
    }
    printf("%d\n",length-1);
}
~Y(){
    for(int i=0;i<M;++i){
        double xi;
        scanf("%lf",&xi);
        double mul_y=1;
        double result_y=0;
        for(int j=0;j<length;++j){
            result_y+=t[j]*mul_y;
            mul_y*=(xi-x[j]);
        }
        printf("%lf\n",result_y);
    }
}
int N;
int M;
double * t;
double * x;
double * xx;
double * y;
double * yy;
int length;

};

int main(){
Y y;
}


// class X{
// public:
//     X(){
//         scanf("%d%d",&N,&M);
//         w=new double[N];
//         x=new double[N];
//         xx=new double[N];
//         y=new double[N];
//         yy=new double[N];
//         // for(int i=0;i<N;++i){
//         //     scanf("%lf%lf",&xx[i],&yy[i]);
//         // }
//         length=0;
//         for(int i=0;i<N;++i){
//             double xi,yi;
//             // xi=xx[(-i+50)%N];
//             // yi=yy[(-i+50)%N];
//             scanf("%lf%lf",&xi,&yi);
//             bool flag=true;
//             for(int j=0;j<length;++j){
//                 if(x[j]==xi){
//                     flag=false;
//                     break;
//                 }
//             }
//             if(!flag){
//                 continue;
//             }
//             if(length==0){
//                 x[0]=xi;
//                 y[0]=yi;
//                 ++length;
//             }else if(length==1){
//                 x[1]=xi;
//                 y[1]=yi;
//                 w[0]=1/(x[0]-x[1]);
//                 w[1]=1/(x[1]-x[0]);
//                 ++length;
//             }else{
//                 double sum_up=0;
//                 double sum_low=0;
//                 for(int j=0;j<length;++j){
//                     sum_up+=w[j]/(xi-x[j])*y[j];
//                     sum_low+=w[j]/(xi-x[j]);
//                 }
//                 if(sum_up/sum_low-yi<=0.000000005&&yi-sum_up/sum_low<=0.000000005){
//                     continue;
//                 }
//                 for(int j=0;j<length;++j){
//                     w[j]/=(x[j]-xi);
//                 }
//                 w[length]=1;
//                 for(int j=0;j<length;++j){
//                     w[length]/=(xi-x[j]);
//                 }
//                 x[length]=xi;
//                 y[length]=yi;
//                 ++length;
//             }
//         }
//         printf("%d\n",length-1);
//     }
//     ~X(){
//         for(int i=0;i<M;++i){
//             double xi;
//             scanf("%lf",&xi);
//             double sum_up=0;
//             double sum_low=0;
//             for(int j=0;j<length;++j){
//                 sum_up+=w[j]/(xi-x[j])*y[j];
//                 sum_low+=w[j]/(xi-x[j]);
//             }
//             printf("%lf\n",sum_up/sum_low);
//         }
//     }
//     int N;
//     int M;
//     double * w;
//     double * x;
//     double * xx;
//     double * y;
//     double * yy;
//     int length;

// };

// int main(){
//     X x;
// }
