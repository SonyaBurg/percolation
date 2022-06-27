#include "Percolation.h"

#include <limits>
#include <numeric>

Percolation::Percolation(size_t dimension)
    : dsu(dimension)
    , dimension(dimension)
    , table(dimension * dimension)
{
    std::fill(table.begin(), table.end(), false);
}

void Percolation::unite(std::size_t row1, std::size_t col1, std::size_t row2, std::size_t col2)
{
    if (row2 == std::numeric_limits<std::size_t>().max() || row2 >= dimension || col2 == std::numeric_limits<std::size_t>().max() || col2 >= dimension) {
        return;
    }
    if (is_open(row2, col2)) {
        dsu.unite(row1 * dimension + col1, row2 * dimension + col2);
    }
}

void Percolation::open(std::size_t row, std::size_t column)
{
    if (table[row * dimension + column]) {
        return;
    }
    unite(row, column, row + 1, column);
    unite(row, column, row, column + 1);
    unite(row, column, row - 1, column);
    unite(row, column, row, column - 1);
    table[row * dimension + column] = true;
    if (row == dimension - 1) {
        is_bottom_open = true;
    }
    number_of_open_cells++;
}

bool Percolation::is_open(std::size_t row, std::size_t column) const
{
    return table[row * dimension + column];
}

bool Percolation::is_full(std::size_t row, std::size_t column) const
{
    return table[row * dimension + column] && dsu.find_parent(row * dimension + column) == dsu.find_parent(0);
}

size_t Percolation::get_number_of_open_cells() const
{
    return number_of_open_cells;
}

bool Percolation::has_percolation() const
{
    return is_bottom_open && dsu.find_parent(std::max(static_cast<std::size_t>(0), dimension * dimension - 1)) == dsu.find_parent(0);
}

Percolation::DSU::DSU(std::size_t size)
    : p(size * size)
    , sz(size * size)
{
    std::fill(p.begin(), p.begin() + size, 0);
    std::iota(p.begin() + size, p.end(), size);
    std::fill(p.end() - size, p.end(), std::max(static_cast<std::size_t>(0), size * size - 1));
    std::fill(sz.begin(), sz.end(), 1);
}

std::size_t Percolation::DSU::find_parent(std::size_t x) const
{
    return x == p[x] ? x : p[x] = find_parent(p[x]);
}
bool Percolation::DSU::unite(std::size_t x, std::size_t y)
{
    x = find_parent(x);
    y = find_parent(y);
    if (x == y) {
        return false;
    }
    if (sz[x] == sz[y]) {
        sz[y]++;
    }
    if (x > y) {
        std::swap(x, y);
    }
    p[y] = x;
    return true;
}
