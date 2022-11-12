#pragma once
struct Tree {
    int key;
    int index;
    Tree* left;
    Tree* right;
    Tree() { left = right = nullptr; }
};

//�������� ��������� ������
Tree* createTreeElement(Tree* element, int key, int index) {
    if (!element) {
        element = new Tree();
        element->key = key;
        element->index = index;
        return element;
    }
    else {
        if (key > element->key) {
            element->right = createTreeElement(element->right, key, index);
            return element;
        }
        else if (key < element->key) {
            element->left = createTreeElement(element->left, key, index);
            return element;
        }
    }
}

//�������� ������ �� ��������� �����
void createTree(Tree* root) {
    ifstream file("Data.dat", ios::binary);
    student s;
    file.read((char*)&s, sizeof(student));
    for (int i = 0; !file.eof(); i++) {
        if (i == 0) {
            root->key = s.numZachBook;
            root->index = i;
        }
        else {
            if (s.numZachBook > root->key) {
                root->right = createTreeElement(root->right, s.numZachBook, i);
            }
            else if (s.numZachBook < root->key) {
                root->left = createTreeElement(root->left, s.numZachBook, i);
            }
        }
        file.read((char*)&s, sizeof(student));
    }
}

//����� ������ ������ �������
void print_Tree(Tree* p, int level) {
    if (p)
    {
        if (level > 0) {
            for (int i = 0; i < level; i++) cout << "  ";
        }
        cout << p->key << endl;
        print_Tree(p->left, level + 1);
        print_Tree(p->right, level + 1);
    }
}

//����� ����� � ������
void searchKey(Tree* root, int key) {
    if (root) {
        if (key == root->key) {
            cout << "\n���� ������: " << root->key << " ������ = " << root->index << endl;
            findedRecord(root->index, root->key);
        }
        else if (key > root->key) {
            searchKey(root->right, key);
        }
        else if (key < root->key) {
            searchKey(root->left, key);
        }
    }
    else cout << "\n���� �� ������!\n";
}

// ����� ���������
Tree* minValueNode(Tree* node) {
    Tree* current = node;

    // ���� ������� ����� ���� � �� � ����� ����������
    while (current && current->left != NULL)
        current = current->left;

    return current;
}

// �������� ����
Tree* deleteNode(Tree* root, int key) {
    if (root == NULL) return root;

    // ���� ����, ������� ����� �������
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // ���� � ���� ���� �������� ������� ��� �� ���
        if (root->left == NULL) {
            Tree* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL) {
            Tree* temp = root->left;
            delete root;
            return temp;
        }
        // ���� � ���� ��� �������� ��������
        Tree* temp = minValueNode(root->right);
        // �������� ��������� �� ����� ����, ������� ����� �������
        root->key = temp->key;
        // ������� ���������
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

void binSearchTreeTest() {
    Tree* root = new Tree();
    createTree(root);
    cout << endl;
    print_Tree(root, 0);
    cout << "����� ����� 20106";
    searchKey(root, 20106);
    root = deleteNode(root, 20106);
    cout << "�������� ����� 20106\n";
    print_Tree(root, 0);
    cout << "����� ����� 20106";
    searchKey(root, 20106);
}