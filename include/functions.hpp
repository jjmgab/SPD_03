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
#include "t_jobSeries.hpp"

namespace FlowShop {

/**
 * Wczytuje dane z podanego pliku do 
 * 
 * @param nazwa pliku
 * @return 
 */
    t_jobSeries* load_data(const std::string&);

}


#endif //FUNCTIONS_H