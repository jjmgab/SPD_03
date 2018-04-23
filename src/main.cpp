#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <vector>
#include <functional>

#include <stdlib.h>

#include "functions.hpp"
#include "t_job.hpp"
#include "t_jobSeries.hpp"
#include "time_fun.hpp"


int main() {

	t_jobSeries* jobs;
	std::string filename = "ta0001.txt";

	std::cout << "loading" << std::endl;
	jobs = FlowShop::load_data(filename);
	std::cout << "printing" << std::endl;
	jobs->print();
	std::cout << "isSeriesDone: " << (jobs->isSeriesDone() ? "true" : "false") << std::endl;
	std::cout << "Cmax: " << jobs->cMax() << std::endl;


	// std::string names = "data/names.txt",	// nazwa listy nazw plikow
	// 			output = "output.txt";		// nazwa pliku z danymi wyjsciowymi

	// std::ifstream file_names;				// strumien wejsciowy do wczytywania nazw plikow

	// std::filebuf file;						// plik z danymi wyjsciowymi
	// file.open(output.c_str(), std::ios::out);
	// std::ostream loader(&file);				// strumien wyjsciowy, zamiast std::cout

	// int number_of_files = 0,				// potrzebne przy wczytywaniu danych z plikow, l. plikow
	// 	i;									// indeks do petli

	// // otwarcie listy nazw plikow
	// file_names.open(names.c_str());
	// if (file_names.is_open()) {
	// 	file_names >> number_of_files;
	// }
	// else exit(-1);
	
 
	// file_names.close();

	return 0;
}