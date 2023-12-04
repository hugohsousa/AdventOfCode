#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>

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

std::vector<std::vector<char>> create2DArray(std::vector<std::string> lines)
{
    int n_l = lines.size();
    int n_col = lines[0].size();

    // Create 2D vector
    std::vector<std::vector<char>> schem(n_l, std::vector<char>(n_col, 0));

    for (int i = 0; i < n_l; i++)
    {
        for (int j = 0; j < n_l; j++)
        {
            schem[i][j] = lines[i][j];
        }
    }

    return schem;
}

std::vector<int> searchPartNumbers(std::vector<std::vector<char>> schem, int x, int y)
{
    // Vector to save the part numbers
    std::vector<int> part_list;
    int i;
    int n_l = schem.size();
    int n_col = schem[0].size();

    // To convert string to number
    std::string number = "";

    // Search all positions adjacent to schem[x][y]
    // (x,y-1)
    i = 1;
    while (y - i >= 0 && isdigit(schem[x][y - i]))
        number = schem[x][y - i++] + number;

    if (number != "")
        part_list.push_back(stoi(number));

    number.clear();

    // (x,y+1)
    i = 1;
    while (y + i < n_col && isdigit(schem[x][y + i]))
        number += schem[x][y + i++];

    if (number != "")
        part_list.push_back(stoi(number));

    number.clear();

    // (x-1,y+1), (x-1,y-1) ,(x-1,y)
    if (x > 0)
    {
        // (x-1,y)
        if (isdigit(schem[x - 1][y]))
        {
            number += schem[x - 1][y];

            // (x-1,y-1)
            i = 1;
            while (y - i >= 0 && isdigit(schem[x - 1][y - i]))
                number = schem[x - 1][y - i++] + number;

            // (x-1,y+1)
            i = 1;
            while (y + i < n_col && isdigit(schem[x - 1][y + i]))
                number += schem[x - 1][y + i++];

            if (number != "")
                part_list.push_back(stoi(number));

            number.clear();
        }
        else
        {
            // (x-1,y-1)
            i = 1;
            while (y - i >= 0 && isdigit(schem[x - 1][y - i]))
                number = schem[x - 1][y - i++] + number;

            if (number != "")
                part_list.push_back(stoi(number));

            number.clear();

            // (x-1,y+1)
            i = 1;
            while (y + i < n_col && isdigit(schem[x - 1][y + i]))
                number += schem[x - 1][y + i++];

            if (number != "")
                part_list.push_back(stoi(number));

            number.clear();
        }
    }

    // (x+1,y+1), (x+1,y-1) ,(x+1,y)
    if (x + 1 < n_l)
    {
        // (x+1,y)
        if (isdigit(schem[x + 1][y]))
        {
            number += schem[x + 1][y];
            // (x+1,y-1)
            i = 1;
            while (y - i >= 0 && isdigit(schem[x + 1][y - i]))
                number = schem[x + 1][y - i++] + number;

            // (x+1,y+1)
            i = 1;
            while (y + i < n_col && isdigit(schem[x + 1][y + i]))
                number += schem[x + 1][y + i++];

            if (number != "")
                part_list.push_back(stoi(number));

            number.clear();
        }
        else
        {
            // (x+1,y-1)
            i = 1;
            while (y - i >= 0 && isdigit(schem[x + 1][y - i]))
                number = schem[x + 1][y - i++] + number;

            if (number != "")
                part_list.push_back(stoi(number));

            number.clear();

            // (x+1,y+1)
            i = 1;
            while (y + i < n_col && isdigit(schem[x + 1][y + i]))
                number += schem[x + 1][y + i++];

            if (number != "")
                part_list.push_back(stoi(number));

            number.clear();
        }
    }

    return part_list;
}

uint32_t part1(std::vector<std::vector<char>> schem)
{
    // Sum of the part numbers
    uint32_t sum = 0;

    int n_l = schem.size();
    int n_col = schem[0].size();

    for (int i = 0; i < n_l; i++)
    {
        // Search for a symbol
        for (int j = 0; j < n_col; j++)
        {
            if (!isdigit(schem[i][j]) && schem[i][j] != '.')
            {
                // Search for part numbers
                std::vector<int> part_list = searchPartNumbers(schem, i, j);
                sum += std::accumulate(part_list.begin(), part_list.end(), 0);
            }
        }
    }

    return sum;
}

uint32_t part2(std::vector<std::vector<char>> schem)
{
    // Sum of the part numbers
    uint32_t sum = 0;

    int n_l = schem.size();
    int n_col = schem[0].size();

    for (int i = 0; i < n_l; i++)
    {
        // Search for a gear
        for (int j = 0; j < n_col; j++)
        {
            if (schem[i][j] == '*')
            {
                // Search for part numbers
                std::vector<int> part_list = searchPartNumbers(schem, i, j);
                if (part_list.size() == 2)
                    sum += part_list[0] * part_list[1];
            }
        }
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
    std::vector<std::vector<char>> schem = create2DArray(lines);

    // Solutions
    int res;

    // Part1
    res = part1(schem);
    std::cout << "Part1: " << res << "\n";

    // Part2
    res = part2(schem);
    std::cout << "Part2: " << res << "\n";

    return 0;
}