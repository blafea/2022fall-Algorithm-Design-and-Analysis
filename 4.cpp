#include <bits/stdc++.h>
using namespace std;

struct MinHeapNode
{
    int idx;
    int freq;
    string code;

    MinHeapNode *left, *right;

    MinHeapNode(int idx = -1, int freq = -1)
    {
        left = right = NULL;
        this->idx = idx;
        this->freq = freq;
    }
};

struct compare
{

    bool operator()(MinHeapNode *l, MinHeapNode *r)
    {
        return (l->freq > r->freq);
    }
};

struct compare2
{

    bool operator()(MinHeapNode *l, MinHeapNode *r)
    {
        return (l->idx > r->idx);
    }
};

priority_queue<MinHeapNode *, vector<MinHeapNode *>, compare2> output;

void printCodes(struct MinHeapNode *root, string str)
{
    if (!root)
    {
        return;
    }
    if (root->idx != -1)
    {
        output.push(root);
        root->code = str;
    }

    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}

int main()
{
    int n;
    cin >> n;
    if (n == 1)
    {
        cout << 0 << "\n";
        return 0;
    }
    int freq;
    priority_queue<MinHeapNode *, vector<MinHeapNode *>, compare> minheap;

    for (int i = 0; i < n; i++)
    {
        cin >> freq;
        minheap.push(new MinHeapNode(i, freq));
    }
    struct MinHeapNode *left, *right, *top;

    while (minheap.size() != 1)
    {
        left = minheap.top();
        minheap.pop();

        right = minheap.top();
        minheap.pop();

        struct MinHeapNode *temp = new MinHeapNode(-1, left->freq + right->freq);
        temp->left = left;
        temp->right = right;

        minheap.push(temp);
    }

    printCodes(minheap.top(), "");

    for (int i = 0; i < n; i++)
    {
        cout << output.top()->code << "\n";
        output.pop();
    }

    return 0;
}
