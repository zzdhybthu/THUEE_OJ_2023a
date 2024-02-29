#include<iostream>
#include<cstring>

int main(){
    int number;
    char data[11];
    int data2[30]{};
    scanf("%d",&number);
    getchar();
    for(int i=0;i<3*number-1;++i){
        scanf("%[^\n]",data);
        getchar();
        int len=10-strlen(data);
        for(int i=0;i<10-len;++i){
            int k=data[i]-'0';
            data2[(i+len)*3+2]+=k%3;
            k/=3;
            data2[(i+len)*3+1]+=k%3;
            k/=3;
            data2[(i+len)*3]+=k%3;
        }
    }
    for(int i=0;i<30;++i){
        data2[i]=(3-data2[i]%3)%3;
    }
    bool flag=false;
    for(int i=0;i<10;++i){
        int result=data2[i*3]*9+data2[i*3+1]*3+data2[i*3+2];
        if(result!=0){
            flag=true;
        }
        if(flag){
            printf("%d",result);
        }
    }
}
