#include<stdio.h>

class X{
public:
    X(int){
        scanf("%d%d%d",&M,&K,&H);
        record=new int[K];
        order=new int[K];
        sum=0;
        flag=false;
        index=0;
        for(int i=0;i<M;++i){
            scanf("%lld",&temp);
            if(!flag){
                if(index!=0){
                    temp+=H;
                    int upper=search2(0,index-1);
                    temp-=2*H;
                    int lower=search(0,index-1);
                    if(upper==K){
                        if(lower!=K){
                            sum+=index-lower;
                        }
                    }else{
                        sum+=upper-lower;
                    }
                    temp+=H;
                    // printf("+%d+%d+",lower,upper);
                }
            }else{
                temp+=H;
                int upper=search2(0,K-1);
                temp-=2*H;
                int lower=search(0,K-1);
                sum+=upper-lower;
                temp+=H;         
                // printf("+%d+%d+",lower,upper);

            }
            insert();
            // for(int i=0;i<K;++i){
            //     printf("-%d-",record[i]);
            // }
            // printf("-%lld-\n",sum);
        }
        printf("%lld",sum);
    }

    void insert(){
        int a;
        if(flag){
            int temp2=temp;
            temp=order[index];
            int index=search(0,K-1);
            temp=temp2;
            a=search(0,K-1);
            if(a>index){
                int b=index;
                while(b<a-1){
                    record[b]=record[b+1];
                    ++b;
                }
                record[a-1]=temp;
            }else if(a<index){
                int b=index;
                while (b>a){
                    record[b]=record[b-1];
                    --b;
                }
                record[a]=temp;
            }else{
                record[index]=temp;
            }
            order[this->index]=temp;
            this->index=(this->index+1)%K;
        }else{
            if(index==0){
                a=K;
            }else{
                a=search(0,index-1);
            }
            if(a==K){
                record[index]=temp;
            }else{
                int b=index;
                while(b>a){
                    record[b]=record[b-1];
                    --b;
                }
                record[a]=temp;
            }
            order[index++]=temp;
            if(index==K){
                index=0;
                flag=true;
            }
        }
    }
    int search(int first,int last){//最小的大于等于
        if(last-first==1){
            if(record[first]>=temp){
                return first;
            }else if(record[last]<temp){
                return K;
            }else{
                return last;
            }
        }else if(last==first){
            if(temp<=record[first]){
                return first;
            }else{
                return K;
            }
        }
        int middle=(first+last)/2;
        if(record[middle]>temp){
            return search(first,middle);
        }else if(record[middle]<temp){
            return search(middle,last);
        }else{
            return middle;
        }
    }
    int search2(int first,int last){//最小的大于
        if(last-first==1){
            if(record[first]>temp){
                return first;
            }else if(record[last]<=temp){
                return K;
            }else{
                return last;
            }
        }else if(last==first){
            if(temp<record[first]){
                return first;
            }else{
                return K;
            }
        }
        int middle=(first+last)/2;
        // printf("\n**%d**%d**%d\n",first,last,middle);

        if(record[middle]>temp){
            return search2(first,middle);
        }else if(record[middle]<temp){
            return search2(middle,last);
        }else{
            return middle+1;
        }
    }
    int M,K,H;
    long long sum;
    long long temp;
    int* record;
    int* order;
    int index;
    int flag;
};



int main(){
    X x(0);   
    return 0;
}
