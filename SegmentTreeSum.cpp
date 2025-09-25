class SegTree {
private:
    int n; 
    std::vector<long long> tree;
    void buildTree(const std::vector<int>& arr, int low, int high, int i) {
        if (low == high) {
            tree[i] = arr[low];
            return;
        }
        int mid = low + (high - low) / 2;
        buildTree(arr, low, mid, 2 * i + 1);
        buildTree(arr, mid + 1, high, 2 * i + 2);
        tree[i] = tree[2 * i + 1] + tree[2 * i + 2];
    }
    // PRIVATE: Recursive helper for point updates
    void pointUpdate(int low, int high, int val, int idx, int i) {
        if (low == high) {
            tree[i] = val;
            return;
        }
        int mid = low + (high - low) / 2;
        if (idx <= mid) {
            pointUpdate(low, mid, val, idx, 2 * i + 1);
        } else {
            pointUpdate(mid + 1, high, val, idx, 2 * i + 2);
        }
        tree[i] = tree[2 * i + 1] + tree[2 * i + 2];
    }

    // PRIVATE: Recursive helper for range sum queries
    long long rangeSum(int low, int high, int qs, int qe, int i) {
        // No overlap
        if (qe < low || qs > high) {
            return 0;
        }
        // Complete overlap
        if (low >= qs && high <= qe) {
            return tree[i];
        }
        // Partial overlap
        int mid = low + (high - low) / 2;
        long long leftSum = rangeSum(low, mid, qs, qe, 2 * i + 1);
        long long rightSum = rangeSum(mid + 1, high, qs, qe, 2 * i + 2);
        return leftSum + rightSum;
    }

public:
    // Constructor: Takes the initial array and builds the tree
    SegTree(const std::vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n, 0);
        buildTree(arr, 0, n - 1, 0);
    }

    // PUBLIC: Clean interface for point updates
    void update(int idx, int val) {
        pointUpdate(0, n - 1, val, idx, 0);
    }

    // PUBLIC: Clean interface for range sum queries
    long long query(int qs, int qe) {
        return rangeSum(0, n - 1, qs, qe, 0);
    }
};
