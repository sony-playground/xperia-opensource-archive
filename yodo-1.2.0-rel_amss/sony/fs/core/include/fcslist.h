/*
 * Copyright (c) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef FCS_LIST_H_
#define FCS_LIST_H_

/*
 * Generic linked lists
 */

#include <stddef.h>

/*
 * List entry.
 *
 * This struct represents an entry in a list, and is also used to represent
 * the list as a whole.
 */
struct list_entry {
	struct list_entry *prev; /* Pointer to the previous entry in the list */
	struct list_entry *next; /* Pointer to the next entry in the list */
};

/*
 * Macro to define and initialize a list variable.
 *
 * Example:
 *
 * static LIST(example_list);
 */
#define LIST(x) struct list_entry x = { &(x), &(x) }

/*
 * Macro to initialize list members of structs in static macros
 *
 * Example:
 *
 * typedef struct
 * {
 *   int dummy;
 *   list_entry_t list;
 * }foo_t;
 * #define FOO(name, i) foo_t name = {i, INIT_LIST_ENTRY(name.list)}
 *
 * static FOO(myFoo, 5);
 */
#define INIT_LIST_ENTRY(x) { &(x), &(x) }

/*
 * Get a pointer to the containing data structure of a list.
 *
 * To have data in a list element the list_entry_t member has to be embedded
 * inside a struct that defines the data of a list element. This macro
 * is used to be able to get a pointer to the containing struct variable.
 * All of the calculations are done at compile time, so it is important
 * that all the parameters to the macro are correct.
 *
 * Example:
 *
 * struct example_struct {
 *   int val;
 *   list_entry_t list;
 * } example_variable;
 * ...
 * list_entry_t *example_list_entry = &example_variable.list;
 * ...
 * struct example_struct *ptr;
 * ptr = LIST_DATA(example_list_entry, struct example_struct, list);
 *
 * [in] entry
 *   A pointer to the actual list entry inside the containing struct
 * [in] type
 *   The name of the containing struct type
 * [in] member
 *   The name of the member variable inside the containing struct
 */
#define LIST_DATA(entry, type, member)				\
	(type *)(((char *) entry) - offsetof(type, member))

/*
 * Get the first entry in a list.
 *
 * Example:
 *
 * struct example_struct {
 *   int val;
 *   list_entry_t list;
 * } example_variable;
 * LIST(example_list);
 * struct example_struct *p;
 * ...
 * list_add_head(&example_list, &example_variable.list);
 * p = LIST_FIRST(&example_list, struct example_variable, list);
 *
 * In this example, p will point to example_variable.
 *
 * warning
 *   Calling this on an empty list will have unpredictable consequences.
 *
 * [in] list
 *   A pointer to the list
 * [in] type
 *   The name of the containing struct type
 * [in] member
 *   The name of the member variable inside the containing struct
 */
#define LIST_FIRST(list, type, member)		\
	LIST_DATA((list)->next, type, member)

/*
 * Get the last entry in a list.
 *
 * Example:
 *
 * struct example_struct {
 *   int val;
 *   list_entry_t list;
 * } example_variable;
 * LIST(example_list);
 * struct example_struct *p;
 * ...
 * list_add_tail(&example_list, &example_variable.list);
 * p = LIST_LAST(&example_list, struct example_variable, list);
 *
 * In this example, p will point to example_variable.
 *
 * warning
 *   Calling this on an empty list will have unpredictable consequences.
 *
 * [in] list
 *   A pointer to the list
 * [in] type
 *   The name of the containing struct type
 * [in] member
 *   The name of the member variable inside the containing struct
 */
#define LIST_LAST(list, type, member)		\
	LIST_DATA((list)->prev, type, member)

/*
 * Iterate forward over all entries in a list.
 *
 * This macro should be used as a replacement for a normal for-statement.
 *
 * Example:
 *
 * LIST(l);
 * list_entry_t e;
 * ...
 * LIST_FOR_EACH(&l, e)
 * {
 *   ...do something useful with 'e'...
 * }
 *
 * [in] list
 *   The list
 * [in] ptr
 *   A list_entry_t pointer variable which will be used for iteration
 */
#define LIST_FOR_EACH(list, ptr)				\
	for (ptr = (list)->next; ptr != (list); ptr = ptr->next)

/*
 * Iterate forward over all entries in a list.
 *
 * This macro should be used as a replacement for a normal for-statement.
 *
 * Example:
 *
 * LIST(l);
 * struct example_struct {
 *   int val;
 *   list_entry_t list;
 * } *p;
 * ...
 * LIST_FOR_EACH_DATA(&l, p, list)
 * {
 *   ...p now points to a variable of type 'struct example_struct'...
 * }
 *
 * [in] list
 *   The list
 * [in] ptr
 *   A pointer to the correct data type which will be used for iteration
 * member
 *   The name of the member variable inside the containing struct
 */
#ifdef __GNUC__
#define LIST_FOR_EACH_DATA(list, ptr, member)				\
	for (ptr = LIST_FIRST((list), __typeof__(*ptr), member);	\
	     &(ptr)->member != (list);					\
	     ptr = LIST_DATA((ptr)->member.next, __typeof__(*ptr), member))
#else
#error Your compiler does not support a __typeof__-operator
#define LIST_FOR_EACH_DATA(list, ptr, member)
#endif

/*
 * Initialize a list.
 *
 * This can be used to initialize a dynamically allocated list entry.
 *
 * Example:
 *
 * list_entry_t *example_list = malloc(sizeof(list_entry_t));
 * ...
 * list_init(example_list);
 *
 * [in] list
 *   The list to initialize
 */
static inline void list_init(struct list_entry *list)
{
	list->next = list;
	list->prev = list;
}

/*
 * Add an entry first in a list.
 *
 * In reality, entry is added just after the list entry, so this can be
 * used to insert an entry anywhere in the list.
 *
 * Example:
 *
 * static LIST(example_list);
 * ...
 * struct example_struct {
 *   int val;
 *   list_entry_t list;
 * } example_variable;
 * ...
 * list_add_head(&example_list, &example_variable.list);
 *
 * In this example, example_variable is added first in the list.
 *
 * [in] list
 *   The list
 * [in] entry
 *   Entry to add
 */
static inline void list_add_head(
	struct list_entry *list, struct list_entry *entry)
{
	entry->next = list->next;
	list->next->prev = entry;
	list->next = entry;
	entry->prev = list;
}

/*
 * Add an entry last in a list.
 *
 * In reality, entry is added just before the list entry, so this can be
 * used to insert an entry anywhere in the list.
 *
 * Example:
 *
 * static LIST(example_list);
 * ...
 * struct example_struct {
 *   int val;
 *   list_entry_t list;
 * } example_variable;
 * ...
 * list_add_tail(&example_list, &example_variable.list);
 *
 * In this example, example_variable is added last in the list.
 *
 * [in] list
 *   The list
 * [in] entry
 *   Entry to add
 */
static inline void list_add_tail(
	struct list_entry *list, struct list_entry *entry)
{
	entry->prev = list->prev;
	list->prev->next = entry;
	list->prev = entry;
	entry->next = list;
}

/*
 * Remove an entry from whatever list it is currently in.
 *
 * Example:
 *
 * static LIST(example_list);
 * ...
 * struct example_struct {
 *   int val;
 *   list_entry_t list;
 * } example_variable;
 * ...
 * list_add_head(&example_list, &example_variable.list);
 * ...
 * list_remove(&example_variable.list);
 *
 * In this example, example_variable is first added to a list, and
 * later on removed from whatever list it is in (most probably example_list).
 *
 * [in] entry
 *   The entry to remove
 */
static inline void list_remove(struct list_entry *entry)
{
	entry->prev->next = entry->next;
	entry->next->prev = entry->prev;
}

/*
 * Check if a list is empty.
 *
 * [in] list
 *   The list to check
 */
static inline int list_empty(struct list_entry *list)
{
	return (list->next == list);
}

/*
 * Move an entry from one list to the beginning of another list.
 *
 * [in] list
 *   The list to move the entry to
 * [in] entry
 *   The entry to move
 */
static inline void list_move_head(
	struct list_entry *list, struct list_entry *entry)
{
	list_remove(entry);
	list_add_head(list, entry);
}

/*
 * Move an entry from one list to the end of another list.
 *
 * [in] list
 *   The list to move the entry to
 * [in] entry
 *   The entry to move
 */
static inline void list_move_tail(
	struct list_entry *list, struct list_entry *entry)
{
	list_remove(entry);
	list_add_tail(list, entry);
}

#endif /* FCS_LIST_H_ */
