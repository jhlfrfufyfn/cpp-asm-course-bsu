#include <iostream>
#include <cmath>
#include <vector>
#include <random>
using namespace std;
mt19937 generator(2134231);
class TreeNode {
public:
	TreeNode *left,*right;
	int key,prior;
	TreeNode(int newKey) {
		left=right=nullptr;
		key=newKey;
		prior=generator();
	}
};

pair<TreeNode*, TreeNode*> split(TreeNode *root, int key) {
	if (root == nullptr) {
		return{ nullptr,nullptr};
	}
	else if (root->key < key) {
		pair<TreeNode*,TreeNode*> p=split(root->right,key);
		root->right=p.first;
		return{ root,p.second };
	}
	else {
		pair<TreeNode*,TreeNode*> p=split(root->left,key);
		root->left=p.second;
		return{ p.first,root };
	}
}

TreeNode* merge(TreeNode *root1,TreeNode *root2) {
	if(root1==nullptr)
		return root2;
	else if(root2==nullptr)
		return root1;
	if (root1->key < root2->key) {
		root2->left=merge(root2->left,root1);
		return root2;
	}
	else {
		root1->right=merge(root1->right,root2);
		return root1;
	}
}

void insert(TreeNode *&root, TreeNode* newNode) {
	if (root == nullptr) {
		root=newNode;
		return ;
	}
	if (root->prior > newNode->prior) {
		if (root->key < newNode->key) {
			insert(root->right,newNode);
		}
		else {
			insert(root->left,newNode);
		}
		return;
	}
	pair<TreeNode*,TreeNode*> pp=split(root,newNode->key);
	newNode->left=pp.first;
	newNode->right=pp.second;
	root=newNode;
}

void erase(TreeNode *&root, int key) {
	if(root==nullptr)
		return;
	if (key < root->key) {
		erase(root->left,key);
	}
	else if(key>root->key) {
		erase(root->right,key);
	}
	else {
		root = merge(root->left,root->right);
	}
}

bool search(TreeNode *root, int key) {
	if(root==nullptr)
		return 0;
	if(root->key==key)
		return 1;
	if(root->key<key)
		return search(root->right,key);
	else
		return search(root->left,key);
}

int main() {
	vector<int> values = { 1,2,2,3,3,2,1,1 };
	TreeNode *tree=nullptr;
	for (auto it : values) {
		TreeNode* newOne=new TreeNode(it);
		insert(tree,newOne);
	}
	int i=3;
	for (auto it : values) {
		if(!search(tree,it))
			cout<<"Bad";
		else
			cout<<"Good";
		cout<<"\n";
		erase(tree,it);
	}
	system("pause");
	return 0;
}
