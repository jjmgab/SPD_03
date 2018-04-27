#include "t_jobSeries.hpp"

void t_jobSeries::print() {
    for (auto iter : series) {
        for (auto it : iter.getJob()) {
            std::cout << it << "\t";
        }
        std::cout << std::endl;
    }
}

bool t_jobSeries::isSeriesDone() {
    for (std::vector<t_job>::iterator it = series.begin(); it != series.end(); it++)
        if (!it->isDone()) return false;
    return true;
}

const int t_jobSeries::cMax(std::vector<t_job>& _series) const {
    int _job_number = _series.size(),
        _machines = _series.at(0).getJob().size();

    int C[_job_number+1][_machines+1];

    int cmax_value = 0;
    int index = 0;
    int flow_steps = _job_number+_machines-1 -2;

    int n,m,
        n_start=0,m_start=0,
        i;

    for (m=0; m<_machines+1; m++)
        for (n=0; n<_job_number+1; n++)
            C[n][m] = 0;

    for (i = 0; i < flow_steps; i++) {
        m_start = (m_start > _machines ? _machines : 1 + i);
        n_start = (n_start > _machines ? _machines : 1 + i);

        for (m = m_start; m <= _machines; m++) {
            for (n = n_start; n <= _job_number; n++) {
                //std::cout << "C[" << n-1 << "][" << m << "]=" << C[n-1][m] << std::endl;
                //std::cout << "C[" << n << "][" << m-1 << "]=" << C[n][m-1] << std::endl;
                //std::cout << "p[" << n << "][" << m << "]=" << (*this)[n-1][m-1] << std::endl;

                C[n][m] = std::max(C[n-1][m], C[n][m-1]) + _series.at(n-1).getJob().at(m-1);
            }
        }
    }

    return C[_job_number][_machines];
}

const int t_jobSeries::cMax() {

    // algorytm wyznaczania cmax polega na wyznaczeniu ilosci "przekatnych"
    // macierzy, po ktorej bedzie "rozlewac" sie algorytm. dla macierzy nxm
    // ilosc przekatnych wynosi n+m-1. dla kazdej przekatnej inkrementujemy
    // indeks dla liczby maszyn i danego kroku, do maksymalnej wartosci.
    //
    // dzieki temu mamy mozliwosc wyznaczenia w iteracyjny sposob wartosc
    // cmax dla problemu przeplywowego.

    int C[job_number+1][machines+1];

    int cmax_value = 0;
    int index = 0;
    int flow_steps = job_number+machines-1 -2;

    int n,m,
        n_start=0,m_start=0,
        i;

    for (m=0; m<machines+1; m++)
        for (n=0; n<job_number+1; n++)
            C[n][m] = 0;

    for (i = 0; i < flow_steps; i++) {
        m_start = (m_start > machines ? machines : 1 + i);
        n_start = (n_start > machines ? machines : 1 + i);

        for (m = m_start; m <= machines; m++) {
            for (n = n_start; n <= job_number; n++) {
                //std::cout << "C[" << n-1 << "][" << m << "]=" << C[n-1][m] << std::endl;
                //std::cout << "C[" << n << "][" << m-1 << "]=" << C[n][m-1] << std::endl;
                //std::cout << "p[" << n << "][" << m << "]=" << (*this)[n-1][m-1] << std::endl;

                C[n][m] = std::max(C[n-1][m], C[n][m-1]) + (*this)[n-1][m-1];
            }
        }
    }

    return C[job_number][machines];
}

t_jobSeries& t_jobSeries::alogrithm_NEH() {

    std::cout << "Loaded:" << std::endl;
    for (std::vector<t_job>::iterator elem=this->series.begin(); elem!=this->series.end(); elem++) {
        for (std::vector<int>::iterator e = elem->getJob().begin(); e != elem->getJob().end(); e++)
            std::cout << *e << " ";
        std::cout << std::endl;
    }
    std::cout << "Sorting. . ." << std::endl;
    std::sort(this->series.begin(), this->series.end(), [](t_job a, t_job b) {
        return a.getPriority() > b.getPriority();
    });
    std::cout << "Sorted:" << std::endl;
    for (std::vector<t_job>::iterator elem=this->series.begin(); elem!=this->series.end(); elem++) {
        for (std::vector<int>::iterator e = elem->getJob().begin(); e != elem->getJob().end(); e++)
            std::cout << *e << " ";
        std::cout << std::endl;
    }


    int i,j,x=0;

    int* Cmax;
    std::vector<t_job> current_series;

    for (std::vector<t_job>::iterator job = this->series.begin(); job != this->series.end(); job++) {
        
        std::cout << "--- element " << x++ << " ---" << std::endl;

        std::cout << "adding " << current_series.size() + 1 << ". element" << std::endl;
        if (current_series.size() > 0) {
            current_series.insert(current_series.begin(), *job);
        } else {
            current_series.push_back(*job);
        }

        int cs_size = current_series.size();
        Cmax = new int[cs_size];
        Cmax[0] = this->cMax(current_series);

        std::cout << "Permutation nr " << 0 << ", current Cmax = " << Cmax[0] << std::endl;
            for (std::vector<t_job>::iterator elem=current_series.begin(); elem!=current_series.end(); elem++) {
                for (std::vector<int>::iterator e = elem->getJob().begin(); e != elem->getJob().end(); e++)
                    std::cout << *e << " ";
                std::cout << std::endl;
            }

        if (cs_size > 1) {
            for (i = 1; i < cs_size; i++) {

                std::cout << "Swapping verse " << i << " and " << i-1 << std::endl;
                std::swap(current_series.at(i), current_series.at(i-1));
                Cmax[i] = this->cMax(current_series);

                std::cout << "Permutation nr " << i << ", current Cmax = " << Cmax[i] << std::endl;
                for (std::vector<t_job>::iterator elem=current_series.begin(); elem!=current_series.end(); elem++) {
                    for (std::vector<int>::iterator e = elem->getJob().begin(); e != elem->getJob().end(); e++)
                        std::cout << *e << " ";
                    std::cout << std::endl;
                }

            }
        }

        current_series.pop_back();

        int minCmax;
        int minCmax_index;

        std::cout << "Cmax list for size " << cs_size << ": " << std::endl;
        std::cout << "Cmax[" << 0 << "] = " << Cmax[0] << std::endl;
        minCmax = Cmax[0];
        minCmax_index = 0;

        for (i = 1; i < cs_size; i++) {
            std::cout << "Cmax[" << i << "] = " << Cmax[i] << std::endl;
            if (minCmax > Cmax[i]) {
                minCmax = Cmax[i];
                minCmax_index = i;
                std::cout << "min Cmax index = " << i << std::endl;
            }
        }

        std::cout << "Minimal Cmax = " << minCmax << ", at index = " << minCmax_index << std::endl;

        if (current_series.size() > 0) {
            if (minCmax_index == cs_size) {
                current_series.push_back(*job);
            } else {
                current_series.insert(current_series.begin()+minCmax_index, *job);
            }

        } else {
            current_series.push_back(*job);
        }

        delete[] Cmax;
    }

    std::cout << this->cMax(current_series) << std::endl;

    std::swap(this->series, current_series);

    return (*this);
}