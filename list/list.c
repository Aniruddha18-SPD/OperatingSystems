// list/list.c
// 
// Implementation for linked list.
//
// <Author>

#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

#include "list.h"



list_t *list_alloc() { 
  list_t* list=(list_t*)malloc(sizeof(list_t));
  list -> head=NULL;
  return list;
}

node_t *node_alloc(elem val){
  node_t* new_node=(node_t*)malloc(sizeof(node_t));
  new_node -> value=val;
  new_node -> next=NULL;
  return new_node;
  }

void node_free(node_t *n){
  free(n);
}

void list_free(list_t *l) {
  node_t* temp;
  while (l->head != NULL){
    temp=l->head;
    l->head = temp->next;
    free(temp);
  }
}

void list_print(list_t *l) {
  node_t* curr=l->head;
  while(curr!=NULL){
    printf("%d", curr->value);
    curr=curr->next;
  }
  printf("\n");
}

int list_length(list_t *l) { 
  int count=0;
  node_t* curr=node_alloc(0);
  curr=l->head;
  while(curr!=NULL){
    count+=1;
    curr=curr->next;
  }
  return (count); 
  }

void list_add_to_back(list_t *l, elem value) {
  if (l->head){
    node_t* curr=l->head;
    while(curr->next!=NULL){
    curr=curr->next;
    }
    node_t* new=node_alloc(value);
    curr->next=new;
}
else{
  node_t* new = node_alloc(value);
  if (l->head!=NULL){
    new->next = l->head;
    l->head = new;
  }
  else{
    l->head = new;
  }
}
}

void list_add_to_front(list_t *l, elem value) {
  node_t* new = node_alloc(value);
  if (l->head!=NULL){
    new->next = l->head;
    l->head = new;
  }
  else{
    l->head = new;
  }
}

void list_add_at_index(list_t *l, elem value, int index) {
  if (l->head == NULL || index == 0){
      node_t* new = node_alloc(value);
      if (l->head!=NULL){
        new->next = l->head;
        l->head = new;
        }
      else{
        l->head = new;
        }
  }
  else{
    node_t* curr = l->head;
    node_t* prev = NULL;
    int i = 0;
    while (curr!=NULL && i<index) {
      i+=1;
      prev = curr;
      curr = curr->next;
    }
    if (curr == NULL && i == index){
      list_add_to_back(l, value);
    }
    else if (i==index){
      node_t* new = node_alloc(value);
      new->next = prev->next;
      prev->next = new;
    }
  }
}

elem list_remove_from_back(list_t *l) { 
  if (l->head!=NULL){
    node_t* remove = NULL;
    remove = l->head;
    node_t* prev = NULL;
    while (remove->next) {
      prev = remove;
      remove = remove->next;
    }
    prev->next = remove->next;
    elem val = remove->value;
    node_free(remove);
    return val;
  }
  else{
  return -1; }
  }

elem list_remove_from_front(list_t *l) { 
  if(l->head){
    node_t*remove=NULL;
    remove=l->head;
    l->head=remove->next;
    elem val=remove->value;
    node_free(remove);
    return val;
  }
else{  
  return -1; }
  }

elem list_remove_at_index(list_t *l, int index) { 
  if (index == 0){
    return list_remove_from_front(l);
  }
  if (l->head != NULL){
    node_t* remove = NULL;
    remove=l->head;
    node_t* prev = NULL;
    int i = 0;
    while (remove && i < index) {
      i+=1;
      prev = remove;
      remove = remove->next;
    }
    if (remove == NULL && i == index){
      return list_remove_from_back(l);
    }
    else if (i == index){
      elem var = remove->value;
      prev->next = remove->next;
      node_free(remove);
      return var;
    }
  }
else{
return -1; }
}

bool list_is_in(list_t *l, elem value) { 
  if (l->head==NULL){
    return false;
  }
  else{
    node_t* curr=NULL;
    curr=l->head;
    while (curr!=NULL){
      if (curr->value==value){
        return true;
      }
      curr=curr->next;
    }
  }
  return false; }

elem list_get_elem_at(list_t *l, int index) {
  if (l->head==NULL){
    return -1;
  }
  if (l->head!=NULL){
    node_t* curr = NULL;
    curr=l->head;
    int i = 0;
    while(curr->value){
      if (i == index){
        return curr->value;
    }
      i+=1;
      curr=curr->next;
  }
  }
return -1; 
}

int list_get_index_of(list_t *l, elem value) { 
  if(l->head==NULL){
    return -1;
  }
  if (l->head!=NULL){
    node_t* curr = NULL;
    curr=l->head;
    int i=0;
    while(curr->value){
      if (curr->value==value){
        return i;
      }
      i+=1;
      curr=curr->next;
    }
  }
  else{
  return -1; }
}
