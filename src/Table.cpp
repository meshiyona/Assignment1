#include "Table.h"
#include <iostream>


Table::Table(int t_capacity){
};
int Table::getCapacity() const{
    return capacity;
};
void Table::addCustomer(Customer* customer){
    customersList.push_back(customer);
};
void Table::removeCustomer(int id){
};

Customer* Table::getCustomer(int id){};
std::vector<Customer*>& Table::getCustomers(){
    return customersList;
};
std::vector<OrderPair>& Table::getOrders(){
    return orderList;
};
void Table::order(const std::vector<Dish> &menu){};
void Table::openTable(){};
void Table::closeTable(){};
int Table::getBill(){
    return 1;
};
bool Table::isOpen(){
    return open;
};

