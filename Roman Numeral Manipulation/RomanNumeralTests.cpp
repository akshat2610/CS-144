#include <iostream>
#include <fstream>
#include "RomanNumeral.h"

using namespace std;

const string INPUT_FILE_NAME = "RomanNumeral.txt";

/**
 * A test with some predefined Roman numerals.
 * Output the Roman numerals and perform arithmetic
 * and relational operations on them.
 */
void test1();

/**
 * A test that reads simple arithmetic expressions with
 * Roman numerals from an input file, one per line.
 * Evaluate each expression and print the result.
 * Each expression is in the form    r1 op r2
 * where r1 and r2 are the two Roman numeral operands,
 * and arithmetic operator op is surrounded by blanks
 * and is either + - * or /
 * @param in the input file stream
 */
void test2(ifstream& in);

/**
 * The main. Run the two tests.
 */
int main()
{
    test1();

    ifstream in;
    in.open(INPUT_FILE_NAME);
    if (in.fail())
    {
        cout << "Input file open failed: " << INPUT_FILE_NAME;
        return -1;
    }

    test2(in);
    return 0;
}

void test1()
{
    cout << "Test 1" << endl << endl;

    RomanNumeral r1(53);
    RomanNumeral r2("MCMXLIX");
    RomanNumeral r3("XXXIV");
    RomanNumeral r4(1949);

    cout << "r1 = " << r1 << endl;
    cout << "r2 = " << r2 << endl;
    cout << "r3 = " << r3 << endl;
    cout << "r4 = " << r4 << endl;

    RomanNumeral result = r1 + r2/r3;
    cout << "result = r1 + r2/r3 = "
         << r1 << " + " << r2 << "/" << r3
         << " = " << result << endl;

    cout << endl;

    cout << r1 << " and " << r3 << " are equal: "
         << boolalpha << (r1 == r3) << endl;
    cout << r1 << " and " << r4 << " are not equal: "
         << boolalpha << (r1 != r4) << endl;
    cout << r2 << " and " << r4 << " are equal: "
         << boolalpha << (r2 == r4) << endl;
    cout << r3 << " and " << r4 << " are not equal: "
         << boolalpha << (r3 != r4) << endl;
}

void test2(ifstream& in)
{
    cout << endl;
    cout << "Test 2" << endl << endl;

    RomanNumeral r1, r2, result;
    char op;

    // Read and evaluate each expression, one per line,
    // in the form r1 op r2
    while (in >> r1 >> op >> r2)
    {
        /***** Complete this loop. *****/
        if (op == '+'){
           result = r1 + r2;
        }
        if (op == '-'){
           result = r1 - r2;
        }
        if (op == '*'){
           result = r1 * r2;
        }
        if (op == '/'){
           result = r1 / r2;
        }
        
        // Output the operands, the operator, and the result.
        cout << r1 << " " << op << " " << r2
             << " = " << result << endl;
    }
}