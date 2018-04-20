#ifndef TIMEF_H
#define TIMEF_H

#include <iostream>
#include <vector>
#include <ctime>

#include "t_job.hpp"

/**
 * Mierzy i przesyla do strumienia wyjsciowego czas
 * rzeczywisty wykonywania sie funkcji implementujacej
 * dany algorytm szeregowania zadan.
 * 
 * @param wskaznik na funkcje szeregujaca
 * @param wskaznik na wektor zadan
 * @param referencja na strumien wyjsciowy
 * @return czas wykonywania sie szeregu zadan
 */
int measure_time(int(*f)(std::vector<t_job>&), std::vector<t_job>* jobs, std::ostream& str);

#endif // TIME_H