#include "Action.h"
#include "Table.h"
#include "Restaurant.h"
#include "Tools.h"
#include <iostream>


//Forward declaration
extern Restaurant *backup;

BaseAction::BaseAction() {
    status = PENDING;
}

BaseAction::BaseAction(BaseAction &other) : errorMsg(other.errorMsg), status(other.status) {};

BaseAction::~BaseAction() {
    delete &errorMsg;
    delete &status;
};

BaseAction &BaseAction::operator=(BaseAction &other) {
    if (this != &other) {
        errorMsg = other.errorMsg;
        status = other.status;
    }
};

ActionStatus BaseAction::getStatus() const {
    return status;
};

void BaseAction::act(Restaurant &restaurant) {};

std::string BaseAction::toString() const {
    return " ";
};

void BaseAction::complete() {
    status = COMPLETED;
}

void BaseAction::error(std::string errorMsg) {
    this->errorMsg = errorMsg;
    status = ERROR;
}

std::string BaseAction::getErrorMsg() const {
    return errorMsg;
}


OpenTable::OpenTable(int
                     id, std::vector<Customer *> &customersList) : tableId(id) {
}

OpenTable::OpenTable(OpenTable &other) : tableId(other.tableId), customers(other.customers) {};

OpenTable::~OpenTable() {
    delete &tableId;
    for (int i = 0; i < customers.size(); ++i) {
        delete customers[i];
    }
};

void OpenTable::act(Restaurant &restaurant) {
    Table *newTable = restaurant.getTable(tableId);
    if (newTable->isOpen() | restaurant.getTable(tableId) == nullptr)
        error("Table does not exist or is already open");
    else
        newTable->openTable();
    for (int i = 0; i < customers.size(); i++) {
        newTable->addCustomer(customers[i]);
    }
    toString();
};

std::string OpenTable::toString() const {
    std::string str = "";
    for (int i = 0; i < customers.size(); i++) {
        str = str + customers[i]->toString() + " ";
    }
    if (this->getStatus() == ERROR)
        return "open " + std::to_string(tableId) + " " + str + "Error: " + getErrorMsg();
    if (this->getStatus() == COMPLETED)
        return "open " + std::to_string(tableId) + " " + str + "Completed";
    else
        return "Pending";
};


Order::Order(int
             id) : tableId(id) {

};

Order::Order(Order &other) : tableId(other.tableId) {};

Order::~Order() {
    delete &tableId;
};


void Order::act(Restaurant &restaurant) {
    Table *newTable = restaurant.getTable(tableId);
    if (newTable->isOpen() | restaurant.getTable(tableId) == nullptr)
        error("Table does not exist or is already open");
    else
        newTable->order(restaurant.getMenu());
    this->toString();
};

std::string Order::toString() const {
    if (this->getStatus() == ERROR)
        return "order " + std::to_string(tableId) + " Error: " + getErrorMsg();
    if (this->getStatus() == COMPLETED)
        return "order " + std::to_string(tableId) + " Completed";
    else
        return "Pending";
};


MoveCustomer::MoveCustomer(int
                           src, int
                           dst, int
                           customerId) : srcTable(src), dstTable(dst), id(customerId) {};


MoveCustomer::MoveCustomer(MoveCustomer &other) : srcTable(other.srcTable), dstTable(other.dstTable), id(other.id) {};

MoveCustomer::~MoveCustomer() {
    delete &srcTable;
    delete &dstTable;
    delete &id;
};


void MoveCustomer::act(Restaurant &restaurant) {
    Table *dsTable = restaurant.getTable(dstTable);
    Table *srTable = restaurant.getTable(srcTable);
    if (dsTable == nullptr || !dsTable->isOpen() || srTable == nullptr || !srTable->isOpen()
        || srTable->getCustomer(id) == nullptr || dsTable->getCustomers().size() == dsTable->getCapacity()) {
        error("Cannot move customer");
    } else {
        dsTable->addCustomer(srTable->getCustomer(id)); // add to dest table
//        src vector
//        dest vector push customer orders
//        tmp vector = orders that are not belong to this customer
//        then clear src vector
//          push back from tmp to src

        for (int i = 0; i < srTable->getOrders().size(); i++) { // move all dishes to dst table
            if (srTable->getOrders()[i].first == id) {
                dsTable->getOrders().push_back(srTable->getOrders()[i]);
                srTable->getOrders().erase(srTable->getOrders().begin() + i); // remove dished from src table
            }
        }
        srTable->removeCustomer(id); // remove customer from src table
    }
};

std::string MoveCustomer::toString() const {
    if (this->getStatus() == ERROR)
        return "move " + std::to_string(srcTable) + " " + std::to_string(dstTable) + " " + std::to_string(id) +
               " Error: " + getErrorMsg();
    if (this->getStatus() == COMPLETED)
        return "move " + std::to_string(srcTable) + " " + std::to_string(dstTable) + " " + std::to_string(id) +
               " Completed";
    else
        return "Pending";
};


Close::Close(int
             id) : tableId(id) {};

Close::Close(Close &other) : tableId(other.tableId) {};

Close::~Close() {
    delete &tableId;
};

void Close::act(Restaurant &restaurant) {
    int bill;
    Table *tableToClose = restaurant.getTable(tableId);
    if (tableToClose == nullptr || !tableToClose->isOpen()) {
        error("Table does not exist or is not open");
    } else {
        Tools *tools = new Tools();
        bill = tools->getBill(tableToClose->getOrders());
        std::cout << "Table " << std::to_string(tableId) << " was closed. Bill " << bill << "NIS" << std::endl;
        tableToClose->getOrders().clear();
        tableToClose->getCustomers().clear();
    }
};

std::string Close::toString() const {
    if (this->getStatus() == ERROR)
        return "Error: " + getErrorMsg();
    if (this->getStatus() == COMPLETED)
        return "Table " + std::to_string(tableId) + " Completed";
    else
        return "Pending";
};


CloseAll::CloseAll() {};

void CloseAll::act(Restaurant &restaurant) {
    std::vector<Table *> tables = restaurant.getTables();
    for (int i = 0; i < tables.size(); i++) {
        if (tables[i]->isOpen()) {
            Close *close = new Close(i);
            close->act(restaurant);
            tables[i]->closeTable();
        }
    }

};

std::string CloseAll::toString() const {
    return "";
};


PrintMenu::PrintMenu() {
};

void PrintMenu::act(Restaurant &restaurant) {
    std::vector<Dish> menu = restaurant.getMenu();
    for (int i = 0; i < menu.size(); i++) {
        std::cout << menu[i].getName() << " " << menu[i].getType() << " " << menu[i].getPrice() << "NIS"
                  << std::endl;
    }
};

std::string PrintMenu::toString() const {
    return "menu completed";
};


PrintTableStatus::PrintTableStatus(int
                                   id) : tableId(id) {};

PrintTableStatus::PrintTableStatus(PrintTableStatus &other) : tableId(other.tableId) {};

PrintTableStatus::~PrintTableStatus() {
    delete &tableId;
};

void PrintTableStatus::act(Restaurant &restaurant) {
    Table *table = restaurant.getTable(tableId);
    if (table->isOpen()) {
        std::cout << "Table " << tableId << " status: open" << std::endl;
        std::cout << "Customers: " << std::endl;
        std::vector<Customer *> customersList = restaurant.getTable(tableId)->getCustomers();
        std::vector<OrderPair> orderList = restaurant.getTable(tableId)->getOrders();
        for (int i = 0; i < customersList.size(); ++i) {
            std::cout << customersList[i]->getId() << " " << customersList[i]->getName() << std::endl;
        }
        std::cout << "Orders: " << std::endl;
        for (int i = 0; i < orderList.size(); ++i) {
            std::cout << orderList[i].second.getName() << " " << orderList[i].second.getPrice() << "NIS "
                      << orderList[i].first << std::endl;
        }
        std::cout << "Current bill: " << table->getBill() << "NIS" << std::endl;
    } else {
        std::cout << "Table " << tableId << " status: closed" << std::endl;
    }
};

std::string PrintTableStatus::toString() const {
    return "Status " + std::to_string(tableId) + " completed";
};


PrintActionsLog::PrintActionsLog() {};

void PrintActionsLog::act(Restaurant &restaurant) {
    std::vector<BaseAction *> actions = restaurant.getActionsLog();
    for (int i = 0; i < actions.size(); ++i) {
        if (actions[i]->getStatus() == ERROR)
            std::cout << actions[i]->toString() << std::endl;
        else {
            std::cout << actions[i]->toString() << " " << actions[i]->getStatus() << std::endl;
        }
    }
};

std::string PrintActionsLog::toString() const {
    return " ";
};


BackupRestaurant::BackupRestaurant() {};

void BackupRestaurant::act(Restaurant &restaurant) {
    if (backup == nullptr)
        backup = new Restaurant(restaurant);
    else
        backup = &restaurant;
};

std::string BackupRestaurant::toString() const {
    return "backup completed";
};


RestoreResturant::RestoreResturant() {}

void RestoreResturant::act(Restaurant &restaurant) {
    if (backup != nullptr)
        restaurant = *backup;
    else
        error("No backup available");
}

std::string RestoreResturant::toString() const {
    if (this->getStatus() == ERROR)
        return "Error: " + getErrorMsg();
    if (this->getStatus() == COMPLETED)
        return "backup completed";
    else
        return "Pending";
};
