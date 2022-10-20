#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main() {
  printf("Test cases for linked list implementation\n");
  list_t* a = list_alloc();
  list_add_to_front(a,1);
  list_add_to_front(a,3);
  list_add_to_back(a,2);
  list_add_at_index(a,4,1);
  list_print(a);
  printf("%d\n",list_length(a));
  printf("Remove\n");
  printf("%d\n",list_remove_from_back(a));
   printf("%d\n",list_remove_from_front(a));
  printf("%d\n",list_remove_from_back(a));
  // printf("%d\n",list_remove_from_front(a));
  printf("%d\n",list_length(a));
  printf("Check\n");
  printf("%s\n", list_is_in(a,5)?"True":"False");
  printf("%s\n", list_is_in(a,4)?"True":"False");
  printf("%s\n", list_is_in(a,7)?"True":"False");
  list_add_to_back(a,6);
  printf("%d\n", list_get_elem_at(a,1));
  printf("%d\n", list_get_elem_at(a,0));
  printf("Index\n");
  printf("%d\n", list_get_index_of(a,6));
  printf("%d\n", list_get_index_of(a,4));
  printf("Remove at index\n");
  printf("%d\n",list_remove_at_index(a,1));
  return 0;
}