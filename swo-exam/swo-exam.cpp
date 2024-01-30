#include <iostream>
#include <cstdlib>
#include <cstdio>

typedef struct node* node_ptr;

typedef struct node {
	int val;
	node_ptr left, right;
}node;

typedef node_ptr tree_ptr;


tree_ptr new_tree() {
	return nullptr;
}

node_ptr new_node(const int val) {
	node_ptr new_n = (node_ptr)malloc(sizeof(node));
	new_n->val = val;
	new_n->left = NULL;
	new_n->right = NULL;
	return new_n;
}

void insert(const int val, tree_ptr* root) {
	if (*root == NULL) {
		*root = new_node(val);
	}
	else if (val < (*root)->val) {
		insert(val, &(*root)->left);
	}
	else {
		insert(val, &(*root)->right);
	}
}

int nr_of_node(tree_ptr root) {
	if (root != NULL) {
		return nr_of_node(root->left) + nr_of_node(root->right) + 1;
	}
	else {
		return 0;
	}
}

void print(tree_ptr root) {
	if (root != NULL) {
		print(root->left);
		printf("%d, ", root->val);
		print(root->right);
	}
}

void clear(tree_ptr* root) {
	if (*root != NULL) {
		clear(&(*root)->left);
		clear(&(*root)->right);
		free(*root);
	}
}

void copy_helper(tree_ptr t, int* array, int * idx) {
	if (t != NULL) {
		copy_helper(t->left, array,idx);
		array[(*idx)++] = t->val;
		copy_helper(t->right, array, idx);
	}
}

int* array_of(tree_ptr t) {
	int* array = (int*)malloc(sizeof(int) * nr_of_node(t));
	int idx = 0;
	copy_helper(t, array, &idx);
	return array;
}


int main()
{
	tree_ptr tree = new_tree();
	insert(10, &tree);
	insert(5, &tree);
	insert(14, &tree);
	insert(16, &tree);
	insert(3, &tree);
	print(tree);
	printf("\n");
	printf("Amount of Nodes: %d\n", nr_of_node(tree));

	int* array = array_of(tree);
	for (int i = 0; i < 5; i++)
	{
		printf("%d, ", array[i]);
	}
	printf("\n");
	clear(&tree);
}
