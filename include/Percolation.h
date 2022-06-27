#pragma once

#include <stdio.h>
#include <vector>

struct Percolation
{
    /**
     * Construct a new Percolation object
     * @param dimension dimension of percolation table
     */
    Percolation(size_t dimension);

    /**
     * Opens the cell[row, column] if it's not opened already
     * @param row row index
     * @param column column index
     */
    void open(size_t row, size_t column);

    /**
     * Checks if cell[row, column] is open
     * @param row row index
     * @param column column index
     * @return true cell is open
     * @return false cell is blocked
     */
    bool is_open(size_t row, size_t column) const;

    /**
     * Checks if cell[row, column] is full
     * @param row row index
     * @param column column index
     * @return true cell is full
     * @return false cell is not full
     */
    bool is_full(size_t row, size_t column) const;

    /**
     * Gets number of open cells in table
     * @return number of open cells
     */
    size_t get_number_of_open_cells() const;

    /**
     * Checks if system percolates
     * @return true system percolates
     * @return false system doesn't percolate
     */
    bool has_percolation() const;

private:
    struct DSU
    {
        mutable std::vector<std::size_t> p;
        std::vector<std::size_t> sz;
        DSU(size_t size);

        std::size_t find_parent(std::size_t x) const;
        bool unite(std::size_t x, std::size_t y);
    };

    void unite(std::size_t row1, std::size_t col1, std::size_t row2, std::size_t col2);

    DSU dsu;
    bool is_bottom_open = false;
    std::size_t number_of_open_cells = 0;
    std::size_t dimension;
    std::vector<bool> table;
};
