class SegTree{
public:
   vector<long long>tree;
   SegTree(){}
   SegTree(int n){
      tree.resize(4*n,0);
   }
   void buildTree(vector<int>&arr,int low,int high,int i){
      if(low == high){
         tree[i] = arr[low];
         return;
      }
      int mid = (low+high)/2;
      buildTree(arr,low,mid,2*i+1);
      buildTree(arr,mid+1,high,2*i+2);
      tree[i] = tree[2*i+1] + tree[2*i+2]; //sum
   }
   void pointUpdate(vector<int>&arr,int low ,int high, int val,int idx,int i){
      if(idx  == low && high == idx){
         tree[i] = val;
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
      tree[i] = tree[2*i+1] + tree[2*i+2]; //update the sum
   }
   long long rangeSum(vector<int>&arr,int low,int high ,int qs,int qe,int idx){
      if(qe < low || qs > high){ //no overlap
        return 0;
    }
    if(low >= qs && high <= qe){ //complete overlap
        return tree[idx];
    }
    //otherwise partial overlap
    int mid = (low + high)/2;
    return(rangeSum(arr,low,mid,qs,qe,2*idx+1)+
            rangeSum(arr,mid+1,high,qs,qe,2*idx+2));
   }
};
