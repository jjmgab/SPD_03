#include "functions.hpp"

t_jobSeries* FlowShop::load_data(const std::string& filename) {

    t_jobSeries* jobSeries;

    std::string s_buffer;
    int machines = 0,       // liczba maszyn (zadan)
        job_number = 0,     // liczba prac
        buffer = 0;         // bufor do wczytywania danych

    int i, j;

    std::ifstream file;     // plik z danymi

    file.open(filename.c_str(), std::ios::in);
    if (file.is_open()) {
        //file >> s_buffer;     // ignoruj nazwe
        //std::cout << "buffer: " << s_buffer << std::endl;

        file >> job_number;
        file >> machines;

        //std::cout << "job number: " << job_number << " machines: " << machines << std::endl;

        jobSeries = new t_jobSeries(machines, job_number);

        for (i = 0; i < job_number; i++) {
            for (j = 0; j < machines; j++) {
                file >> buffer >> buffer; // ignoruj numer zadania i wczytaj czas
                jobSeries->stepAt(i, j) = buffer;
            }
        }

    } else exit(-2);
    file.close();

    return jobSeries;
}