#include<stdio.h>
#include<stack>
using namespace std;

int main(){
    int number;
    scanf("%d",&number);
    long long result=0;
    int this_soldier;
    stack<pair<int,int>> soldiers;
    int num;
    for(int i=0;i<number;++i){
        scanf("%d",&this_soldier);
        while(!soldiers.empty()&&soldiers.top().first<this_soldier){
            num=soldiers.top().second;
            result+=num;
            // printf("%d",num);
            soldiers.pop();
        }
        if(!soldiers.empty()&&soldiers.top().first==this_soldier){
            num=soldiers.top().second;
            soldiers.pop();
            result+=num;
            // printf("%d",num);
            if(!soldiers.empty()){
                ++result;
            }
            soldiers.push(make_pair(this_soldier,++num));
        }else{
            if(!soldiers.empty()){
                ++result;
                // printf("%d",soldiers.top().second);
            }
            soldiers.push(make_pair(this_soldier,1));
        }
    }
    printf("%lld",result);
}
