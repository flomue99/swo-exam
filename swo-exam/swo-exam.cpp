#include <iostream>
#include <ostream>
#include <cstdlib>
#include <cstdio>
#include <initializer_list>
#include <cassert>

#ifdef BinTree C
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


#ifdef Person CPP
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

#ifdef SLL C
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
		idx++;
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

#ifdef Vector C CPP
template<typename T, int S>
class vector final {
private:
	int size;
	int capacity{ 0 };
	T* data;

public:

	vector(std::initializer_list list) :size{ S }, data{ new T[s] }{
		for (auto v : &list) {
			data[capacity] = v;
			capacity++;
		}
	}

	void push_back(T val) {
		data[capacity] = val;
		capacity++;
	}

	void pop_back() {
		data[capacity] = 0;
		--capacity;
	}


	int get_size() { return capacity };

	T* get_data() { return data };


	~vector() {
		delete[] data;
	}
};



class vector :public{
private:
	int size{ 0 }
public:
	vector = default;
	~vector() = 0;
};
#endif // Fertig stellen!

#ifdef ArrayOF, ListOF C
typedef struct node* node_ptr;
typedef struct node {
	node_ptr next;
	int val;
}node;
typedef node_ptr list_ptr;


//Liste		VT:Ändern der Größe kein Problem, 	NT:	zugriff O(n), Einfügen einfach eifnach ptr umhängen, keine Binäre suche falls sortiert
//Felder	NT:Ändern der Größte nicht so einfach, alles muss in ein Feld mit neuer Größe kopiert werden, Einfügen blöd _> alles um 1 verschieben, VT: zugriff O(1), , binäre suche falls sortiert

list_ptr new_list() {
	return NULL;
}

node_ptr new_node(const int val) {
	node_ptr n = (node_ptr)malloc(sizeof(node));
	n->next = NULL;
	n->val = val;
	return n;
}

list_ptr list_of_array(int* arr) {
	list_ptr list = new_list();

	int count = 0;
	while (arr[count] != 0)
	{
		count++;
	}

	for (int i = count - 1; i >= 0; i--) {
		node_ptr n = new_node(arr[i]);
		n->next = list;
		list = n;
	}

	return list;
}

void print_list(list_ptr list) {
	while (list != NULL)
	{
		printf("%d-> ", list->val);
		list = list->next;
	}
	printf("\n");
}

int number_of_nodes(list_ptr list) {
	int count = 0;
	while (list != NULL)
	{
		count++;
		list = list->next;
	}
	return count;
}


int* array_of_list(list_ptr list) {
	int* arr = (int*)malloc(sizeof(int) * number_of_nodes(list));
	int idx = 0;
	while (list != NULL)
	{
		arr[idx] = list->val;
		idx++;
		list = list->next;
	}
	return arr;
}

typedef void (*ofp)(int* val);

void print_val(int* val) {
	printf("%d, ", *val);
}

void for_each(list_ptr list, ofp ofp)
{
	while (list != NULL)
	{
		ofp(&list->val);
		list = list->next;
	}
}


int main() {
	int arr[] = { 10, 20, 30 ,40, 10, 0 };
	list_ptr list = list_of_array(arr);
	print_list(list);
	int* arr1 = array_of_list(list);
	for (int i = 0; i < number_of_nodes(list); i++)
	{
		printf("%d, ", arr1[i]);
	}
	printf("\n");
	for_each(list, print_val);

}

#endif // ArrayOF, ListOF C

#ifdef Graph CPP
class graph {
	int n;
public:
	graph(int n) :n{ n } {};
	int get_n() const { return n; };
	virtual void add_edge(int v1, int v2) = 0;
	virtual bool has_edge(int v1, int v2) const = 0;
	friend
		auto operator<<(std::ostream& os, const graph& self)->  std::ostream& {
		os << "E={";
		for (int i = 0; i < self.get_n(); i++)
		{
			for (int j = 0; j < self.get_n(); j++)
			{
				if (self.has_edge(i, j)) os << "<" << i << "," << j << "> ";
			}
		}
		os << "}\n";
		return os;
	}
};

class node {
public:
	int v; // vertex number, range 0 .. n – 1 for any graph(n)
	node* next;
	node(int v, node* next = nullptr) : v(v), next(next) { }
}; // node

class al_graph :public graph {
private:
	node** adj_list;
public:
	//call ctor from base class
	al_graph(int n) :graph(n) {
		adj_list = new node * [n];
		for (int i = 0; i < n; i++)
		{
			adj_list[i] = nullptr;
		}
	}
	void add_edge(int v1, int v2)override {
		assert(v1 >= 0 && v1 <= get_n());
		assert(v2 >= 0 && v2 <= get_n());

		if (!has_edge(v1, v2)) {
			adj_list[v1] = new node{ v2, adj_list[v1] };
		}
	}
	bool has_edge(int v1, int v2) const override {
		assert(v1 >= 0 && v1 <= get_n());
		assert(v2 >= 0 && v2 <= get_n());
		node* no = adj_list[v1];
		while (no != nullptr)
		{
			if (no->v == v2) return true;
			no = no->next;
		}
		return false;
	}

	~al_graph() {
		for (int i = 0; i < get_n(); i++)
		{
			node* list = adj_list[i];
			node* tmp = adj_list[i];
			while (list != nullptr)
			{
				std::cout << "Node cleared\n";
				list = list->next;
				delete tmp;
				tmp = nullptr;
			}
		}

		delete[]adj_list;
		std::cout << "List cleared\n";
		adj_list = nullptr;
	}

};


int main() {

	al_graph g{ 10 };
	g.add_edge(0, 2);
	g.add_edge(1, 2);
	g.add_edge(1, 5);
	g.add_edge(3, 1);
	g.add_edge(3, 4);
	g.add_edge(1, 2);
	std::cout << g;

}
#endif // graph, al_graph


// C++, OOP und Mehrfache Vererbeung
// Einfach Vererbung: Eine BasisKlasse von der Abgeleitet wird, zb. Klasse shape und Klasse Rectangle, rectangel:shape, rectangle erbt von shape
// Mehrfache Vererbung: Mehr als 1 Basisklasse von der abgeleitet wirdm zb. Schweizer Taschenmesser, Probleme _> Mehrdeutigkeit,Ohne virtuelle Basisklasse eventuell mehrere objekte der basiklasse in der Abgeleitetn klasse, PÜRoblem falls in Mehren Klassen die selbe Methode mit selber para  liste ist

#ifdef Mehrfahrvereberung CPP
class task {
public:
	int priority;
	virtual int pending();
}; // task
class drawable {

public:
	position pos;
	virtual void draw();
}; // drawable

class agent : public task, public drawable {
	...
}; // agent


//Nachbilden der Mehfachvererbung;
// Deklaration -> Primäre Basisklasse festlegen.(ableiten), Hinzufügen aller Methoden der andern Klassen durch kopie
// Klassen implelentierungen, -> 
//beste methode je sekundär klasse in object in der Basisklasse und dann delegieren

#endif //Mehrfahrvereberung


#ifdef Charset C
bool char_exists(const char* str, char ch, int length) {
	for (int i = 0; i <= length; i++)
	{
		if (str[i] == ch) return true;
	}
	return false;
}

char* CharSetOf(const char* a, const char* b) {
	char* tmp = (char*)malloc(sizeof(char) * strlen(a) + strlen(b) + 1);
	int tmp_idx = 0;
	for (int i = 0; i <= strlen(a); i++)
	{
		if (a[i] != ' ') {
			if (!char_exists(tmp, a[i], tmp_idx)) {
				tmp[tmp_idx] = a[i];
				tmp_idx++;
			}

		}
	}
	tmp_idx--;
	for (int i = 0; i <= strlen(b); i++)
	{
		if (b[i] != ' ') {
			if (!char_exists(tmp, b[i], tmp_idx)) {
				tmp[tmp_idx] = b[i];
				tmp_idx++;
			}

		}
	}
	char* result = (char*)malloc(sizeof(char) *tmp_idx);
	for (int i = 0; i < tmp_idx; i++)
	{
		result[i] = tmp[i];
	}

	for (int i = 0; i < strlen(result); i++)
	{
		for (int j = i + 1; j < strlen(result); j++)
		{
			if (result[i] > result[j]) {
				char temp = result[i];
				result[i] = result[j];
				result[j] = temp;
			}
		}
	}
	free(tmp);
	return result;
}


int main() {
	printf("Ordered Charset of \"hell o\" \"world!\" = %s \n",CharSetOf("hell o", "world!"));

}
#endif // Charset C


int main() {


}
