/*! \file
 *
 * Definitions for the nTrix class. \n
 * Programmer: Noah Klein and Jeffrey Strahm \n
 * Class: CS5201 \n
 * Assignment: Homework 7 \n
 */

#ifndef NTRIX_H
#define NTRIX_H

#include "vector.h"
#include <iterator>
#include <cmath>
#include <fstream>

//! nTrix class.
/*!
 * This class uses a 1D array to simulate a 2D array for
 * matrix implementation
 */
template <typename T>
class nTrix
{
	private:
		short m_row; /*!< A short that is used to store the number of rows */
		short m_col; /*!< A short that is used to store the number of columns */
		T* m_matrix; /*!< A T* that simulates a 2D array of type T objects */

	public:

		// Essential //

		/*! \brief Default Constructor
		 *
		 * Description: Creates a default 2x2 matrix.
		 * \post A 2x2 matrix is initialized with no values stored.
		 */
		nTrix()
			: m_row(2)
			, m_col(2)
			, m_matrix(new T[m_row*m_col])
		{};

		/*! \brief Constructor
		 *
		 * Description: A constructor that accepts a std::initializer_list of
		 * std::initializer_list<T> to fill a matrix with the values specified.
		 * \param grid is a list of lists that store the values to be input
		 * into the matrix.
		 * \pre = operator must be defined for type T.
		 * \post A matrix is initialized with the dimensions and values of the
		 * list of lists passed.
		 * \throw Throws a std::domain_error object if one of the lists is
		 * not the same length as the others.
		 */
		nTrix(const std::initializer_list<std::initializer_list<T>>& grid)
			: m_row(grid.size())
			, m_col(grid.begin() -> size())
			, m_matrix(new T[m_row*m_col])
		{
			unsigned int temp_size = grid.begin() -> size();
			for(auto r_itr = grid.begin(); r_itr != grid.end(); r_itr++)
			{
				if((*r_itr).size() != temp_size)
				{
					throw(std::domain_error(std::to_string(r_itr -> size())));
				}
			}

			short row_counter = 0;
			short col_counter = 0;

			for(auto r_itr = grid.begin(); r_itr != grid.end(); r_itr++)
			{
				for(auto c_itr = r_itr -> begin(); c_itr != r_itr -> end();
																		c_itr++)
				{
					m_matrix[(row_counter * m_col) + col_counter] = *c_itr;
					col_counter++;
				}
				col_counter = 0;
				row_counter++;
			}
		};

		/*! \brief Constructor
		 *
		 * Description: Constructs a matrix of size num_rows x num_cols with no
		 * values stored.
		 * \param num_rows is the number of rows for the matrix.
		 * \param num_cols is the number of columns for the matrix.
		 * \post A r x c matrix is initialized with no values stored.
		 * \throw Throws a std::domain_error object if either of the
		 * dimensions are negative.
		 */
		nTrix(const short num_rows, const short num_cols)
			: m_row(num_rows)
			, m_col(num_cols)
			, m_matrix(new T[m_row*m_col])
		{
			if(num_rows < 0)
			{
				throw(std::domain_error(std::to_string(num_rows)));
			}
			if(num_cols < 0)
			{
				throw(std::domain_error(std::to_string(num_cols)));
			}
		};

		/*! \brief Vector Constructor
		 *
		 * Description: Allows a matrix to be constructed based on a vector
		 * vector. The matrix is a column matrix.
		 * \param rhs is the vector to be copied.
		 * \pre = operator needs to be defined for type T.
		 * \post A column matrix is constructed with the same values in the
		 * vector.
		 */
		nTrix(const vector<T>& rhs)
			: m_row(rhs.size())
			, m_col(1)
			, m_matrix(new T[m_row])
		{
			for(int i = 0; i < m_row; i++)
			{
				m_matrix[i] = rhs[i];
			}
		};

		/*! \brief Copy Constructor
		 *
		 * Description: Copy constructor that initializes a new matrix with the
		 * same values as the matrix passed.
		 * \param rhs is the matrix to be copied.
		 * \pre = operator needs to be defined for type T.
		 * \post A new matrix is initialized with the same values as the one
		 * passed.
		 */
		nTrix(const nTrix<T>& rhs)
			: m_row(rhs.m_row)
			, m_col(rhs.m_col)
			, m_matrix(new T[m_row*m_col])
		{
			for(int i = 0; i < m_row; i++)
			{
				for(int j = 0; j < m_col; j++)
				{
					m_matrix[(i*m_col) + j] = rhs.m_matrix[(i*rhs.m_col) + j];
				}
			}
		};

		/*! \brief = operator
		 *
		 * Description: = operator for the nTrix class that sets the calling
		 * object equal to the object passed.
		 * \param rhs is the matrix to be copied.
		 * \return Returns *this with the copied values.
		 * \pre = operator needs to be defined for type T.
		 * \post The calling object is set equal to the object passed.
		 */
		nTrix<T>& operator=(const nTrix<T>& rhs);

		/*! \brief Destructor
		 *
		 * Description: Properly destructs a nTrix object to avoid memory leaks.
		 * \post The calling object is safely destructed.
		 */
		~nTrix();

		// Accessors //

		/*! \brief Row accessor
		 *
		 * Description: Returns the number of rows in a matrix.
		 * \return The number of rows in a matrix.
		 */
		short rows() const;

		/*! \brief Column accessor
		 *
		 * Description: Returns the number of columns in a matrix.
		 * \return The number of columns in a matrix.
		 */
		short cols() const;

		/*! \brief Index accessor
		 *
		 * Description: Allows the user to view the i,j-th element in the matrix.
		 * \param row_index is the row to view.
		 * \param col_index is the column member of the row to view.
		 * \return Returns a const reference to the T object at that index in
		 * the matrix.
		 * \throw Throws a std::domain_error object if either of the indexes are
		 * less than zero or greater than their respective domains that they are
		 * attempting to access.
		 */
		const T& operator()(const int row_index, const int col_index) const;

		/*! \brief One norm calculator
		 *
		 * Description: Calculates the one-norm or the maximum column sum of a
		 * matrix.
		 * \return Returns a float that represents the maximum column sum.
		 * \pre std::abs() needs to be defined for type T.
		 * \pre += operator needs to be defined for type T.
		 */
		T one_norm() const;

		/*! \brief Infinity norm calculator
		 *
		 * Description: Calculates the infinity-norm or the maximum row sum of
		 * a matrix.
		 * \return Returns a float that represents the maximum row sum.
		 * \pre std::abs() needs to be defined for type T.
		 * \pre += operator needs to be defined for type T.
		 */
		T infinity_norm() const;

		/*! \brief frobenius norm
		 *
		 * Description: Two norm calculator for matrices.
		 * \return returns the frobenius norm of the matrix as a float.
		 * \pre * operator must be defined for type T.
		 */
		T frobenius() const;

		// Mutators //

		/*! \brief Index accessor
		 *
		 * Description: Allows the user to access the i,j-th element in the matrix.
		 * \param row_index is the row to view.
		 * \param col_index is the column member of the row to view.
		 * \return Returns a reference to the T object at that index in the
		 * matrix.
		 * \throw Throws a std::domain_error object if either of the indexes are
		 * less than zero or greater than their respective domains that they are
		 * attempting to access.
		 */
		T& operator()(const int row_index, const int col_index);

		/*! \brief + operator
		 *
		 * Description: + operator overload for the nTrix class that allows for
		 * the addition of two nTrix objects.
		 * \param rhs is the nTrix to be added to the calling object.
		 * \return Returns a new matrix that is the sum of the calling object
		 * and the object passed.
		 * \pre += operator needs to be defined for type T.
		 * \throw Throws a std::invalid_argument object if the matrices are not
		 * the same size.
		 */
		nTrix<T> operator+(const nTrix<T>& rhs) const;

		/*! \brief Binary - operator
		 *
		 * Description: - operator overload for the nTrix class that allows for
		 * the subtraction of two nTrix objects.
		 * \param rhs is the nTrix to be subtracted from the calling object.
		 * \return Returns a new matrix that is the difference of the calling
		 * object and the object passed.
		 * \pre * operator must be defined for type T.
		 * \pre += operator must be defined for type T.
		 * \throw Throws a std::invalid_argument object if the matrices are not
		 * the same size.
		 */
		nTrix<T> operator-(const nTrix<T>& rhs) const;

		/*! \brief Unary - operator
		 *
		 * Description: - operator overload for the nTrix class that negates every
		 * element in the matrix.
		 * \return Returns a new nTrix with all values from the calling object
		 * negated.
		 * \pre * operator must be defined for type T.
		 */
		nTrix<T> operator-() const;

		/*! \brief * operator
		 *
		 * Description: * operator overload for the nTrix class that allows the user
		 * to multiply two nTrix objects of the same type.
		 * \param rhs is the nTrix to be multiplied with the calling object.
		 * \return Returns a new nTrix that is the product of the calling object
		 * and the object passed.
		 * \pre * operator must be defined for type T.
		 * \throw Throws a std::invalid_argument object if the two matrices are
		 * not the correct dimensions for matrix multiplication to occur.
		 */
		nTrix<T> operator*(const nTrix<T>& rhs) const;

		/*! \brief * operator
		 *
		 * Description: * operator overload for the nTrix class that allows the user
		 * to multiply a matrix with a vector.
		 * \param rhs is a vector object to be multiplied to a nTrix.
		 * \return Returns a vector<T> object with the values having matrix
		 * multiplicaion applied.
		 * \pre * operator must be defined for type T.
		 * \throw Throws a std::invalid_argument object if the vector and matrix
		 * are not the correct dimensions for multiplication to occur.
		 */
		vector<T> operator*(const vector<T>& rhs) const;

		/*! \brief Clear function
		 *
		 * Description: Allows the user to clear a nTrix object.
		 * \post All of the calling object's data is erased and the size is set to
		 * 0x0.
		 */
		void clear();

		/*! \brief invert function
		 *
		 * Description: Inverts the calling object using the Newton-Schultz
		 * iterative method for inverting a matrix.
		 * \return Returns a nTrix<float> that represents the inverted calling
		 * object.
		 * \post Calls the r_invert() function to recursively iterate the matrix.
		 * \throw Throws a std::range_error object if the object is not a square
		 * matrix.
		 */
		nTrix<T> invert() const;

		/*! \brief Transpose function
		 *
		 * Description: Calculates the transpose of a matrix.
		 * \return Returns a new nTrix<T> that is the transpose of the calling
		 * object.
		 * \pre = operator must be defined for type T.
		 */
		nTrix<T> transpose() const;

		// Friends //

		/*! \brief << operator
		 *
		 * Description: << operator overloaded to pretty print the nTrix object.
		 * \param out is the ostream object passed to the function.
		 * \param rhs is the nTrix<T> object to be output.
		 * \return Returns the ostream.
		 * \pre << operator must be defined for type T.
		 * \post Outputs the matrix to the user.
		 */
		template <typename U>
		friend std::ostream& operator<<(std::ostream& out, const nTrix<U>& rhs);

		/*! \brief >> operator
		 *
		 * Description: >> operator overloaded to extract a matrix object from
		 * the istream. The inputted matrix overloads any previously stored data
		 * in the nTrix object.
		 * \param in is the istream object passed to the function.
		 * \param rhs is the nTrix<T> object to store the input.
		 * \return Returns the istream.
		 * \pre >> operator must be defined for type T.
		 * \post Stores the input in the object passed.
		 * \throw Throws a std::range_error object if the user inputs an incorrect
		 * number of items for a column.
		 */
		template <typename U>
		friend std::istream& operator>>(std::istream& in, nTrix<U>& rhs);
};

// Extras //

/*! \brief << operator
 *
 * Description: << operator overloaded to pretty print the nTrix object.
 * \param out is the ostream object passed to the function.
 * \param rhs is the nTrix<T> object to be output.
 * \return Returns the ostream.
 * \pre << operator must be defined for type T.
 * \post Outputs the matrix to the user.
 */
template <typename T>
std::ostream& operator<<(std::ostream& out, const nTrix<T>& rhs);

/*! \brief >> operator
 *
 * Description: >> operator overloaded to extract a matrix object from
 * the istream. The inputted matrix overloads any previously stored data
 * in the nTrix object.
 * \param in is the istream object passed to the function.
 * \param rhs is the nTrix<T> object to store the input.
 * \return Returns the istream.
 * \pre >> operator must be defined for type T.
 * \post Stores the input in the object passed.
 * \throw Throws a std::range_error object if the user inputs an incorrect
 * number of items for a column.
 */
template <typename T>
std::istream& operator>>(std::istream& in, nTrix<T>& rhs);

/*! \brief * operator
 *
 * Description: Scalar multiplication for a nTrix<T> object.
 * \param lhs is the nTrix<T> object to be multiplied through.
 * \param scalar is the scalar to multiply through the matrix.
 * \return Returns a new nTrix<T> object with the scalar
 * multiplied throughout.
 * \pre * operator must be defined for type T.
 */
template <typename T>
nTrix<T> operator*(const nTrix<T>& lhs, const float scalar);

/*! \brief * operator
 *
 * Description: * operator overload for the nTrix class that allows the user
 * to multiply a matrix with a vector.
 * \param lhs is a vector object to be multiplied to a nTrix.
 * \param rhs is a nTrix object to be multiplied to a vector.
 * \return Returns a nTrix<T> object with the proper dimensions and
 * with the values having matrix multiplicaion applied.
 * \pre * operator must be defined for type T.
 * \throw Throws a std::invalid_argument object if the two matrices are
 * not the correct dimensions for matrix multiplication to occur.
 */
template <typename T>
nTrix<T> operator*(const vector<T>& lhs, const nTrix<T>& rhs);

/*! \brief recursive invert
 *
 * Description: Recursive part of the invert function that iteratively
 * calculates the inverse of a matrix.
 * \param A is the matrix that the user wants the inverse of.
 * \param B is the previous version of one of the matrices needed in
 * the iterative calculation.
 * \param E is one of the matrices needed in the iterative calculation.
 * \param I is the identity matrix in the proper dimension of the matrix A.
 * \param Cerror is the current frobenius norm of matrix B.
 * \param Perror is the previous frobenius norm of  matrix B.
 * \return Returns an inverted matrix A.
 * \pre =, -, and * operators need to be defined for type T.
 */
template <typename T>
nTrix<T> r_invert(const nTrix<T>& A, nTrix<T>& B,
	nTrix<T>& E, const nTrix<T>& I,  T Cerror, T Perror);


#include "nTrix.hpp"
#endif
