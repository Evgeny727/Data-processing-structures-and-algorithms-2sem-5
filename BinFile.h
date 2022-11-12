#pragma once

using namespace std;

struct student {
    int numZachBook;
    int numGroup;
    char FIO[100];
};

// создание бинарного фала из текстового
int CreateBinFile(string nametf, string namebf) {
    ifstream tf(nametf);
    if (tf) {
        fstream bf(namebf, ios::out | ios::binary);
        student s;
        while (!tf.eof()) {
            tf >> s.numZachBook;
            tf.get();//прочитать до пробела(вместе с пробелом)
            tf >> s.numGroup;
            tf.get();//прочитать до пробела(вместе с пробелом)
            tf.getline(s.FIO, 100, '\n');
            bf.write((char*)&s, sizeof(student));
        }
        tf.close();
        bf.close();
        return 0;
    }
    return 1;
}

//вывод бинарного файла на монитор
void outBinFile(string namebf) {
    fstream bf(namebf, ios::in | ios::binary);
    cout << "Содержание бинарного файла: \n";
    student s;
    bf.read((char*)&s, sizeof(student));
    while (!bf.eof()) {
        cout << s.numZachBook << " " << s.numGroup << " " << s.FIO << endl;
        bf.read((char*)&s, sizeof(student));
    }
    bf.close();
}

ostream& operator<< (ostream& out, const student s) {
    out << s.numZachBook << " " << s.numGroup << " " << s.FIO;
    return out;
}

//вывод записи через прямой доступ
void findedRecord(int offset, int key) {
    ifstream file("Data.dat", ios::binary);
    file.seekg(offset * sizeof(student), ios::beg);
    student s;
    file.read((char*)&s, sizeof(student));
    cout << "Запись с ключом " << key << ": " << s << endl;
}

void testBinTask() {
    cout << "Тестирование управления бинарным файлом\n";
    if (CreateBinFile("programTextFile.txt", "Data.dat")) {
        cout << "Error";
    }
    outBinFile("Data.dat");
}