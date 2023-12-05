#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

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

void getNumbers(std::string str, std::vector<uint32_t> &winning, std::vector<u_int32_t> &ours)
{
    // Vector to save the scratchcard
    std::vector<std::string> scratchcard;
    // Vector to help split the numbers
    std::vector<std::string> temp;

    // Remove Game info (not needed)
    str = str.substr(str.find(": ", 0) + 2, str.size() - 1);
    scratchcard = split(str, " | ");

    // Make the vector with the winning vectors
    temp = split(scratchcard[0], " ");
    for (std::string n : temp)
        if (isdigit(n[0]))
            winning.push_back(stoi(n));

    // Make the vector with our numbers
    temp = split(scratchcard[1], " ");
    for (std::string n : temp)
        if (isdigit(n[0]))
            ours.push_back(stoi(n));
}

uint32_t part1(std::vector<std::string> lines)
{
    // Sum of the points
    uint32_t sum = 0;
    // Vector to save winning numbers
    std::vector<uint32_t> winning;
    // Vector to save our numbers
    std::vector<uint32_t> ours;

    for (std::string str : lines)
    {
        getNumbers(str, winning, ours);

        // Intersection of both sets
        std::sort(winning.begin(), winning.end());
        std::sort(ours.begin(), ours.end());
        std::vector<uint32_t> matches;
        std::set_intersection(winning.begin(), winning.end(), ours.begin(), ours.end(), std::back_inserter(matches));

        // Sum the result
        sum += (1 << matches.size()) >> 1;

        // Clear vectors
        matches.clear();
        winning.clear();
        ours.clear();
    }
    return sum;
}

uint32_t part2(std::vector<std::string> lines)
{
    // Sum of the number of scratchcards
    uint32_t sum = 0;
    // Total number of scratchcards
    int nr_cards = lines.size();
    // Vector to keep track of number of scratchcards
    std::vector<int> n_scratchcards(nr_cards);
    // Variable to keep track of the scratch card
    int curr_scratchcard = 0;
    // Vector to save winning numbers
    std::vector<uint32_t> winning;
    // Vector to save our numbers
    std::vector<uint32_t> ours;

    // Add original copies of each scratchcard
    std::fill(n_scratchcards.begin(), n_scratchcards.end(), 1);

    for (std::string str : lines)
    {

        getNumbers(str, winning, ours);

        // Intersection of both sets
        std::sort(winning.begin(), winning.end());
        std::sort(ours.begin(), ours.end());
        std::vector<uint32_t> matches;
        std::set_intersection(winning.begin(), winning.end(), ours.begin(), ours.end(), std::back_inserter(matches));

        int size = matches.size();
        // Skip if last scratchcard
        if (curr_scratchcard < nr_cards - 1 && size > 0)
        {
            // For each match add +1 to the next scratchcards
            for (int j = curr_scratchcard + 1; j <= curr_scratchcard + size; j++)
            {
                if (j == nr_cards)
                    break;
                // Add the number of current_scratchcards
                n_scratchcards[j] += n_scratchcards[curr_scratchcard];
            }
        }

        // Sum the result
        sum += n_scratchcards[curr_scratchcard++];

        // Clear vectors
        matches.clear();
        winning.clear();
        ours.clear();
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