#include <bits/stdc++.h>
using namespace std;
#define N 10000
int degree[N]={0};
bool occupy[N]={false};
int points,edges;
vector<vector<int>>v;
void show(vector<int>&q){
  int i;
  for(i=0;i<q.size();i++){
    cout<<">>"<<q[i];
    //q.pop_back();
  }
  cout<<endl;
}
bool toposort(vector<vector<int>>&v){
    vector<int>q;
    int i,j;
    int counts=0;

    for(j=1;j<points+1;j++){
      cout<<degree[i]<<"->";
    }
    cout<<endl;

    while(1){
      // int signal=false;
      for(i=1;i<points+1;i++){
        if(degree[i]==0&&occupy[i]==false){
          q.push_back(i);
          cout<<"push:"<<i<<endl;
          occupy[i]=true;
          // signal=true;
        }
      }
      if(q.size()==0){
        cout<<"die";
        break;
      }
      // if(signal==false){
      //   break;
      // }
      //cout<<"****"<<endl;
      sort(q.begin(),q.end());
      int start=q.size();
      show(q);
      for(i=0;i<start;i++){
        int pre=q[0];
        q.erase(q.begin());
        counts++;
        cout<<pre<<":"<<v[pre].size()<<endl;
        for(i=0;i<v[pre].size();i++){
          int choosed=v[pre][i];
          degree[choosed]--;
        }
      }
      cout<<endl;
      for(j=1;j<points+1;j++){
        cout<<degree[i]<<"->";
      }
    }
    if(counts==points){
      return true;
    }
    else{
      return false;
    }
}

int main(){
  int i,j;
  scanf("%d %d",&points,&edges);
  for(i=0;i<points+1;i++){
    vector<int>vv;
    v.push_back(vv);
  }
  int point1,point2;
  for(i=0;i<edges;i++){
    scanf("%d %d",&point1,&point2);
    v[point1].push_back(point2);
    degree[point2]++;
  }
  toposort(v);

}

/*
7 7
1 5
1 2
1 7
2 3
3 4
5 4
4 6
*/
