#include<iostream>

#include<math.h>
using namespace std;

struct Node
{
	int key;
	int height;
	Node *left = NULL;
	Node *right = NULL;
};

class AVL_Tree
{
private:
	Node *root;
	Node *pre;
public:
	AVL_Tree()
	{
		pre = new Node;
		pre->key = INT_MAX;
		root = NULL;
	}
	void insert(Node *&node,int key);
	void fix();
	void Insert_Fix(int key);
	void Left_Rotation(Node *parent, Node *head);
	void Right_Rotation(Node *parent, Node *head);
};

void AVL_Tree::insert(Node *&node,int key)
{
	if (node == NULL)
	{
		node = new Node;
		node->key = key;
		node->height = 1;
	}
	else
	{
		if (key >= node->key)
		{
			insert(node->right, key);
			if (!node->left||node->right->height > node->left->height)
				node->height = node->right->height + 1;
			
		}
		else
		{
			insert(node->left, key);
			if (!node->right || node->left->height > node->right->height)
				node->height = node->left->height+1;
		}
	}
	return;
}

void AVL_Tree::Left_Rotation(Node *parent, Node *head)
{
	if (parent->left == head)
		parent->left = head->right;
	else
		parent->right = head->right;
	Node *temp = head->right;
	head->right = temp->left;
	temp->left = head;
}

void AVL_Tree::Right_Rotation(Node *parent, Node *head)
{
	if (parent->left == head)
		parent->left = head->left;
	else
		parent->right = head->left;
	Node *temp = head->left;
	head->left = temp->right;
	temp->right = head;
}

void AVL_Tree::fix()
{
	if (root->height < 3 || (!(root->height == 3 && (!root->left || !root->right)) && abs(root->left->height - root->right->height) <= 1))
		return; 
	Node *head = root;
	pre->left = root;
	Node *parent = pre;
	while (head->height > 3)
	{
		if (head->right->height > head->left->height)
		{   
			parent = head;
			head->height--;
			head = head->right;
		}
		else
		{
			parent=head;
			head->height--;
			head = head->left;
		}
	}
	if (head->right&&head->right->right)
	{
		head->height-=2;
		Left_Rotation(parent, head);
		root = pre->left;
			return;
	}

	if (head->left&&head->left->left)
	{   
		head->height-=2;
		Right_Rotation(parent, head);
		root = pre->left;
			return;
	}

	if (head->left&&head->left->right)
	{
		Left_Rotation(head, head->left);
		head->height-=2;
		Right_Rotation(parent, head);
		root = pre->left;

		return;
	}
	if (head->right&&head->right->left)
	{
		Right_Rotation(head, head->right);
		head->height-=2;
		Left_Rotation(parent, head);
		root = pre->left;
		return;
	}
}

void AVL_Tree::Insert_Fix(int key)
{
	insert(root, key);
	fix();
}


int main()
{
	AVL_Tree T;
	T.Insert_Fix(8);
	T.Insert_Fix(7);
	T.Insert_Fix(6);
	T.Insert_Fix(10);
	T.Insert_Fix(9);
	T.Insert_Fix(5);
	T.Insert_Fix(2);
	system("pause");
}