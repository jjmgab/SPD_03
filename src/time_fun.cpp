#include "time_fun.hpp"

int measure_time(int(*f)(std::vector<t_job>&), std::vector<t_job>* jobs, std::ostream& str) {
	clock_t t;
	int value;

	t = clock();
	value = (*f)(*jobs);
	t = clock()-t;

	str << ((float)t/CLOCKS_PER_SEC) << std::endl;

	return value;
}