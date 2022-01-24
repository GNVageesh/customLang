#include <iostream>
using namespace std;

int main()
{
    cout << "simplepareser 0.1\n"
         << endl;

    File *fh = fopen("test.bi", "r");
    if (!fh)
    {
        cerr << "Cant find file" << endl;
    }
    fseek(fh, 0, SEEK_END);
    size_t fileSize = ftell(fh);
    fseek(fh, 0, SEEK_SET);
    string fileContents(fileSize, ' ');
    fread(fileContents.data(), fileSize, fh);

    cout << fileContents << endl;

    return 0;
}