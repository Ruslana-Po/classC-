#include  "header.h"
class BinaryTree {
private:
    struct Tree {
        int value;
        Tree* left;
        Tree* right;
        // Конструктор
        Tree(int val) : value(val), left(nullptr), right(nullptr) {}
    };

    Tree* root;

public:
    // Конструктор
    BinaryTree() : root(nullptr) {}

    // Деструктор
    ~BinaryTree() {
        destroyTree(root);
    }

    // Добавление элемента в дерево
    void add(int value) {
        addTree(root, value);
    }

    // поиск
    bool remove(int value) {
        return removeTree(root, value);
    }

    // Отображение дерева
    void print() const {
        printTree(root, 0);
    }

    // Проверка, является ли дерево полным бинарным
    bool isComplete() const {
        int numNodes = countNumNodes(root);
        return checkComplete(root, 0, numNodes);
    }
 // Подсчет количества элементов в дереве
    int countElements() const {
        return countNumNodes(root);
    }

     // Сериализация в бинарный формат
    void serializeBinary(const string& filename) const {
        ofstream out(filename, ios::binary);
        if (!out) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        serializeTreeBinary(root, out);
        out.close();
    }

    // Десериализация из бинарного формата
    void deserializeBinary(const string& filename) {
        ifstream in(filename, ios::binary);
        if (!in) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        destroyTree(root);
        root = nullptr;
        deserializeTreeBinary(root, in);
        in.close();
    }

    // Сериализация в текстовый формат
    void serializeText(const string& filename) const {
        ofstream out(filename);
        if (!out) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        serializeTreeText(root, out);
        out.close();
    }

    // Десериализация из текстового формата
    void deserializeText(const string& filename) {
        ifstream in(filename);
        if (!in) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        destroyTree(root);
        root = nullptr;
        deserializeTreeText(root, in);
        in.close();
    }
private:
    // Рекурсивное добавление элемента в дерево
    void addTree(Tree*& root, int value) {
        if (root == nullptr) {
            // Создаем новый узел, если дерево пустое
            root = new Tree(value);
            return;
        }

        if (value <= root->value) {
            // Рекурсивно добавляем в левое поддерево
            addTree(root->left, value);
        } else {
            // Рекурсивно добавляем в правое поддерево
            addTree(root->right, value);
        }
    }

    // Подсчет количества узлов в дереве
    int countNumNodes(Tree* tree) const {
        if (tree == nullptr)
            return 0;
        return 1 + countNumNodes(tree->left) + countNumNodes(tree->right);
    }

    bool removeTree(Tree* root, int value) {
       if (root == nullptr) {
            return false;
        }

        if (value == root->value) {
            return true;
        } else if (value < root->value) {
            return removeTree(root->left, value);
        } else {
            return removeTree(root->right, value);
        }
    }

    // Рекурсивное отображение дерева
    void printTree(Tree* root, int level) const {
        if (root != nullptr) {
            printTree(root->left, level + 1);
            for (int i = 0; i < level; i++) cout << "   ";
            cout << root->value << endl;
            printTree(root->right, level + 1);
        }
    }

    // Проверка, является ли дерево полным бинарным
    bool checkComplete(Tree* tree, int index, int numberNodes) const {
        if (tree == nullptr)
            return true;
        if (index >= numberNodes)
            return false;

        return (checkComplete(tree->left, 2 * index + 1, numberNodes) &&
                checkComplete(tree->right, 2 * index + 2, numberNodes));
    }

     // Рекурсивное удаление дерева
    void destroyTree(Tree* root) {
        if (root != nullptr) {
            destroyTree(root->left);
            destroyTree(root->right);
            delete root;
        }
    }
     // Рекурсивная сериализация дерева в бинарный формат
    void serializeTreeBinary(Tree* root, ofstream& out) const {
        if (root == nullptr) {
            out.write(reinterpret_cast<const char*>(&root), sizeof(root));
            return;
        }

        out.write(reinterpret_cast<const char*>(&root->value), sizeof(root->value));
        serializeTreeBinary(root->left, out);
        serializeTreeBinary(root->right, out);
    }

    // Рекурсивная десериализация дерева из бинарного формата
    void deserializeTreeBinary(Tree*& root, ifstream& in) {
        int value;
        in.read(reinterpret_cast<char*>(&value), sizeof(value));
        if (value == 0) {
            root = nullptr;
            return;
        }
        root = new Tree(value);
        deserializeTreeBinary(root->left, in);
        deserializeTreeBinary(root->right, in);
    }

    // Рекурсивная сериализация дерева в текстовый формат
    void serializeTreeText(Tree* root, ofstream& out) const {
        if (root == nullptr) {
            out << "null" << endl;
            return;
        }

        out << root->value << endl;
        serializeTreeText(root->left, out);
        serializeTreeText(root->right, out);
    }

    // Рекурсивная десериализация дерева из текстового формата
    void deserializeTreeText(Tree*& root, ifstream& in) {
        string line;
        getline(in, line);
        if (line == "null") {
            root = nullptr;
            return;
        }

        int value = stoi(line);
        root = new Tree(value);
        deserializeTreeText(root->left, in);
        deserializeTreeText(root->right, in);
    }

};
