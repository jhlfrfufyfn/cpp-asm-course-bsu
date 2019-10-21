#include <iostream>
using namespace std;
int sum1(int *mat,int n,int m){
    int res=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            res+=mat[i*m+j];
            cerr<<"mat["<<i*m+j<<"]="<<mat[i*m+j]<<"\n";
        }
    }
    return res;
}
int sum2(int *mat[],int n,int m){
    int res=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            res+=mat[i][j];
            cerr<<"mat["<<i<<"]["<<j<<"]="<<mat[i][j]<<"\n";
        }
    }
    return res;
}
void input(int &n,int &m){
    cin>>n>>m;
}
int solve1(int n,int m){
  int *mat=new int(n*m);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>mat[i*m+j];
            cerr<<"mat["<<i*m+j<<"]="<<mat[i*m+j]<<"\n";
        }
    }
    cout<<sum1(mat,n,m);
}
int solve2(int n,int m){
    int *mat[n];
    for(int i=0;i<n;i++)
        mat[i]=new int(m);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>mat[i][j];
            cerr<<"mat["<<i<<"]["<<j<<"]="<<mat[i][j]<<"\n";
        }
    }
    cout<<sum2(mat,n,m);
}
int main()
{
    int n,m;
    input(n,m);
    solve1(n,m);
    cout<<"\n";
    solve2(n,m);
    return 0;
}
