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

	t_jobSeries jobs(3, 5);
	
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 3; x++) {
			std::cout << jobs[y][x] << "\t";
			if (x == 2) std::cout << std::endl;
		}
	}

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