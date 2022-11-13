#pragma once
// ���� ������ 
struct SplayTree {
    int key;
    int index;
    SplayTree* left;
    SplayTree* right;
    SplayTree() { left = right = nullptr; }
};

//�������� ��������� ������
SplayTree* createSplayTreeElement(SplayTree* element, int key, int index) {
    if (!element) {
        element = new SplayTree();
        element->key = key;
        element->index = index;
        return element;
    }
    else {
        if (key > element->key) {
            element->right = createSplayTreeElement(element->right, key, index);
            return element;
        }
        else if (key < element->key) {
            element->left = createSplayTreeElement(element->left, key, index);
            return element;
        }
    }
}

//�������� ������ �� ��������� �����
void createSplayTree(SplayTree* root) {
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
                root->right = createSplayTreeElement(root->right, s.numZachBook, i);
            }
            else if (s.numZachBook < root->key) {
                root->left = createSplayTreeElement(root->left, s.numZachBook, i);
            }
        }
        file.read((char*)&s, sizeof(student));
    }
}

//�������� ��������� � ������ y ������
SplayTree* rightRotate(SplayTree* x) {
    SplayTree* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

//�������� ��������� � ������ x ����� 
SplayTree* leftRotate(SplayTree* x) {
    SplayTree* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

// ��� ������� �������� ������ � ���������� ����� ������ (root). 
SplayTree* splay(SplayTree* root, int key) {
    if (root == NULL || root->key == key)
        return root;
    // ���� ����� � ����� ���������
    if (root->key > key) {
        if (root->left == NULL) return root;
        // Zig-Zig (�����-�����) 
        if (root->left->key > key) {
            root->left->left = splay(root->left->left, key);
            root = rightRotate(root);
        }
        else if (root->left->key < key) { // Zig-Zag (�����-������) 
            root->left->right = splay(root->left->right, key);
            if (root->left->right != NULL)
                root->left = leftRotate(root->left);
        }
        return (root->left == NULL) ? root : rightRotate(root);
    }
    else { // ���� ��������� � ������ ���������
        if (root->right == NULL) return root;
        // Zag-Zig (������-�����) 
        if (root->right->key > key) {
            root->right->left = splay(root->right->left, key);
            if (root->right->left != NULL)
                root->right = rightRotate(root->right);
        }
        else if (root->right->key < key) { // Zag-Zag (������-������) 
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }
        return (root->right == NULL) ? root : leftRotate(root);
    }
}

// ������� ������ ��� splay-������
SplayTree* searchSplay(SplayTree* root, int key) {
    SplayTree* temp = splay(root, key);
    if (temp->key == key) {
        cout << "\n���� ������: " << temp->key << " ������ = " << temp->index << endl;
        findedRecord(temp->index, temp->key);
    }
    else {
        cout << "\n���� �� ������!\n";
    }
    return temp;
}

// ����� ���������
SplayTree* minValueSplayNode(SplayTree* node) {
    SplayTree* current = node;

    // ���� ������� ����� ���� � �� � ����� ����������
    while (current && current->left != NULL)
        current = current->left;

    return current;
}

// �������� ����
SplayTree* deleteSplayNode(SplayTree* root, int key) {
    if (root == NULL) return root;

    // ���� ����, ������� ����� �������
    if (key < root->key)
        root->left = deleteSplayNode(root->left, key);
    else if (key > root->key)
        root->right = deleteSplayNode(root->right, key);
    else {
        // ���� � ���� ���� �������� ������� ��� �� ���
        if (root->left == NULL) {
            SplayTree* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL) {
            SplayTree* temp = root->left;
            delete root;
            return temp;
        }
        // ���� � ���� ��� �������� ��������
        SplayTree* temp = minValueSplayNode(root->right);
        // �������� ��������� �� ����� ����, ������� ����� �������
        root->key = temp->key;
        // ������� ���������
        root->right = deleteSplayNode(root->right, temp->key);
    }
    return root;
}

//����� ������
void print_Splay(SplayTree* root, int level) {
    if (root) {
        if (level > 0) {
            for (int i = 0; i < level; i++) cout << "   ";
        }
        cout << root->key << endl;
        print_Splay(root->left, level + 1);
        print_Splay(root->right, level + 1);
    }
}

void splaySearchTreeTest() {
    cout << "\n������������ ������ ������ ������(������� 2)\n";
    SplayTree* root = new SplayTree();
    createSplayTree(root);
    cout << endl;
    print_Splay(root, 0);
    cout << "\n����� ����� 20106";
    root = searchSplay(root, 20106);
    print_Splay(root, 0);
    root = deleteSplayNode(root, 20106);
    cout << "�������� ����� 20106\n";
    print_Splay(root, 0);
    cout << "\n����� ����� 20106";
    root = searchSplay(root, 20106);
    print_Splay(root, 0);
}