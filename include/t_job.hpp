#ifndef T_JOB_HPP
#define T_JOB_HPP

#include <vector>

class t_job {
    private:
        std::vector<int> steps;
        int machines;

    public:
        t_job(const int& job_machines) : machines(job_machines) { for (int i = 0; i < job_machines; i++) steps.push_back(0); }
        t_job(const t_job& _job) : steps(_job.steps), machines(_job.machines) {}

        int& operator[](const int& index) { return steps.at(index); }
        t_job& operator=(t_job& _job) {this->steps = _job.steps; this->machines = _job.machines; return *this;}

        std::vector<int>& getJob() { return steps; }
};

#endif