#pragma once
#ifndef Data_h
#define Data_h

#include <stdio.h>
#include <vector>
#include <string>

class Data {
private:
	std::string html;
	std::string sign;
	std::string name;
	double low=0;
	double high=0;
	double current=0;
	double chg=0;
	double pChg=0;

public:
	/**
	 * @brief Constructor for a Data object.
	 *
	 * @param NAME The ticker of the company.
	 * @param HTML The html to pull info from.
	 */
	Data(std::string NAME, std::string HTML);

	/**
	 * @brief Picks through the html to find the needed data.
	 */
	void fillData();

	/**
	 * @brief Prints out all the stock data for a company.
	 */
	void printData();
};
#endif /* Data_hpp */