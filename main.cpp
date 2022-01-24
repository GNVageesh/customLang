#include <iostream>
using namespace std;

int main()
{
    cout << "simpleparser\n"
         << endl;

    FILE *fh = fopen("D:\\customLang\\test.bi", "r");
    if (!fh)
    {
        cerr << "Cant open file" << endl;
    }
    fseek(fh, 0, SEEK_END);
    size_t fileSize = ftell(fh);
    fseek(fh, 0, SEEK_SET);
    string fileContents(fileSize, ' ');
    fread(fileContents.data(), 1, fileSize, fh);

    cout << fileContents << endl;

    return 0;
}