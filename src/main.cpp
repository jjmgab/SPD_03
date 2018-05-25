#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <vector>
#include <functional>

#include <stdlib.h>

#include <chrono>
#include <iomanip>      // std::setprecision

#include "functions.hpp"
#include "t_job.hpp"
#include "t_jobSeries.hpp"
#include "time_fun.hpp"

int main()
{

	t_jobSeries *jobs, *jobs2;

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


	for (i = 0; i < number_of_files; i++) {

		// wczytuje nazwe pliku
		std::string filename = "";
		file_names >> filename;
		
		// wczytuje dane z pliku
		std::cout << " * " << filename << std::endl;
		std::cout << "loading jobs for SA . . . ";
		jobs = FlowShop::load_data("data/"+filename+".txt");
		std::cout << "loading jobs for NEH . . . ";
		jobs2 = FlowShop::load_data("data/"+filename+".txt");
		std::cout << std::endl;

		loader << filename << " ";
		loader << jobs->cMax() << " ";
		std::cout << "Cmax clear:\t" << jobs->cMax() << std::endl;

		auto start_SA = std::chrono::high_resolution_clock::now();
		jobs->algorithm_SA(100.00f, 0.999f, t_jobSeries::t_SA_choice::SWAP, false);
		auto finish_SA = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed_SA = finish_SA - start_SA;

		std::cout << "Cmax SA:\t" << jobs->cMax() << std::endl;

		auto start_NEH = std::chrono::high_resolution_clock::now();
		jobs2->algorithm_NEH();
		auto finish_NEH = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed_NEH = finish_NEH - start_NEH;

		std::cout << "Cmax NEH:\t" << jobs2->cMax() << std::endl;

		loader << jobs2->cMax() << " ";
		loader << jobs->cMax() << std::endl;
		

		std::cout << "time SA:\t" 	<< elapsed_SA.count() 	<< " s" << std::endl;
		std::cout << "time NEH:\t" 	<< elapsed_NEH.count() 	<< " s" << std::endl;


		delete jobs;
	}


	file_names.close();
	return 0;
}