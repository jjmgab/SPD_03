#ifndef T_JOB_HPP
#define T_JOB_HPP

#include <vector>

class t_job {
    private:
        std::vector<int> steps;
        int machines;
        int step_index;

    public:
        t_job(const int& job_machines) : machines(job_machines), step_index(-1) { for (int i = 0; i < job_machines; i++) steps.push_back(0); }
        t_job(const t_job& _job) : steps(_job.steps), machines(_job.machines), step_index(_job.step_index) {}

        int& operator[](const int& index) { return steps.at(index); }
        t_job& operator=(t_job& _job) {this->steps = _job.steps; this->machines = _job.machines; return *this;}

        std::vector<int>& getJob() { return steps; }

        bool isDone() { return (step_index >= machines ? true : false); }

        bool isStarted() { return (step_index < 0 ? false : true); }

        int nextStepIndex() { return step_index + 1; }

        int doNext() { 
            if (!this->isDone()) {
                step_index++;
                return steps.at(step_index);
            } else return -1;
        }
};

#endif