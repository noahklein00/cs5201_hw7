// Programmer : Noah Klein and Jeffrey Strahm
// Instructor : Price
// Class      : CS5201 Spring 2020
// Assignment : Homework 7 (Final Project) - Image Analysis with Poisson's
//				Equation
// Filename   : nTrix.hpp

//***************************** Essentials **********************************//
template <typename T>
nTrix<T>& nTrix<T>::operator=(const nTrix<T>& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

	delete[] m_matrix;

	m_row = rhs.m_row;
	m_col = rhs.m_col;
	m_matrix = new T[m_row*m_col];

	for(int i = 0; i < m_row; i++)
	{
		for(int j = 0; j < m_col; j++)
		{
			m_matrix[(i * m_col) + j] = rhs.m_matrix[(i * rhs.m_col) + j];
		}
	}

	return *this;
}

template <typename T>
nTrix<T>::~nTrix()
{
	delete[] m_matrix;
	m_matrix = NULL;
}

//***************************** Accessors ***********************************//

template <typename T>
short nTrix<T>::rows() const
{
	return m_row;
}

template <typename T>
short nTrix<T>::cols() const
{
	return m_col;
}

template <typename T>
const T& nTrix<T>::operator()(const int row_index, const int col_index) const
{
	if(row_index < 0 || row_index >= m_row)
	{
		throw(std::domain_error(std::to_string(row_index)));
	}
	if(col_index < 0 || col_index >= m_col)
	{
		throw(std::domain_error(std::to_string(col_index)));
	}

	return m_matrix[(row_index * this->m_col) + col_index];
}

template <typename T>
T nTrix<T>::one_norm() const
{
	T col_sum = T(0); //individual column sums
	T max_sum = T(0); //maximum column sum

	for(int i = 0; i < this -> cols(); ++i)
	{
		for(int j = 0; j < this -> rows(); ++j)
		{
			col_sum += std::abs(this -> m_matrix[(j * this->m_col) + i]);
		}
		if(i == 0)
		{
			max_sum = col_sum;
		}
		else
		{
			if(col_sum > max_sum)
			{
				max_sum = col_sum;
			}
		}
		col_sum = T(0);
	}
	return max_sum;
}

template <typename T>
T nTrix<T>::infinity_norm() const
{
	T row_sum = T(0); //individual row sums
	T max_sum = T(0); //maximum row sum

	for(int i = 0; i < this -> rows(); ++i)
	{
		for(int j = 0; j < this -> cols(); ++j)
		{
			row_sum += std::abs(this -> m_matrix[(i * this->m_col) + j]);
		}
		if(i == 0)
		{
			max_sum = row_sum;
		}
		else
		{
			if(row_sum > max_sum)
			{
				max_sum = row_sum;
			}
		}
		row_sum = T(0);
	}
	return max_sum;
}

template <typename T>
T nTrix<T>::frobenius() const
{
	T norm = T(0);
	for(int i = 0; i < this -> rows(); i++)
	{
		for(int j = 0; j < this -> cols(); j++)
		{
			norm += (this -> m_matrix[(i * this->m_col) + j] * this ->
				m_matrix[(i * this->m_col) + j]);
		}
	}
	return sqrt(norm);
}

//***************************** Mutators ************************************//

template <typename T>
T& nTrix<T>::operator()(const int row_index, const int col_index)
{
	if(row_index < 0 || row_index >= m_row)
	{
		throw(std::domain_error(std::to_string(row_index)));
	}
	if(col_index < 0 || col_index >= m_col)
	{
		throw(std::domain_error(std::to_string(col_index)));
	}

	return m_matrix[(row_index * m_col) + col_index];
}

template <typename T>
nTrix<T> nTrix<T>::operator+(const nTrix<T>& rhs) const
{
	if(this -> rows() != rhs.rows())
	{
		throw(std::invalid_argument(std::to_string(this -> rows())));
	}
	if(this -> cols() != rhs.cols())
	{
		throw(std::invalid_argument(std::to_string(this -> cols())));
	}

	nTrix<T> copy(*this);

	for(int i = 0; i < copy.m_row; i++)
	{
		for(int j = 0; j < copy.m_col; j++)
		{
			copy.m_matrix[(i * m_col) + j] += rhs.m_matrix[(i * rhs.m_col) + j];
		}
	}

	return copy;
}

template <typename T>
nTrix<T> nTrix<T>::operator-(const nTrix<T>& rhs) const
{
	return *this + (-rhs);
}

template <typename T>
nTrix<T> nTrix<T>::operator-() const
{
	return (*this*(-1));
}

template <typename T>
nTrix<T> nTrix<T>::operator*(const nTrix<T>& rhs) const
{
	if(this -> cols() != rhs.rows())
	{
		throw(std::invalid_argument(std::to_string(this -> cols())));
	}

	T sum = 0;

	nTrix<T> copy(this -> rows(),rhs.cols());

	for(int i = 0; i < copy.rows(); i++)
	{
		for(int j = 0; j < copy.cols(); j++)
		{
			for(int k = 0; k < rhs.rows(); k++)
			{
				sum += (this -> m_matrix[(i * this->m_col) + k] *
					rhs.m_matrix[(k * rhs.m_col) + j]);
			}
			copy.m_matrix[(i * copy.m_col) + j] = sum;
			sum = 0;
		}
	}

	return copy;
}

template <typename T>
vector<T> nTrix<T>::operator*(const vector<T>& rhs) const
{
	if(this -> cols() != rhs.size())
	{
		throw(std::invalid_argument(std::to_string(rhs.size())));
	}

	vector<T> ret_vect(rhs.size());
	T temp;
	temp = 0;

	for(int i = 0; i < this -> rows(); ++i)
	{
		for(int j = 0; j < this -> cols(); ++j)
		{
			temp = temp + (this -> m_matrix[(i * this->m_col) + j] * rhs[j]);
		}
		ret_vect[i] = temp;
		temp = 0;
	}
	return ret_vect;
}

template <typename T>
void nTrix<T>::clear()
{
	delete[] m_matrix;
	m_matrix = NULL;
	m_row = 0;
	m_col = 0;
}

template <typename T>
nTrix<T> nTrix<T>::invert() const
{
	if(this -> rows() != this -> cols())
	{
		std::cout << "Cannot invert non square matrix: ";
		throw(std::range_error(std::to_string(this -> rows())));
	}

	nTrix<T> copy(*this);
	T t = T(1)/((this -> infinity_norm()) * (this -> one_norm()));
	nTrix<T> B = t * (this -> transpose());
	nTrix<T> identity(this -> cols(), this -> cols());

	for(int i = 0; i < identity.rows(); i++)
	{
		for(int j = 0; j < identity.cols(); j++)
		{
			if(i == j)
			{
				identity.m_matrix[(i * identity.m_col) + j] = T(1);
			}
			else
			{
				identity.m_matrix[(i * identity.m_col) + j] = T(0);
			}
		}
	}
	nTrix<T> E = identity - (B * *this);

	return r_invert(*this, B, E, identity, B.frobenius(), T(0));
}

template <typename T>
nTrix<T> nTrix<T>::transpose() const
{
	nTrix<T> copy(this -> cols(), this -> rows());

	for(int i = 0; i < this -> rows(); ++i)
	{
		for(int j = 0; j < this -> cols(); ++j)
		{
			copy.m_matrix[(j * m_col) + i] = this -> m_matrix[(i * m_col) + j];
		}
	}
	return copy;
}

//***************************** Friends *************************************//

template <typename T>
std::ostream& operator<<(std::ostream& out, const nTrix<T>& rhs)
{
	for(int i = 0; i < rhs.m_row; i++)
	{
		for(int j = 0; j < rhs.m_col; j++)
		{
			out << rhs.m_matrix[(i * rhs.m_col) + j] << " ";
		}
		if(i < rhs.m_row -1)
		{
			out << std::endl;
		}
	}
	return out;
}

template <typename T>
std::istream& operator>>(std::istream& in, nTrix<T>& rhs)
{
	std::string line = "";
	std::size_t rows = 1;
	std::size_t cols = 1;
	std::getline(in, line);
	for (char character : line)
	{
			if (character == ' ')
			{
					cols++;
			}
	}
	if (line.size() <= 0)
	{
			cols = 0;
			rows = 0;
	}

	std::string data = line;
	getline(in, line);

	while (line.size() > 1)
	{
		data = data + " " + line;

		std::size_t curCols = 1;
		for (char character : line)
		{
			if (character == ' ')
			{
				curCols++;
			}
		}
		if (curCols != cols)
		{
			const std::string err = "input matrix must be a constant size. "
									"input line: " + std::to_string(cols) +
									", latest number of columns: " +
									std::to_string(curCols);
			throw(std::length_error(err));
		}

		rows++;
		getline(in, line);
	}
	nTrix<T> result(rows, cols);

	std::stringstream input(data);
	for (std::size_t row = 0; row < rows; row++)
	{
		for (std::size_t col = 0; col < cols; col++)
		{
			input >> result.m_matrix[(row * result.m_col) + col];
		}
	}

	rhs = result;

	return in;
}

//***************************** Extras **************************************//

template <typename T>
nTrix<T> operator*(const nTrix<T>& lhs, const float scalar)
{
	nTrix<T> copy(lhs);
	for(int i = 0; i < copy.rows(); i++)
	{
		for(int j = 0; j < copy.cols(); j++)
		{
			copy(i,j) *= scalar;
		}
	}
	return copy;
}

template <typename T>
nTrix<T> operator*(const float scalar, const nTrix<T>& rhs)
{
	return (rhs*scalar);
}

template <typename T>
nTrix<T> operator*(const vector<T>& lhs, const nTrix<T>& rhs)
{
	nTrix<T> copy(lhs);
	return copy * rhs;
}

template <typename T>
nTrix<T> r_invert(const nTrix<T>& A, nTrix<T>& B,
	nTrix<T>& E, const nTrix<T>& I,  T Cerror, T Perror)
{
	B = (I + E) * B;
	Perror = Cerror;
	Cerror = B.frobenius();

	if(((std::abs(Cerror - Perror)/Perror) * 100) < .0001)
	{
		return B;
	}
	else
	{
		E = I - (B * A);
		return r_invert(A, B, E, I, Cerror, Perror);
	}
}
