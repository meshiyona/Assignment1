#include <string>
#include <vector>
#include <sstream>
#include <Tools.h>
// may
Tools::Tools(){};
DishType Tools::enumCheck(std::string str) {
    DishType type;
    if (str == "VEG")
        type = VEG;
    if (str == "SPC")
        type = SPC;
    if (str == "ALC")
        type = ALC;
    if (str == "BVG")
        type = BVG;
    return type;
};

std::vector<std::string> Tools::split(std::string str, char delimiter){
    std::vector<std::string> vect;
    std::stringstream ss(str);
    std::string i;
    while (ss >> i) {
        vect.push_back(i);
        if (ss.peek() == delimiter)
            ss.ignore();
    }
    return vect;
};

std::vector<Customer*> Tools::customerByType(std::vector<std::string> input){
    int counter=0;
    std::vector<Customer*> customersList;
    for (int i=2; i<input.size(); i++) {
        std::vector<std::string> nameAndType = split(input[i], ',');
        std::string name = nameAndType[0];
        std::string type = nameAndType[1];
        if (nameAndType[1] == "veg") {
            VegetarianCustomer veg = VegetarianCustomer(name, counter);
            customersList.push_back(&veg);
        }
        if (nameAndType[1] == "spc") {
            SpicyCustomer spc = SpicyCustomer(name, counter);
            customersList.push_back(&spc);
        }
        if (nameAndType[1] == "alc") {
            AlchoholicCustomer alc = AlchoholicCustomer(name, counter);
            customersList.push_back(&alc);
        } else {
            CheapCustomer chp = CheapCustomer(name, counter);
            customersList.push_back(&chp);
        }
        counter++;
    }
    return customersList;
};

int Tools::getBill(std::vector<OrderPair> orderList){
    int bill = 0;
    for(int i=0; i< orderList.size(); i++) {
        bill = bill + orderList[i].second.getPrice();
    }
    return bill;
};
