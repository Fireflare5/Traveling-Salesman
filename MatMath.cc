#include "ThreadPool.h"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <cmath>

inline std::vector<std::vector<double>> dot(std::vector<std::vector<double>> u, std::vector<std::vector<double>> v) {
    try
    {
        if (u[0].size() != v.size())
        {
            throw -1;
        }
        std::vector<std::vector<double>> outputs(u.size(),std::vector<double>(v[0].size(), 0.0));
        ThreadPool pool(8);
        for (int j = 0; j < u.size(); j++)
        {
            for (int k = 0; k < v[0].size(); k++)
            {
                pool.enqueue([j, k, &outputs, u, v] {
                    for (int t = 0; t < v.size(); t++)
                    {
                        outputs[j][k] += (u[j][t] * v[t][k]);
                    }
                });
            }
        }
        return outputs;
    }
    catch (int e)
    {
        if (e == -1) {
            std::cout << "ValueError: shapes (" << u.size() << "," << u[0].size() << ") and ("<< v.size() << "," << v[0].size() << ") not aligned: " << u[0].size() << " (dim 1) != " << v.size() << " (dim 0)\n";
        }
        
    }
}

inline std::ostream& operator<<(std::ostream& out, const std::vector<std::vector<double>>& v)
{
    out << "[";
    for (int j = 0; j < v.size(); j++)
    {
        out << "[";
        for (int k = 0; k < v[0].size(); k++)
        {
            out << v[j][k];
            if (k != v[0].size() - 1)
            {
                out << ",";
            }
        }
        out << "]";
        if (j != v.size() - 1)
        {
            out << ",";
        }
    }
    out << "]";
    return out;
}

int main()
{
    std::vector<std::vector<double>> x(500,std::vector<double>(10,1.0));
    std::vector<std::vector<double>> y(10,std::vector<double>(500,1.0));
    auto start = std::chrono::high_resolution_clock::now();
    //std::cout << dot(x,y) << "\n";
    dot(x,y);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Execution time: " << duration.count() << " seconds\n";
    return 0;
}