#include <iostream>
#include <fstream>
#include <vector>
#include <string>

/**
 * @brief Reads "pc_input.txt" and returns the contents of this
 * file a vector of strings, with each line as the element of the array
 * 
 * @return std::vector<std::string> 
 */
std::vector<std::string> file_contents()
{
    std::vector<std::string> data;
    std::string line;
    std::ifstream pc_input_file("pc_input.txt");
    if (!pc_input_file.is_open())
        return data;

    while (std::getline(pc_input_file, line))
    {
        // Ignore lines starting with #
        if (line[0] == '#')
            continue;
        data.push_back(line);
    }
    pc_input_file.close();
    return data;
}

int main()
{
    std::vector<std::string> file_data = file_contents();
    for (std::string &line : file_data)
    {
        std::cout << line << std::endl;
    }
    return 0;
}
