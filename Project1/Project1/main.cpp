#include"iostream"
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include "Data.h"
#define CURL_STATICLIB
#include"curl/curl.h"

#ifdef _DEBUG
# pragma comment(lib,"curl/libcurl_a_debug.lib")

#endif // _DEBUG



class CurlObj {
public:
	/**
	 * @brief Constructor for a curl object.
	 *
	 * @param url The url of the page to scrape.
	 */
	CurlObj(std::string url) {
		std::cout<< "in curl";
		curl = curl_easy_init();
		if (!curl) {
			throw std::string("Curl did not initialize.");
		}

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &CurlObj::curlWriter);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &curlBuffer);
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
		curl_easy_perform(curl);
	};

	static int curlWriter(char* data, int size, int nmemb, std::string *buffer)
	{
		int result = 0;
		if (buffer != NULL) {
			//buffer->assign(data, size * nmemb);
			*buffer += data; // Append instead
			result = size * nmemb;
		}
		return result;
	}
	std::string getData() {
		return curlBuffer;
	}

protected:
	CURL * curl;
	std::string curlBuffer;
};
//credit to stack overflow for help on the CurlObj class

int main() {

	//the tickers of companies
	std::vector<std::string> names;
	std::string numCompaniesString;

	//get number of companies to research
	std::cout << "Enter the number of companies whose stocks you would like to analyze: ";
	int numCompanies = -1;
	while (numCompanies < 0) {
		try {
			std::cin >> numCompanies;
			// = std::stoi(numCompaniesString);
			if (numCompanies < 0) {
				std::cout << "That is not a valid number. Enter any number greater than 0: ";
			}
		}
		catch (std::exception e) {
			std::cout << "That is not a valid number. Enter any number greater than 0: ";
		}
	}

	//enter the wanted companies' tickers
	for (int i = 0; i < numCompanies; ++i) {
		std::string name;
		std::cout << "Enter the ticker symbol of a company: ";
		std::cin >> name;
		std::transform(name.begin(), name.end(), name.begin(), ::toupper);
		names.push_back(name);
	}

	std::cout << "Please wait for your data. This may take a few seconds." << std::endl << std::endl;

	std::vector<Data> dataObjs;

	//get all the data and print it out
	for (size_t i = 0; i < names.size(); i++) {
		std::string name = names[i];
		std::string address = "https://finance.yahoo.com/quote/" + name;
		CurlObj temp(address);
		try {
			std::cout << "in try";
			Data data = Data::Data(name, temp.getData());
			int npp = 1;
			while (npp == 1)
			{
				data.printData();
				std::cin >> npp;
			}
		}
		catch (std::exception e) {
			std::cout << "\n" << name << " is not a valid ticker." << std::endl;
			int npp = 1;
			while (npp == 1)
			{
				
				std::cin >> npp;
			}
		}
	}

	std::cout << std::endl;

	return 0;
}