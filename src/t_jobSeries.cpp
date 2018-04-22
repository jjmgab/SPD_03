#include "t_jobSeries.hpp"

void t_jobSeries::print() {

    for (std::vector<t_job>::iterator iter = series.begin(); iter != series.end(); iter++) {
        for (std::vector<int>::iterator it = iter->getJob().begin(); it != iter->getJob().end(); it++) {
            std::cout << *it << "\t";
        }
        std::cout << std::endl;
    }

}