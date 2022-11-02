#include <stdio.h>
//#include "list.c"
#include "list.h"

int main() {
//allocate list
  list_t* l1=list_alloc();

  printf("add to back of list\n");
  list_add_to_back(l1,1);
  list_add_to_back(l1,2);
  list_add_to_back(l1,6);
  list_add_to_back(l1,7);
  list_add_to_back(l1,8);
  list_add_to_back(l1,9);
  printf("Expected:126789 :");
  list_print(l1);

  printf("add to front\n");
  //add to front
  list_add_to_front(l1,1);
  list_add_to_front(l1,2);
  printf("Expected:21126789 :");
  list_print(l1);

  // print list length
  printf("print list length\n");
  printf("Expected:8 :");
  printf("%d\n",list_length(l1));

  //add at index
  printf("add at index\n");
  list_add_at_index(l1, 4,2 );
  list_add_at_index(l1, 5,2 );
  printf("Expected:2154126789 :");
  list_print(l1);

  // remove from back
  printf("remove from back\n");
  printf("%d\n",list_remove_from_back(l1));
  printf("%d\n",list_remove_from_back(l1));
  printf("Expected:21541267 :");
  list_print(l1);

  // remove from front
  printf("remove from front\n");
  printf("%d\n", list_remove_from_front(l1));
  printf("%d\n", list_remove_from_front(l1));
  printf("Expected:541267 :");
  list_print(l1);

// remove at index
  printf("remove at index\n");
  printf("%d\n", list_remove_at_index(l1, 0));
  printf("%d\n", list_remove_at_index(l1, 1));
  printf("Expected:4267 :");
  list_print(l1);

// is in list?
  printf("is in list?\n");
  printf("Expected:true :");
  printf("%s\n", list_is_in(l1,6)?"true":"false");
  printf("Expected:false :");
  printf("%s\n", list_is_in(l1,1)?"true":"false");

// get at index
  printf("get at index\n");
  printf("Expected:4 :");
  printf("%d\n",list_get_elem_at(l1, 0));
  printf("Expected:2 :");
  printf("%d\n",list_get_elem_at(l1,1));

// get index of
  printf("get index of\n");
  printf("Expected:2 :");
  printf("%d\n", list_get_index_of(l1,6));
  printf("Expected:1 :");
  printf("%d\n", list_get_index_of(l1,2));

// free list
printf("free list\n");
list_free(l1);
printf("Expected: :");
list_print(l1);
}