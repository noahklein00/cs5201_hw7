/**
 * @file    vector.h
 * @author  Jeffrey Strahm
 * @brief   class: CS5201 - Prof. Price
 * @brief   Homework 7 - Complex Numbers, Outer Products, and Quantum Computing
 * @brief   Due: 5/10/2020
 * @date    5/2/2020
 *
 * @brief   This is the vector class definition. This is used to store data in
 *          an array. It can support any type as long as the type supports =,
 *          binary +, *, and - preforming their namesake operations and
 *          returning T, +=, *=, -=, preforming their namesake operations and
 *          returning T, unary -, a default constructor, >>, <<, (double),
 *          and a copy constructor.
*/

#include <ostream>
#include <istream>
#include <iostream>
#include <sstream>
#include <initializer_list>
#include <cstddef>
#include <exception>
#include <algorithm>
#include <functional>

#ifndef VECTOR_H
#define VECTOR_H

/**
 * @class   vector
 * @brief   stores data of type T in a resizable array. It can modify the array
 *          with addition, subtraction, vector multiplication, dot products,
 *          unary minus, and scalar multiplication
 *
 * @tparam  the type T is the type of data stored
 * @remark  type T must support =, +, *,and - as binary operations preforming
 *          their namesake operatations, +=, *=, -=, as the assignment variant
 *          of their binary operations, unary - to invert the value, a default
 *          constructor, >>, <<, (double) casting, and a copy constructor
 */
template <class T>
class vector
{
    private:
        std::size_t m_size;
        T* m_data;

        /**
         * @class   Iterator
         * @brief   used to create an iterator the allows non const range based
         *          for loops
         *
         * @tparam  the type T is the type of data stored
         */
        class Iterator {
            private:
                T* i_data;
                std::size_t m_pos;
            public:
                /********************* iterator functions *********************/
                /**
                * @brief    creates a iterator for a vector of type T
                * @pre      N/A
                * @post     creates a iterator
                *
                * @param    data - the data that the iterator goes through
                * @param    pos - the location along the list it will start at
                */
                Iterator(T* data, std::size_t pos) noexcept;

                /**
                * @brief    returns the value of an iterator position
                * @pre      N/A
                * @post     returns the value of the current iterator position
                *
                * @return   reference to the currently pointed to object
                */
                T& operator*() noexcept;

                /**
                * @brief   Goes to the next item in the vector
                * @pre     N/A
                * @post    modifies the iterator to point at the next
                *          position
                *
                * @return   reference to the iterator.
                */
                Iterator& operator++() noexcept;

                /**
                * @brief    Checks if the iterator is not equal to another
                *           iterator
                * @pre      N/A
                * @post     returns if they are pointing to the same
                *           position
                *
                * @param    it - the other iterator used in the comparison
                *
                * @return   if the two iterators are equivalent.
                */
                bool operator!=(const Iterator& it) const noexcept;
        };

        /**
         * @class   ConstIterator
         * @brief   used to create an iterator the allows non const range based
         *          for loops
         *
         * @tparam  the type T is the type of data stored
         */
        class ConstIterator {
            private:
                T* i_data;
                std::size_t m_pos;
            public:
                /********************* iterator functions *********************/
                /**
                * @brief    creates a const iterator for a vector of type T
                * @pre      N/A
                * @post     creates a const iterator
                *
                * @param    data - the data that the iterator goes through
                * @param    pos - the location along the list it will start at
                */
                ConstIterator(T* data, std::size_t pos) noexcept;

                /**
                * @brief    returns a const value of an iterator position
                * @pre      N/A
                * @post     returns the const value of the current iterator
                *           position
                *
                * @return   a const reference to the pointed at object
                */
                const T& operator*() const noexcept;

                /**
                * @brief    Goes to the next item in the vector
                * @pre      N/A
                * @post     modifies the iterator to point at the next
                *           position
                *
                * @return   const reference to the iterator
                */
                ConstIterator& operator++() noexcept;

                /**
                * @brief    Checks if the const iterator is not equal to another
                *           const iterator
                * @pre      N/A
                * @post     returns if they are pointing to the same
                *           position
                *
                * @param    it - the other iterator used in the comparison
                *
                * @return   if the two iterators are equivalent.
                */
                bool operator!=(const ConstIterator& it) const noexcept;
        };

        /********************* other functions *********************/
        /**
        * @brief    prints out and throws a length error
        * @pre      N/A
        * @post     ends the program
        *
        * @exception    throws a length error.
        *
        * @param    msg - the message printed to explain the error
        */
        void lenError(const std::string& msg) const;

        /**
        * @brief    takes x to the power of y
        * @pre      y must be a whole number
        * @post     resturn the result of x being multiplied by it'self y times
        *
        * @param    x - the number to be multiplied/divided.
        * @param    y - the number of times x is multiplied/divided.
        *
        * @return   the result of x being multiplied by it'self y times
        */
        double exp(double x, long y) const noexcept;

        /**
        * @brief    find a number that when multiplied n times equals num using
        *           newton's method
        * @pre      n must be a positive whole number
        * @post     return the result found to be the n root of num
        *
        * @param    num - the number that the root will be found for
        * @param    n - the degree of the root to be found
        *
        * @return   the result found to be the n root of num
        */
        double root(double num, long n) const noexcept;
    public:
        /********************* constructor/destructors *********************/
        /**
        * @brief    creates a vector of type T
        * @pre      type T must have the copy = operator
        * @post     modifies the vectors size and data to match the passed list
        *
        * @param    data - the list the vector will be set to match
        */
        explicit vector(const std::initializer_list<T>& data) noexcept
            : m_size(data.size())
            , m_data(new T[data.size()])
        {
            std::size_t loc = 0;
            for (const T item : data)
            {
                m_data[loc] = item;
                loc++;
            }
        };

        /**
        * @brief    creates a vector of type T
        * @pre      type T must have a default constructor, and copy = operator
        * @post     modifies the vector to be a list of the passed size full of
        *           default values
        *
        * @param    size - the size the vector will be
        */
        explicit vector(std::size_t size = 10) noexcept
            : m_size(size)
            , m_data(new T[size])
        {
            for (std::size_t loc = 0; loc < m_size; loc++)
            {
                m_data[loc] = T();
            }
        };

        /**
        * @brief    creates a vector of type T
        * @pre      type T must have a copy = operator
        * @post     modifies the vector size and data to match the passed vector
        *
        * @param    source - the vector to be copied
        */
        vector(const vector<T>& source) noexcept
            : m_size(source.size())
            , m_data(new T[m_size])
        {
            std::size_t loc = 0;
            for (const T item : source)
            {
                m_data[loc] = item;
                loc++;
            }
        };

        /**
        * @brief    destroys the vector
        * @pre      N/A
        * @post     safely deletes the vector
        */
        ~vector() noexcept;

        /********************* other functions *********************/
        /**
        * @brief    changes the size of the vector to match the passed value
        * @pre      type T must support the copy = operator
        * @post     changes the vectors size to match the value. Excess data is
        *           removed
        *
        * @param    size - the new size of the vector
        */
        void resize(std::size_t size) noexcept;

        /**
        * @brief    returns the size of the vector
        * @pre      N/A
        * @post     returns the size of the vector
        *
        * @return   the size of the vector.
        */
        std::size_t size() const noexcept;

        /**
        * @brief    returns a vector instance where the function is run on every
        *           value in the vecctor
        * @pre      The function must take in and return the type of the vector,
        *           and the passed value must be a constant. type T must support
        *           the copy = operator, and any other operators needed for the
        *           function
        * @post     returns a new vector instance where every value was run
        *           through the function
        *
        * @param    f - must be of the same type as the array
        *
        * @return   a new vector modified by the function.
        */
        vector<T> apply(std::function<T(const T)> f) const noexcept;

        /********************* operator functions *********************/
        /**
        * @brief    copies another vector by assignment
        * @pre      Type T must support the copy = operator
        * @post     returns a new vector instance that is the came as the source
        *
        * @param    source - the vector to be copied
        *
        * @return   returns a vector of the same type
        */
        vector<T>& operator = (const vector<T>& source) noexcept;

        /**
        * @brief    used to fetch and possibly modify a vector item.
        * @pre      the index must be smaller than the size of the vector
        * @post     returns a reference to the designated item in the vector
        *
        * @exception    a length error if the index is too large
        *
        * @param    index - the location the desired information is at
        *
        * @return   A reference to an item in the vector
        */
        T& operator [] (std::size_t index);

        /**
        * @brief    used to fetch a item at a specific index.
        * @pre      the index must be smaller than the size of the vector
        * @post     returns a constant reference to an item in the vector
        *
        * @exception    a length error if the index is too large
        *
        * @param    index - the location the desired information is at
        *
        * @return   A const reference to an item in the vector
        */
        const T& operator [] (std::size_t index) const;

        /**
        * @brief    used to preform a unary minus operation on all values of the
        *           vector.
        * @pre      Type T must support the copy = operator and unary - operator
        *           which returns the inverted value of T
        * @post     returns a new vector where every value had a unary value
        *           preformed on it
        *
        * @return   a new vector of the same type.
        */
        vector<T> operator-() const noexcept;

        /**
        * @brief    used to subtract two vectors
        * @pre      both vectors must be the same length. Type T must support
        *           the copy = operator and the - operator defined for T - T
        *           returning T
        * @post     returns a new vector that is the result of the subtraction
        *
        * @exception    a length error if the vectors aren't the same length
        *
        * @param    li - the left vector of the subtraction
        * @param    ri - the right vector of the subraction
        *
        * @return   a new vector of the same type
        */
        template <class R>
        friend vector<R> operator - (const vector<R>& li, const vector<R>& ri);

        /**
        * @brief    used to subtract each value of a vector by the values of
        *           another
        * @pre      both vectors must be the same length. Type T must support
        *           the -= operator which should preform the T -= T operation
        *           returning T
        * @post     modifies the vector by the subtraction
        *
        * @exception    a length error if the vectors aren't the same length
        *
        * @param    i - the other vector that will decrease the source vector
        *
        * @return   a reference to the vector object
        */
        vector<T>& operator -= (const vector<T>& i);

        /**
        * @brief    used to add two vectors
        * @pre      both vectors must be thw same length. Type T must support
        *           the copy = operator and the + operator preforming T + T
        *           returning T
        * @post     returns a nev vector that is the result of the addition
        *
        * @exception    a length error if the vectors aren't the same length
        *
        * @param    li - the left vector in the addition
        * @param    ri - the right vector in the addition
        *
        * @return   a new vector of the same type
        */
        template <class R>
        friend vector<R> operator + (const vector<R>& li, const vector<R>& ri);

        /**
        * @brief    used to add each value of a vector by the value of another
        * @pre      both vectors must be the same length. Type T must support
        *           the += operator which should preform T += T and return T
        * @post     modifies the vector by the addition
        *
        * @exception    a length error if the vectors aren't the same length
        *
        * @param    i - the other vector that will increase the source vector
        *
        * @return   a reference to the vector
        */
        vector<T>& operator += (const vector<T>& i);

        /**
        * @brief    find the dot product of two vectors
        * @pre      both vectors must be the same length. Type T must support
        *           the copy = operator, the * operator which preforms the T * T
        *           operation and return T, and the += operator
        * @post     returns the result of the dot product
        *
        * @exception    a length error if the vectors aren't the same length
        *
        * @param    li - the left vector in the multiplication
        * @param    ri - the right vector in the multiplication
        *
        * @return   a value of the same type as the vector
        */
        template <class R>
        friend R operator * (const vector<R>& li, const vector<R>& ri);

        /**
        * @brief    preforms a scalar multiplication on the vector
        * @pre      Type T must support the copy = operator, and the * operator
        *           which preforms the T * T operation
        * @post     returns a new vector where each value is multiplied by the
        *           scalar
        *
        * @param    li - the scalar that will be multiplied into the
        *           vector
        * @param    ri - the vector to be multiplied
        *
        * @return   a new vector of the same type
        */
        template <class R>
        friend vector<R> operator * (const R& li, const vector<R>& ri) noexcept;

        /**
        * @brief    preforms a scalar multiplication on the vector
        * @pre      Type T must support the copy = operator, and the * operator
        *           which returns the T * T operation returning T
        * @post     returns a new vector where each value is multiplied by the
        *           scalar
        *
        * @param    li - the vector to be multiplied
        * @param    ri - the scalar that will be multiplied into the
        *           vector
        *
        * @return   a new vector of the same type
        */
        template <class R>
        friend vector<R> operator * (const vector<R>& li, const R& ri) noexcept;

        /**
        * @brief    used to multiply each value of the vector by the scalar.
        * @pre      Type T must support the copy = operator, and the *= operator
        *           which preforms the Tv *= T operation returning T
        * @post     modifies the vector by the multiplication
        *
        * @param    i - the scalar that will be multiplied into the
        *           vector
        *
        * @return   a reference to the vector
        */
        vector<T>& operator *= (const T& i) noexcept;

        /**
        * @brief    used to find the p-norm of a vector
        * @pre      paramater p must be a positive whole number. Type T must be
        *           able to be explicitly converted to a double
        * @post     returns the p-norm of a vector as a double
        *
        * @exception    a domain if p is less than 0 or not a whole number
        *
        * @param    p - the degree of norm that will be found
        *
        * @return   the p-norm of a vector as a double
        */
        double operator ^ (unsigned long p) const noexcept;

        /**
        * @brief    used to take in the data of a list via input from a istream
        * @pre      The incoming list must be space deliminated. Type T must
        *           support the >> operator
        * @post     sets the vectors size and value to the data read in
        *
        * @param    in - the istream that takes in the input
        * @param    i - the vector the data will be put into
        *
        * @return   a refernce to the istream
        */
        template <class R>
        friend std::istream& operator >> (std::istream& in, vector<R>& i)
                                                                       noexcept;

        /**
        * @brief    used to print out the data of the list to a ostream
        * @pre      Type T must support the << operator
        * @post     print out the list in a space deliminated fashion
        *
        * @param    out - the ostream that takes in the output
        * @param    i - the vector the data will be print from
        *
        * @return   a reference to the ostream
        */
        template <class R>
        friend std::ostream& operator << (std::ostream& out,
                                          const vector<R>& i) noexcept;

        /**
        * @brief    Used to convert the vector into a double
        * @pre      Type T must be explicitly convertable into a double
        * @post     return a double equivalent of the vector.
        *
        * @return   the double equivalent of the vector
        */
        explicit operator double () const noexcept;

        /********************* constiterator begin/end *********************/
        /**
        * @brief    used to create a iterator that points to the
        *           beginning of the vector
        * @pre      N/A
        * @post     creates a iterator that points to the start of the
        *           list
        *
        * @return   an iterator that points to the beginning of the list
        */
        Iterator begin() noexcept;

        /**
        * @brief    used to create a iterator that points to the end of
        *           the vector
        * @pre      N/A
        * @post     creates a iterator that points to the end of the
        *           list
        *
        * @return   an iterator that points to the end of the list
        */
        Iterator end() noexcept;

        /********************* constiterator begin/end *********************/
        /**
        * @brief    used to create a const iterator that points to the
        *           beginning of the vector
        * @pre      N/A
        * @post     creates a const iterator that points to the start of
        *           the list
        *
        * @return   a const iterator that points to the beginning of the
        *           list
        */
        ConstIterator begin() const noexcept;

        /**
        * @brief    used to create a const iterator that points to the
        *           end of the vector
        * @pre      N/A
        * @post     creates a const iterator that points to the end of
        *           the list
        *
        * @return   a const iterator that points to the end of the list
        */
        ConstIterator end() const noexcept;
};

#include "vector.hpp"
#endif /* VECTOR_H */
