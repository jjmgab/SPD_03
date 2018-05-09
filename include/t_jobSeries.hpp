#ifndef T_JOBSERIES_HPP
#define T_JOBSERIES_HPP

#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

#include "t_job.hpp"

class t_jobSeries {
    private:
        std::vector<t_job> series;
        int job_number;
        int machines;

        const int cMax(std::vector<t_job>&) const;

    public:
        t_jobSeries(const int& _machines, const int& _job_number) :
            machines(_machines), job_number(_job_number) {
                for (int i = 0; i < _job_number; i++) {
                    t_job job(_machines);
                    series.push_back(t_job(_machines));
                }
            }

        t_jobSeries(t_jobSeries& jobSeries) :
            series(jobSeries.series), job_number(jobSeries.job_number), machines(jobSeries.machines) {}

        t_job& operator[](const int& index) { return series.at(index); }
        int& stepAt(const int& i, const int& j) { return series.at(i).getJob().at(j); }
        t_job& jobAt(const int& i) { return series.at(i); }

        bool isSeriesDone();

        void print();

        const int cMax();
        

        t_jobSeries& algorithm_NEH();
};

#endif