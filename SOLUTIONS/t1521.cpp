#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

class list
{
    // Part 1. Build a tree
    vector<int> tree;
    int size, bottom, step, current, remains;
    // Basic function of a tree
    inline int parent(const int& node) const
    {
        return node/2;
    }

    inline int rightchild(const int& node) const
    {
        return node*2+1;
    }

    inline int leftchild(const int& node) const
    {
        return node*2;
    }

    inline int intree(const int& node) const
    {
        return node <= bottom + size && node > 0;
    }
    
    // Calculate n^2
    inline int square(int n)
    {
        int ret = 1;
        while (n -- > 0)
        {
            ret *= 2;
        }
        return ret;
    }

    // Find next n^2
    inline int nextSquare(int n)
    {
        n--;
        for (int i = 1; i <= 16; i *= 2)
        {
            n |= n >> i;
        }
        return n + 1;
    }

    // Calculate log2 n
    int log2(int n)
    {
        int ret = 0;
        while ( n/= 2)
        {
            ret ++;
        }
        return ret;
    }

public:
    // Constrction
    list(int n, int step): size(n), step(step), current(step), remains(n)
    {
        tree.resize(nextSquare(n*2));
        int height = log2(n*2 - 1);
        bottom = square(height) - 1; // The node immediately preceding the first leaf

        for(int i = bottom + 1; i <= bottom + n; i++) // Leafs have key 1
            tree[i] = 1;
        for(int i = bottom; i >= 1; i--) // Internal nodes' keys are the sum their childrens keys
            tree[i] = (intree(leftchild(i)) ? tree[leftchild(i)] : 0)
                + (intree(rightchild(i)) ? tree[rightchild(i)] : 0);
    }

    int remaining()
    {
        return remains;
    }

    int getNext()
    {
        if (remains-- == size)
            return current;

        int node = bottom + current;
        while (node) // Bubble up a subtraction through the tree
        {
            tree[node]--;
            node = parent(node);
        }
        node = bottom + current;

        int k = step; // The remaining number of soldiers that we need to skip
        enum source {left, right, up};
        source source = right;

        // Start at a leaf, search our way through the tree 
        // until we have skipped the number of soldiers that need to be skipped
        while (k)
        {
            int lc = leftchild(node);
            int rc = rightchild(node);
            if(source == up)
            {
                // if we can skip entire left
                if (intree(lc)&& k >tree[lc]) 
                {
                    k -= tree[lc];
                    source = up;
                    node = rc;
                }
                // Final leaf found
                else if (!intree(lc) && k == tree[node])
                {
                    k--;
                }
                else // Then the answer is on the left
                {
                    source = up;
                    node = lc;
                }
            }
            else if (source == right)
            {
                source =node == rightchild(parent(node)) ? right : left;
                node = parent(node);
            }

            else // coming from the left
            {
                if (intree(rc)&&k>tree[rc])
                {
                    source = node == rightchild(parent(node))? right : left;
                    k-= tree[rc];
                    node = parent(node);
                }
                else
                {
                    node = rc;
                    source = up;
                }
                
            }
            if (!intree(node))
            {
                node = bottom + 1;
                k -= tree[node];
                source = right;
            }
        }
        return current = node - bottom;
    }
};

int main(){
    int N,K;
    scanf("%d %d", &N, &K);

    list list(N, K);
    while (list.remaining())
    {
        int ans = list.getNext();

        char str[9];
        int l = 0;
        while (ans)
        {
            str[l++] = ans % 10;
            ans /= 10;
        }
        while (l--)
        {
            putc('0' + str[l], stdout);
        }
        putc(' ', stdout);
    }
    return 0;
    
}
