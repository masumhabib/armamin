/*
 * FileName: main.cpp
 * Description: Main program.
 * Copyright (C) 2014  K M Masum Habib <masum.habib@gmail.com>
 * Created: 02 Nov 2014.
 */

#include "main.h"
#include "config.h"

#include <iostream>
#include <string>
#include <stdexcept>

#include <armadillo>



using namespace std;
using namespace arma;

/*
 * The main function
 */
int main(int argc, char** argv) {

    cout << "Armadillo Minimum Project v" << ARMAMIN_VERSION << endl;

    mat A = randu<mat>(3,3); // construct a random 3x3 matrix.
    mat B;
    B << 1 << 2 << 3 << endr // B = | 1    2    3 |
      << 4 << 5 << 6 << endr //     | 4    5    6 |
      << 7 << 8 << 9 << endr;//     | 7    8    8 |

    // print A and B
    cout << "A = " << endl << A << endl;
    cout << "B = " << endl << B << endl;
    
    // compute A*B
    mat C = A*B;
    // show A*B
    cout << "A*B = " << endl << C << endl;
    
    // compute A+B
    C = A+B;
    // show A+B
    cout << "A+B = " << endl << C << endl;

    // compute inverse
    C = solve(A, B);
    cout << "A\\B = " << endl << C << endl;

    
    return MAIN_SUCCESS;
}

