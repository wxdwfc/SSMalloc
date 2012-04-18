typedef struct double_list_elem		double_list_elem_t;
typedef struct double_list		        double_list_t;

struct double_list_elem {
	void* __padding;
	struct double_list_elem* next;
	struct double_list_elem* prev;
};

struct double_list {
	struct double_list_elem* head;
	struct double_list_elem* tail;
};


/* Places new_node at the front of the list. */
static void double_list_insert_front(void* new_node, double_list_t* list)
{
	double_list_elem_t* elem_new = (double_list_elem_t*)new_node;
	double_list_elem_t* old_head = list->head;

	if (old_head == NULL) {
		list->tail = elem_new;
	}
	else {
		old_head->prev = elem_new;
	}

	elem_new->next = old_head;
	elem_new->prev = NULL;
	list->head = elem_new;
}

/* Moves head to the back. */
static void double_list_rotate_back(double_list_t* list)
{
	double_list_elem_t* old_head = list->head;
	double_list_elem_t* old_tail = list->tail;
	double_list_elem_t* new_head = NULL;

	if (old_head == old_tail) {
		return;
	}

	new_head = old_head->next;

	new_head->prev = NULL;
	old_tail->next = old_head;
	old_head->prev = old_tail;
	old_head->next = NULL;
	
	list->head = new_head;
	list->tail = old_head;
}

/* Removes node from the list. */
static void double_list_remove(void* node, double_list_t* list)
{
	double_list_elem_t* elem_node = (double_list_elem_t*)node;

	if (elem_node->prev != NULL) {
		elem_node->prev->next = elem_node->next;
	}
	else {
		list->head = elem_node->next;
	}

	if (elem_node->next != NULL) {
		elem_node->next->prev = elem_node->prev;
	}
	else {
		list->tail = elem_node->prev;
	}

	if (list->head != NULL && list->head->next == NULL) {
		list->tail = list->head;
	}
	else if (list->tail != NULL && list->tail->prev == NULL) {
		list->head = list->tail;
	}
}
