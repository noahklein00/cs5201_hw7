/**
 * @file    vector.hpp
 * @author  Jeffrey Strahm and Noah Klein
 * @brief   class: CS5201 - Prof. Price
 * @brief   Homework 7 (Final Project) - Image Analysis with Poisson's Equation
 * @brief   Due: 5/10/2020
 * @date    5/10/2020
 * 
*/

// constant for error used by the root function.
const double ERROR = .000001;

/********************* constructor/destructors *********************/
template <class T>
vector<T>::~vector() noexcept
{
    delete[] m_data;
}
/********************* other functions *********************/
template <class T>
void vector<T>::resize(std::size_t size) noexcept
{
    if (size != m_size)
    {
        if (size < 0)
        {
            const std::string err = "vector must be a positive size. Passed "
                                    "size: " + std::to_string(size);
            lenError(err);
        }
        T* newData = new T[size];
        for (std::size_t loc = 0; loc < std::min(size, m_size); loc++)
        {
            newData[loc] = m_data[loc];
        }
        for (std::size_t loc = std::min(size, m_size); loc < size; loc++)
        {
            newData[loc] = T();
        }
        delete[] m_data;
        m_data = newData;
        m_size = size;
    }
}

template <class T>
std::size_t vector<T>::size() const noexcept
{
    return m_size;
}

template <class T>
vector<T> vector<T>::apply(std::function<T(const T)> f) const noexcept
{
    vector<T> copy(m_size);

    for (std::size_t loc = 0; loc < m_size; loc++)
    {
        copy[loc] = f(m_data[loc]);
    }

    return copy;
}

template <class T>
void vector<T>::lenError(const std::string& msg) const
{
    std::cout << msg << std::endl;
    throw std::length_error(msg);
}

template <class T>
double vector<T>::exp(double x, long y) const noexcept
{
    if (y == 0)
    {
        return 1;
    }
    double result = exp(x, y / 2);
    if (y % 2 == 0)
    {
        return result * result;
    }
    else
    {
        if (y < 0)
        {
            return (result * result) / x;
        }
        else
        {
            return x * result * result;
        }
    }
}

template <class T>
double vector<T>::root(double num, long n) const noexcept
{
    if (n < 0)
    {
        return 1/root(num, -n);
    }
    double x = num * 0.5;
    double dx = (num/exp(x,n-1)-x)/n;
    while(dx >= ERROR || dx <= -ERROR){
        x = x + dx;
        dx = (num/exp(x,n-1)-x)/n;
    }

    return x;
}
/********************* operator functions *********************/
template <class T>
vector<T>& vector<T>::operator = (const vector<T>& source) noexcept
{
    delete[] m_data;
    m_size = source.size();
    m_data = new T[m_size];
    for (std::size_t loc = 0; loc < m_size; loc++)
    {
        m_data[loc] = source[loc];
    }

    return (*this);
}

template <class T>
T& vector<T>::operator [] (std::size_t index)
{
    if (index >= m_size)
    {
        const std::string err = "index: " + std::to_string(index) + " is less" +
                                " than 0 or greater than the vector size of " +
                                std::to_string(m_size);
        lenError(err);
    }

    return m_data[index];
}

template <class T>
const T& vector<T>::operator [] (std::size_t index) const
{
    if (index > m_size)
    {
        const std::string err = "index: " + std::to_string(index) + " is less" +
                                " than 0 or greater than the vector size of " +
                                std::to_string(m_size);
        lenError(err);
    }

    return m_data[index];
}

template <class T>
vector<T> vector<T>::operator-() const noexcept
{
    vector<T> copy(m_size);
    for(std::size_t loc = 0; loc < m_size; loc++)
    {
        copy[loc] = -m_data[loc];
    }

    return copy;
}

template <class T>
vector<T> operator - (const vector<T>& li, const vector<T>& ri)
{
    if (li.size() != ri.size())
    {
        const std::string err = "vectors must be the same size. left vector "
                                "size: " + std::to_string(li.size()) + " right "
                                "vector size: " + std::to_string(ri.size());
        li.lenError(err);
    }

    vector<T> copy(li.size());

    for (std::size_t loc = 0; loc < li.size(); loc++)
    {
        copy[loc] = li[loc] - ri[loc];
    }

    return copy;
}

template <class T>
vector<T>& vector<T>::operator -= (const vector<T>& i)
{
    if (m_size != i.size())
    {
        const std::string err = "vectors must be the same size. left vector "
                                "size: " + std::to_string(m_size) + " right "
                                "vector size: " + std::to_string(i.size());
        lenError(err);
    }

    for (std::size_t loc = 0; loc < i.size(); loc++)
    {
        m_data[loc] -= i[loc];
    }

    return (*this);
}

template <class T>
vector<T> operator + (const vector<T>& li, const vector<T>& ri)
{
    if (li.size() != ri.size())
    {
        const std::string err = "vectors must be the same size. left vector "
                                "size: " + std::to_string(li.m_size) + " right "
                                "vector size: " + std::to_string(ri.m_size);
        li.lenError(err);
    }

    vector<T> copy(li.size());

    for (std::size_t loc = 0; loc < li.size(); loc++)
    {
        copy[loc] = li[loc] + ri[loc];
    }

    return copy;
}

template <class T>
vector<T>& vector<T>::operator += (const vector<T>& i)
{
    if (m_size != i.size())
    {
        const std::string err = "vectors must be the same size. left vector "
                                "size: " + std::to_string(m_size) + " right "
                                "vector size: " + std::to_string(i.size());
        lenError(err);
    }

    std::size_t loc = 0;
    for (const T item : i)
    {
        m_data[loc] += item;
        loc++;
    }

    return (*this);
}

template <class T>
T operator * (const vector<T>& li, const vector<T>& ri)
{
    if (li.size() != ri.size())
    {
        const std::string err = "vectors must be the same size. left vector "
                                "size: " + std::to_string(li.size()) + " right "
                                "vector size: " + std::to_string(ri.size());
        li.lenError(err);
    }

    T result = T();

    for (std::size_t loc = 0; loc < li.size(); loc++)
    {
        result += li[loc] * ri[loc];
    }

    return result;
}

template <class T>
vector<T> operator * (const T& li, const vector<T>& ri) noexcept
{
    vector<T> copy(ri);

    for (std::size_t loc = 0; loc < ri.size(); loc++)
    {
        copy[loc] = copy[loc] * li;
    }

    return copy;
}

template <class T>
vector<T> operator * (const vector<T>& li, const T& ri) noexcept
{
    vector<T> copy(li);

    for (std::size_t loc = 0; loc < li.size(); loc++)
    {
        copy[loc] = copy[loc] * ri;
    }

    return copy;
}

template <class T>
vector<T>& vector<T>::operator *= (const T& i) noexcept
{
    for (std::size_t loc = 0; loc < m_size; loc++)
    {
        m_data[loc] *= i;
    }

    return (*this);
}

template <class T>
double vector<T>::operator ^ (unsigned long p) const noexcept
{
    double sum = 0;
    for (std::size_t loc = 0; loc < m_size; loc++)
    {
        double val = (m_data[loc] < 0) ? static_cast<double>(-m_data[loc])
                                       : static_cast<double>(m_data[loc]);
        sum += exp(val, p);
    }
    return root(sum, p);
}

template <class T>
std::istream& operator >> (std::istream& in, vector<T>& i) noexcept
{
    
    std::string line;
    line = "";
    std::size_t size = 1;
    std::getline(in, line);
    for (char character : line)
    {
        if (character == ' ')
        {
            size++;
        }
    }
    if (line.size() <= 0)
    {
        size = 0;
    }

    vector<T> list(size);

    std::stringstream input(line);
    for (std::size_t loc = 0; loc < list.size(); loc++)
    {
        input >> list[loc];
    }
    i = list;

    return in;
}

template <class T>
std::ostream& operator << (std::ostream& out, const vector<T>& i) noexcept
{
    for (std::size_t loc = 0; loc < i.m_size; loc++)
    {
        out << i[loc];
        if (loc != i.m_size - 1)
        {
            out << " ";
        }
    }

    return out;
}

template <class T>
vector<T>::operator double() const noexcept
{
    return (*this)^2l;
}
/********************* iterator functions *********************/
template <class T>
vector<T>::Iterator::Iterator(T* data, std::size_t pos) noexcept
{
    i_data = data;
    m_pos = pos;
}

template <class T>
T& vector<T>::Iterator::operator*() noexcept
{
    return i_data[m_pos];
}

template <class T>
typename vector<T>::Iterator& vector<T>::Iterator::operator++() noexcept
{
    m_pos++;
    return *this;
}

template <class T>
bool vector<T>::Iterator::operator!=(const Iterator& it) const noexcept
{
    return m_pos != it.m_pos;
}
/********************* constiterator functions *********************/
template <class T>
vector<T>::ConstIterator::ConstIterator(T* data, std::size_t pos) noexcept
{
    i_data = data;
    m_pos = pos;
}

template <class T>
const T& vector<T>::ConstIterator::operator*() const noexcept
{
    return i_data[m_pos];
}

template <class T>
typename vector<T>::ConstIterator& vector<T>::ConstIterator::operator++()
                                                                        noexcept
{
    m_pos++;
    return *this;
}

template <class T>
bool vector<T>::ConstIterator::operator!=(const ConstIterator& it) const
                                                                   noexcept
{
    return m_pos != it.m_pos;
}
/********************* iterator begin/end *********************/
template <class T>
typename vector<T>::Iterator vector<T>::begin() noexcept
{
    return Iterator(m_data, 0);
}

template <class T>
typename vector<T>::Iterator vector<T>::end() noexcept
{
    return Iterator(m_data, m_size);
}
/********************* constiterator begin/end *********************/
template <class T>
typename vector<T>::ConstIterator vector<T>::begin() const noexcept
{
    return ConstIterator(m_data, 0);
}

template <class T>
typename vector<T>::ConstIterator vector<T>::end() const noexcept
{
    return ConstIterator(m_data, m_size);
}