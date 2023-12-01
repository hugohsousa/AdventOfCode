#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void parseInput(char *fileName, std::vector<std::string> &lines)
{
    // Open input file
    std::ifstream in(fileName);
    if (!in)
    {
        std::cerr << "Cannot open " << fileName << std::endl;
        exit(1);
    }

    // Parse input
    std::string str;
    while (std::getline(in, str))
    {
        lines.push_back(str);
    }

    in.close();
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Please provide input file name!\n";
        return -1;
    }

    // Read and Parse Input
    std::vector<std::string> lines{};
    parseInput(argv[1], lines);

    // Solutions
    int res;

    // Part1
    res = -1;
    std::cout << "Part1: " << res << "\n";

    // Part2
    res = -1;
    std::cout << "Part2: " << res << "\n";

    return 0;
}