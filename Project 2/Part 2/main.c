#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#include "BENSCHILLIBOWL.h"



// help from Ujjwal
// worked together with Anirudd



// Feel free to play with these numbers! This is a great way to
// test your implementation.
#define BENSCHILLIBOWL_SIZE 100
#define NUM_CUSTOMERS 90
#define NUM_COOKS 10
#define ORDERS_PER_CUSTOMER 3
#define EXPECTED_NUM_ORDERS NUM_CUSTOMERS * ORDERS_PER_CUSTOMER

// Global variable for the restaurant.
BENSCHILLIBOWL *bcb;
int total=0;
/**
 * Thread funtion that represents a customer. A customer should:
 *  - allocate space (memory) for an order.
 *  - select a menu item.
 *  - populate the order with their menu item and their customer ID.
 *  - add their order to the restaurant.
 */
void* BENSCHILLIBOWLCustomer(void* tid) {
  int customer_id = *((int*) tid);
  for(int i=0; i<ORDERS_PER_CUSTOMER;i++){
    Order* order=(Order*)malloc(sizeof(Order));
    order->menu_item=PickRandomMenuItem();
    order->customer_id=customer_id;
    order->next=NULL;
    AddOrder(bcb,order);
    total++;
    printf("Customer nr.%d added Order nr.%d\n", customer_id,total);
  }
}

/**
 * Thread function that represents a cook in the restaurant. A cook should:
 *  - get an order from the restaurant.
 *  - if the order is valid, it should fulfill the order, and then
 *    free the space taken by the order.
 * The cook should take orders from the restaurants until it does not
 * receive an order.
 */
void* BENSCHILLIBOWLCook(void* tid) {
  int cook_id = *((int*) tid);
	int orders_fulfilled = 0;
  Order *order=GetOrder(bcb);
  while(order){
    orders_fulfilled+=1;
    free(order);
    order=GetOrder(bcb);
    }
  printf("Cook #%d fulfilled %d orders\n", cook_id, orders_fulfilled);
  return NULL;
}

/**
 * Runs when the program begins executing. This program should:
 *  - open the restaurant
 *  - create customers and cooks
 *  - wait for all customers and cooks to be done
 *  - close the restaurant.
 */
int main() {
    srand(time(NULL));
    bcb=OpenRestaurant(BENSCHILLIBOWL_SIZE, EXPECTED_NUM_ORDERS);
    bcb->expected_num_orders=EXPECTED_NUM_ORDERS;
    pthread_t customer[NUM_CUSTOMERS];
    pthread_t cook[NUM_COOKS];
    int cu[NUM_CUSTOMERS];
    int co[NUM_COOKS];
    for(int i=0; i<NUM_CUSTOMERS;i++){
      cu[i]=i+1;
      pthread_create(&customer[i],NULL,&BENSCHILLIBOWLCustomer,&cu[i]);
    }
    for(int i=0; i<NUM_COOKS;i++){
      co[i]=i+1;
      pthread_create(&cook[i],NULL,&BENSCHILLIBOWLCook,&co[i]);
    }
    for(int i=0; i<NUM_CUSTOMERS;i++){
      pthread_join(customer[i],NULL);
    }
    for(int i=0; i<NUM_COOKS;i++){
      pthread_join(cook[i],NULL);
    }  
  CloseRestaurant(bcb);
  return 0;
}