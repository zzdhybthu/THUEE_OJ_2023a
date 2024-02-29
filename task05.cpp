#include<stdio.h>

// class Node{
// public:
//     Node(unsigned short v,Node* n):value(v),next(n){};
//     unsigned short value;
//     Node* next;
// };
// class Queue{
// public:
//     Node* head=nullptr,*tail=nullptr;
//     void Push(unsigned short value){
//         Node* newNode=new Node(value,nullptr);
//         if(tail==nullptr){
//             head=tail=newNode;
//         }else{
//             tail=tail->next=newNode;
//         }
//     }
//     unsigned short Pop(){
//         Node* temp=head;
//         unsigned short value=temp->value;
//         head=head->next;
//         delete temp;
//         if(head==nullptr){
//             tail=nullptr;
//         }
//         return value;
//     }
//     bool Empty(){
//         return head==nullptr;
//     }
// };

// class Stack{
// public:
//     Node* head=nullptr;
//     void Push(unsigned short value){
//         Node* newNode=new Node(value,head);
//         head=newNode;
//     }
//     unsigned short Pop(){
//         Node* temp=head;
//         unsigned short value=temp->value;
//         head=head->next;
//         delete temp;
//         return value;
//     }
//     bool Empty(){
//         return head==nullptr;
//     }
// };


class Solution{
public:
    unsigned short N,M;
    unsigned short **v;
    unsigned short *o;//order
    unsigned short *f;//father
    unsigned short *flag;

    Solution(int){
        scanf("%hu",&N);
        scanf("%hu",&M);
        v=new unsigned short *[N];
        o=new unsigned short [N]{0};
        f=new unsigned short [N]{0};
        f[0]=o[0]=0;

        unsigned short length;
        for(int i=0;i<N;++i){
            scanf("%hu",&length);
            v[i]=new unsigned short [length+1];
            v[i][0]=length+1;
            for(int j=1;j<length+1;++j){
                scanf("%hu",&v[i][j]);
            }
        }
    }

    unsigned short number;
    void CountDFS(unsigned short value){
        for(int i=1;i<v[value][0];++i){
            if(v[value][i]==0){
                continue;
            }
            if(o[v[value][i]]==0){
                o[v[value][i]]=++number;
                f[v[value][i]]=value;
                CountDFS(v[value][i]);
            }
        }
    }
    void Count(){
        number=0;
        CountDFS(0);
        printf("%d\n",number==N-1);
    }

    unsigned short from,to;
    bool DeleteDFS(unsigned short value){
        if(value==to){
            return true;
        }
        flag[value]=1;
        for(int i=1;i<v[value][0];++i){
            if(flag[v[value][i]]==0){
                if(DeleteDFS(v[value][i])){
                    return true;
                }
            }
        }
        return false; 
    }

    void Delete(){
        if(number!=N-1){
            for(int i=0;i<M;++i)
                printf("%d\n",0);
            return;
        }
        
        for(int i=0;i<M;++i){
            scanf("%hu",&from);
            scanf("%hu",&to);
            if(f[to]!=from){
                printf("%d\n",1);
            }else{
                for(int j=1;j<v[from][0];++j){
                    if(v[from][j]==to){
                        v[from][j]=v[from][v[from][0]-1];
                        --v[from][0];
                        break;
                    }
                }
                flag=new unsigned short[N]{0};
                printf("%d\n",DeleteDFS(0));
                delete[] flag;
                ++v[from][0];
                v[from][v[from][0]-1]=to;
            }
        }
    }
};

int main(){
    Solution s(1);
    s.Count();
    s.Delete();
    return 0;
}

// int main2(){
//     unsigned short N,M;
//     scanf("%hu",&N);
//     scanf("%hu",&M);
//     unsigned short **v=new unsigned short *[N];
    
//     unsigned short length;
//     for(int i=0;i<N;++i){
//         scanf("%hu",&length);
//         v[i]=new unsigned short [length+1];
//         v[i][0]=length+1;
//         for(int j=1;j<length+1;++j){
//             scanf("%hu",&v[i][j]);
//         }
//     }
    
//     unsigned short *flag=new unsigned short [N]{0};
//     unsigned short count=1;
    
//     Stack q;
//     for(int i=1;i<v[0][0];++i){
//         flag[v[0][i]]=1;
//         q.Push(v[0][i]);
//         ++count;
//     }
//     flag[0]=1;

//     unsigned short value;
//     while(!q.Empty()){
//         value=q.Pop();
//         // printf("%d-",value);
//         for(int i=1;i<v[value][0];++i){
//             if(flag[v[value][i]]==0){
//                 flag[v[value][i]]=1;
//                 q.Push(v[value][i]);
//                 ++count;
//             }
//         }
//         if(count>=N){
//             break;
//         }
//     }
//     if(count<N){
//         printf("%d\n",0);
//     }else{
//         printf("%d\n",1);
//     }
//     return 0;
// }
