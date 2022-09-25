#include <stdio.h>

#include "list.h"

int main() {
  printf("Tests for linked list\n");

  list_t* list = list_alloc();
  // add to front tests
  list_add_to_front(list, 1);
  list_add_to_front(list, 2);
  list_add_to_front(list, 3);
  list_add_to_front(list, 4);
  list_print(list);
  
  // add to back tests
  list_add_to_back(list, 13);
  list_add_to_back(list, 14);
  list_add_to_back(list, 15);
  list_add_to_back(list, 16);
  list_print(list);
  
  // add at index
  list_add_at_index(list, 11, 4);
  list_add_at_index(list, 12, 5);
  list_add_at_index(list, 12, 50);
  list_add_at_index(list, 12, -1);

  list_print(list);
  
  // remove from back tests
  printf("%d\n", list_remove_from_back(list));
  printf("%d\n", list_remove_from_back(list));
  
  list_print(list);
  
  // remove from front tests
  printf("%d\n", list_remove_from_front(list));
  printf("%d\n", list_remove_from_front(list));
  
  list_print(list);
  
  // remove from index tests
  printf("%d\n", list_remove_at_index(list, 2));
  printf("%d\n", list_remove_at_index(list, 2));
  
  list_print(list);
  
  // is in list tests
  printf("%s\n", list_is_in(list, 0) ? "true" : "false");
  printf("%s\n", list_is_in(list, 10) ? "true" : "false");
  printf("%s\n", list_is_in(list, 1) ? "true" : "false");
  printf("%s\n", list_is_in(list, 12) ? "true" : "false");
  
  list_print(list);
  
  // get at index tests
  printf("%d\n", list_get_elem_at(list, 0));
  printf("%d\n", list_get_elem_at(list, 1) );
  printf("%d\n", list_get_elem_at(list, 3));
  printf("%d\n", list_get_elem_at(list, -10));
  printf("%d\n", list_get_elem_at(list, 10));
  
  list_print(list);
  
  // get index of tests
  printf("%d\n", list_get_index_of(list, 9));
  printf("%d\n", list_get_index_of(list, 10) );
  printf("%d\n", list_get_index_of(list, 11));
  printf("%d\n", list_get_index_of(list, 12));
  printf("%d\n", list_get_index_of(list, 13));
  
  list_print(list);
  
  list_free(list);
  list_print(list);
  
  
  return 0;
}