#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> parseInput(std::ifstream &in)
{
    std::vector<std::string> lines;

    // Parse input
    std::string str;
    while (std::getline(in, str))
    {
        // Save line
        lines.push_back(str);
    }

    in.close();

    return lines;
}

uint32_t part1(std::vector<std::string> lines)
{
    // Sum of the calibration values
    uint32_t sum = 0;

    for (std::string str : lines)
    {
        std::string value;
        int size = str.length();

        // Find first digit
        for (int i = 0; i < size; i++)
        {
            if (isdigit(str[i]))
            {
                value += str[i];
                break;
            }
        }

        // Find second digit
        for (int i = size - 1; i >= 0; i--)
        {
            if (isdigit(str[i]))
            {
                value += str[i];
                break;
            }
        }

        // Sum the value
        sum += stoi(value);
    }

    return sum;
}

int checkSubstrings(std::string &str, int size, int index)
{
    // Spelled Numbers
    std::vector<std::string> numbers{"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    // Check if there is a number in the substring
    for (auto it = numbers.begin(), end = numbers.end(); it != end; ++it)
    {
        std::string n = *it;
        if (index + n.size() <= str.size())
        {
            if (str.substr(index, n.size()) == n)
            {
                return std::distance(numbers.begin(), it) + 1;
            }
        }
    }

    return -1;
}

uint32_t part2(std::vector<std::string> lines)
{
    // Sum of the calibration values
    uint32_t sum = 0;

    for (std::string str : lines)
    {
        std::string value;
        int size = str.length();

        // Find first digit
        for (int i = 0; i < size; i++)
        {
            if (isdigit(str[i]))
            {
                value += str[i];
                break;
            }
            // Check substring
            int number = checkSubstrings(str, size, i);
            if (number != -1)
            {
                value += std::to_string(number);
                break;
            }
        }

        // Find second digit
        for (int i = size - 1; i >= 0; i--)
        {
            if (isdigit(str[i]))
            {
                value += str[i];
                break;
            }
            // Check substring
            int number = checkSubstrings(str, size, i);
            if (number != -1)
            {
                value += std::to_string(number);
                break;
            }
        }

        // Sum the value
        sum += stoi(value);
    }

    return sum;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Please provide input file name!\n";
        return -1;
    }

    // Open input file
    std::ifstream in(argv[1]);
    if (!in)
    {
        std::cerr << "Cannot open " << argv[1] << std::endl;
        exit(1);
    }
    // Read and Parse Input
    std::vector<std::string> lines = parseInput(in);

    // Solutions
    int res;

    // Part1
    res = part1(lines);
    std::cout << "Part1: " << res << "\n";

    // Part2
    res = part2(lines);
    std::cout << "Part2: " << res << "\n";

    return 0;
}