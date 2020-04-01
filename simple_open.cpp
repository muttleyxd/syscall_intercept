#include <fstream>

int main()
{
    std::ofstream plik("hello.txt");
    plik << "xd";
    plik.close();
    return 0;
}