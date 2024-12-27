#ifndef BST_HPP
#define BST_HPP

#include <iostream>


using namespace std;

class BSTNode {

	private:

	public:

		BSTNode* left;
		BSTNode* right;
		int data;

		BSTNode(int data,BSTNode* lf = nullptr, BSTNode* rg = nullptr)
		{
			this->left = lf;
			this->right = rg;
			this->data = data;

			//cout << "BSTNode Constructor Called." <<" Data: "<< this->data << endl;

		}
		~BSTNode()
		{
			//cout << "BSTNode Desctructor Called" << endl;
		}
};

class BST {
	private:
		BSTNode* root;
		void SearchAndAdd(BSTNode* &subNode, int data);
		void inOrder(BSTNode* subNode);
		void preOrder(BSTNode* subNode);
		void postOrder(BSTNode* subNode);
		int postOrderInt(BSTNode* subNode);
		int height(BSTNode* subNode);
		int LeftHeight(BSTNode* subNode);
		int RightHeight(BSTNode* subNode);
		bool IsEmpty();
	public:
		BST();
		~BST();
		void inOrder();
		void preOrder();
		void postOrder();
		int postOrderInt();
		void Add(int key);
		int height();
		int LeftHeight();
		int RightHeight();
		void Delete(int data);
		void Clear();
		bool SearchAndDelete(BSTNode *&subNode,int data);
		bool DeleteNode(BSTNode *&subNode);
};


#endif // !BST_HPP



