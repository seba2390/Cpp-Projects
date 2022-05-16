#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <utility>

class Sudoku  // The class
{

public: // Access specifier for class

    /*-- Public attributes --*/
    int sudoku_array[9][9];
    int solved_sudoku_array[9][9];
    int rnd_number_list[9];
    std::vector <std::pair<int,int>> position_list;



    /*-- Constructor --*/
    Sudoku()
    {
        // Setting randomly shuffled list of ints (1-9).
        set_rnd_number_list();
        // Initializing sudoku array (filling with zeroes).
        initialize_sudoku();
        // Setting filled sudoku array.
        fill_sudoku();
        // Copying fully solved sudoku sudoku_array -> solved_sudoku_array.
        set_solved_sudoku();
        // Setting vector list of pairs of ints representing positions in sudoku array.
        set_position_list();
    }

    /* -- Member Functions --*/
    void initialize_sudoku()
    {
        for(int i = 0; i < 9; i++)
        {
            for(int j = 0; j < 9; j++)
            {
                sudoku_array[i][j] = 0;
            }
        }
    }

    void set_solved_sudoku()
    {
        for(int i = 0; i < 9; i++)
        {
            for(int j = 0; j < 9; j++)
            {
                solved_sudoku_array[i][j] = sudoku_array[i][j];
            }
        }
    }

    void set_rnd_number_list()
    {
        // setting vector with integers
        std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};

        // get a time-based seed
        unsigned seed = std::chrono::system_clock::now()
                .time_since_epoch()
                .count();

        // randomly shuffle vector
        shuffle (v.begin(), v.end(), std::default_random_engine(seed));

        // append values to rnd_number_list
        for(int i = 0; i < 9; i++)
        {
            rnd_number_list[i] = v[i];
        }
    }


    void print_rnd_number_list()
    {
        for(int i = 0; i < 9; i++)
        {
            std::cout << rnd_number_list[i] << " ";
        }
    }

    void set_position_list()
    {
        for(int row = 0; row < 9; row++)
        {
            for(int col = 0; col < 9; col++)
            {
                position_list.push_back(std::make_pair(row,col));
            }
        }
    }

    void shuffle_position_list()
    {
        // get a time-based seed
        unsigned seed = std::chrono::system_clock::now()
                .time_since_epoch()
                .count();

        // randomly shuffle vector
        shuffle (position_list.begin(), position_list.end(), std::default_random_engine(seed));
    }

    void print_position_list()
    {
        for(int i = 0; i < 81; i++)
        {
            std::cout<<"("<<position_list[i].first<<","<<position_list[i].second<<")"<<"\n";
        }
    }

    bool is_possible(int row, int col, int number)
    {
        // Checking column
        for(int i = 0; i < 9; i++)
        {
            if (sudoku_array[i][col] == number)
            {
                return false;
            }
        }
        // Checking row
        for(int i = 0; i < 9; i++)
        {
            if (sudoku_array[row][i] == number)
            {
                return false;
            }
        }
        // Checking Square
        int row_0 = (int)(floor((double)row/3) * 3);
        int col_0 = (int)(floor((double)col/3) * 3);
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                if(sudoku_array[row_0 + i][col_0 + j] == number)
                {
                    return false;
                }
            }
        }
        // If everything is ok
        return true;
    }

    bool check_grid()
    {
        for(int i = 0; i < 9; i++)
        {
            for(int j = 0; j < 9; j++)
            {
                if (sudoku_array[i][j] == 0)
                {
                    return false;
                }
            }
        }
        // If no zeros remain
        return true;
    }

    bool fill_sudoku()
    {
        // Re-shuffling rnd number list
        set_rnd_number_list();
        // Main recursion
        int row, col;
        for (int i = 0; i < 81; i++)
        {
            row = (int)floor((double)i/9);
            col = i % 9;
            if (sudoku_array[row][col] == 0)
            {

                for (int j = 0; j < 9; j++)
                {
                    int number = rnd_number_list[j];
                    if (is_possible(row,col,number))
                    {
                        sudoku_array[row][col] = number;
                        if (check_grid())
                        {
                            return true;
                        }
                        else
                        {
                            if (fill_sudoku())
                            {
                                return true;
                            }
                        }
                    }
                }
                break;
            }
        }
        sudoku_array[row][col] = 0;
    }

    void print_sudoku(int array[9][9])
    {
        for(int i = 0; i < 9; i++)
        {
            if(i == 3 || i == 6)
            {
                std::cout << "----------------------------" << "\n";
            }
            for(int j = 0; j < 9; j++)
            {
                if(j == 3 || j == 6)
                {
                    std::cout << "| " << array[i][j] << " ";
                }
                else
                {
                    std::cout << " " << array[i][j] << " ";
                }
            }
            std::cout << "\n";
        }
    }


    void set_sudoku()
    {
        // Placeholder variable
        int currently_removed;

        // Shuffling positions
        shuffle_position_list();

        // counter variable
        int pos_nr = 0;

        /*--- Main loop ---*/
        while (pos_nr < 81)
        {
            int row = position_list[pos_nr].first;
            int col = position_list[pos_nr].second;
            currently_removed = sudoku_array[row][col];
            sudoku_array[row][col] = 0;

            // Re-shuffling rnd number list
            set_rnd_number_list();

            // Counting number of solutions
            int solution_counter = 0;
            for(int i = 0; i < 9; i++)
            {
                int number = rnd_number_list[i];
                if(is_possible(row,col,number))
                {
                    solution_counter++;
                }
            }

            //  multiple solutions -> Undo current removal
            if (solution_counter > 1)
            {
                sudoku_array[row][col] = currently_removed;
                pos_nr++;
            }
            // perfect! still only one solution
            else if (solution_counter == 1)
            {
                pos_nr++;
            }
            // no solutions :((
            else if (solution_counter == 0)
            {
                break;
            }
        }

    }
};

    int main ()
{
    Sudoku my_sudoku;
    my_sudoku.set_sudoku();
    std::cout << "\n";
    std::cout << "##### PRINTING SUDOKU ##### " << "\n";
    my_sudoku.print_sudoku(my_sudoku.sudoku_array);
    std::cout << "\n";
    std::cout << "### PRINTING SOLVED SUDOKU ###  " << "\n";
    my_sudoku.print_sudoku(my_sudoku.solved_sudoku_array);
    return 0;
}