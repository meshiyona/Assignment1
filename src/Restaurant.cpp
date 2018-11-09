#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Dish.h"
#include "Table.h"
#include "Action.h"
#include "Restaurant.h"
using namespace std;


Restaurant::Restaurant(){
}
Restaurant::Restaurant(const std::string &configFilePath){
    std::string line;
    std::string tablesCapacity = "";
    std::string menu = "";
    int counter = 0;
    int numOfTables = 0;
    ifstream myfile(configFilePath);
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            if ((line[0] != '#') && (!line.empty())) {
                counter++;
                if (counter == 1)
                    numOfTables = atoi(line.c_str());
                else if (counter == 2)
                    tablesCapacity = line;
                else
                    menu = menu + "$" + line;
            }
        }
        myfile.close();
    }
    std::stringstream ss(tablesCapacity);
    int index;
    while (ss >> index) {
        Table* t = new Table(index);
        tables.push_back(t);
        if (ss.peek() == ',')
            ss.ignore();
    }
    std::stringstream menuss(menu);
    std::string ind;
    int counter1 = 1;
    int dishId = 0;
    std::string name;
    DishType code=DishType::VEG;
    std::string price;
    while (ss >> ind) {
        if (counter1 % 3 ==1)
            name = ind;
        if (counter1 % 3 ==2) {
             code = ind;
        }
        if (counter1 % 3 == 0) {
            price = ind;
            Dish* t = new Dish(dishId, name, atoi(price.c_str()), code);
            dishId++;
        }
        counter1++;
        Dish t = new Dish();
        tables.push_back(t);
        if (ss.peek() == ',')
            ss.ignore();
    }
}
void Restaurant::start(){
    open = true;
}
int Restaurant::getNumOfTables() const{
	return tables.size();
}
Table* Restaurant::getTable(int ind){
    if (tables.size() <= ind)
        return nullptr;
    else
	    return tables[ind-1];
}
const std::vector<BaseAction*>& Restaurant::getActionsLog() const{

} // Return a reference to the history of actions
std::vector<Dish>& Restaurant::getMenu(){
	return menu;
}