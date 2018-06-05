#include "t_jobSeries.hpp"

void t_jobSeries::print()
{
    for (auto iter : series)
    {
        for (auto it : iter.getJob())
        {
            std::cout << it << "\t";
        }
        std::cout << std::endl;
    }
}

bool t_jobSeries::isSeriesDone()
{
    for (std::vector<t_job>::iterator it = series.begin(); it != series.end(); it++)
        if (!it->isDone())
            return false;
    return true;
}

const int t_jobSeries::cMax(std::vector<t_job> &_series) const
{
    int _job_number = _series.size(),
        _machines = _series.at(0).getJob().size();

    int C[_job_number + 1][_machines + 1];

    int cmax_value = 0;
    int index = 0;
    int flow_steps = _job_number + _machines - 1 - 2;

    int n, m,
        n_start = 0, m_start = 0,
        i;

    for (m = 0; m < _machines + 1; m++)
        for (n = 0; n < _job_number + 1; n++)
            C[n][m] = 0;

    for (i = 0; i < flow_steps; i++)
    {
        m_start = (m_start > _machines ? _machines : 1 + i);
        n_start = (n_start > _machines ? _machines : 1 + i);

        for (m = m_start; m <= _machines; m++)
        {
            for (n = n_start; n <= _job_number; n++)
            {
                //std::cout << "C[" << n-1 << "][" << m << "]=" << C[n-1][m] << std::endl;
                //std::cout << "C[" << n << "][" << m-1 << "]=" << C[n][m-1] << std::endl;
                //std::cout << "p[" << n << "][" << m << "]=" << (*this)[n-1][m-1] << std::endl;

                C[n][m] = std::max(C[n - 1][m], C[n][m - 1]) + _series.at(n - 1).getJob().at(m - 1);
            }
        }
    }

    return C[_job_number][_machines];
}

const int t_jobSeries::cMax()
{

    // algorytm wyznaczania cmax polega na wyznaczeniu ilosci "przekatnych"
    // macierzy, po ktorej bedzie "rozlewac" sie algorytm. dla macierzy nxm
    // ilosc przekatnych wynosi n+m-1. dla kazdej przekatnej inkrementujemy
    // indeks dla liczby maszyn i danego kroku, do maksymalnej wartosci.
    //
    // dzieki temu mamy mozliwosc wyznaczenia w iteracyjny sposob wartosc
    // cmax dla problemu przeplywowego.

    int C[job_number + 1][machines + 1];

    int cmax_value = 0;
    int index = 0;
    int flow_steps = job_number + machines - 1 - 2;

    int n, m,
        n_start = 0, m_start = 0,
        i;

    for (m = 0; m < machines + 1; m++)
        for (n = 0; n < job_number + 1; n++)
            C[n][m] = 0;

    for (i = 0; i < flow_steps; i++)
    {
        m_start = (m_start > machines ? machines : 1 + i);
        n_start = (n_start > machines ? machines : 1 + i);

        for (m = m_start; m <= machines; m++)
        {
            for (n = n_start; n <= job_number; n++)
            {
                //std::cout << "C[" << n-1 << "][" << m << "]=" << C[n-1][m] << std::endl;
                //std::cout << "C[" << n << "][" << m-1 << "]=" << C[n][m-1] << std::endl;
                //std::cout << "p[" << n << "][" << m << "]=" << (*this)[n-1][m-1] << std::endl;

                C[n][m] = std::max(C[n - 1][m], C[n][m - 1]) + (*this)[n - 1][m - 1];
            }
        }
    }

    return C[job_number][machines];
}

t_jobSeries &t_jobSeries::algorithm_NEH()
{

    // std::cout << "Loaded:" << std::endl;
    // for (std::vector<t_job>::iterator elem=this->series.begin(); elem!=this->series.end(); elem++) {
    //     for (std::vector<int>::iterator e = elem->getJob().begin(); e != elem->getJob().end(); e++)
    //         std::cout << *e << " ";
    //     std::cout << std::endl;
    // }
    // std::cout << "Sorting. . ." << std::endl;
    std::sort(this->series.begin(), this->series.end(), [](t_job a, t_job b) {
        return a.getPriority() > b.getPriority();
    });
    // std::cout << "Sorted:" << std::endl;
    // for (std::vector<t_job>::iterator elem=this->series.begin(); elem!=this->series.end(); elem++) {
    //     for (std::vector<int>::iterator e = elem->getJob().begin(); e != elem->getJob().end(); e++)
    //         std::cout << *e << " ";
    //     std::cout << std::endl;
    // }

    int i, j, x = 0;

    int *Cmax;
    std::vector<t_job> current_series;

    for (std::vector<t_job>::iterator job = this->series.begin(); job != this->series.end(); job++)
    {

        // std::cout << "--- element " << x++ << " ---" << std::endl;

        // std::cout << "adding " << current_series.size() + 1 << ". element" << std::endl;
        if (current_series.size() > 0)
        {
            current_series.insert(current_series.begin(), *job);
        }
        else
        {
            current_series.push_back(*job);
        }

        int cs_size = current_series.size();
        Cmax = new int[cs_size];
        Cmax[0] = this->cMax(current_series);

        // std::cout << "Permutation nr " << 0 << ", current Cmax = " << Cmax[0] << std::endl;
        //     for (std::vector<t_job>::iterator elem=current_series.begin(); elem!=current_series.end(); elem++) {
        //         for (std::vector<int>::iterator e = elem->getJob().begin(); e != elem->getJob().end(); e++)
        //             std::cout << *e << " ";
        //         std::cout << std::endl;
        //     }

        if (cs_size > 1)
        {
            for (i = 1; i < cs_size; i++)
            {

                //std::cout << "Swapping verse " << i << " and " << i-1 << std::endl;
                std::swap(current_series.at(i), current_series.at(i - 1));
                Cmax[i] = this->cMax(current_series);

                // std::cout << "Permutation nr " << i << ", current Cmax = " << Cmax[i] << std::endl;
                // for (std::vector<t_job>::iterator elem=current_series.begin(); elem!=current_series.end(); elem++) {
                //    for (std::vector<int>::iterator e = elem->getJob().begin(); e != elem->getJob().end(); e++)
                //        std::cout << *e << " ";
                //    std::cout << std::endl;
                // }
            }
        }

        current_series.pop_back();

        int minCmax;
        int minCmax_index;

        // std::cout << "Cmax list for size " << cs_size << ": " << std::endl;
        // std::cout << "Cmax[" << 0 << "] = " << Cmax[0] << std::endl;
        minCmax = Cmax[0];
        minCmax_index = 0;

        for (i = 1; i < cs_size; i++)
        {
            // std::cout << "Cmax[" << i << "] = " << Cmax[i] << std::endl;
            if (minCmax > Cmax[i])
            {
                minCmax = Cmax[i];
                minCmax_index = i;
                // std::cout << "min Cmax index = " << i << std::endl;
            }
        }

        // std::cout << "Minimal Cmax = " << minCmax << ", at index = " << minCmax_index << std::endl;

        if (current_series.size() > 0)
        {
            if (minCmax_index == cs_size)
            {
                current_series.push_back(*job);
            }
            else
            {
                current_series.insert(current_series.begin() + minCmax_index, *job);
            }
        }
        else
        {
            current_series.push_back(*job);
        }

        delete[] Cmax;
    }

    //std::cout << this->cMax(current_series) << std::endl;

    std::swap(this->series, current_series);

    return (*this);
}


t_jobSeries &t_jobSeries::algorithm_NEH_mod()
{

    // std::cout << "Loaded:" << std::endl;
    // for (std::vector<t_job>::iterator elem=this->series.begin(); elem!=this->series.end(); elem++) {
    //     for (std::vector<int>::iterator e = elem->getJob().begin(); e != elem->getJob().end(); e++)
    //         std::cout << *e << " ";
    //     std::cout << std::endl;
    // }
    // std::cout << "Sorting. . ." << std::endl;

    // ---- krok 2
    std::sort(this->series.begin(), this->series.end(), [](t_job a, t_job b) {
        return a.getPriority() > b.getPriority();
    });
    // std::cout << "Sorted:" << std::endl;
    // for (std::vector<t_job>::iterator elem=this->series.begin(); elem!=this->series.end(); elem++) {
    //     for (std::vector<int>::iterator e = elem->getJob().begin(); e != elem->getJob().end(); e++)
    //         std::cout << *e << " ";
    //     std::cout << std::endl;
    // }

    int i, j, x = 0;

    int *Cmax;
    std::vector<t_job> current_series;

    for (std::vector<t_job>::iterator job = this->series.begin(); job != this->series.end(); job++)
    {

        // std::cout << "--- element " << x++ << " ---" << std::endl;

        // std::cout << "adding " << current_series.size() + 1 << ". element" << std::endl;
        if (current_series.size() > 0)
        {
            current_series.insert(current_series.begin(), *job);
        }
        else
        {
            current_series.push_back(*job);
        }

        int cs_size = current_series.size();
        Cmax = new int[cs_size];
        Cmax[0] = this->cMax(current_series);

        // std::cout << "Permutation nr " << 0 << ", current Cmax = " << Cmax[0] << std::endl;
        //     for (std::vector<t_job>::iterator elem=current_series.begin(); elem!=current_series.end(); elem++) {
        //         for (std::vector<int>::iterator e = elem->getJob().begin(); e != elem->getJob().end(); e++)
        //             std::cout << *e << " ";
        //         std::cout << std::endl;
        //     }

        if (cs_size > 1)
        {
            for (i = 1; i < cs_size; i++)
            {

                //std::cout << "Swapping verse " << i << " and " << i-1 << std::endl;
                std::swap(current_series.at(i), current_series.at(i - 1));
                Cmax[i] = this->cMax(current_series);

                // std::cout << "Permutation nr " << i << ", current Cmax = " << Cmax[i] << std::endl;
                // for (std::vector<t_job>::iterator elem=current_series.begin(); elem!=current_series.end(); elem++) {
                //    for (std::vector<int>::iterator e = elem->getJob().begin(); e != elem->getJob().end(); e++)
                //        std::cout << *e << " ";
                //    std::cout << std::endl;
                // }
            }
        }

        current_series.pop_back();

        int minCmax;
        int minCmax_index;

        // std::cout << "Cmax list for size " << cs_size << ": " << std::endl;
        // std::cout << "Cmax[" << 0 << "] = " << Cmax[0] << std::endl;
        minCmax = Cmax[0];
        minCmax_index = 0;

        for (i = 1; i < cs_size; i++)
        {
            // std::cout << "Cmax[" << i << "] = " << Cmax[i] << std::endl;
            if (minCmax > Cmax[i])
            {
                minCmax = Cmax[i];
                minCmax_index = i;
                // std::cout << "min Cmax index = " << i << std::endl;
            }
        }

        // std::cout << "Minimal Cmax = " << minCmax << ", at index = " << minCmax_index << std::endl;

        if (current_series.size() > 0)
        {
            if (minCmax_index == cs_size)
            {
                current_series.push_back(*job);
            }
            else
            {
                current_series.insert(current_series.begin() + minCmax_index, *job);
            }
        }
        else
        {
            current_series.push_back(*job);
        }

        // tutaj modyfikacja
        

        if (cs_size > 2) {

        //std::cout << "modyfikacja dla size = " << cs_size << std::endl;

        int mod_i = 0,
            delta_Cmax = 0,
            current_Cmax = this->cMax(current_series);


        // znajdz element dla ktorego jest najwieksza deltaCmax
        for (i = 0; i < cs_size; i++) {
            if (i != minCmax_index) {
                //std::cout << "kopiowanie wektora" << std::endl;
                std::vector<t_job> _series (current_series);
                //std::cout << "wektor.size() = " << _series.size() << std::endl;
                //std::cout << "kopiowanie elementu" << std::endl;
                t_job deleted_element (_series.at(i));

                //std::cout << "usuwanie elementu" << std::endl;
                _series.erase(_series.begin() + i);
                //std::cout << "wyznaczanie min" << std::endl;
                if (std::abs(current_Cmax - this->cMax(_series)) > delta_Cmax)
                    mod_i = i;
                //std::cout << "wstawianie elementu" << std::endl;
                _series.insert(_series.begin() + i, deleted_element);
            }
        }

        //std::cout << "modyfikacja" << std::endl;

        t_job deleted_element (current_series.at(mod_i));
        current_series.erase(current_series.begin() + mod_i);

        int minCmax_at = 0,
            minCmax_value = this->cMax(current_series);

        if (minCmax_index > mod_i) minCmax_index--;

        //std::cout << "modyfikacja" << std::endl;

        for (i = 0; i < cs_size - 1; i++) {
            if (i != minCmax_index) {
                current_series.insert(current_series.begin() + i, deleted_element);
                int curr_minCmax = this->cMax(current_series);
                if (minCmax_value > curr_minCmax) {
                    minCmax_value = curr_minCmax;
                    minCmax_at = i;
                }
                current_series.erase(current_series.begin() + i);
            }
        }

        //std::cout << "modyfikacja" << std::endl;

        current_series.insert(current_series.begin() + minCmax_at, deleted_element);

        }

        delete[] Cmax;
    }

    std::cout << this->cMax(current_series) << std::endl;

    std::swap(this->series, current_series);

    return (*this);
}

/**
* Algorytm SA (Simulated Annealing - symulowane wyzarzanie)
*/
t_jobSeries &t_jobSeries::algorithm_SA(const double& _T, const double& _wsp, const t_SA_choice& _choice, const bool& _sort) {

    //std::cout << "Algorithm SA -- start" << std::endl;
    if (_wsp > 1.000f) exit(-1);

    srand(time(NULL));
    
    double T = _T;                   // temperatura poczatkowa
    const double T_min = 0.010f;     // temperatura minimalna, przy ktorej algorytm sie konczy
    const double wsp = _wsp;           // wspolczynnik wychladzania
    int F_curr = -1,                // wartosc f. celu dla obecnej permutacji
        F_prev = -1,                // wartosc f. celu dla poprzedniej permutacji
        F_diff;                     // roznica miedzy poprzednia a obecna permutacja

    int iter = 0;

    // sortowanie listy zadan
    if (_sort) {
        std::sort(this->series.begin(), this->series.end(), [](t_job a, t_job b) {
            return a.getPriority() > b.getPriority();
        });
    }

    // petla wyzarzania
    do {
        F_prev = this->cMax();  // wyznacza poprzednia wartosc f. celu

        switch (_choice) {

            case t_SA_choice::SWAP:
            // zamienia miejscami dwa losowe zadania
            {
                int series_size = this->series.size(),
                    first = -1,
                    second = -1;

                double k = 1000000000;

                // losuje 1. i 2. indeks
                first = rand() % series_size;
                second = rand() % series_size;
                while (second == first) { second = rand() % series_size; }

                // zamienia miejscami wylosowane zadania
                std::swap(this->series[first], this->series[second]);
                F_curr = this->cMax();

                // w momencie, gdy zmiana jest niepozadana
                if (F_curr > F_prev) {

                    // prawdopodobienstwo niekorzystnego ruchu
                    double P = std::exp(((double)(F_prev - F_curr))/(k * T));
                    // losowana zmienna z zakresu (0,1)
                    double rnd = ((double)(rand() % RANDOM_DOUBLE_MAX)) / ((double)RANDOM_DOUBLE_MAX);
                    
                    // jesli prawdopodobnienstwo n. r. jest za duze
                    if (rnd < P) {
                        // cofnij
                        std::swap(this->series[first], this->series[second]);
                    }
                }
                if (this->series.size() != series_size) exit(-1);
            }
            break;

            case t_SA_choice::INSERT:
            // losuje zadanie i przesuwa je w losowe miejsce
            {
                int series_size = this->series.size(),
                    job_index = -1,
                    place_index = -1;
                double k = 1000000000;

                // losuje 1. i 2. indeks
                job_index = rand() % series_size;
                place_index = rand() % series_size;
                while (place_index == job_index) { place_index = rand() % series_size; }

                // przenosi element w wylosowane miejsce

                t_job job(this->series.at(job_index));
                this->series.erase(this->series.begin() + job_index);
                this->series.insert(this->series.begin() + place_index, job);
                
                F_curr = this->cMax();

                // w momencie, gdy zmiana jest niepozadana
                if (F_curr > F_prev) {

                    // prawdopodobienstwo niekorzystnego ruchu
                    double P = std::exp(((double)(F_prev - F_curr))/(k * T));
                    // losowana zmienna z zakresu (0,1)
                    double rnd = ((double)(rand() % RANDOM_DOUBLE_MAX)) / ((double)RANDOM_DOUBLE_MAX);
                    
                    // jesli prawdopodobnienstwo n. r. jest za duze
                    if (rnd < P) {
                        // cofnij
                        this->series.erase(this->series.begin() + place_index);
                        this->series.insert(this->series.begin() + job_index, job);
                    }
                }

                if (this->series.size() != series_size) exit(-1);
            }
            break;

            case t_SA_choice::TWIST:
            // losuje dwa zadania i odwraca kolejnosc wszystkich zadan miedzy nimi
            {
                int series_size = this->series.size(),
                    first_index = -1,
                    second_index = -1;
                double k = 1000000000;

                // losuje 1. i 2. indeks
                first_index = rand() % series_size;
                second_index = rand() % series_size;
                while (first_index + 2 < second_index) { first_index = rand() % series_size; }

                // przenosi element w wylosowane miejsce
                int f = first_index,
                    s = second_index;
                while (f < s) {
                    f++;
                    s--;
                    std::swap(this->series.at(f), this->series.at(s));
                }
                
                F_curr = this->cMax();

                // w momencie, gdy zmiana jest niepozadana
                if (F_curr > F_prev) {

                    // prawdopodobienstwo niekorzystnego ruchu
                    double P = std::exp(((double)(F_prev - F_curr))/(k * T));
                    // losowana zmienna z zakresu (0,1)
                    double rnd = ((double)(rand() % RANDOM_DOUBLE_MAX)) / ((double)RANDOM_DOUBLE_MAX);
                    
                    // jesli prawdopodobnienstwo n. r. jest za duze
                    if (rnd < P) {
                        // cofnij
                        int f = first_index,
                            s = second_index;
                        while (f < s) {
                            f++;
                            s--;
                            std::swap(this->series.at(f), this->series.at(s));
                        }
                    }
                }

                if (this->series.size() != series_size) exit(-1);
            }
            break;
        }

        T = T * wsp;
        iter++;

    } while (T > T_min);
}