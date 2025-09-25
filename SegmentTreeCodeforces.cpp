//For each question we need to change the structure
struct item{
   long long pref,suf,sum,seg;
};
class SegTree{
public:
   vector<item>tree;

   item NEUTRAL_ELEMENT = {0,0,0,0}; //this will change in each question
   SegTree(){}
   SegTree(int n){
      tree.resize(4*n);
   }
   // Logic Changes here
   item merge(item a , item b){
      return{
         max(a.pref,a.sum+b.pref), 
         max(b.suf,b.sum+a.suf),
         a.sum+b.sum,
         max({a.seg, b.seg, a.suf + b.pref})
      };
   }
   item single(int v){
      if(v > 0){ //+ve
         return {v,v,v,v}; 
      }else{
         return {0,0,v,0}; //if negative the pref,suf,
      }
   }
   void buildTree(vector<int>&arr,int low,int high,int i){
      if(low == high){
         tree[i] = single(arr[low]);
         return;
      }
      int mid = (low+high)/2;
      buildTree(arr,low,mid,2*i+1);
      buildTree(arr,mid+1,high,2*i+2);
      tree[i] = merge(tree[2*i+1],tree[2*i+2]);
   }

   void pointUpdate(vector<int>&arr,int low ,int high, int val,int idx,int i){
      if(idx  == low && high == idx){
         tree[i] = single(val);
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
   
   item range(vector<int>&arr,int low,int high ,int qs,int qe,int idx){
      if(qe < low || qs > high){
        return NEUTRAL_ELEMENT;
    } 
    if(low >= qs && high <= qe){
        return tree[idx];
    }
   
    int mid = (low + high)/2;
    return(merge(range(arr,low,mid,qs,qe,2*idx+1),
            range(arr,mid+1,high,qs,qe,2*idx+2)));
   }
   
};
