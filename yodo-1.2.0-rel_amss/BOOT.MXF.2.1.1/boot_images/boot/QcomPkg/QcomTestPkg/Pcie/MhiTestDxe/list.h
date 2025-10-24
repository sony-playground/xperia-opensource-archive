#ifndef LIST_H
#define LIST_H
/**
 *  @file list.h
 *
 *  @brief This header files defines the double link list implementation.
 */
/*============================================================================
               Copyright (c) 2021 Qualcomm Technologies, Inc.
               All Rights Reserved.
               Confidential and Proprietary - Qualcomm Technologies, Inc.
============================================================================*/

#include <stddef.h>
#include <stdint.h>

/* Generic list. Any object can be added to list if it containts
this type as a member */
typedef struct _list
{
   struct _list *next;
   struct _list *prev;
} list_t;

/**
* @brief      list_init
*
*             Initialize list
*
*
* @param[in]  *h Head of list
*
* @dependencies
*             None
*
*
* @return
*             None
*
* @sideeffect None
*/
static __inline void list_init(list_t *h)
{
   if (NULL == h)
      return;

   h->next = h;
   h->prev = h;
}

/**
* @brief      _list_insert
*
*             Insert element into list. Element is inserted between prev and next
*
*
* @param[in]  *prev - Previous element
* @param[in]  *next - Next element
* @param[in]  *new  - New element
*
* @dependencies
*             None
*
*
* @return
*             None
*
* @sideeffect None
*/
static __inline int _list_insert(list_t *prev, list_t *next, list_t *new)
{
   if (NULL == prev || NULL == next || NULL == new)
      return -1;

   prev->next = new;
   next->prev = new;
   new->prev = prev;
   new->next = next;

   return 0;
}
/**
* @brief      list_add_tail
*
*             Add item at the end of the list
*
*
* @param[in]  *h - List head
* @param[in]  *i - Item pointer
*
* @dependencies
*             None
*
*
* @return
*             None
*
* @sideeffect None
*/
static __inline int list_add_tail(list_t *h, list_t *i)
{
   if (NULL == h)
      return -1;

   return _list_insert(h->prev, h, i);
}
/**
* @brief      list_add_head
*
*             Add item at the head of the list
*
*
* @param[in]  *h - Head of the list
* @param[in]  *i - Item pointer
*
* @dependencies
*             None
*
*
* @return
*             None
*
* @sideeffect None
*/
static __inline int list_add_head(list_t *h, list_t *i)
{
   if (NULL == h)
      return -1;

   return _list_insert(h, h->next, i);
}

/**
* @brief      list_is_empty
*
*             Returns TRUE if the list is empty
*
*
* @param[in]  *h - Queue
*
* @dependencies
*             mhi_q_init must be called first
*
*
* @return
*             TRUE if queue is empty
*             FALSE if not
*             ERROR if q is invalid
*
* @sideeffect None
*/
static __inline int list_is_empty(list_t *h)
{
   if (NULL == h)
      return -1;

   return h->next == h;
}

/**
* @brief      list_del
*
*             Remove item from list
*
*
* @param[in]  *i - Item to remove
*
* @dependencies
*             None
*
*
* @return
*             None
*
* @sideeffect None
*/
static __inline int list_del(list_t *i)
{
   if (NULL == i || NULL == i->next || NULL == i->prev)
      return -1;

   i->prev->next = i->next;
   i->next->prev = i->prev;

   return 0;
}

/**
* @brief      list_get_item
*
*             Get first item on list. Will not remove the item off the list. If
*             list is empty return NULL
*
*
* @param[in]  *h - List head
* @param[in]  type - Type of container structure which embeds list
* @param[in]  member - List member name

*
* @dependencies
*             None
*
*
* @return
*             None
*
* @sideeffect None
*/
#define list_get_item(h, type, member) \
   ((h) != (h)->next ? (type *)((uintptr_t)(h)->next - offsetof(type, member)) : NULL)


/**
* @brief      list_for_each_item
*
*             Macro to loop through all elements in a list
*
* @param[in]  *h - List head
* @param[in]  type - Type of container structure which embeds list
* @param[in]  member - List member name
* @param[in]  var - Current element
*
*
* @dependencies
*             None
*
*
* @return
*             None
*
* @sideeffect None
*/
#define list_for_each_item(h, type, member, var, next) \
   for ((var) = list_get_item((h), type, member), (next) = (var) ? list_get_item(&(var)->member, type, member) : NULL; \
        (list_t *)(var) != (h) && (var) != NULL; \
        (var) = (next), (next) = (var) ? list_get_item(&(var)->member, type, member) : NULL)

#endif

