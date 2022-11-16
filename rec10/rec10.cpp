// Rec10 Created by Fanyue Meng

#include <iostream>
#include <vector>
using namespace std;

class PrintedMaterial {
public:
    PrintedMaterial(unsigned numPages)
    : numOfPages(numPages)
    {}

    virtual void displayNumPages() const = 0;

private:
    unsigned numOfPages;
};

void PrintedMaterial::displayNumPages() const {
    cout << numOfPages << endl;
}

class Magazine : public PrintedMaterial {
public:
    Magazine(unsigned numPages)
    : PrintedMaterial(numPages)
    {}

    // virtual NOTE even without writing "virtual"
    // again, this overriden method IS virtual
    // viruality cannot be removed once installed
    // Also note that the = 0 has is not there
    void displayNumPages() const {
    cout << "Hi, I'm a Magazine object stored\n"
         << "(but I can't know that I am being\n"
         << "stored (by pointer) in a vector of\n"
         << "PrintedMaterial pointers!\n";
    PrintedMaterial::displayNumPages();
    cout << "(and I'm very glossy!\n";
    }

private:
};

class Book : public PrintedMaterial {
public:
    Book(unsigned numPages)
    : PrintedMaterial(numPages)
    {}

private:
};

class TextBook : public Book {
public:
    TextBook(unsigned numPages, unsigned numIndxPgs)
    : Book(numPages),
      numOfIndexPages(numIndxPgs)
    {}

    void displayNumPages() const {
    cout << "\nThis is a textbook.\n";
    cout << "It is a very boring textbook.\n";
    cout << "Pages: ";
    PrintedMaterial::displayNumPages();
    cout << "Index pages: ";
    cout << numOfIndexPages << endl;
    }

private:
    unsigned numOfIndexPages;
};

class Novel : public Book {
public:
    Novel(unsigned numPages)
        : Book(numPages)
    {}
    void displayNumPages() const
    {
        cout << "\nThis is the story of a very\n"
             << " interesting programmer's quest\n"
             << "  understand inheritance.\n"
             << "   The journey is just beginning\n"
             << "    and already the journeyman\n"
             << "      hacker, no - not a hacker! -\n"
             << "         a programmer who reads, and\n"
             << "             studies and understands code\n"
             << "                 Hackers steal and don't even\n"
             << "                      try to understand what they stole\n"
             << "                           before using it.\n"
             << "\n       ...But I digress.\n"
             << "\nThis novel is quite long, there\n"
             << "being this number of pages:\n"
             << "=====================================\n"
             << "                 ";
        PrintedMaterial::displayNumPages();
        cout << "=====================================\n"
             << "Whew!\n"
             << " but there is an exciting\n"
             << "  programming adventure on every\n"
             << "   single one of them!\n"
             << "    And now, let's let the quest continue..."
             << endl << endl << endl;
    }

private:
};


// tester/modeler code
int main() {
    TextBook text(5430, 23);
    Novel novel(213);
    Magazine mag(6);

    // as direct method calls
    cout << "\nEach will now be asked directly,\n"
     << "using the dot member operator to\n"
     << "display its number of pages:\n";
    text.displayNumPages();
    novel.displayNumPages();
    mag.displayNumPages();
    cout << "===========\n";

    // Storing generic objects in a vector
    cout << "\n\nNow we'll use a container. Yea!!!\n\n";
    vector< PrintedMaterial* > allThemPrinties;
    allThemPrinties.push_back(&text);
    allThemPrinties.push_back(&novel);
    allThemPrinties.push_back(&mag);
    for(size_t ndx=0; ndx < allThemPrinties.size(); ++ ndx) {
    allThemPrinties[ndx]->displayNumPages();
    cout << endl;
    }
//    cout << "===========\n";
//    for (const PrintedMaterial* pmPtr : allThemPrinties) {
//    pmPtr->displayNumPages();
//    cout << endl;
//    }
}
