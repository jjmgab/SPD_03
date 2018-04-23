#include "t_jobSeries.hpp"

void t_jobSeries::print() {

    for (std::vector<t_job>::iterator iter = series.begin(); iter != series.end(); iter++) {
        for (std::vector<int>::iterator it = iter->getJob().begin(); it != iter->getJob().end(); it++) {
            std::cout << *it << "\t";
        }
        std::cout << std::endl;
    }

}

bool t_jobSeries::isSeriesDone() {
    for (std::vector<t_job>::iterator it = series.begin(); it != series.end(); it++)
        if (!it->isDone()) return false;
    return true;
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