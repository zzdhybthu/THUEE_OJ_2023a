#include<stdio.h>

int main(){
    int number, option;
    scanf("%d", &number);
    int stu[100000]{};
    int stu2[100000]{};
    stu[0]=1.0;
    stu2[0]=1;
    int count=1;
    int input1,input2;
    for(int i=0;i<number;++i){
        scanf("%d",&option);
        switch(option){
        case 1:
            scanf("%d",&input1);
            scanf("%d",&input2);
            stu2[stu[input1]]=input2;
            stu2[input2]=input1;
            stu[input2]=stu[input1];
            stu[input1]=input2;
            ++count;
            break;
        case 2:
            scanf("%d",&input1);
            printf("%d\n",stu[input1]);
            break;
        case 3:
            scanf("%d",&input1);
            // int k=0;
            // while(stu[k]!=input1){
            //     k=stu[k];
            // }
            // stu[k]=stu[input1];
            stu[stu2[input1]]=stu[input1];
            stu2[stu[input1]]=stu2[input1];
            --count;
            break;
        }
        // int k=0;
        // for(int i=0;i<count;++i){
        //     printf("%d ",stu[k]);
        //     k=int(stu[k]);
        // }
        // cout<<endl;
    }
    int k=0;
    for(int i=0;i<count;++i){
        printf("%d\n",stu[k]);
        k=int(stu[k]);
    }
}
