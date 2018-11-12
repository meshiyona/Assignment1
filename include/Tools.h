#ifndef TOOLS_H_
#define TOOLS_H_

#include <string>
#include <vector>
#include <sstream>
#include "Dish.h"
#include "Customer.h"

typedef std::pair<int, Dish> OrderPair;

class Tools{
public:
    Tools();
    std::vector<std::string> split(std::string str, char delimiter);
    DishType enumCheck(std::string str);
    std::vector<Customer*> customerByType(std::vector<std::string> input);
    int getBill(std::vector<OrderPair> orderList);
};


#endif