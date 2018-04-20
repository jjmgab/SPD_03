#ifndef FUNCTIONS_H
#define FUNCTIONS_H


#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <string>
#include <limits>
#include <queue>
#include <cmath>

#include "t_job.hpp"


namespace FlowProblem {

/**
 * Wczytuje dane z podanego pliku do 
 * 
 * @param nazwa pliku
 * @return 
 */
    std::vector<t_job>* load_data(const std::string& filename);

    namespace NEH {

    }

}


#endif //FUNCTIONS_H