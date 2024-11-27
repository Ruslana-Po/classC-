#include  "header.h"
class Stack {
private:
    struct NodeS {
        string person;
        NodeS* next;
    };

    NodeS* head;

public:
    // Конструктор
    Stack() : head(nullptr) {}

    // Деструктор
    ~Stack() {
        while (head != nullptr) {
            pop();
        }
    }

    // Добавление элемента в стек
    void push(const string& element) {
        NodeS* new_node = new NodeS{element, head};
        head = new_node;
    }

    // Удаление элемента из стека
    void pop() {
        if (head == nullptr) {
            cout << "Stack is empty!" << endl;
            return;
        }
        NodeS* new_head = head->next;
        delete head;
        head = new_head;
    }

    // Отображение содержимого стека
    void show() const {
        NodeS* current = head;
        while (current != nullptr) {
            cout << current->person << " ";
            current = current->next;
        }
        cout << endl;
    }

    // Проверка, пуст ли стек
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

        NodeS* current = head;
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

        NodeS* current = head;
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
