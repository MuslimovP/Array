#include <iostream>
using namespace std;

// Шаблонный класс-контейнер Array, представляющий собой массив объектов заданного типа
template <class T>
class Array
{
private:
    T* data; // Указатель на массив данных
    int size; // Текущий размер массива (количество элементов)
    int capacity; // Емкость массива (количество выделенной памяти)
    int grow; // Шаг увеличения массива

    // Функция для изменения размера массива
    void resize(int newCapacity);

public:
    // Конструктор с параметрами по умолчанию
    Array(int initialSize = 0, int growBy = 1);

    // Конструктор копирования
    Array(const Array& other);

    // Деструктор
    ~Array();

    // Получение текущего размера массива
    int GetSize() const;

    // Установка нового размера массива
    void SetSize(int newSize, int growBy = 1);

    // Получение последнего допустимого индекса в массиве
    int GetUpperBound() const;

    // Проверка, пуст ли массив
    bool IsEmpty() const;

    // Удаление лишней памяти (выше последнего допустимого индекса)
    void FreeExtra();

    // Удаление всех элементов массива
    void RemoveAll();

    // Получение элемента массива по индексу
    T GetAt(int index) const;

    // Установка значения элемента массива по индексу
    void SetAt(int index, const T& value);

    // Перегрузка оператора [], для доступа к элементам массива по индексу
    T& operator[](int index);
    const T& operator[](int index) const;

    // Добавление элемента в массив
    void Add(const T& value);

    // "Сложение" двух массивов
    void Append(const Array<T>& other);

    // Перегрузка оператора присваивания
    Array<T>& operator=(const Array<T>& other);

    // Получение указателя на массив данных
    T* GetData();

    // Вставка элемента в заданную позицию
    void InsertAt(int index, const T& value);

    // Удаление элемента(-ов) с заданной позиции
    void RemoveAt(int index, int count = 1);

    // Вывод массива на экран
    void Print() const;
};
// Функция для изменения размера массива
template<class T>
void Array<T>::resize(int newCapacity) 
{
    T* newData = new T[newCapacity];
    int elementsToCopy = (size < newCapacity) ? size : newCapacity;  

    // Копирование элементов в новый массив
    for (int i = 0; i < elementsToCopy; ++i) 
    {

        newData[i] = move(data[i]); 
    }

    delete[] data;
    data = newData;
    capacity = newCapacity;
}

// Конструктор с параметрами по умолчанию
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

// Конструктор копирования
template <class T>
Array<T>::Array(const Array& other) : size(other.size), capacity(other.capacity), grow(other.grow) 
{
    data = new T[capacity];
    for (int i = 0; i < size; ++i) 
    {
        data[i] = other.data[i];
    }
}

// Деструктор
template <class T>
Array<T>::~Array() 
{
    delete[] data;
}

// Получение текущего размера массива
template <class T>
int Array<T>::GetSize() const 
{
    return size;
}

// Установка нового размера массива
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

// Получение последнего допустимого индекса в массиве
template <class T>
int Array<T>::GetUpperBound() const 
{
    return size - 1;
}

// Проверка, пуст ли массив
template <class T>
bool Array<T>::IsEmpty() const 
{
    return size == 0;
}

// Удаление лишней памяти (выше последнего допустимого индекса)
template <class T>
void Array<T>::FreeExtra() 
{
    if (size < capacity) 
    {
        resize(size);
    }
}

// Удаление всех элементов массива
template <class T>
void Array<T>::RemoveAll() 
{
    size = 0;
}

// Получение элемента массива по индексу
template <class T>
T Array<T>::GetAt(int index) const 
{
    if (index < 0 || index >= size) 
    {
        cout << "Index out of range" << endl; 
        return T(); // Возвращение значения по умолчанию для типа T
    }
    return data[index];
}

// Установка значения элемента массива по индексу
template <class T>
void Array<T>::SetAt(int index, const T& value) 
{
    if (index >= 0 && index < size)
    {
        data[index] = value;
    }

}

// Перегрузка оператора [], для доступа к элементам массива по индексу
template <class T>
T& Array<T>::operator[](int index) 
{
    if (index < 0 || index >= size) 
    {
        cout << "Index out of range" << endl; 
        static T dummy = T(); // Возвращение ссылки на значение по умолчанию для типа T
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
        static T dummy = T(); // Возвращение ссылки на значение по умолчанию для типа T
        return dummy;
    }
    return data[index];
}

// Добавление элемента в массив
template <class T>
void Array<T>::Add(const T& value) 
{
    if (size >= capacity) 
    {
        resize(capacity + grow);
    }
    data[size++] = value;
}

// "Сложение" двух массивов
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

// Перегрузка оператора присваивания
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

// Получение указателя на массив данных
template <class T>
T* Array<T>::GetData() 
{
    return data;
}

// Вставка элемента в заданную позицию
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

// Удаление элемента(-ов) с заданной позиции
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

// Вывод массива на экран
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
    // Создание массива с начальным размером 5 и шагом увеличения 3
    Array<int> arr(5, 3);

    // Заполнение массива
    for (int i = 0; i < 5; ++i)
    {
        arr.Add(i + 1);
    }

    // Вывод массива
    cout << "Array contents: ";
    arr.Print();

    // Проверка функций
    cout << "Size: " << arr.GetSize() << endl;
    cout << "Upper Bound: " << arr.GetUpperBound() << endl;
    cout << "Is Empty: " << (arr.IsEmpty() ? "Yes" : "No") << endl;

    // Пробуем получить элемент за пределами массива
    cout << "Element at index 10: " << arr.GetAt(10) << endl;

    // Пробуем установить элемент за пределами массива
    arr.SetAt(10, 100);

    // Пробуем вставить элемент за пределами массива
    arr.InsertAt(10, 200);

    // Пробуем удалить элемент за пределами массива
    arr.RemoveAt(10);

    // Вывод итогового состояния массива
    std::cout << "Final array contents: ";
    arr.Print();

    return 0;
}