/******************************************************************************
 * src/pgsql.h
 *
 * Encapsulate PostgreSQL queries into a C++ class, which is a specialization
 * of the generic SQL database interface.
 *
 ******************************************************************************
 * Copyright (C) 2013-2014 Timo Bingmann <tb@panthema.net>
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 *****************************************************************************/

#ifndef PGSQL_HEADER
#define PGSQL_HEADER

#include <string>
#include <map>

#include <libpq-fe.h>

class PgSqlQuery
{
private:
    //! Saved query string
    std::string m_query;

    //! PostgreSQL result object
    PGresult* m_res;

    //! Current result row
    unsigned int m_row;

    //! Type of m_colmap
    typedef std::map<std::string, unsigned int> colmap_type;

    //! Mapping column name -> number
    colmap_type m_colmap;

public:
    
    //! Execute a SQL query without parameters, throws on errors.
    PgSqlQuery(const std::string& query);

    //! Free result
    ~PgSqlQuery();

    //! Return number of rows in result, throws if no tuples.
    unsigned int num_rows() const;

    //! Return number of columns in result, throws if no tuples.
    unsigned int num_cols() const;

    // *** Column Name Mapping ***

    //! Return column name of col
    const char* col_name(unsigned int col) const;

    //! Read column name map for the following col -> num mappings.
    PgSqlQuery& read_colmap();

    //! Check if a column name exists.
    bool exist_col(const std::string& name) const;

    //! Returns column number of name or throws if it does not exist.
    unsigned int find_col(const std::string& name) const;

    // *** Result Iteration ***

    //! Advance current result row to next (or first if uninitialized)
    bool step();

    //! Return the current row number.
    unsigned int curr_row() const;

    //! Returns true if cell (row,col) is NULL.
    bool isNULL(unsigned int col) const;

    //! Return text representation of column col of current row.
    const char* text(unsigned int col) const;

    // *** Complete Result Caching ***

    //! read complete result into memory
    PgSqlQuery& read_complete();

    //! Returns true if cell (row,col) is NULL.
    bool isNULL(unsigned int row, unsigned int col) const;

    //! Return text representation of cell (row,col).
    const char* text(unsigned int row, unsigned int col) const;

    // *** TEXTTABLE formatting ***

    //! format result as a text table
    std::string format_texttable();
};

typedef PgSqlQuery SqlQuery;

#endif // PGSQL_HEADER
