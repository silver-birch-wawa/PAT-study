#include<bits/stdc++.h>
using namespace std;
class fraction{
  public:
    int UP;
    int DOWN;
    fraction(int uup,int ddown){
      UP=uup;
      DOWN=ddown;
      simplify();
    }
  // 需要制定一系列的规则：
  // 1. down为非负数，正负交给分子就好。
  // 2. 若该分数为0，则其分子为0，分母为1
  // 3. 分子分母没有除1以外的公约数
    void simplify(){
      // 1
      if(DOWN<0){
          UP*=-1;
          DOWN*=-1;
      }
      // 2
      if(UP==0){
        DOWN=1;
      }
      if(gcd(UP,DOWN)!=1){
        int a=gcd(UP,DOWN);
        UP/=a;
        DOWN/=a;
      }
    }
    int gcd(int a,int b){
      if(b==0){
        return a;
      }
      else{
        return gcd(b,a%b);
      }
    }
    void print(){
        cout<<UP<<'/'<<DOWN<<endl;
    }
};
int main(){
  fraction x(24,39);
  x.print();
}
