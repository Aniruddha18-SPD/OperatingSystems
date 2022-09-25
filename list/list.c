// list/list.c
// 
// Implementation for linked list.
//
// <Author>

#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

#include "list.h"

list_t *list_alloc() { return (list_t *) malloc(sizeof(list_t)); }

void recurse_free(node_t *n){
  if (n) {
    recurse_free(n->next);
    free(n);
  }
}
void list_free(list_t *l) {
  recurse_free(l->head);
  free(l);
}

void list_print(list_t *l) {
  node_t* node = l->head;
  while (node) {
    printf("%d->", node->value);
    node = node->next;
  }
  printf("NULL\n");
}
int list_length(list_t *l) {
  node_t* node = l->head;
  int count = 0;
  while (node) {
    count++;
    node = node->next;
  }
  return count;
}

void list_add_to_back(list_t *l, elem value) {
  if (l->head){
    node_t* node = l->head;
    while (node->next) {
      node = node->next;
    }
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->value = value;
    node->next = new_node;
    new_node->next = NULL;
  }
  else {
    list_add_to_front(l, value);
  }
}
void list_add_to_front(list_t *l, elem value) {
  node_t* new_node = (node_t*)malloc(sizeof(node_t));
  new_node->value = value;
  if (l->head){
    new_node->next = l->head;
    l->head = new_node;
  }
  else{
    new_node->next = NULL;
    l->head = new_node;
  }
}
void list_add_at_index(list_t *l, elem value, int index) {
  if (index == 0 || l->head == NULL){
    list_add_to_front(l, value);
  }
  else{
    node_t* node = l->head;
    node_t* prev = NULL;
    int idx = 0;
    while (node && idx < index) {
      idx++;
      prev = node;
      node = node->next;
    }
    if (node == NULL && idx == index){
      list_add_to_back(l, value);
    }
    else if (idx == index){
      node_t* new_node = (node_t*)malloc(sizeof(node_t));
      new_node->value = value;
      new_node->next = prev->next;
      prev->next = new_node;
    }
  }
}

elem list_remove_from_back(list_t *l) {
  if (l->head){
    node_t* node = l->head;
    node_t* prev = NULL;
    while (node->next) {
      prev = node;
      node = node->next;
    }
    prev->next = node->next;
    elem temp = node->value;
    free(node);
    return temp;
  }
  return -1;
}
elem list_remove_from_front(list_t *l) {
  if (l->head){
    node_t* node = l->head;
    elem temp = node->value;
    l->head = node->next;
    free(node);
    return temp;
  }
return -1;
}
elem list_remove_at_index(list_t *l, int index) {
  if (index == 0){
    return list_remove_from_front(l);
  }
  if (l->head){
    node_t* node = l->head;
    node_t* prev = NULL;
    int idx = 0;
    while (node && idx < index) {
      idx++;
      prev = node;
      node = node->next;
    }
    if (node == NULL && idx == index){
      return list_remove_from_back(l);
    }
    else if (idx == index){
      elem temp = node->value;
      prev->next = node->next;
      free(node);
      return temp;
    }
  }
return -1;
}

bool list_is_in(list_t *l, elem value) { 
  if (l->head){
    node_t* node = l->head;
    while(node){
      if (node->value == value){
        return true;
      }
      node=node->next;
    }
  }
  return false; }
elem list_get_elem_at(list_t *l, int index) {
  
  if (l->head){
    node_t* node = l->head;
    int idx = 0;
    while(node){
      if (idx == index){
        return node->value;
      }
      idx++;
      node=node->next;
    }
  }
  
  return -1; 
}
int list_get_index_of(list_t *l, elem value) { 
  
   if (l->head){
    node_t* node = l->head;
    int idx = 0;
    while(node){
      if (node->value == value){
        return idx;
      }
      idx++;
      node=node->next;
    }
  }
  
  return -1; 
}