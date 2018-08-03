#include<bits/stdc++.h>
using namespace std;
int N,M,K;
int k[1000]={0};
// 每个人的等待处理时间
int t[1000]={0};
// 存放每个人完成的时间,17:00以后不能 serve(值为0)就返回 Sorry

queue<int>waitingline;
// 等待的队伍,如果溢出的话

/*
第一行 窗口数，最长等待数，顾客数，查询数
各个顾客的业务处理时间
查询的顾客名
*/
typedef struct Windows{
  int next_time;
  // 轮到下一个人进队的时间(秒)
  queue<int>q;
  // 存放顾客
  Windows(){
    next_time=0;
  }
}Windows;
// 填充进队列，不需要考虑超时
void addin(Windows*win,int target,int id){
  win[target].q.push(id);
}
// 添加时看队伍长度，next_time只需要注册第一个人的就可以
void add(Windows*win,int id){
  // id 第几个顾客
  int length=1000000;
  // 挑选最短的队伍排
  int i,j,target=0;
  for(i=0;i<N;i++){
    if(win[i].q.size()<length){
      length=win[i].q.size();
      target=i;
    }
  }
  // 发现最小队列target
  if(length==0){
    // cout<<"id:"<<id<<"  "<<t[id]<<endl;
    addin(win,target,id);
    // 没人排队则初始化 next_time
    win[target].next_time+=k[id];
    t[id]=k[id];
  }
  else if(length<M){
    // 有人则加入队列
    addin(win,target,id);
  }
  else{
    // 溢出放入队列
    waitingline.push(id);
  }
}
// 将waitingline的顾客放入队列，把队列中的第一个顾客出队，然后标记next_time，再next_time+=
void waitaddin(Windows*win,int target,int nextone){
  int out=win[target].q.front();
  t[out]=win[target].next_time<(9*60)?win[target].next_time:0;
  win[target].q.pop();
  win[target].q.push(nextone);
  // cout<<"out:"<<out<<"   "<<t[out]<<endl;
  win[target].next_time+=k[win[target].q.front()];
}
void waitadd(Windows*win){
  int recent_time=540;
  int i,j,target=0;
  int nextone=waitingline.front();
  waitingline.pop();
  // 挑选最先空出来的队伍排
  for(i=0;i<N;i++){
    if(recent_time>win[i].next_time){
      recent_time=win[i].next_time;
      target=i;
    }
  }
  waitaddin(win,target,nextone);
}
// 当 waitingline清空了，就把
void clearqueue(Windows*win){
  int i,j;
  // cout<<"***next_time:"<<win[0].q.size()<<"  "<<win[1].q.size()<<endl;
  for(i=0;i<N;i++){
    int length=win[i].q.size();
        if(length>0){
          int first=win[i].q.front();
          win[i].q.pop();
          t[first]=win[i].next_time-k[first]<9*60?win[i].next_time:0;
          // 处理后面的顾客
          for(j=1;j<length;j++){
            int first=win[i].q.front();
            win[i].q.pop();
            // cout<<"next_time:"<<win[i].next_time<<endl;
            t[first]=win[i].next_time<9*60?win[i].next_time+k[first]:0;
            win[i].next_time+=k[first];
            // cout<<"q:"<<i<<endl;
            // cout<<"first:"<<first<<endl;
            // win[i].q.pop();
          }
        }
    }
}
void print(){
  int i=0;
  cout<<"----------"<<endl;
  for(i=0;i<K;i++){
    cout<<"time:"<<t[i]<<endl;
  }
}
// 处理时间s->h+m
void times(int t){
  if(t==0){
    cout<<"Sorry"<<endl;
    return;
  }
  int hour=8+t/60;
  int minutes=(t%60);
  printf("%02d:%02d\n",hour,minutes);
}
void query(int num){
  times(t[num-1]);
}
int main(){
  int i,j,Q,input;
  scanf("%d %d %d %d",&N,&M,&K,&Q);
  Windows* win=new Windows[N];
  for(i=0;i<K;i++){
    scanf("%d",&input);
    k[i]=input;
    add(win,i);
    // 插入
  }
  // 如果黄线之前排满了，waitingline
  int length=waitingline.size();
  for(i=0;i<length;i++){
    waitadd(win);
  }
  // waitingline全部都入队了，对队伍中的最后一批顾客进行清算
  clearqueue(win);
  // print();
  for(i=0;i<Q;i++){
    scanf("%d",&input);
    query(input);
  }
}
/*
2 2 7 5
1 2 6 4 3 534 2
3 4 5 6 7
08:07
08:06
08:10
17:00
Sorry


2 2 9 9
1 2 6 4 3 1 9 100 534
1 2 3 4 5 6 7 8 9
08:01 08:02 08:07 08:06 08:10 08:07 08:16 09:50 17:10
*/
