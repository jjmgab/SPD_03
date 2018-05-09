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

int main()
{

	t_jobSeries *jobs;
	// std::string filename = "ta0000.txt";

	// std::cout << "loading" << std::endl;
	// jobs = FlowShop::load_data(filename);

	// jobs->print();

	// std::cout << "Cmax after loading = " << jobs->cMax() << std::endl;
	// jobs->alogrithm_NEH();
	// std::cout << "Cmax after NEH algorithm = " << jobs->cMax() << std::endl;

	std::string names = "data/names.txt", 		// nazwa listy nazw plikow
		output = "output.txt";			  		// nazwa pliku z danymi wyjsciowymi

	std::ifstream file_names; 					// strumien wejsciowy do wczytywania nazw plikow

	std::filebuf file; 							// plik z danymi wyjsciowymi
	file.open(output.c_str(), std::ios::out);
	std::ostream loader(&file); 				// strumien wyjsciowy, zamiast std::cout

	int number_of_files = 0, 					// potrzebne przy wczytywaniu danych z plikow, l. plikow
		i;					 					// indeks do petli

	// otwarcie listy nazw plikow
	file_names.open(names.c_str());
	if (file_names.is_open())
	{
		file_names >> number_of_files;
	}
	else
		exit(-1);

	loader << "filename" << std::endl;
	loader << "Cmax before alg." << std::endl;
	loader << "Cmax after alg." << std::endl;
	loader << "clock time of alg., s" << std::endl << std::endl;

	for (i = 0; i < number_of_files; i++) {

		// wczytuje nazwe pliku
		std::string filename = "";
		file_names >> filename;
		
		// wczytuje dane z pliku
		std::cout << " * " << filename << std::endl;
		jobs = FlowShop::load_data("data/"+filename+".txt");


		clock_t t;

		loader << filename << std::endl;
		loader << jobs->cMax() << std::endl;
		std::cout << jobs->cMax() << std::endl;

		t = clock();
		jobs->algorithm_NEH();
		t = clock()-t;

		loader << jobs->cMax() << std::endl;
		loader << ((float)t/CLOCKS_PER_SEC) << std::endl;
		std::cout << ((float)t/CLOCKS_PER_SEC) << " s" << std::endl;


		delete jobs;
	}


	file_names.close();
	return 0;
}