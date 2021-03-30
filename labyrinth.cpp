#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<int> dir_r = {0, 0, -1, 1};
std::vector<int> dir_c = {-1, 1, 0, 0};

std::vector<std::string> read_maze(std::string file)
{
    std::vector<std::string> maze;
    std::ifstream maze_file;
    std::string row;
    maze_file.open(file);

    if (!maze_file)
    {
        std::cout << "Unable to open file!";
        return {};
    }
    else
    {
        while (std::getline(maze_file, row))
            maze.emplace_back(row);

        maze_file.close();
        return maze;
    }
}

void print_maze(std::vector<std::string> &maze)
{
    for (int i = 0; i < maze.size(); i++)
    {
        for (int j = 0; j < maze[0].size(); j++)
        {
            std::cout << maze[i][j] << " ";
        }
        std::cout << "\n";
    }
}

bool is_safe(std::vector<std::string> &maze, std::pair<int, int> cell)
{
    return (cell.first >= 0 && cell.first < maze.size() &&
            cell.second >= 0 && cell.second < maze[0].size() &&
            maze[cell.first][cell.second] == '.');
}

int labyrinth_solver(std::vector<std::string> &maze, std::pair<int, int> cell, int counter)
{
    maze[cell.first][cell.second] = '0' + counter;
    int max_length = 0;

    for (int i = 0; i < dir_r.size(); i++)
    {
        std::pair<int, int> new_cell;
        new_cell.first = cell.first + dir_r[i];
        new_cell.second = cell.second + dir_c[i];

        if (is_safe(maze, new_cell))
        {
            int length = labyrinth_solver(maze, new_cell, counter + 1);
            max_length = std::max(max_length, length);
        }
    }

    return 1 + max_length;
}

std::pair<int, std::pair<int, int>> find_longest_path(std::vector<std::string> maze)
{
    std::pair<int, int> cell = std::make_pair(-1, -1);
    int longest_length = -1;

    for (int i = 0; i < maze[0].size(); i++)
    {
        if (maze[0][i] == '.')
        {
            int length = labyrinth_solver(maze, std::make_pair(0, i), 0);
            if (length > longest_length)
            {
                longest_length = length;
                cell = std::make_pair(0, i);
            }
        }
    }
    return std::make_pair(longest_length, cell);
}

int main(int argc, char *argv[])
{
    std::string input_file = "input.txt";
    std::vector<std::string> maze;
    std::pair<int, std::pair<int, int>> longest_path;
    if (argc > 1)
    {
        input_file = argv[1];
    }
    maze = read_maze(input_file);
    longest_path = find_longest_path(maze);
    labyrinth_solver(maze, longest_path.second, 0);
    std::cout << longest_path.first << "\n";
    print_maze(maze);
    return 0;
}