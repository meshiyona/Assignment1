#include <vector>
#include <string>
#include "Dish.h"
#include "Customer.h"

Customer::Customer(std::string c_name, int c_id): name(c_name), id(c_id){}

std::vector<int> Customer::order(const std::vector<Dish> &menu){
    std::vector<int> dishesId;
}
std::string Customer::toString() const{
	return "";
}
std::string Customer::getName() const{
	return "";
}
int Customer::getId() const{
	return 1;
}

VegetarianCustomer::VegetarianCustomer(std::string name, int id): Customer::Customer(name,id){}

std::vector<int> VegetarianCustomer::order(const std::vector<Dish> &menu){
	std::vector<int> v;
	return v;
}
std::string VegetarianCustomer::toString() const{
	return "";
}

CheapCustomer::CheapCustomer(std::string name, int id): Customer::Customer(name,id){}
std::vector<int> CheapCustomer::order(const std::vector<Dish> &menu){
	std::vector<int> v;
	return v;
}
std::string CheapCustomer::toString() const{
	return "";
}

SpicyCustomer::SpicyCustomer(std::string name, int id): Customer::Customer(name,id){}
std::vector<int> SpicyCustomer::order(const std::vector<Dish> &menu){
	std::vector<int> v;
	return v;
}
std::string SpicyCustomer::toString() const{
	return "";
}


AlchoholicCustomer::AlchoholicCustomer(std::string name, int id): Customer::Customer(name,id){}
std::vector<int> AlchoholicCustomer::order(const std::vector<Dish> &menu){
	std::vector<int> v;
	return v;
}
std::string AlchoholicCustomer::toString() const{
	return "";
}
