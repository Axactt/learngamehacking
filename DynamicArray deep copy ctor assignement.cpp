template<typename T>
class DynamicArray
{
private:
    int m_length{};
    T* m_array{};
public:
    DynamicArray( int length )
        :m_length{ length }, m_array{ new T[length] }
    {

    }
    ~DynamicArray()
    {
        delete[] m_array;
        m_array = nullptr;
    }
    //copy constructor doing deep copy
    DynamicArray( const DynamicArray& a )
        //copy length with shallow-copy
        : m_length( a.m_length )
    {
        //dynamically allocate mem0ry for array type T using array version of new 
        m_array = new T[m_length];
        //deep copy the contents of array
        for (int i{ 0 }; i < m_length; ++i)
            m_array[i] = a.m_array[i];
    }
    //copy assignement operator doing deep copy

    DynamicArray& operator=( const DynamicArray& a )
    {
        //self-assignement check 
        if (&a = this)
            return *this;
        // Deallocate the previous resources if any
        delete[]m_array;
        //copy the length with shallow-copy
        m_length = a.m_length;
        //dynamically allocate mem0ry for array type T using array version of new 
        m_array = new T[m_length];

        //deep copy the contents of array
        for (int i{ 0 }; i < a.m_length; ++i)
            m_array[i] = a.m_array[i];

        return *this;
    }
    int getLength()const
    {
        return m_length;
    }
    T& operator[]( int index )
    {
        return m_array[index];
    }
    const T& operator[]( int index )const
    {
        return m_array[index];
    }
};