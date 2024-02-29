#include<cstdio>
using namespace std;

int main(){
    long long numOfAbs,numOfTar;
    scanf("%lld",&numOfAbs);
    scanf("%lld",&numOfTar);
    long long* absNodes=new long long[numOfAbs];
    long long* tarNodes=new long long[numOfTar];
    for(long long i=0;i<numOfAbs;++i){
        scanf("%lld",&absNodes[i]);
    }
    for(long long i=0;i<numOfTar;++i){
        scanf("%lld",&tarNodes[i]);
    }
    
    long long tail[200]={1};
    unsigned long long absNum=0;
    long long addAbsNum=0;
    long long layer=0;
    long long layerArea=1;
    unsigned long long most=0;
    for(long long i=0;i<numOfAbs;++i){
        if(most!=0){
            break;
        }
        while(tail[layer]<absNodes[i]){
            absNum=absNum*2+addAbsNum;
            addAbsNum=0;
            layerArea*=2;
            if(layerArea==absNum){
                most=tail[layer];
                break;
            }
            tail[layer+1]=layerArea-absNum+tail[layer];
            ++layer;
        }
        addAbsNum+=2;
    }

    long long maxLayer=0;
    for(long long i=0;i<numOfTar;++i){
        if(most==0){
            while(tail[layer]<tarNodes[i]){
                absNum=absNum*2+addAbsNum;
                addAbsNum=0;
                layerArea*=2;
                if(layerArea==absNum){
                    most=tail[layer];
                    break;
                }
                tail[layer+1]=layerArea-absNum+tail[layer];
                ++layer;
            }
        }
        if(most!=0&&tarNodes[i]>most){
            printf("%d\n",0);
            continue;
        }

        while(tail[maxLayer]<tarNodes[i]){
            ++maxLayer;
        }

        long long* line=new long long[maxLayer+1];
        long long thisLayer=maxLayer;
        line[thisLayer]=tarNodes[i];
        long long absIndex=numOfAbs-1;

        while(thisLayer>0){
            long long diff=(tail[thisLayer]-line[thisLayer])/2;
            --thisLayer;
            while(absIndex>=0&&absNodes[absIndex]>tail[thisLayer]){
                --absIndex;
            }
            while(true){
                long long count=0; 
                while(absIndex>=0&& absNodes[absIndex]>=tail[thisLayer]-diff){
                    --absIndex;
                    ++count;
                }
                if(count==0){
                    break;
                }
                diff+=count;
            }
            line[thisLayer]=tail[thisLayer]-diff;
        }
        for(long long j=0;j<=maxLayer;++j){
            printf("%lld ",line[j]);
        }
        printf("\n");
    }

    return 0;
}
