/*
Name of Program: EECS 348 Lab 9
Description: Program that reads a file containing two matrices (ints or doubles) and performs various matrix operations
Input: matrixfile.txt (or any other user-inputted file)
Output: Matrices and various matrix operations
Collaborators: None
Sources: DeepSeek
Author: Oscar Ohly
Creation date: 04/07/2025
*/
#include <iostream> //gets standard C++ library
#include <fstream> //gets file reading capabilities
#include <vector> //gets vector functions used to make matrices
#include <iomanip> //gets input/output formatting functions
#include <stdexcept> //gets exception library
#include <typeinfo> //gets type information
#include <limits> //gets numeric limits operations

template <typename T> //creates new generic type T
class Matrix { //new class Matrix
private: //private functions only accessible within Matrix class
    size_t size; //creates Matrix size variable
    std::vector<std::vector<T> > data; //vector of vectors to store matrix data

public: //public functions available outside class definition
    Matrix(size_t n = 0) : size(n), data(n, std::vector<T>(n)) {} //creates matrix with generic values

    size_t getSize() const { return size; } //functions gets size of matrix

    std::vector<T>& operator[](size_t index) { //defines [] operator allowing for access to rows of matrix
        if (index >= size) { //runs if index is of out of range of matrix
            throw std::out_of_range("Index out of range"); //throws error
        } //ends if statement
        return data[index]; //returns row of matrix
    } //ends operator definition

    // Const access operator
    const std::vector<T>& operator[](size_t index) const { //defines [] operator allowing for access to rows of const Matrix objects
        if (index >= size) { //runs if index is out of range of matrix
            throw std::out_of_range("Index out of range"); //throws error
        } //ends if statement
        return data[index]; //returns row of matrix
    } //ends operator definition

    Matrix<T> operator+(const Matrix<T>& other) const { //overloads + operator allowing for addition of Matrix objects
        if (size != other.size) { //runs if matrices are different sizes
            throw std::invalid_argument("Matrix sizes don't match for addition"); //throws error
        } //ends if statement
        Matrix<T> result(size); //creates new matrix containing values of type T
        for (size_t i = 0; i < size; ++i) { //runs for size of matrix
            for (size_t j = 0; j < size; ++j) { //runs for size of matrix
                result[i][j] = data[i][j] + other[i][j]; //adds every index of added matrices to result
            } //ends for loop
        } //ends for loop
        return result; //returns result matrix
    } //ends operator overload

    Matrix<T> operator*(const Matrix<T>& other) const { //overloads * operator allowing for matrix multiplication
        if (size != other.size) { //runs if matrices are different sizes
            throw std::invalid_argument("Matrix sizes don't match for multiplication"); //throws error
        } //ends if statement
        Matrix<T> result(size); //new matrix containing values of type T
        for (size_t i = 0; i < size; ++i) { //runs for size of matrix
            for (size_t j = 0; j < size; ++j) { //runs for size of matrix
                for (size_t k = 0; k < size; ++k) { //runs for size of matrix
                    result[i][j] += data[i][k] * other[k][j]; //performs matrix multiplication and adds final values to result matrix
                } //ends for loop
            } //ends for loop
        } //ends for loop
        return result; //returns result matrix
    } //ends operator overloader

    void display() const { //function that displays matrices
        for (const auto& row : data) { //runs for number of rows in matrix
            for (const auto& val : row) { //runs for number of values in each row
                std::cout << std::setw(8) << val; //prints values of matrix with proper spacing
            } //ends loop
            std::cout << std::endl; //starts new line
        } //ends loop
    } //ends loop

    T sumMainDiagonal() const { //function returns sum of major diagonal
        T sum = 0; //new variable of type T set to 0
        for (size_t i = 0; i < size; ++i) { //runs for size of matrix
            sum += data[i][i]; //adds major diagonal values to sum
        } //ends for loop
        return sum; //returns sum of major diagonal
    } //ends function

    T sumSecondaryDiagonal() const { //function returns sum of minor diagonal
        T sum = 0; //new variable of type T set to 0
        for (size_t i = 0; i < size; ++i) { //runs for size of matrix
            sum += data[i][size - 1 - i]; //adds minor diagonal values to sum
        } //ends for loop
        return sum; //returns sum of minor diagonal
    } //ends function

    void swapRows(size_t row1, size_t row2) { //function swaps rows in a matrix
        if (row1 >= size || row2 >= size) { //checks if rows are within size of matrix
            throw std::out_of_range("Row index out of range"); //throws error
        } //ends if statement
        std::swap(data[row1], data[row2]); //swaps rows using overloaded [] operator
    } //ends function

    void swapColumns(size_t col1, size_t col2) { //function swaps cols in a matrix
        if (col1 >= size || col2 >= size) { //checks if cols are within size of matrix
            throw std::out_of_range("Column index out of range"); //throws error
        } //ends if statement
        for (size_t i = 0; i < size; ++i) { //runs for size of matrix
            std::swap(data[i][col1], data[i][col2]); //swaps cols using overloaded [] operator, index by index
        } //ends for loop
    } //ends function

    void updateElement(size_t row, size_t col, T value) { //function takes two indices and a value, replaces value at indices with value
        if (row >= size || col >= size) { //checks if given sets of indices is out of bounds of matrix
            throw std::out_of_range("Index out of range"); //throws error
        } //ends if statement
        data[row][col] = value; //replaces value at row/col with value
    } //ends function
}; //ends Matrix class definition

template <typename T> //declares template for a generic type T
void loadMatricesFromFile(const std::string& filename, Matrix<T>& matrix1, Matrix<T>& matrix2) { //function generates two matrices from a file
    std::ifstream file(filename); //opens file with name filename
    if (!file.is_open()) { //checks if file opens
        throw std::runtime_error("Failed to open file"); //throws error
    } //ends if statement

    size_t size; //creates size_T size
    int typeFlag; //creates int typeFlag representing type of matrices
    file >> size >> typeFlag; //sets first value in file to size, second value to typeFlag

    matrix1 = Matrix<T>(size); //creates new Matrix with type T called matrix1
    matrix2 = Matrix<T>(size); //creates new Matrix with type T called matrix2

    for (size_t i = 0; i < size; ++i) { //runs for size of matrix1
        for (size_t j = 0; j < size; ++j) { //runs for size of matrix1
            file >> matrix1[i][j]; //fills matrix1 with values from file
        } //ends loop
    } //ends loop

    for (size_t i = 0; i < size; ++i) { //runs for size of matrix2
        for (size_t j = 0; j < size; ++j) { //runs for size of matrix2
            file >> matrix2[i][j]; //fills matrix2 with values from file
        } //ends loop
    } //ends loop
} //ends function

void swapRows(std::vector<std::vector<int> >& matrix, size_t row1, size_t row2) { //int version of func to swap rows in a matrix
    if (row1 >= matrix.size() || row2 >= matrix.size()) { //checks if rows are within matrix
        throw std::out_of_range("Row index out of range"); //throws error
    } //ends if statement
    std::swap(matrix[row1], matrix[row2]); //swaps rows
} //ends func

void swapRows(std::vector<std::vector<double> >& matrix, size_t row1, size_t row2) { //double version of func to swap rows in a matrix
    if (row1 >= matrix.size() || row2 >= matrix.size()) { //checks if rows are within matrix
        throw std::out_of_range("Row index out of range"); //throws error
    } //ends if statement
    std::swap(matrix[row1], matrix[row2]); //swaps rows
} //ends func

template <typename T> //declares template for generic type T
void updateElement(std::vector<std::vector<T> >& matrix, size_t row, size_t col, T value) { //func that takes two indices and a value of type T
    if (row >= matrix.size() || col >= matrix[0].size()) { //checks if indices are within matrix
        throw std::out_of_range("Index out of range"); //throws error
    } //ends if statement
    matrix[row][col] = value; //replaces value at row/col with value with type T
} //ends func

int main() { //func main that runs when program is executed
    try { //try block that runs if code doesn't error
        std::string filename; //initializes variable filename that stores name of file
        std::cout << "Enter the input file name: "; //prints message
        std::cin >> filename; //sets filename to next user input

        int typeFlag; //new int typeFlag
        size_t size; //new size_T size
        
        std::ifstream tempFile(filename); //opens file
        if (!tempFile.is_open()) { //checks if file is open
            throw std::runtime_error("Failed to open file"); //throws error
        } //ends if statement
        tempFile >> size >> typeFlag; //sets first value in tempFile to size, second value to typeFlag
        tempFile.close(); //closes file

        if (typeFlag == 0) { //block runs if typeFlag=0, e.g. matrices contain int values
            Matrix<int> matrix1, matrix2; //creates two int matrices matrix1 and matrix2
            loadMatricesFromFile(filename, matrix1, matrix2); //calls loadMatricesFromFile which fills matrix1 and matrix2 with values

            std::cout << "\nMatrix 1:\n"; //prints message
            matrix1.display(); //prints matrix1
            std::cout << "\nMatrix 2:\n"; //prints message
            matrix2.display(); //prints matrix2

            std::cout << "\nMatrix Addition Result:\n"; //prints message
            Matrix<int> sum = matrix1 + matrix2; //creates matrix sum that uses overloaded + operator to add matrices
            sum.display(); //prints matrix sum

            std::cout << "\nMatrix Multiplication Result:\n"; //prints message
            Matrix<int> product = matrix1 * matrix2; //creates matrix product that uses overloaded * operator to multiply matrices
            product.display(); //prints matrix product

            std::cout << "\nMatrix 1 Diagonal Sums:\n"; //prints message
            std::cout << "Main Diagonal: " << matrix1.sumMainDiagonal() << "\n"; //calls sumMainDiagonal on matrix1 and prints sum
            std::cout << "Secondary Diagonal: " << matrix1.sumSecondaryDiagonal() << "\n"; //calls sumMinorDiagonal on matrix1 and prints sum

            int choice; //new int choice
            do { //do block that runs and could repeat
                std::cout << "\nMenu for operations on Matrix 1:\n"; //(lines 210-215) prints menu
                std::cout << "1. Swap Rows\n";
                std::cout << "2. Swap Columns\n";
                std::cout << "3. Update Element\n";
                std::cout << "4. Exit\n";
                std::cout << "Enter your choice (1-4): ";
                std::cin >> choice; //sets choice to next user input

                try { //block runs if it doesn't error
                    switch (choice) { //switch block with choice used for comparison
                        case 1: { //runs if choice = 1
                            size_t row1, row2; //creates two size_ts row1 and row2
                            std::cout << "Enter two row indices to swap (0-based): "; //prints message
                            std::cin >> row1 >> row2; //sets next two user inputs to row1 and row2
                            if (!std::cin || row1 >= size || row2 >= size) { //checks if row1 and row2 are within bounds of matrix
                                std::cin.clear(); //clears user input interface
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //removes any input from buffer until new line
                                throw std::out_of_range("Invalid row indices"); //throws error
                            } //ends if statement
                            matrix1.swapRows(row1, row2); //swaps rows in matrix1
                            std::cout << "After swapping rows " << row1 << " and " << row2 << ":\n"; //prints message
                            matrix1.display(); //displays matrix1 after swap
                            break; //breaks from switch block
                        } //ends case
                        case 2: { //runs if choice = 2
                            size_t col1, col2; //creates two size_ts col1 and col2
                            std::cout << "Enter two column indices to swap (0-based): "; //prints message
                            std::cin >> col1 >> col2; //sets next two user inputs to col1 and col2
                            if (!std::cin || col1 >= size || col2 >= size) { //checks if col1 and col2 are within bounds of matrix1
                                std::cin.clear(); //clears user input interface
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //removes any input from buffer until new line
                                throw std::out_of_range("Invalid column indices"); //throws error
                            } //ends if statement
                            matrix1.swapColumns(col1, col2); //swaps cols in matrix1
                            std::cout << "After swapping columns " << col1 << " and " << col2 << ":\n"; //prints message
                            matrix1.display(); //displays matrix1 after swap
                            break; //breaks from switch block
                        } //ends case
                        case 3: { //runs if choice = 3
                            size_t row, col; //creates two size_ts row and col
                            int value; //creates new int value
                            std::cout << "Enter row, column, and new value (0-based indices): "; //prints message
                            std::cin >> row >> col >> value; //sets next three user inputs to row, col, and value
                            if (!std::cin || row >= size || col >= size) { //checks if indices are within bounds
                                std::cin.clear(); //clears user interface
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //clears buffer until new line is reached
                                throw std::out_of_range("Invalid indices"); //throws error
                            } //ends if statement
                            matrix1.updateElement(row, col, value); //calls updateElement on matrix1 to update element at row, col to value
                            std::cout << "After updating element at (" << row << "," << col << "):\n"; //prints message
                            matrix1.display(); //prints matrix1 after change
                            break; //breaks from switch block
                        } //ends case
                        case 4: //runs if case = 4
                            std::cout << "Exiting operations menu.\n"; //prints message
                            break; //breaks from switch block
                        default: //runs if choice didn't equal any of previous cases
                            std::cout << "Invalid choice. Please try again.\n"; //prints message
                    } //ends switch block
                } catch (const std::exception& e) { //runs if error within try block
                    std::cerr << "Error: " << e.what() << ". Please try again.\n"; //prints error message
                } //ends catch block
            } while (choice != 4); //repeats do block if choice didn't equal 4

        } else if (typeFlag == 1) { //runs if typeFlag=1, e.g. matrices contain double values
        //(lines 275-368) All the same code as code in above if statement, only handles double values instead of ints
            Matrix<double> matrix1, matrix2;
            loadMatricesFromFile(filename, matrix1, matrix2);

            std::cout << "\nMatrix 1:\n";
            matrix1.display();
            std::cout << "\nMatrix 2:\n";
            matrix2.display();

            // Matrix addition
            std::cout << "\nMatrix Addition Result:\n";
            Matrix<double> sum = matrix1 + matrix2;
            sum.display();

            // Matrix multiplication
            std::cout << "\nMatrix Multiplication Result:\n";
            Matrix<double> product = matrix1 * matrix2;
            product.display();

            // Diagonal sums
            std::cout << "\nMatrix 1 Diagonal Sums:\n";
            std::cout << "Main Diagonal: " << matrix1.sumMainDiagonal() << "\n";
            std::cout << "Secondary Diagonal: " << matrix1.sumSecondaryDiagonal() << "\n";

            // User input for operations on Matrix 1
            int choice;
            do {
                std::cout << "\nOperations Menu (Matrix 1):\n";
                std::cout << "1. Swap Rows\n";
                std::cout << "2. Swap Columns\n";
                std::cout << "3. Update Element\n";
                std::cout << "4. Exit\n";
                std::cout << "Enter your choice (1-4): ";
                std::cin >> choice;

                try {
                    switch (choice) {
                        case 1: {
                            // Swap rows
                            size_t row1, row2;
                            std::cout << "Enter two row indices to swap (0-based): ";
                            std::cin >> row1 >> row2;
                            if (!std::cin || row1 >= size || row2 >= size) {
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                throw std::out_of_range("Invalid row indices");
                            }
                            matrix1.swapRows(row1, row2);
                            std::cout << "After swapping rows " << row1 << " and " << row2 << ":\n";
                            matrix1.display();
                            break;
                        }
                        case 2: {
                            // Swap columns
                            size_t col1, col2;
                            std::cout << "Enter two column indices to swap (0-based): ";
                            std::cin >> col1 >> col2;
                            if (!std::cin || col1 >= size || col2 >= size) {
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                throw std::out_of_range("Invalid column indices");
                            }
                            matrix1.swapColumns(col1, col2);
                            std::cout << "After swapping columns " << col1 << " and " << col2 << ":\n";
                            matrix1.display();
                            break;
                        }
                        case 3: {
                            // Update element
                            size_t row, col;
                            double value;
                            std::cout << "Enter row, column, and new value (0-based indices): ";
                            std::cin >> row >> col >> value;
                            if (!std::cin || row >= size || col >= size) {
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                throw std::out_of_range("Invalid indices");
                            }
                            matrix1.updateElement(row, col, value);
                            std::cout << "After updating element at (" << row << "," << col << "):\n";
                            matrix1.display();
                            break;
                        }
                        case 4:
                            std::cout << "Exiting operations menu.\n";
                            break;
                        default:
                            std::cout << "Invalid choice. Please try again.\n";
                    }
                } catch (const std::exception& e) {
                    std::cerr << "Error: " << e.what() << ". Please try again.\n";
                }
            } while (choice != 4);

        } else { //runs if typeFlag didn't equal 1 or 0
            throw std::invalid_argument("Invalid type flag in input file"); //throws error
        } //ends if statement

    } catch (const std::exception& e) { //runs if try block failed
        std::cerr << "Error: " << e.what() << std::endl; //prints error message
        return 1; //default return value for main
    } //ends catch block

    return 0; //default return value for main
} //ends main