class SegTree
{
private:
    struct item
    {
        long long sum = 0;
        bool lazy = false;
        long long lazyVal = 0;
    };

    vector<item> tree;
    vector<int> original_array;
    int n;

    void buildTree(int low, int high, int i)
    {
        if (low == high)
        {
            tree[i].sum = original_array[low];
            return;
        }
        int mid = low + (high - low) / 2;
        buildTree(low, mid, 2 * i + 1);
        buildTree(mid + 1, high, 2 * i + 2);
        tree[i].sum = tree[2 * i + 1].sum + tree[2 * i + 2].sum;
    }

    void push_Down(int i, int low, int high)
    {
        if (!tree[i].lazy) return;

        tree[i].sum += (long long)(high - low + 1) * tree[i].lazyVal;
        if (low != high)
        {
            tree[2 * i + 1].lazy = true;
            tree[2 * i + 2].lazy = true;
            tree[2 * i + 1].lazyVal += tree[i].lazyVal;
            tree[2 * i + 2].lazyVal += tree[i].lazyVal;
        }
        tree[i].lazy = false;
        tree[i].lazyVal = 0;
    }

    void rangeUpdate_helper(int low, int high, int l, int r, int val, int i)
    {
        push_Down(i, low, high);

        if (r < low || high < l) return;

        if (l <= low && high <= r)
        {
            tree[i].sum += (long long)(high - low + 1) * val;
            if (low != high)
            {
                tree[2 * i + 1].lazy = true;
                tree[2 * i + 2].lazy = true;
                tree[2 * i + 1].lazyVal += val;
                tree[2 * i + 2].lazyVal += val;
            }
            return;
        }

        int mid = low + (high - low) / 2;
        rangeUpdate_helper(low, mid, l, r, val, 2 * i + 1);
        rangeUpdate_helper(mid + 1, high, l, r, val, 2 * i + 2);
        tree[i].sum = tree[2 * i + 1].sum + tree[2 * i + 2].sum;
    }

    long long rangeSum_helper(int low, int high, int l, int r, int i)
    {
        push_Down(i, low, high);

        if (r < low || high < l) return 0;
        
        if (l <= low && high <= r) return tree[i].sum;
        
        int mid = low + (high - low) / 2;
        return rangeSum_helper(low, mid, l, r, 2 * i + 1) + rangeSum_helper(mid + 1, high, l, r, 2 * i + 2);
    }

public:
    SegTree(vector<int> &arr)
    {
        n = arr.size();
        tree.resize(4 * n);
        original_array = arr;
        buildTree(0, n - 1, 0);
    }

    void update(int l, int r, int val) {
        rangeUpdate_helper(0, n - 1, l, r, val, 0);
    }

    long long query(int l, int r) {
        return rangeSum_helper(0, n - 1, l, r, 0);
    }
};
