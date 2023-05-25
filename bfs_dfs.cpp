#include<bits/stdc++.h>
using namespace std;
 
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
 
void bfs(TreeNode* root) {
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        cout << node->val << " ";
        if (node->left) {
            q.push(node->left);
        }
        if (node->right) {
            q.push(node->right);
        }
    }
}
 
void parallel_bfs(TreeNode* root) {
    queue<TreeNode*> q;
    q.push(root);
    #pragma omp parallel
    {
        while (!q.empty()) {
            #pragma omp for
            for (int i = 0; i < q.size(); i++) {
                TreeNode* node = q.front();
                q.pop();
                #pragma omp critical
                {
                    cout << node->val << " ";
                }
                if (node->left) {
                    q.push(node->left);
                }
                if (node->right) {
                    q.push(node->right);
                }
            }
        }
    }
}
 
void dfs(TreeNode* root) {
    stack<TreeNode*> s;
    s.push(root);
    while (!s.empty()) {
        TreeNode* node = s.top();
        s.pop();
        cout << node->val << " ";
        if (node->right) {
            s.push(node->right);
        }
        if (node->left) {
            s.push(node->left);
        }
    }
}
 
void parallel_dfs(TreeNode* root) {
    stack<TreeNode*> s;
    s.push(root);
    #pragma omp parallel
    {
        while (!s.empty()) {
            #pragma omp for
            for (int i = 0; i < s.size(); i++) {
                TreeNode* node = s.top();
                s.pop();
                #pragma omp critical
                {
                    cout << node->val << " ";
                }
                if (node->right) {
                    s.push(node->right);
                }
                if (node->left) {
                    s.push(node->left);
                }
            }
        }
    }
}
 
int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);
 
    cout << "BFS traversal: ";
    auto start1 = chrono::high_resolution_clock::now();
    bfs(root);
    auto end1 = chrono::high_resolution_clock::now();
    cout << "\nBFS took " << chrono::duration_cast<chrono::microseconds>(end1 - start1).count() << " microseconds." << endl;
    cout << endl;
 
    cout << "Parallel BFS traversal: ";
    auto start2 = chrono::high_resolution_clock::now();
    parallel_bfs(root);
    auto end2 = chrono::high_resolution_clock::now();
    cout << "\nParallel BFS took " << chrono::duration_cast<chrono::microseconds>(end2 - start2).count() << " microseconds." << endl;
    cout << "\nSpeedup is : " << chrono::duration_cast<chrono::microseconds>(end1 - start1).count() / chrono::duration_cast<chrono::microseconds>(end2 - start2).count()<< endl;
    cout << "---------------------------------------------------------"<<endl;
 
    cout << "DFS traversal: ";
    auto start3 = chrono::high_resolution_clock::now();
    dfs(root);
    auto end3 = chrono::high_resolution_clock::now();
    cout << "\nDFS took " << chrono::duration_cast<chrono::microseconds>(end3 - start3).count() << " microseconds." << endl;
    cout << endl;
 
    cout << "Parallel DFS traversal: ";
    auto start4 = chrono::high_resolution_clock::now();
    parallel_dfs(root);
    auto end4 = chrono::high_resolution_clock::now();
    cout << "\nParallel DFS took " << chrono::duration_cast<chrono::microseconds>(end4 - start4).count() << " microseconds." << endl;
    cout << "\nSpeedup is : " << chrono::duration_cast<chrono::microseconds>(end3 - start3).count() / chrono::duration_cast<chrono::microseconds>(end4 - start4).count()<< endl;

 
    return 0;
}