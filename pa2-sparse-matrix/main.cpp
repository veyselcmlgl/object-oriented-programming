#include <iostream>
#include <fstream>
#include <string>
#include "SparseVector.h"
#include "SparseMatrix.h"

using namespace std;

int main()
{
ofstream outfile;
outfile.open("output.txt", ios::out | ios::trunc );

//Creating a SparseVector from file
SparseVector a1("a1.txt");
SparseVector a2("a2.txt");
SparseVector a3;
/*cout << endl << "test:" << endl;
for(int i=0; i<a1.vec.size(); i++) {
    cout << "Element: " << a1.vec[i] << endl;
}*/

outfile<<"a1"<<endl<<a1<<endl;
outfile<<"a2"<<endl<<a2<<endl;

//Binary operations and assignment
a3 = a1 + a2;
outfile<<"a3"<<endl<<a3<<endl;
outfile<<"a2-a1"<<endl<<a2-a1<<endl;
outfile << "Dot product of a1 and a3"<< endl << dot(a1,a3) << endl;

a1 = a1 + (-a1);

outfile<<"a1"<<endl<<a1<<endl;

//Creating SparseMatrix from file
SparseMatrix m1("m1.txt");
SparseMatrix m2("m2.txt");
SparseMatrix m3("m3.txt");

/*vector<vector<double>> test;
outfile<<"m3"<<endl<<m3<<endl;

for (const auto& row : test) {
    for (double value : row) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
}*/
outfile<<"m1"<<endl<<m1<<endl;
outfile<<"m2"<<endl<<m2<<endl;
outfile<<"m1+m2"<<endl<<m1+m2<<endl;
outfile<<"m1-m2"<<endl<<m1-m2<<endl;
m2 = -m2;
outfile<<"-m2"<<endl<<m2<<endl;
outfile << "m1 + (-m2)" << endl << m1+m2 << endl;
//Transpose
//outfile<<"transpose of m2"<< endl << m2.transpose()<<endl;
outfile<<"transpose of m3" << endl << m3.transpose() << endl;
outfile << "m3*transpose of m3" << endl << m3*m3.transpose() << endl;
//Dot product
//outfile<<dot(a2,a3)<<endl;

return 0;
}