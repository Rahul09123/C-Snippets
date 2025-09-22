class Fenwick{
public:
   vector<int>BIT;
   Fenwick(vector<int>&arr){
      int n = arr.size();
      BIT.resize(n+1,0);
      build(arr);
   }
   void build(vector<int>&arr){
      for(int i = 0 ; i < arr.size();i++){
         add(i,arr[i]);
      }
   }
   void add(int i,int val){
      int n = BIT.size()-1;
      i = i + 1;
      while(i <= n){
         BIT[i] += val;
         i = i + (i & (-i));
      }
   }
   int getSum(int idx){
      int res = 0;
      idx = idx + 1;
      while(idx > 0){
         res += BIT[idx];
         idx = (idx - (idx & (-idx)));
      }
      return res;
   }
   void update(vector<int>&arr,int idx,int val){
      int diff = val - arr[idx];
      arr[idx] = val;
      int n = BIT.size()-1;
      idx = idx + 1;
      while(idx <= n){
         BIT[idx] += diff; 
         idx = (idx + (idx & (-idx)));
      }
   }   
};
