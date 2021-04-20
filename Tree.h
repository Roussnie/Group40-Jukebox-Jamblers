#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <fstream>
#include <sstream>
#include <istream>
using namespace std;

struct TreeNode {
	int val;

	string artist;
	string name;
	int popularity = 0;
	int releaseYear = 0;

	int balanceFactor;

	TreeNode* left;
	TreeNode* right;

	TreeNode(int x, string a, string n, int p, int y) : val(x), artist(a), name(n), popularity(p),
		releaseYear(y), balanceFactor(0), left(nullptr), right(nullptr) {}
};

struct JJTree {
	int calculateHeight(struct TreeNode*& root);

	TreeNode* rotateLeft(struct TreeNode*& root);
	TreeNode* rotateRight(struct TreeNode*& root);
	TreeNode* rotateLeftRight(struct TreeNode*& root);
	TreeNode* rotateRightLeft(struct TreeNode*& root);
	
	TreeNode* BalanceTree(struct TreeNode*& root);

	TreeNode* Insert(struct TreeNode*& root, int number, string artist, string name, int popularity, int year);

	void PrintInorder(struct TreeNode*& root, string artist, string name, int popularity, int year);
};

int JJTree::calculateHeight(TreeNode*& root) {

	int height = 0;

	if (root == nullptr)
		height = 1;
	else
		height = 1 + std::max(calculateHeight(root->left), calculateHeight(root->right));

	return height;

}

TreeNode* JJTree::rotateLeft(TreeNode*& root) {

	TreeNode* newParent = root->right;
	TreeNode* temp = newParent->left;
	newParent->left = root;
	root->right = temp;
	return newParent;

}

TreeNode* JJTree::rotateRight(TreeNode*& root)
{
	TreeNode* newParent = root->left;
	TreeNode* temp = newParent->right;
	newParent->right = root;
	root->left = temp;
	return newParent;

}

TreeNode* JJTree::rotateLeftRight(TreeNode*& root) {

	root->left = rotateLeft(root->left);
	root = rotateRight(root);
	return root;

}

TreeNode* JJTree::rotateRightLeft(TreeNode*& root) {

	root->right = rotateRight(root->right);
	root = rotateLeft(root);
	return root;

}

TreeNode* JJTree::BalanceTree(TreeNode*& root) {

	root->balanceFactor = calculateHeight(root->left) - calculateHeight(root->right);

	if (root->balanceFactor > 1) {
		if (root->left->balanceFactor > 0) {
			root = rotateRight(root);
		}
		else {
			root = rotateLeftRight(root);
		}
	}
	else if (root->balanceFactor < -1) {
		if (root->right->balanceFactor > 0) {
			root = rotateRightLeft(root);
		}
		else {
			root = rotateLeft(root);
		}
	}

	return root;

}

TreeNode* JJTree::Insert(struct TreeNode*& root, int number, string artist, string name, int popularity, int year) {//(TreeNode*& root, int ID, string name) {

	int count = 0;
	if (root == nullptr) {
		TreeNode* temp = new TreeNode(number, artist, name, popularity, year);
		root = temp;
		return root;
	}
	TreeNode* curr = root;
	if (number < root->val) {
		root->left = Insert(root->left, number, artist, name, popularity, year);
	}
	else if (number > root->val) {
		root->right = Insert(root->right, number, artist, name, popularity, year);
	}
	else {
		return root;
	}
	root = BalanceTree(root);

	return root;

}

void JJTree::PrintInorder(struct TreeNode*& root, string artist, string name, int popularity, int year) {

	if (root == nullptr) {
		return;
	}

	PrintInorder(root->left, root->artist, root->name, root->popularity, root->releaseYear);
	cout << "Title: " << root->name << endl;
	cout << "Artist: " << root->artist << endl;
	cout << "Year of Release: " << root->releaseYear << endl;
	cout << "Popularity: " << root->popularity << endl;
	cout << endl;
	PrintInorder(root->right, root->artist, root->name, root->popularity, root->releaseYear);

}
