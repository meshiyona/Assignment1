#include <vector>
#include <string>
#include "Dish.h"
#include "Table.h"
#include "Action.h"
#include "Restaurant.h"


Restaurant::Restaurant(){
}
Restaurant::Restaurant(const std::string &configFilePath){}
void Restaurant::start(){}
int Restaurant::getNumOfTables() const{
	return tables.size();
}
Table* Restaurant::getTable(int ind){
    if (tables.size() <= ind)
        return nullptr;
    else
	    return tables[ind];
}
const std::vector<BaseAction*>& Restaurant::getActionsLog() const{

} // Return a reference to the history of actions
std::vector<Dish>& Restaurant::getMenu(){
	std::vector<Dish> v;
	return v;
}