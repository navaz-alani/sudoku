#ifndef __SUDOKU_H__
#define __SUDOKU_H__

#include "defs.h"
#include <vector>
#include <iostream>
#include <memory>

class Sudoku {
    int m_dim, m_abs_dim;
    u_ptr<Vec<u_ptr<Vec<int>>>> m_grid;

    void populate_grid() noexcept;
    /*
     * perm_grid_rc swaps rows and columns of the grid while perserving the
     * validity of the Sudoku puzzle.
     * */
    void perm_grid_rc();
    /*
     * perm_grid_swaps swaps the values in a grid while perserving the validity
     * of the Sudoku puzzle.
     * */
    void perm_grid_swaps();
    /*
     * get_elem accesses the element in the Sudoku grid at the given row, col
     * pair.
     * */
    int get_elem( int row, int col ) const noexcept;
    void set_elem( int row, int col, int new_val ) noexcept;

    friend std::ostream& operator<<( std::ostream &out, const Sudoku &s );
  public:
    /*
     * The constructor creates an underlying (square) grid of dimensions dim^2.
     * This ensures that the grid has a dimension which is a perfect square.
     * For example, to create a 9X9 grid, dim ought to be 3.
     * */
    Sudoku( const int dim );
};

#endif
