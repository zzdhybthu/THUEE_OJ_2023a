#include<stdio.h>

struct Q{
    Q(){
        scanf("%d%d",&N,&K);
        nodes=new int*[N];
        costs=new int*[N];
        records=new int*[N];
        for(int i=0;i<N;++i){
            nodes[i]=new int[K];
            costs[i]=new int[N]{0};
            records[i]=new int[N]{0};
            for(int j=0;j<K;++j){
                scanf("%d",&nodes[i][j]);
            }
        }
    }

    void Cal(){
        int** temp_nodes=new int*[N];
        for(int i=0;i<N;++i){
            temp_nodes[i]=new int[K-1];
            for(int j=0;j<K-1;++j){
                temp_nodes[i][j]=nodes[i][j];
            }
        }
        for(int step=1;step<N;++step){
            for(int i=0;i+step<N;++i){
                int cost=1;
                for(int j=0;j<K-2;++j){
                    if(temp_nodes[i][j]<nodes[i+step][j]){
                        temp_nodes[i][j]=nodes[i+step][j];
                    }
                    cost*=temp_nodes[i][j];
                }
                costs[step][i]=cost*nodes[i][K-2]*nodes[i+step][K-1];
            }
        }
    }

    void Solve(){
        int min_cost,cost_o;
        for(int step=1;step<N;++step){
            for(int i=0;i+step<N;++i){
                min_cost=2147483647;
                for(int l=i+step;l>i;--l){
                    if(records[l][i+step]+costs[step][i]+records[i][l-1]>=min_cost){
                        continue;
                    }
                    cost_o=records[l][i+step]+nodes[l][K-2]*costs[step][i]+records[i][l-1];
                    if(cost_o<min_cost){
                        min_cost=cost_o;
                    }
                }
                records[i][i+step]=min_cost;
            }
        }
    }

    int N,K;
    int** nodes;
    int** costs;
    int** records;
};

int main(){
    Q q;
    q.Cal();
    q.Solve();
    printf("%d",q.records[0][q.N-1]);
    return 0;
}
