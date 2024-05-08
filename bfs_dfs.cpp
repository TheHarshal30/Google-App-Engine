#include<iostream>
#include<queue>
using namespace std;

struct Node{
    int data;
    Node* left;
    Node* right;
    Node(int val): data(val), left(nullptr), right(nullptr){}
};
class BinaryTree{
    private:
    Node* root;
    void BFS(Node* node){
        if(!node) return;
        queue<Node*>  q;
        q.push(node);
        while(!q.empty()){
            Node* currNode = q.front();
            q.pop();
            cout << currNode->data << " ";
            if(currNode->left) q.push(currNode->left);
            if(currNode->right) q.push(currNode->right);
        }
        cout << endl;
    }

    void DFS(Node* node){
        if(!node) return;
        cout << node->data << " ";
        if(node->left) DFS(node->left);
        if (node->right) DFS(node->right);
    }

    void preorder(Node* node){
        if(!node) return ;
        cout << node->data << " ";
        if(node->left) DFS(node->left);
        if (node->right) DFS(node->right);
    }
    Node* insertHelper(Node* node, int val) {

        if (!node) return new Node(val);

        if (val < node->data)
            node->left = insertHelper(node->left, val);
        else
            node->right = insertHelper(node->right, val);

        return node;
    }
    public:
    BinaryTree() : root(nullptr) {}
     void printBFS(){
        BFS(root);
        cout << endl;
    }
    void printDFS(){
        DFS(root);
        cout << endl;
    }
    void printPreorder(){
        preorder(root);
        cout << endl;
    }
    void insert(int val){
        root = insertHelper(root,val);
        
    }

};

int main(){
    BinaryTree tree;
    tree.insert(8);
    tree.insert(3);
    tree.insert(10);
    tree.insert(1);
    tree.insert(6);
    tree.insert(14);
    tree.insert(4);
    tree.insert(7);
    tree.insert(13);

    cout << "BFS: " << endl;
    tree.printBFS();
    cout << "DFS: " << endl;
    tree.printDFS();
    cout << "Preorder: " << endl;
    tree.printPreorder();
    return 0;
}