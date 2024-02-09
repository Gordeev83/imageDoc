#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Document {
public:
    virtual void create() = 0;
    virtual void open(const string& filename) = 0;
    virtual void save() = 0;
    virtual void saveAs(const string& filename) = 0;
    virtual void print() = 0;
    virtual void close() = 0;
};


class ImageDocument : public Document {
private:
    vector<char> imageData;
    string filename;
    bool isOpen;

public:
    void create() override {
        if (isOpen) {
            cout << "Документ уже открыт" << endl;
            return;
        }
        isOpen = true;
        imageData.clear();
        filename = "";
        cout << "Создан новый графический документ" << endl;
    }

    void open(const string& filename) override {
        if (isOpen) {
            cout << "Документ уже открыт" << endl;
            return;
        }
        isOpen = true;
        this->filename = filename;
        cout << "Открыт документ с изображением: " << filename << endl;
    }

    void save() override {
        if (!isOpen) {
            cout << "Документ не открыт, пожалуйста, откройте или создайте новый документ" << endl;
            return;
        }
        if (filename.empty()) {
            cout << "Пожалуйста, укажите имя файла для сохранения документа" << endl;
            return;
        }
        ofstream file(filename, ios::binary);
        for (char c : imageData) {
            file.put(c);
        }
        file.close();
        cout << "Сохраненный документ с изображением" << endl;
    }

    void saveAs(const string& filename) override {
        if (!isOpen) {
            cout << "Документ не открыт, пожалуйста, откройте или создайте новый документ" << endl;
            return;
        }
        this->filename = filename;
        save();
    }

    void print() override {
        cout << "Размер данных изображения: " << imageData.size() << " bytes" << endl;
    }

    void close() override {
        isOpen = false;
        imageData.clear();
        filename = "";
        cout << "Документ с изображением закрыт" << endl;
    }
};

int main()
{
    setlocale(LC_ALL, "");
    Document* imageDoc = new ImageDocument();
    imageDoc->create();
    imageDoc->open("image_document.jpg");
    imageDoc->saveAs("new_image_document.jpg");
    imageDoc->print();
    imageDoc->close();

    delete imageDoc;

    return 0;
}