#include  "header.h"
class DoublyLinkedList {

private:
    struct NodeT {
        string number;
        NodeT* next;
        NodeT* prev;
    };

    NodeT* head;
    NodeT* tail;

public:
    // Конструктор
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // Деструктор
    ~DoublyLinkedList() {
        while (head != nullptr) {
            DeleteToHead();
        }
    }

    // Добавление в конец
    void AddToEnd(const string& element) {
        NodeT* new_node = new NodeT{element, nullptr, tail};
        if (head != nullptr) {
            tail->next = new_node;
            tail = new_node;
        } else {
            head = tail = new_node;
        }
    }

    // Добавление в начало
    void AddToHead(const string& element) {
        NodeT* new_node = new NodeT{element, head, nullptr};
        if (head != nullptr) {
            head->prev = new_node;
            head = new_node;
        } else {
            head = tail = new_node;
        }
    }

    // Удаление с головы
    void DeleteToHead() {
        if (head != nullptr) {
            NodeT* delete_node = head;
            head = head->next;
            if (head != nullptr) {
                head->prev = nullptr;
            } else {
                tail = nullptr;
            }
            delete delete_node;
        }
    }

    // Удаление с конца
    void DeleteToEnd() {
        if (tail != nullptr) {
            NodeT* delete_node = tail;
            tail = tail->prev;
            if (tail != nullptr) {
                tail->next = nullptr;
            } else {
                head = nullptr;
            }
            delete delete_node;
        }
    }

    // Удаление по значению
    void DeleteValue(const string& element) {
        NodeT* temp = head;
        while (temp != nullptr) {
            if (temp->number == element) {
                if (temp == head) {
                    DeleteToHead();
                } else if (temp == tail) {
                    DeleteToEnd();
                } else {
                    temp->prev->next = temp->next;
                    temp->next->prev = temp->prev;
                    delete temp;
                }
                return;
            }
            temp = temp->next;
        }
        cout << "Error: no such element" << endl;
    }

    // Поиск по значению
    bool Quest(const string& element) const {
        NodeT* new_node = head;
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
        NodeT* new_node = head;
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
            cerr << "Error opening file for writing: " << filename << endl;
            return;
        }

        NodeT* current = head;
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

        NodeT* current = head;
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
