#include <iostream>
#include <vector>
#include <omp.h>
#include <chrono>

void printLineSierpinski(int n, int b, std::vector<std::string>& lines)
{
    int y = n - b;
    std::string line;

    for (int i = 0; i < y; i++) {
        line += " ";
    }

    for (int x = 0; x + y < n; x++) {
        if (x & y)
            line += "  ";
        else
            line += "* ";
    }

    lines[b - 1] = line;
}

void printSierpinski(int n)
{
    std::vector<std::string> lines(n);
    int i;
    #pragma omp parallel for private(i)
    for (i = 1; i <= n; i++) {
        printLineSierpinski(n, i, lines);
    }

    // for (const auto& line : lines) {
    //     std::cout << line << std::endl;
    // }
}

int main()
{
    auto start_time = std::chrono::high_resolution_clock::now();
    int n = 8192;

    // Function calling
    printSierpinski(n);

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end_time - start_time;

    std::cout << "Tempo de execucao: " << duration.count() << " segundos" << std::endl;

    return 0;
}
