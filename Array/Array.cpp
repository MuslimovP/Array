#include <iostream>
using namespace std;

// ��������� �����-��������� Array, �������������� ����� ������ �������� ��������� ����
template <class T>
class Array
{
private:
    T* data; // ��������� �� ������ ������
    int size; // ������� ������ ������� (���������� ���������)
    int capacity; // ������� ������� (���������� ���������� ������)
    int grow; // ��� ���������� �������

    // ������� ��� ��������� ������� �������
    void resize(int newCapacity);

public:
    // ����������� � ����������� �� ���������
    Array(int initialSize = 0, int growBy = 1);

    // ����������� �����������
    Array(const Array& other);

    // ����������
    ~Array();

    // ��������� �������� ������� �������
    int GetSize() const;

    // ��������� ������ ������� �������
    void SetSize(int newSize, int growBy = 1);

    // ��������� ���������� ����������� ������� � �������
    int GetUpperBound() const;

    // ��������, ���� �� ������
    bool IsEmpty() const;

    // �������� ������ ������ (���� ���������� ����������� �������)
    void FreeExtra();

    // �������� ���� ��������� �������
    void RemoveAll();

    // ��������� �������� ������� �� �������
    T GetAt(int index) const;

    // ��������� �������� �������� ������� �� �������
    void SetAt(int index, const T& value);

    // ���������� ��������� [], ��� ������� � ��������� ������� �� �������
    T& operator[](int index);
    const T& operator[](int index) const;

    // ���������� �������� � ������
    void Add(const T& value);

    // "��������" ���� ��������
    void Append(const Array<T>& other);

    // ���������� ��������� ������������
    Array<T>& operator=(const Array<T>& other);

    // ��������� ��������� �� ������ ������
    T* GetData();

    // ������� �������� � �������� �������
    void InsertAt(int index, const T& value);

    // �������� ��������(-��) � �������� �������
    void RemoveAt(int index, int count = 1);

    // ����� ������� �� �����
    void Print() const;
};
// ������� ��� ��������� ������� �������
template<class T>
void Array<T>::resize(int newCapacity) 
{
    T* newData = new T[newCapacity];
    int elementsToCopy = (size < newCapacity) ? size : newCapacity;  

    // ����������� ��������� � ����� ������
    for (int i = 0; i < elementsToCopy; ++i) 
    {

        newData[i] = move(data[i]); 
    }

    delete[] data;
    data = newData;
    capacity = newCapacity;
}

// ����������� � ����������� �� ���������
template<class T>
Array<T>::Array(int initialSize, int growBy) : size(0), capacity(initialSize), grow(growBy) 
{ 
    if (initialSize < 0 || growBy < 1) 
    {
        cout << "Invalid initial size or grow size" << endl;
        initialSize = 0;
        growBy = 1;
    }
    data = new T[capacity];
}

// ����������� �����������
template <class T>
Array<T>::Array(const Array& other) : size(other.size), capacity(other.capacity), grow(other.grow) 
{
    data = new T[capacity];
    for (int i = 0; i < size; ++i) 
    {
        data[i] = other.data[i];
    }
}

// ����������
template <class T>
Array<T>::~Array() 
{
    delete[] data;
}

// ��������� �������� ������� �������
template <class T>
int Array<T>::GetSize() const 
{
    return size;
}

// ��������� ������ ������� �������
template <class T>
void Array<T>::SetSize(int newSize, int growBy) 
{
    grow = growBy;
    if (newSize > capacity) 
    {
        resize(newSize);
    }
    size = newSize;
}

// ��������� ���������� ����������� ������� � �������
template <class T>
int Array<T>::GetUpperBound() const 
{
    return size - 1;
}

// ��������, ���� �� ������
template <class T>
bool Array<T>::IsEmpty() const 
{
    return size == 0;
}

// �������� ������ ������ (���� ���������� ����������� �������)
template <class T>
void Array<T>::FreeExtra() 
{
    if (size < capacity) 
    {
        resize(size);
    }
}

// �������� ���� ��������� �������
template <class T>
void Array<T>::RemoveAll() 
{
    size = 0;
}

// ��������� �������� ������� �� �������
template <class T>
T Array<T>::GetAt(int index) const 
{
    if (index < 0 || index >= size) 
    {
        cout << "Index out of range" << endl; 
        return T(); // ����������� �������� �� ��������� ��� ���� T
    }
    return data[index];
}

// ��������� �������� �������� ������� �� �������
template <class T>
void Array<T>::SetAt(int index, const T& value) 
{
    if (index >= 0 && index < size)
    {
        data[index] = value;
    }

}

// ���������� ��������� [], ��� ������� � ��������� ������� �� �������
template <class T>
T& Array<T>::operator[](int index) 
{
    if (index < 0 || index >= size) 
    {
        cout << "Index out of range" << endl; 
        static T dummy = T(); // ����������� ������ �� �������� �� ��������� ��� ���� T
        return dummy;
    }
    return data[index];
}

template <class T>
const T& Array<T>::operator[](int index) const 
{
    if (index < 0 || index >= size) 
    {
        cout << "Index out of range" << endl;
        static T dummy = T(); // ����������� ������ �� �������� �� ��������� ��� ���� T
        return dummy;
    }
    return data[index];
}

// ���������� �������� � ������
template <class T>
void Array<T>::Add(const T& value) 
{
    if (size >= capacity) 
    {
        resize(capacity + grow);
    }
    data[size++] = value;
}

// "��������" ���� ��������
template <class T>
void Array<T>::Append(const Array<T>& other) 
{
    int newSize = size + other.size;
    if (newSize > capacity) 
    {
        resize(newSize);
    }
    for (int i = 0; i < other.size; ++i) 
    {
        data[size++] = other.data[i];
    }
}

// ���������� ��������� ������������
template <class T>
Array<T>& Array<T>::operator=(const Array<T>& other) 
{
    if (this == &other) 
    {
        return *this; 
    }
    if (this != &other) 
    {
        delete[] data;
    }

    size = other.size;
    capacity = other.capacity;
    grow = other.grow;
    data = new T[capacity];
    for (int i = 0; i < size; ++i) 
    {
        data[i] = other.data[i];
    }

    return *this;
}

// ��������� ��������� �� ������ ������
template <class T>
T* Array<T>::GetData() 
{
    return data;
}

// ������� �������� � �������� �������
template <class T>
void Array<T>::InsertAt(int index, const T& value) 
{
    if (index < 0 || index > size)
    {
        cout << "Index out of range" << endl;
        return;
    }
    if (size >= capacity) 
    {
        resize(capacity + grow);
    }
    for (int i = size; i > index; --i) 
    {
        data[i] = data[i - 1];
    }
    data[index] = value;
    ++size;
}

// �������� ��������(-��) � �������� �������
template <class T>
void Array<T>::RemoveAt(int index, int count) 
{
    if (index < 0 || index > size)
    {
        cout << "Index out of range" << endl;
        return;
    } 
    for (int i = index; i < size - count; ++i) 
    {
        data[i] = data[i + count];
    }
    size -= count;
}

// ����� ������� �� �����
template <class T>
void Array<T>::Print() const 
{
    for (int i = 0; i < size; ++i) 
    {
        std::cout << data[i] << " ";
    }
    cout << endl;
}



int main()
{
    // �������� ������� � ��������� �������� 5 � ����� ���������� 3
    Array<int> arr(5, 3);

    // ���������� �������
    for (int i = 0; i < 5; ++i)
    {
        arr.Add(i + 1);
    }

    // ����� �������
    cout << "Array contents: ";
    arr.Print();

    // �������� �������
    cout << "Size: " << arr.GetSize() << endl;
    cout << "Upper Bound: " << arr.GetUpperBound() << endl;
    cout << "Is Empty: " << (arr.IsEmpty() ? "Yes" : "No") << endl;

    // ������� �������� ������� �� ��������� �������
    cout << "Element at index 10: " << arr.GetAt(10) << endl;

    // ������� ���������� ������� �� ��������� �������
    arr.SetAt(10, 100);

    // ������� �������� ������� �� ��������� �������
    arr.InsertAt(10, 200);

    // ������� ������� ������� �� ��������� �������
    arr.RemoveAt(10);

    // ����� ��������� ��������� �������
    std::cout << "Final array contents: ";
    arr.Print();

    return 0;
}