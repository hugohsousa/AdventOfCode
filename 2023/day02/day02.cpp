#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>
#include <algorithm>

// Max number of cubes per game (part1)
#define MAX_RED 12
#define MAX_GREEN 13
#define MAX_BLUE 14

// Struct to save game
struct game
{
    int id;
    std::vector<int> red;
    std::vector<int> green;
    std::vector<int> blue;
};

// Split strings
std::vector<std::string> split(std::string s, std::string delimiter)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos)
    {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

std::vector<game> parseInput(std::ifstream &in)
{
    std::vector<game> games;

    // Parse input
    std::string str;
    std::vector<std::string> temp;
    while (std::getline(in, str))
    {
        // New game
        game n;
        temp = split(str, ": ");
        // Save id
        n.id = stoi(temp[0].substr(temp[0].find(" ", 0) + 1, temp[0].size() - 1));

        // Split rounds
        temp = split(temp[1], "; ");
        for (std::string g : temp)
        {
            // Split cubes from the play
            std::vector<std::string> play = split(g, ", ");
            for (std::string p : play)
            {
                // Save the number of cubes
                std::vector<std::string> cube = split(p, " ");
                if (cube[1] == "red")
                    n.red.push_back(stoi(cube[0]));
                if (cube[1] == "green")
                    n.green.push_back(stoi(cube[0]));
                if (cube[1] == "blue")
                    n.blue.push_back(stoi(cube[0]));
            }
        }
        // Save the game
        games.push_back(n);
    }

    in.close();

    return games;
}

int part1(std::vector<game> games)
{

    // Sum of the valid game ids
    uint32_t sum = 0;

    // Variable to track game validation
    bool valid_game = true;

    for (game g : games)
    {
        // Check if a red hand is invalid
        for (int c : g.red)
        {
            if (!valid_game || c > MAX_RED)
            {
                valid_game = false;
                break;
            }
        }
        
        // Check if a green hand is invalid
        for (int c : g.green)
        {
            if (!valid_game || c > MAX_GREEN)
            {
                valid_game = false;
                break;
            }
        }
        
        // Check if a blue hand is invalid
        for (int c : g.blue)
        {
            if (!valid_game || c > MAX_BLUE)
            {
                valid_game = false;
                break;
            }
        }

        // If valid_game sum the id
        if (valid_game)
        {
            sum += g.id;
        }
        valid_game = true;
    }

    return sum;
}

int part2(std::vector<game> games)
{

    // Sum of the power of the sets
    // Power = Number of cubes(needed) of each color multiplied
    uint32_t sum = 0;

    // Variable to track number of cubes
    uint32_t n_red = 0;
    uint32_t n_green = 0;
    uint32_t n_blue = 0;

    // Check if the game is valid
    for (game g : games)
    {
        // Find the number of cubes needed for each color
        // Cubes needed = Max draw
        n_red = *max_element(g.red.begin(), g.red.end());
        n_green = *max_element(g.green.begin(), g.green.end());
        n_blue = *max_element(g.blue.begin(), g.blue.end());
        
        // Sum the power
        sum += n_red * n_green * n_blue;
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
    std::vector<game> games = parseInput(in);

    // Solutions
    int res;

    // Part1
    res = part1(games);
    std::cout << "Part1: " << res << "\n";

    // Part2
    res = part2(games);
    std::cout << "Part2: " << res << "\n";

    return 0;
}