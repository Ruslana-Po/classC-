#include  "header.h"
class Queue {

private:
    struct NodeQ {
        string person;
        NodeQ* next;
    };

    NodeQ* head;
    NodeQ* tail;

public:
    // Конструктор
    Queue() : head(nullptr), tail(nullptr) {}

    // Деструктор
    ~Queue() {
        while (head != nullptr) {
            pop();
        }
    }

    // Добавление элемента в очередь
    void push(const string& element) {
        NodeQ* new_node = new NodeQ{element, nullptr};
        if (head != nullptr) {
            tail->next = new_node;
            tail = new_node;
        } else {
            tail = new_node;
            head = tail;
        }
    }

    // Удаление элемента из очереди
    void pop() {
        if (head != nullptr) {
            NodeQ* new_head = head;
            head = head->next;
            delete new_head;
            if (head == nullptr) {
                tail = nullptr;
            }
        } else {
            cout << "Error: list is empty" << endl;
        }
    }

    // Отображение содержимого очереди
    void show() const {
        NodeQ* current = head;
        while (current != nullptr) {
            cout << current->person << " ";
            current = current->next;
        }
        cout << endl;
    }

    // Проверка, пуста ли очередь
    bool isEmpty() const {
        return head == nullptr;
    }
    // Сериализация в бинарный формат
    void serializeBinary(const string& filename) const {
        ofstream out(filename, ios::binary);
        if (!out) {
            cerr << "Error opening file for writing: " << filename << endl;
            return;
        }

        NodeQ* current = head;
        while (current != nullptr) {
            size_t len = current->person.size();
            out.write(reinterpret_cast<char*>(&len), sizeof(len));
            out.write(current->person.c_str(), len);
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
            pop();
        }

        while (in) {
            size_t len;
            if (!in.read(reinterpret_cast<char*>(&len), sizeof(len))) break;
            string person(len, '\0');
            if (!in.read(&person[0], len)) break;
            push(person);
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

        NodeQ* current = head;
        while (current != nullptr) {
            out << current->person << endl;
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
            pop();
        }

        string line;
        while (getline(in, line)) {
            push(line);
        }

        in.close();
    }
};
