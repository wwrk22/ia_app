#include "IA_AppConfig.h"

#include <IA_Metric/revenue.h>
#include <IA_Metric/cost_of_goods_sold.h>

#include <iostream>


int main([[maybe_unused]]int argc, [[maybe_unused]]char* argv[]) {
	std::cout << "Investment Analysis version "
		<< IA_App_VERSION_MAJOR << "."
		<< IA_App_VERSION_MINOR << "."
		<< IA_App_VERSION_PATCH << '\n';

	ia::Revenue r(2023, 100, 5);
	std::cout << r.year_ << ", " << r.value_ << ", " << r.annual_growth_ << '\n';

	ia::CostOfGoodsSold c(2023, 20, 3);
	std::cout << c.year_ << ", " << c.value_ << ", " << c.annual_growth_ << '\n';


	return 0;
}
