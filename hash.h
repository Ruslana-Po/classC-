#include  "header.h"
class HashTable {
private:
    struct Item {
        string key;
        string value;
        Item* next;
    };

    int sizeArr;
    Item** tabl;

public:
    // Конструктор
    HashTable(int size = 5) : sizeArr(size) {
        tabl = new Item*[sizeArr];
        for (int i = 0; i < sizeArr; i++) {
            tabl[i] = nullptr;
        }
    }

    // Деструктор
    ~HashTable() {
        for (int i = 0; i < sizeArr; i++) {
            Item* current = tabl[i];
            while (current != nullptr) {
                Item* next = current->next;
                delete current;
                current = next;
            }
        }
        delete[] tabl;
    }

    // Хэш-функция
    int Hash(const string& itemKey) const {
        int result = 0;
        for (char i : itemKey) {
            result += static_cast<int>(i);
        }
        return abs(result) % sizeArr;
    }

    // Проверка на заполненность таблицы
    bool isFull() const {
        int count = 0;
        for (int i = 0; i < sizeArr; i++) {
            if (tabl[i] != nullptr) {
                count++;
            }
        }
        return count >= sizeArr;
    }

    // Добавление элемента
    void AddHash(const string& key, const string& value) {
        int index = Hash(key);

        // Проверка на наличие уже такого ключа
        Item* current = tabl[index];
        while (current != nullptr) {
            if (current->key == key) {
                cout << "Ключ '" << key << "' уже существует. Значение не добавлено." << endl;
                return;
            }
            current = current->next;
        }

        // Проверка на есть ли место
        if (isFull()) {
            cout << "Хэш-таблица переполнена. Невозможно добавить новый элемент." << endl;
            return;
        }

        // Добавление элемента
        Item* new_node = new Item{key, value, tabl[index]};
        tabl[index] = new_node;
    }

    // Получение значения по ключу
    string KeyItem(const string& key) const {
        int index = Hash(key);
        Item* current = tabl[index];
        while (current != nullptr) {
            if (current->key == key) {
                cout << "key: " << key << " value: " << current->value << endl;
                return current->value;
            }
            current = current->next;
        }
        return "Пусто";
    }

    // Удаление элемента по ключу
    bool DelValue(const string& key) {
        int index = Hash(key);
        Item* current = tabl[index];
        Item* prev = nullptr;
        while (current != nullptr) {
            if (current->key == key) {
                if (prev == nullptr) {
                    tabl[index] = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                return true;
            }
            prev = current;
            current = current->next;
        }
        cout << "Такого ключа нет." << endl;
        return false;
    }

    // Вывод таблицы
    void Print() const {
        for (int i = 0; i < sizeArr; i++) {
            Item* current = tabl[i];
            while (current != nullptr) {
                cout << "key: " << current->key << " value: " << current->value << endl;
                current = current->next;
            }
        }
    }

    // Сериализация в бинарный формат
    void serializeBinary(const string& filename) const {
        ofstream out(filename, ios::binary);
        if (!out) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        for (int i = 0; i < sizeArr; i++) {
            Item* current = tabl[i];
            while (current != nullptr) {
                size_t keyLen = current->key.size();
                size_t valueLen = current->value.size();
                out.write(reinterpret_cast<char*>(&keyLen), sizeof(keyLen));
                out.write(current->key.c_str(), keyLen);
                out.write(reinterpret_cast<char*>(&valueLen), sizeof(valueLen));
                out.write(current->value.c_str(), valueLen);
                current = current->next;
            }
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

        for (int i = 0; i < sizeArr; i++) {
            Item* current = tabl[i];
            while (current != nullptr) {
                Item* next = current->next;
                delete current;
                current = next;
            }
            tabl[i] = nullptr;
        }

        while (in) {
            size_t keyLen, valueLen;
            if (!in.read(reinterpret_cast<char*>(&keyLen), sizeof(keyLen))) break;
            string key(keyLen, '\0');
            if (!in.read(&key[0], keyLen)) break;
            if (!in.read(reinterpret_cast<char*>(&valueLen), sizeof(valueLen))) break;
            string value(valueLen, '\0');
            if (!in.read(&value[0], valueLen)) break;
            AddHash(key, value);
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

        for (int i = 0; i < sizeArr; i++) {
            Item* current = tabl[i];
            while (current != nullptr) {
                out << current->key << " " << current->value << endl;
                current = current->next;
            }
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

        for (int i = 0; i < sizeArr; i++) {
            Item* current = tabl[i];
            while (current != nullptr) {
                Item* next = current->next;
                delete current;
                current = next;
            }
            tabl[i] = nullptr;
        }

        string key, value;
        while (in >> key >> value) {
            AddHash(key, value);
        }

        in.close();
    }

};
