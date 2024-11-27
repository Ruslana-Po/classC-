#include  "header.h"
class DynamicArray {
private:
    string* number;
    int sizes;
    int capacity;

public:
    // Конструктор
    DynamicArray(int cap = 10) : sizes(0), capacity(cap) {
        number = new string[capacity];
    }

    // Деструктор
    ~DynamicArray() {
        delete[] number;
    }

    // Увеличение размера массива
    void reSize() {
        capacity *= 2;
        string* new_node = new string[capacity];
        for (int i = 0; i < sizes; ++i) {
            new_node[i] = number[i];
        }
        delete[] number;
        number = new_node;
    }

    // Добавление элемента в конец
    void AddArr(const string& value) {
        if (sizes >= capacity) {
            reSize();
        }
        number[sizes++] = value;
    }

    // Добавление элемента по индексу
    void AddAtIndex(int index, const string& value) {
        if (index < 0 || index > sizes) {
            return;
        }
        if (sizes >= capacity) {
            reSize();
        }
        for (int i = sizes; i > index; --i) {
            number[i] = number[i - 1];
        }
        number[index] = value;
        sizes++;
    }

    // Получение элемента по индексу
    string returnItemByIndex(int index) const {
        if (index < 0 || index >= sizes) {
            cout << "Индекс вне диапазона!" << endl;
            return "Индекс вне диапазона!";
        }
        return number[index];
    }

    // Удаление элемента по индексу
    void removeItemByIndex(int index) {
        if (index < 0 || index >= sizes) {
            cout << "Индекс вне диапазона!" << endl;
            return;
        }
        for (int i = index; i < sizes - 1; ++i) {
            number[i] = number[i + 1];
        }
        sizes--;
    }

    // Замена элемента по индексу
    void replaceItemByIndex(int index, const string& value) {
        if (index < 0 || index >= sizes) {
            cout << "Индекс вне диапазона!" << endl;
            return;
        }
        number[index] = value;
    }

    // Получение текущего размера массива
    int Size() const {
        return sizes;
    }

    // Вывод массива
    void Print() const {
        for (int i = 0; i < sizes; ++i) {
            cout << number[i] << " ";
        }
        cout << endl;
    }

     // Сериализация в бинарный формат
    void serializeBinary(const string& filename) const {
        ofstream out(filename, ios::binary);
        if (!out) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        out.write(reinterpret_cast<const char*>(&sizes), sizeof(sizes));
        for (int i = 0; i < sizes; ++i) {
            size_t len = number[i].size();
            out.write(reinterpret_cast<const char*>(&len), sizeof(len));
            out.write(number[i].c_str(), len);
        }

        out.close();
    }

    // Десериализация из бинарного формата
    void deserializeBinary(const string& filename) {
        ifstream in(filename, ios::binary);
        if (!in) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        int newSize;
        in.read(reinterpret_cast<char*>(&newSize), sizeof(newSize));
        sizes = 0;
        capacity = newSize;
        delete[] number;
        number = new string[capacity];

        for (int i = 0; i < newSize; ++i) {
            size_t len;
            in.read(reinterpret_cast<char*>(&len), sizeof(len));
            string value(len, '\0');
            in.read(&value[0], len);
            AddArr(value);
        }

        in.close();
    }

    // Сериализация в текстовый формат
    void serializeText(const string& filename) const {
        ofstream out(filename);
        if (!out) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        out << sizes << endl;
        for (int i = 0; i < sizes; ++i) {
            out << number[i] << endl;
        }

        out.close();
    }

    // Десериализация из текстового формата
    void deserializeText(const string& filename) {
        ifstream in(filename);
        if (!in) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        int newSize;
        in >> newSize;
        sizes = 0;
        capacity = newSize;
        delete[] number;
        number = new string[capacity];
        // Считываем оставшуюся пустую строку после числа
        string line;
        getline(in, line); 
        for (int i = 0; i < newSize; ++i) {
            getline(in, line);
            AddArr(line);
        }

        in.close();
    }
};
