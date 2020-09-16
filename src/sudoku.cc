#include "glob_rand.h"
#include "sudoku.h"
#include <algorithm>
#include <iomanip>

Sudoku::Sudoku( const int dim )
  : m_dim{ dim }, m_abs_dim{ dim*dim },
    m_grid{ std::make_unique<Vec<u_ptr<Vec<int>>>>() } {
  populate_grid();
  // perform permutations fo 2 kinds for an effective shuffle
  perm_grid_swaps(); perm_grid_rc();
}

void Sudoku::populate_grid() noexcept {
  m_grid->reserve( m_abs_dim );
  int row_start = 0,
      row_shift = 0;
  // populate grid with a valid sudoku puzzle
  for ( int i = 0; i < m_abs_dim; ++i ) {
    auto row = std::make_unique<Vec<int>>();
    row->reserve( m_abs_dim );
    for ( int j = 0; j < m_abs_dim; ++j )
      row->push_back( (( row_start + row_shift + j ) % m_abs_dim) + 1 );
    m_grid->push_back( std::move( row ) );
    if ( !(( i + 1 ) % m_dim) ) row_shift += 1;
    row_start += m_dim;
  }
}

void Sudoku::perm_grid_rc() {
  // do a permutation on the rows
  for ( int i = 0; i < m_abs_dim; i += m_dim )
    std::shuffle( m_grid->begin() + i, m_grid->begin() + i + m_dim, GlobRand::RNG );
  // do a permutation on the cols
  int col_seed = GlobRand::RNG();
  for ( int i = 0; i < m_abs_dim; i += m_dim ) {
    for ( int j = 0; j < m_abs_dim; ++j ) {
      GlobRand::RNG.seed( col_seed );
      std::shuffle( (*m_grid)[ j ]->begin() + i, (*m_grid)[ j ]->begin() + i + m_dim,
          GlobRand::RNG );
    }
  }
}

void Sudoku::perm_grid_swaps() {
  Vec<int> elems;
  for ( int i = 1; i <= m_abs_dim; ++i ) elems.push_back( i );
  std::shuffle( elems.begin(), elems.end(), GlobRand::RNG );
  for ( int row = 0; row < m_abs_dim; ++row )
    for ( int col = 0; col < m_abs_dim; ++col )
      set_elem( row, col, elems[ get_elem( row, col ) - 1] );
}

int Sudoku::get_elem( int row, int col ) const noexcept {
  return (*(*m_grid)[row])[col];
}

void Sudoku::set_elem( int row, int col, int new_val ) noexcept {
  (*(*m_grid)[row])[col] = new_val;
}

void print_row_sep( std::ostream &out, int length ) {
  out << " ";
  for ( int i = 0; i < length; ++i ) out << "-";
  std::cout << std::endl;
}

std::ostream& operator<<( std::ostream &out, const Sudoku &s ) {
  u_short fill_width = 1;
  int dim = s.m_abs_dim;
  do { ++fill_width; dim /= 10; } while ( dim );
  int row_sep_width{ ( s.m_abs_dim * fill_width ) + ( 2 * s.m_dim ) + 1 };

  for ( int row = 0; row < s.m_abs_dim; ++row ) {
    if ( !row ) print_row_sep( out, row_sep_width );
    for ( int col = 0; col < s.m_abs_dim; ++col ) {
      if ( !col ) out << " |";
      out << std::setw( fill_width )
          << s.get_elem( row, col );
      if ( !(( col + 1 ) % s.m_dim ) ) out << " |";
    }
    out << std::endl;
    if ( !(( row + 1 ) % s.m_dim ) ) print_row_sep( out, row_sep_width );
  }
  return out;
}
