#include "Table.h"
#include <iostream>


Table::Table(int t_capacity): capacity(t_capacity){
    std::vector<Customer*> customersList;
};

int Table::getCapacity() const{
    return capacity;
};

void Table::addCustomer(Customer* customer){
    if (customersList.size()==capacity)
        std::cout << "no more room" << std::endl;
    else
        customersList.push_back(customer);
};

void Table::removeCustomer(int id){
    for (int i=0; i<customersList.size(); i++){
        if (customersList[i]->getId()==id) {
            customersList.erase(customersList.begin()+(i-1));
        }
    }
};

Customer* Table::getCustomer(int id){
    for (int i=0; i<customersList.size(); i++){
        if (customersList[i]->getId()==id) {
            return customersList[i];
        }
    }
};



std::vector<Customer*>& Table::getCustomers(){
    return customersList;
};
std::vector<OrderPair>& Table::getOrders(){
    return orderList;
};
void Table::order(const std::vector<Dish> &menu) {
    for (int i = 0; i < customersList.size(); i++) {
        customersList[i]->order(menu);
    }
};

void Table::openTable(){
    open = true;
};
void Table::closeTable(){
    open = false;
};
int Table::getBill(){
    int bill=0;
    for (int i = 0; i < orderList.size(); i++) {
        bill = bill + orderList[i].second.getPrice();
    }
    return bill;
};
bool Table::isOpen(){
    return open;
};

