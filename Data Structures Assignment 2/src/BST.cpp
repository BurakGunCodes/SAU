/**
* @file BST.cpp
* @description Organ sýnýfýnýn kalýtým aldýðý sýnýftýr.Dokulardaki orta degere göre bu sýnýfta agaclar olusturulacaktýr.
* @course 2.Öðretim A Grubu
* @assignment 2.Odev
* @date 23/12/2022
* @author Burak Gün, burak.gun1@ogr.sakarya.edu.tr
*/

#include <iostream>
#include <cmath>
#include "BST.hpp"


using namespace std;
BST::BST()
{
	root = 0;
	//cout << "BST Constructor Called" << endl;
}


BST::~BST(){
	Clear();
}

void BST::Clear(){
	while(!IsEmpty()) DeleteNode(root);
}
bool BST::IsEmpty(){
	return root == NULL;
}
void BST::Add(int key)
{
	SearchAndAdd(root, key);
}

void BST::SearchAndAdd(BSTNode* &subNode, int key)
{
	static int x = 0;
	//cout << "adim sayisi:" << ++x << endl;
	if (subNode == 0) subNode = new BSTNode(key);
	else if (key <= subNode->data) SearchAndAdd(subNode->left, key);
	else if (key > subNode->data) SearchAndAdd(subNode->right, key);
	else return;

}

void BST::inOrder(BSTNode* subNode)
{
	if (subNode != NULL)
	{
		inOrder(subNode->left);
		cout << subNode->data << " ";
		inOrder(subNode->right);
	}
}

void BST::inOrder()
{
	inOrder(root);
}



void BST::preOrder(BSTNode* subNode)
{
	if (subNode != NULL)
	{
		cout << subNode->data << " ";
		preOrder(subNode->left);
		preOrder(subNode->right);
	}
}

void BST::preOrder()
{
	preOrder(root);
}


void BST::postOrder(BSTNode* subNode)
{
	if (subNode != NULL)
	{
		postOrder(subNode->left);
		postOrder(subNode->right);
		//cout << subNode->data << " ";
	}
}


int BST::postOrderInt(BSTNode* subNode)
{
	if (subNode != NULL)
	{
		postOrderInt(subNode->left);
		postOrderInt(subNode->right);
		return  subNode->data ;
	}
}

int BST::postOrderInt()
{
	return postOrderInt(root);
}

void BST::postOrder()
{
	postOrder(root);
}




int BST::height(BSTNode* subNode)
{
	if(subNode == NULL) return -1;
	return 1+max( height(subNode->left), height(subNode->right) ) ;
}

int BST::LeftHeight(BSTNode* subNode)
{
	if(subNode == NULL) return -1;
	return 1+ height(subNode->left);
}

int BST::RightHeight(BSTNode* subNode)
{
	if(subNode == NULL) return -1;
	return 1+ height(subNode->right);
}

int BST::height()
{
	return height(root);
}

int BST::LeftHeight()
{
	return LeftHeight(root);
}
int BST::RightHeight()
{
	return RightHeight(root);
}

void BST::Delete(int data)
{
	SearchAndDelete(root,data) ;
}


bool BST::SearchAndDelete(BSTNode *&subNode,int data){
	if(subNode == NULL) return false;
	if(subNode->data == data) return DeleteNode(subNode);
	else if(data < subNode->data) return SearchAndDelete(subNode->left,data);
	else return SearchAndDelete(subNode->right,data);
}

bool BST::DeleteNode(BSTNode *&subNode){
	BSTNode *DelNode = subNode;
			
	if(subNode->right == NULL) subNode = subNode->left;
	else if(subNode->left == NULL) subNode = subNode->right;
	else
	{
		DelNode = subNode->left;
		BSTNode *parent = subNode;
		while(DelNode->right != NULL)
		{
			parent = DelNode;
			DelNode = DelNode->right;
		}
		subNode->data = DelNode->data;
		if(parent == subNode) subNode->left = DelNode->left;
		else parent->right = DelNode->left;
	}

		delete DelNode;
		DelNode=0;
		return true;
}