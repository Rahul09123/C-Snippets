void update(vector<int>&bit,int i ,int val){
    i = i + 1;
    int n = bit.size();
    while(i < n){
        bit[i] += val;
        i = i + (i & (-i));
    }
}
int getSum(vector<int>&bit,int i){
    i = i + 1;
    int sum = 0;
    while(i > 0){
        sum += bit[i];
        i = i - (i & (-i));
    }
    return sum;
}
