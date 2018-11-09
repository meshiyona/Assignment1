#include "Action.h"
#include "Table.h"
#include "Restaurant.h"
#include <iostream>


//Forward declaration

BaseAction::BaseAction(){}
ActionStatus BaseAction::getStatus() const{
};
void BaseAction::act(Restaurant& restaurant){};
std::string BaseAction::toString() const{
    return "";
};
void BaseAction::complete(){}
void BaseAction::error(std::string errorMsg){
    std::cout << errorMsg << std::endl;
}
std::string BaseAction::getErrorMsg() const{
    return "";
}



OpenTable::OpenTable(int id, std::vector<Customer *> &customersList): tableId(id){
    std::vector<Customer *> customers(customersList);

}
void OpenTable::act(Restaurant &restaurant){
    Table* newTable = restaurant.getTable(tableId);
    if (newTable->isOpen() | restaurant.getTable(tableId) == nullptr)
        error("Table does not exist or is already open");
    else
        newTable->openTable();
        for (int i=0; i<customers.size(); i++){
            newTable->addCustomer(customers[i]);
        }
        toString();
};

std::string OpenTable::toString() const{
    std::string cust = "";
    for (int i=0; i<customers.size(); i++) {
        cust = cust + customers[i]->toString() + " ";
    }
    return "open "+ std::to_string(tableId)+" "+cust;
};



Order::Order(int id): tableId(id){

};
void Order::act(Restaurant &restaurant){
    Table* newTable = restaurant.getTable(tableId);
    if (newTable->isOpen() | restaurant.getTable(tableId) == nullptr)
        error("Table does not exist or is already open");
    else
        newTable->order(restaurant.getMenu());
        toString();
};

std::string Order::toString() const{
    return "";
};




MoveCustomer::MoveCustomer(int src, int dst, int customerId): srcTable(src), dstTable(dst), id(customerId){};
void MoveCustomer::act(Restaurant &restaurant){};
std::string MoveCustomer::toString() const{
    return "";
};



Close::Close(int id): tableId(id){};
void Close::act(Restaurant &restaurant){};
std::string Close::toString() const{
    return "";
};



CloseAll::CloseAll(){};
void CloseAll::act(Restaurant &restaurant){};
std::string CloseAll::toString() const{
    return "";
};




PrintMenu::PrintMenu(){};
void PrintMenu::act(Restaurant &restaurant){};
std::string PrintMenu::toString() const{
    return "";
};



PrintTableStatus::PrintTableStatus(int id):tableId(id){};
void PrintTableStatus::act(Restaurant &restaurant){};
std::string PrintTableStatus::toString() const{
    return "";
};



PrintActionsLog::PrintActionsLog(){};
void PrintActionsLog::act(Restaurant &restaurant){};
std::string PrintActionsLog::toString() const{
    return "";
};


BackupRestaurant::BackupRestaurant(){};
void BackupRestaurant::act(Restaurant &restaurant){};
std::string BackupRestaurant::toString() const{
    return "";
};



RestoreResturant::RestoreResturant(){}
void RestoreResturant::act(Restaurant &restaurant){}
std::string RestoreResturant::toString() const{
    return "";
};
