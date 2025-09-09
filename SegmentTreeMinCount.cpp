#include<bits/stdc++.h>
using namespace std;
struct item{
   int m,c;
};
class SegTree{
public:
   vector<item>tree; //(min,countOfMin)
   item NEUTRAL_ELEMENT = {INT_MAX,0};
   SegTree(){}
   SegTree(int n){
      tree.resize(4*n);
   }
   // Main logic to count the left and right minimum count
   item merge(item a , item b){
      if(a.m < b.m) return a;
      if(a.m > b.m) return b;
      return {a.m,a.c+b.c};
   }
   void buildTree(vector<int>&arr,int low,int high,int i){
      if(low == high){
         tree[i] = {arr[low],1};
         return;
      }
      int mid = (low+high)/2;
      buildTree(arr,low,mid,2*i+1);
      buildTree(arr,mid+1,high,2*i+2);
      tree[i] = merge(tree[2*i+1],tree[2*i+2]);

   }

   void pointUpdate(vector<int>&arr,int low ,int high, int val,int idx,int i){
      if(idx  == low && high == idx){
         tree[i] = {val,1}; //setting the new count
         arr[idx] = val;
         return;
      }
      int mid = (low+high)/2;
      if(idx <= mid){
         pointUpdate(arr,low,mid,val,idx,2*i+1);
      }
      else{
         pointUpdate(arr,mid+1,high,val,idx,2*i+2);
      }
      tree[i] = merge(tree[2*i+1],tree[2*i+2]); 
      
   }
   
   item rangeMin(vector<int>&arr,int low,int high ,int qs,int qe,int idx){
      if(qe < low || qs > high){ //no overlap
        return NEUTRAL_ELEMENT; // < INT_MAX , 0 > 
    } 
    if(low >= qs && high <= qe){ //complete overlap
        return tree[idx];
    }
    //otherwise partial overlap
    int mid = (low + high)/2;
    return(merge(rangeMin(arr,low,mid,qs,qe,2*idx+1),
            rangeMin(arr,mid+1,high,qs,qe,2*idx+2)));
   }

   
};
int main(){
   int n,m; 
   cin>>n>>m;
   vector<int>arr(n);
   for(int i = 0 ; i < n ;i++){
      cin>>arr[i];
   }
   SegTree* sg = new SegTree(n);
   sg->buildTree(arr,0,n-1,0);
   while(m--){
      int type,i,v,l,r;
      cin>>type;
      if(type == 1){
         cin>>i>>v;
         sg->pointUpdate(arr,0,n-1,v,i,0);
      }
      else{
         cin>>l>>r;
         item ans = sg->rangeMin(arr,0,n-1,l,r-1,0);
         cout<<ans.m<<" "<<ans.c<<endl;
      }
   }
   delete(sg);
   
   return 0;
}
