#include<stdio.h>
#include<vector>
using namespace std;

class Node{
public:
    Node(unsigned short time,unsigned short cost,unsigned short end):time(time),cost(cost),end(end){};
    unsigned short time,cost,end;
};
class Line{
public:
    Line(unsigned int total_cost, unsigned int total_time):total_cost(total_cost),total_time(total_time){};
    unsigned int total_cost,total_time;
};

class X{
public:
    X(){
        scanf("%d%d",&N,&M);
        v=new vector<Node>[N];
        l=new vector<Line>[N];
        int start;
        unsigned short time,cost,end;
        for(int i=0;i<M;++i){
            scanf("%d%hu%hu%hu",&start,&end,&time,&cost);
            v[start].push_back(Node(time,cost,end));
        }
        scanf("%d%d%u",&target_start,&target_end,&max_time);
        l[target_start].push_back(Line(0,0));
    }
    ~X(){
        long long min_cost=-1;
        for(auto i=l[target_end].begin();i!=l[target_end].end();++i){
            if(i->total_cost<min_cost||min_cost==-1){
                min_cost=i->total_cost;
            }
        }
        printf("%lld",min_cost);
    }

    void Done(){
        unsigned int t,c;
        while(true){
            bool flag=true;
            for(int i=0;i<N;++i){
                if(i==target_end){
                    continue;
                }
                for(auto now=l[i].begin();now!=l[i].end();++now){
                    flag=false;
                    for(auto next=v[i].begin();next!=v[i].end();++next){
                        t=now->total_time+next->time;
                        c=now->total_cost+next->cost;
                        if(t>max_time){
                            continue;
                        }
                        bool should_escape=false;
                        for(auto find=l[next->end].begin();find!=l[next->end].end();++find){
                            if(find->total_cost<=c&&find->total_time<=t){
                                should_escape=true;
                                break;
                            }
                        }
                        if(!should_escape){
                            l[next->end].push_back(Line(c,t));
                        }
                    } 
                }
                l[i].clear();
            }
            if(flag){
                break;
            }
        }
    }
    int N,M;
    vector<Node>* v;
    vector<Line>* l;
    
    int target_start,target_end;
    unsigned int max_time;
};

int main(){
    X x;
    x.Done();
    return 0;
}
