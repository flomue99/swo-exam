#include <iostream>
#include <cstdlib>
#include <cstdio>

#if BinTree C
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

void copy_helper(tree_ptr t, int* array, int* idx) {
	if (t != NULL) {
		copy_helper(t->left, array, idx);
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
#endif // BinTree


#if Person CPP
class person {
private:
	unsigned long int  snr;
	std::string firstname;
	std::string lastname;

public:
	person(unsigned long int snr, std::string firstname, std::string lastname) :snr{ snr }, firstname{ firstname }, lastname{ lastname } {}
	std::string get_lastname() { return lastname; }
	std::string get_firstname() { return firstname; }
	unsigned long int get_snr() { return snr; }
	void set_lastname(std::string new_lastname) { lastname = new_lastname; }

	person(const person& other) = delete; // COPY CTOR
	auto operator=(const person& other)->person & = delete; // COPY Assign
	person(const person&& other) = delete; //MOVE CTOR
	auto operator=(const person&& other)->person & = delete; //MOVE Assign

	friend
		auto operator<<(std::ostream& os, const person& self)-> std::ostream& {

		os << self.snr << " " << self.firstname << " " << self.lastname << "\n";
		return os;
	}

	friend
		auto operator==(const person& rhs, const person& lhs)-> bool {
		return (rhs.snr == lhs.snr);
	}

	friend
		auto operator<(const person& rhs, const person& lhs)-> bool {
		return (rhs.firstname < lhs.firstname);
	}

};



int main() {
	person p1{ 4199090901, "Florian", "Muehleder" };
	person p2{ 4199090901, "Florian", "Muehleder" };
	person p3{ 3199090901, "Jonas", "Muehleder" };
	std::cout << p1;

	if (p1 == p2)std::cout << "p1 and p2 match \n";
	if (p1 < p3)std::cout << "p1 < p3\n";
}
#endif // Person

#if SLL C
typedef struct node* node_ptr;
typedef struct node {
	int val;
	node_ptr next;
}node;
typedef node_ptr list_ptr;


list_ptr new_list() {
	return NULL;
}

node_ptr new_node(int val) {
	node_ptr new_n = (node_ptr)malloc(sizeof(node));
	new_n->next = NULL;
	new_n->val = val;
	return new_n;
}


void prepend_node(int val, list_ptr* list) {

	if (*list == NULL) {
		*list = new_node(val);
	}
	else {
		node_ptr new_n = new_node(val);
		new_n->next = *list;
		*list = new_n;
	}
}

void append_node(int val, list_ptr* list) {
	if (*list == NULL) {
		*list = new_node(val);
	}
	else {
		while ((*list)->next != NULL)
		{
			list = &(*list)->next;
		}
		(*list)->next = new_node(val);
	}
}

void insert_node(int val, list_ptr* list) {
	if (*list == NULL) {
		*list = new_node(val);
	}
	else {
		node_ptr succ = *list;
		node_ptr pred = NULL;
		while (succ->next != NULL && succ->val <= val)
		{
			pred = succ;
			succ = succ->next;
		}
		node_ptr new_n = new_node(val);
		new_n->next = succ;
		if (pred == NULL) {
			*list = new_n;
		}
		else {
			pred->next = new_n;
		}
	}
}

list_ptr swap_list(list_ptr list) {

	list_ptr rev_list = new_list();
	while (list != NULL)
	{
		node_ptr new_n = new_node(list->val);
		new_n->next = rev_list;
		rev_list = new_n;
		list = list->next;
	}

	return rev_list;
}

void print_list(list_ptr list) {
	while (list != NULL)
	{
		printf("%d, ", list->val);
		list = list->next;
	}
	printf("\n");
}

void clear_list(list_ptr* list) {
	while (*list != nullptr)
	{
		node_ptr tmp = *list;
		*list = (*list)->next;
		free(tmp);
		tmp = nullptr;
	}
}

int nr_of_nodes(list_ptr list) {
	int count = 0;
	while (list != NULL)
	{
		count++;
		list = list->next;
	}
	return count;
}

int* to_array(list_ptr list) {
	int* arr = (int*)malloc(sizeof(int) * nr_of_nodes(list));

	int idx = 0;
	while (list != NULL)
	{
		arr[idx] = list->val;
		idx ++;
		list = list->next;
	}
	return arr;
}

int main() {
	list_ptr list = new_list();
	list_ptr rev_list = new_list();

	append_node(1, &list);
	append_node(2, &list);
	append_node(3, &list);
	append_node(4, &list);
	append_node(5, &list);
	prepend_node(10, &list);
	insert_node(-1, &list);
	insert_node(11, &list);
	print_list(list);

	rev_list = swap_list(list);
	print_list(rev_list);
	int* arr = to_array(list);

	for (int i = 0; i < nr_of_nodes(list); i++)
	{
		printf("%d, ", arr[i]);
	}
	clear_list(&list);
	clear_list(&rev_list);
}
#endif // SLL



int main(){

}