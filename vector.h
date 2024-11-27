#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>
#include <utility>
#include <iostream>

using namespace std;

namespace mine 
{
        
    class concatenate_error : public invalid_argument 
    {
    public:
        explicit concatenate_error(const string& what_arg) : invalid_argument(what_arg) 
        {

        }
    };

    template <typename T>
    class Vector 
    {
    private:
        T* arrayofelements;
        size_t m_size;
        size_t m_capacity;

        void reallocate(size_t new_capacity);

    public:
        Vector();                                  
        explicit Vector(size_t count);            
        Vector(size_t count, const T& value);     
        Vector(const Vector& other);              
        Vector(Vector&& other) noexcept;          
        ~Vector();                                

        T& operator[](size_t pos);                
        T& at(size_t pos);                        
        T& front();                               
        T& back();                                

        bool empty() const noexcept;
        size_t size() const noexcept;
        size_t capacity() const noexcept;
        void reserve(size_t new_cap);
        void resize(size_t count) noexcept;

        void pushback(const T& value);
        void pushback(T&& value);
        void popback();
        void clear() noexcept;

        Vector& operator=(const Vector& other);
        Vector& operator=(Vector&& other) noexcept;

        Vector& operator+=(const T& value);
        Vector& operator+=(const Vector& other);
        Vector& operator++();
        Vector operator++(int);
        Vector& operator--();
        Vector operator--(int);
    };

    template <typename T>
    Vector<T>::Vector() : arrayofelements(nullptr), m_size(0), m_capacity(0) 
    {

    }

    template <typename T>
    Vector<T>::Vector(size_t count) : arrayofelements(new T[count]()), m_size(count), m_capacity(count) 
    {

    }

    template <typename T>
    Vector<T>::Vector(size_t count, const T& value) : Vector(count) 
    {
        for (size_t i = 0; i < count; ++i) 
        {
            arrayofelements[i] = value;
        }
    }

    template <typename T>
    Vector<T>::Vector(const Vector& other) : arrayofelements(new T[other.m_capacity]), m_size(other.m_size), m_capacity(other.m_capacity) 
    {
        for (size_t i = 0; i < m_size; ++i) 
        {
            arrayofelements[i] = other.arrayofelements[i];
        }
    }

    template <typename T>
    Vector<T>::Vector(Vector&& other) noexcept : arrayofelements(other.arrayofelements), m_size(other.m_size), m_capacity(other.m_capacity) 
    {
        other.arrayofelements = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }

    template <typename T>
    Vector<T>::~Vector() 
    {
        delete[] arrayofelements;
    }

    template <typename T>
    T& Vector<T>::operator[](size_t pos) 
    {
        return arrayofelements[pos];
    }

    template <typename T>
    T& Vector<T>::at(size_t pos) 
    {
        if (pos >= m_size) 
        {
            throw out_of_range("index out of range");
        }
        return arrayofelements[pos];
    }

    template <typename T>
    T& Vector<T>::front() 
    {
        if (empty()) 
        {
            throw out_of_range("Vector is empty");
        }
        return arrayofelements[0];
    }

    template <typename T>
    T& Vector<T>::back() 
    {
        if (empty()) 
        {
            throw out_of_range("Vector is empty");
        }
        return arrayofelements[m_size - 1];
    }

    template <typename T>
    bool Vector<T>::empty() const noexcept 
    {
        return m_size == 0;
    }

    template <typename T>
    size_t Vector<T>::size() const noexcept 
    {
        return m_size;
    }

    template <typename T>
    size_t Vector<T>::capacity() const noexcept 
    {
        return m_capacity;
    }

    template <typename T>
    void Vector<T>::reserve(size_t new_cap) 
    {
        if (new_cap > m_capacity) 
        {
            reallocate(new_cap);
        }
    }

    template <typename T>
    void Vector<T>::resize(size_t count) noexcept 
    {
        if (count > m_capacity) 
        {
            reserve(count);
        }
        m_size = count;
    }

    template <typename T>
    void Vector<T>::pushback(const T& value) 
    {
        if (m_size == m_capacity) 
        {
            reserve(m_capacity == 0 ? 1 : m_capacity * 2);
        }
        arrayofelements[m_size++] = value;
    }

    template <typename T>
    void Vector<T>::pushback(T&& value) 
    {
        if (m_size == m_capacity) 
        {
            reserve(m_capacity == 0 ? 1 : m_capacity * 2);
        }
        arrayofelements[m_size++] = move(value);
    }

    template <typename T>
    void Vector<T>::popback() 
    {
        if (empty()) 
        {
            throw out_of_range("empty vector");
        }
        --m_size;
    }

    template <typename T>
    void Vector<T>::clear() noexcept 
    {
        m_size = 0;
    }

    template <typename T>
    void Vector<T>::reallocate(size_t new_capacity) 
    {
        T* new_array = new T[new_capacity];
        for (size_t i = 0; i < m_size; ++i) 
        {
            new_array[i] = move(arrayofelements[i]);
        }
        delete[] arrayofelements;
        arrayofelements = new_array;
        m_capacity = new_capacity;
    }

    template <typename T>
    Vector<T>& Vector<T>::operator=(const Vector& other) 
    {
        if (this == &other) 
        {
            return *this;
        }
        delete[] arrayofelements;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        arrayofelements = new T[m_capacity];
        for (size_t i = 0; i < m_size; ++i) 
        {
            arrayofelements[i] = other.arrayofelements[i];
        }
        return *this;
    }

    template <typename T>
    Vector<T>& Vector<T>::operator=(Vector&& other) noexcept 
    {
        if (this == &other) 
        {
            return *this;
        }
        delete[] arrayofelements;
        arrayofelements = other.arrayofelements;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        other.arrayofelements = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
        return *this;
    }

    template <typename T>
    Vector<T>& Vector<T>::operator+=(const T& value) 
    {
        pushback(value);
        return *this;
    }

    template <typename T>
    Vector<T>& Vector<T>::operator+=(const Vector& other) 
    {
        if (empty() || other.empty()) 
        {
            throw concatenate_error("Can't concatenate empty vector");
        }
        reserve(m_size + other.m_size);
        for (size_t i = 0; i < other.m_size; ++i) 
        {
            pushback(other.arrayofelements[i]);
        }
        return *this;
    }

    template <typename T>
    Vector<T>& Vector<T>::operator++() 
    {
        T value = 1;
        pushback(value);
        return *this;
    }

    template <typename T>
    Vector<T> Vector<T>::operator++(int) 
    {
        Vector temp(*this);
        ++(*this);
        return temp;
    }

    template <typename T>
    Vector<T>& Vector<T>::operator--() 
    {
        if (empty()) 
        {
            throw out_of_range("empty vector");
        }
        for (size_t i = 1; i < m_size; ++i) 
        {
            arrayofelements[i - 1] = move(arrayofelements[i]);
        }
        --m_size;
        return *this;
    }

    template <typename T>
    Vector<T> Vector<T>::operator--(int) 
    {
        Vector temp(*this);
        --(*this);
        return temp;
    }

}

#endif