#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Dish.h"
#include "Table.h"
#include "Action.h"
#include "Tools.h"
#include "Restaurant.h"
using namespace std;


Restaurant::Restaurant(){
}
Restaurant::Restaurant(const std::string &configFilePath){
    std::string line, name, code, price, ind, menuList, tablesCapacity;
    int counter = 0;
    ifstream myfile(configFilePath);
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            if ((line[0] != '#') && (!line.empty())) {
                counter++;
                if (counter == 1)
                    numOfTables = std::stoi(line);
                else if (counter == 2)
                    tablesCapacity = line;
                else
                    menuList = menuList + "$" + line;
            }
        }
        myfile.close();
    }
    Tools *tools =  new Tools();
    std::vector<std::string> vect = tools->split(tablesCapacity, ',');
    for (int m=0; m<vect.size(); m++) {
        Table *t = new Table(atoi(vect[m].c_str()));
        tables.push_back(t);
    }
    std::stringstream menuss(menuList);
    int dishId = 0;
    std::vector<std::string> vect1 = tools->split(menuList, ',');
    for (int m=1; m<vect1.size(); m++) {
        if (m % 3 == 1)
            name = vect1[m];
        if (m % 3 == 2)
            code = vect1[m];
        if (m % 3 == 0) {
            price = vect1[m];
            menu.emplace_back(new Dish(dishId, name, std::stoi(price), tools->enumCheck(code)));
            dishId++;

        }
    }
    start();
}
Restaurant::Restaurant(Restaurant& other){
    open = other.open;
    numOfTables = other.numOfTables;
    tables= other.tables;
    menu = other.menu;
    actionsLog =  other.actionsLog;
};

Restaurant& Restaurant::operator=(Restaurant& other){
    if (this != &other){
        open = other.open;
        numOfTables = other.numOfTables;
        tables= other.tables;
        menu = other.menu;
        actionsLog =  other.actionsLog;
    }
};


void Restaurant::start() {
    open = true;
    string mystr, name;
    int counter = 0;
    getline(cin, mystr);
    Tools *tools = new Tools();
    while (mystr != "closeall") {
        std::vector<std::string> input = tools->split(mystr, ' ');
        if (input[0] == "open") {
            std::vector<Customer *> customersList = tools->customerByType(input);
            OpenTable *open = new OpenTable(std::stoi(input[1]), customersList);
            actionsLog.push_back(open);
            open->act(*this);
        }
        if (input[0] == "order") {
            Order *order = new Order(std::stoi(input[1]));
            actionsLog.push_back(order);
            order->act(*this);
        }
        if (input[0] == "move") {
            MoveCustomer *move = new MoveCustomer(std::stoi(input[1]), std::stoi(input[2]), std::stoi(input[3]));
            actionsLog.push_back(move);
            move->act(*this);
        }
        if (input[0] == "status") {
            PrintTableStatus *status = new PrintTableStatus(std::stoi(input[1]));
            actionsLog.push_back(status);
        }
        if (input[0] == "backup") {
            BackupRestaurant *backup = new BackupRestaurant();
            actionsLog.push_back(backup);
        }
        if (input[0] == "log") {
            PrintActionsLog *log = new PrintActionsLog();
        }
        if (input[0] == "restore") {
            RestoreResturant *restore = new RestoreResturant();
            actionsLog.push_back(restore);
        }
    }
    CloseAll *CA = new CloseAll();
    CA->act(*this);
    open = false;
};
int Restaurant::getNumOfTables() const{
	return numOfTables;
}
Table* Restaurant::getTable(int ind){
    if (tables.size() <= ind)
        return nullptr;
    else
	    return tables[ind];
}
const std::vector<BaseAction*>& Restaurant::getActionsLog() const{
    return actionsLog;
} // Return a reference to the history of actions
std::vector<Dish>& Restaurant::getMenu(){
	return menu;
}
std::vector<Table*> Restaurant::getTables(){
    return tables;
};
