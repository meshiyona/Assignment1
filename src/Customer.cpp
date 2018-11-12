#include <vector>
#include <string>
#include "Dish.h"
#include "Customer.h"

Customer::Customer(std::string c_name, int c_id) : name(c_name), id(c_id) {}

std::vector<int> Customer::order(const std::vector<Dish> &menu) {

}

std::string Customer::toString() const {
    return "";
}

std::string Customer::getName() const {
    return name;
}

int Customer::getId() const {
    return id;
}

VegetarianCustomer::VegetarianCustomer(std::string name, int id) : Customer::Customer(name, id) {}

std::vector<int> VegetarianCustomer::order(const std::vector<Dish> &menu) {
    int bvgID = -1;
    int vegId = -1;
    int price = 0;
    for (int i = 0; i < menu.size(); i++) {
        if (menu[i].getType() == VEG && vegId == -1) {
            vegId = menu[i].getId();
        }
        if (menu[i].getType() == BVG && price < menu[i].getPrice()) {
            price = menu[i].getPrice();
            bvgID = menu[i].getId();
        }
    }
    if (bvgID != -1)
        dishes.push_back(bvgID);
    if (vegId != -1)
        dishes.push_back(vegId);
    return dishes;
}

std::string VegetarianCustomer::toString() const {
    return "";
}


CheapCustomer::CheapCustomer(std::string name, int id) : Customer::Customer(name, id) {}

std::vector<int> CheapCustomer::order(const std::vector<Dish> &menu) {
    int dishID = -1;
    int price = menu[0].getPrice();
    if (dishes.empty()) {
        for (int i = 1; i < menu.size(); i++) {
            if (price > menu[i].getPrice()) {
                price = menu[i].getPrice();
                dishID = menu[i].getId();
            }
        }
        if (dishID != -1)
            dishes.push_back(dishID);
    }
    return dishes;
}

std::string CheapCustomer::toString() const {
    return "";
}

SpicyCustomer::SpicyCustomer(std::string name, int id) : Customer::Customer(name, id) {}

std::vector<int> SpicyCustomer::order(const std::vector<Dish> &menu) {
    int price = 0;
    int priceBVG = -1;
    int spcID = -1;
    if (dishes.empty()) {
        for (int i = 0; i < menu.size(); i++) {
            if (menu[i].getType() == SPC && price < menu[i].getPrice()) {
                spcID = menu[i].getId();
                price = menu[i].getPrice();
            }
        }
        if (spcID != -1)
            dishes.push_back(spcID);
    } else {
        for (int i = 0; i < menu.size(); i++) {
            if (menu[i].getType() == BVG) {
                if (priceBVG == -1) {
                    priceBVG = menu[i].getPrice();
                    spcID = menu[i].getId();
                }
                else if (priceBVG > menu[i].getPrice()) {
                    priceBVG = menu[i].getPrice();
                    spcID = menu[i].getId();
                }
            }
        }
        if (priceBVG != -1)
            dishes.push_back(spcID);
    }
    return dishes;
}

std::string SpicyCustomer::toString() const {
    return "";
}


AlchoholicCustomer::AlchoholicCustomer(std::string name, int id) : Customer::Customer(name, id) {

}

std::vector<int> AlchoholicCustomer::order(const std::vector<Dish> &menu) {
    int price = -1;
    int alcID = -1;
    int dishPrice;
    int index = 0;
    if (alcVec.empty()) {
        for (int i = 0; i < menu.size(); i++) {
            if (menu[i].getType() == ALC) {
                alcVec.push_back(menu[i]);
                if (price == -1) {
                    price = menu[i].getPrice();
                    alcID = menu[i].getId();
                    index = i;
                } else if (price > menu[i].getPrice()) {
                    price = menu[i].getPrice();
                    alcID = menu[i].getId();
                    index = i;
                }
            }
        }
        if (alcID != -1) {
            dishes.push_back(alcID);
            alcVec.erase(alcVec.begin() + index);
        }
    } else {
        dishPrice = alcVec[0].getPrice();
        for (int i = 1; i < alcVec.size(); i++) {
            if (dishPrice > alcVec[i].getPrice()) {
                dishPrice = alcVec[i].getPrice();
                alcID = menu[i].getId();
                index = i;
            }
        }
        if (alcID != -1) {
            dishes.push_back(alcID);
            alcVec.erase(alcVec.begin() + index);
        }
    }
    return dishes;
}

std::string AlchoholicCustomer::toString() const {
    return "";
}
