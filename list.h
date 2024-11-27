#include  "header.h"
class LinkedList {
private:
    struct Node {
        string number;
        Node* next;
    };

    Node* head;

public:
    // Конструктор
    LinkedList() : head(nullptr) {}

    // Деструктор
    ~LinkedList() {
        while (head != nullptr) {
            DeleteToHead();
        }
    }

    // Добавление в голову
    void AddToHead(const string& element) {
        Node* new_node = new Node{element, head};
        head = new_node;
    }

    // Добавление в конец
    void AddToEnd(const string& element) {
        Node* new_node = new Node{element, nullptr};
        if (head == nullptr) {
            head = new_node;
        } else {
            Node* nextNode = head;
            while (nextNode->next != nullptr) {
                nextNode = nextNode->next;
            }
            nextNode->next = new_node;
        }
    }

    // Удаление с головы
    void DeleteToHead() {
        if (head != nullptr) {
            Node* delete_node = head;
            head = head->next;
            delete delete_node;
        }
    }

    // Удаление с конца
    void DeleteToEnd() {
        if (head != nullptr) {
            if (head->next == nullptr) {
                delete head;
                head = nullptr;
            } else {
                Node* delete_node = head;
                while (delete_node->next->next != nullptr) {
                    delete_node = delete_node->next;
                }
                delete delete_node->next;
                delete_node->next = nullptr;
            }
        }
    }

    // Удаление по значению
    void DeleteValue(const string& element) {
        Node* new_node = head;
        Node* previous = nullptr;
        while (new_node != nullptr && new_node->number != element) {
            previous = new_node;
            new_node = new_node->next;
        }
        // Есть ли значение
        if (new_node == nullptr) {
            return;
        }
        // Первое ли оно
        if (previous == nullptr) {
            head = new_node->next;
        } else {
            previous->next = new_node->next;
        }
        delete new_node;
    }

    // Поиск по значению
    bool Quest(const string& element) const {
        Node* new_node = head;
        while (new_node != nullptr) {
            if (new_node->number == element) {
                return true;
            }
            new_node = new_node->next;
        }
        return false;
    }

    // Чтение
    void PrintNode() const {
        Node* new_node = head;
        if (new_node == nullptr) {
            cout << "Error list is empty" << endl;
            return;
        }
        cout << "List: " << endl;
        while (new_node != nullptr) {
            cout << new_node->number << endl;
            new_node = new_node->next;
        }
    }

     // Сериализация в бинарный формат
    void serializeBinary(const string& filename) const {
        ofstream out(filename, ios::binary);
        if (!out) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        Node* current = head;
        while (current != nullptr) {
            size_t len = current->number.size();
            out.write(reinterpret_cast<char*>(&len), sizeof(len));
            out.write(current->number.c_str(), len);
            current = current->next;
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

        while (head != nullptr) {
            DeleteToHead();
        }

        while (in) {
            size_t len;
            if (!in.read(reinterpret_cast<char*>(&len), sizeof(len))) break;
            string number(len, '\0');
            if (!in.read(&number[0], len)) break;
            AddToEnd(number);
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

        Node* current = head;
        while (current != nullptr) {
            out << current->number << endl;
            current = current->next;
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

        while (head != nullptr) {
            DeleteToHead();
        }

        string line;
        while (getline(in, line)) {
            AddToEnd(line);
        }

        in.close();
    }
};
