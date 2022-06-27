#include "PercolationStats.h"

#include "Percolation.h"

#include <random>
#include <vector>

PercolationStats::PercolationStats(std::size_t dimension, std::size_t trials)
    : dimension(dimension)
    , trials(trials)
{
    execute();
}

double PercolationStats::get_mean() const
{
    return mean;
}

double PercolationStats::get_standard_deviation() const
{
    return s;
}

double PercolationStats::get_confidence_low() const
{
    return mean - 1.96 * s / std::sqrt(trials);
}

double PercolationStats::get_confidence_high() const
{
    return mean + 1.96 * s / std::sqrt(trials);
}

void PercolationStats::execute()
{
    std::vector<double> results(trials);
    for (std::size_t i = 0; i < trials; i++) {
        results[i] = step();
    }

    mean = std::accumulate(results.begin(), results.end(), decltype(results)::value_type(0)) / trials;
    s = std::accumulate(results.begin(), results.end(), decltype(results)::value_type(0), [this](double x, double y) {
            return x + std::pow(y - mean, 2);
        }) / (trials - 1);
    s = std::sqrt(s);
}
double PercolationStats::step() const
{
    Percolation percolation(dimension);
    while (!percolation.has_percolation()) {
        size_t row = rand_int();
        size_t column = rand_int();
        percolation.open(row, column);
    }
    return static_cast<double>(percolation.get_number_of_open_cells()) / (dimension * dimension);
}
std::size_t PercolationStats::rand_int() const
{
    static std::mt19937 rnd{std::random_device{}()};
    return std::uniform_int_distribution<std::size_t>(0, dimension - 1)(rnd);
}
