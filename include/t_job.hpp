#ifndef T_JOB_HPP
#define T_JOB_HPP

#include <vector>

class t_job {
    private:
        std::vector<int> steps;
        const int machines;

    public:
        t_job(const int& job_machines) : machines(job_machines) { for (int i = 0; i < job_machines; i++) steps.push_back(0); }
        t_job(t_job& _job) : steps(_job.steps), machines(_job.machines) {}

        int& operator[](const int& index) { return steps.at(index); }
};

#endif