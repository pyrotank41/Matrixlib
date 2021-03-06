#include <iostream>
#include "mymatrix.h"

using namespace std;

bool access_test() // checking if at and operator () is working. 
{
  cout << "Matrix element access test: ";
  try
  {
    mymatrix<int> M;
    int x = M.at(3,3);
    x = M(3,2);
    cout << "Pass" << endl;
    return true;  // since it reached here, at and () access works.
  }
  catch(const std::exception& e)
  {
    cout << "Fail" << endl;
    return false;
  }
  
  
}

bool edit_test() // checking if the the elements of the matrix is editing or not.
{
  cout << "Matrix element access and modify test: ";
  try
  {
    mymatrix<int> M;
    int numRow = M.numrows();
    int newDefault = 1;

    for(int r =0; r < numRow; ++r)
    {
      int numCol = M.numcols(r);
      for(int c =0; c < numCol; ++c){
        M(r,c) = newDefault;
      }
    }
    cout << "Pass" << endl;
    return true;
  }
  catch(const std::exception& e)
  {
    cout << "Fail" << endl;
    return false;
  }
  
}

bool growcol_test() // testing the growcallfunction.
{
  cout << "growcol() test: ";
  try
  {
    mymatrix<int>  M;  // 4x4 matrix, initialized to 0
 
    M(0, 0) = 123;
    M(1, 1) = 456;
    M(2, 2) = 789;
    M(3, 3) = -99;

    M.growcols(1, 8);  // increase # of cols in row 1 to 8
    
    cout << "Pass" << endl;
    return true; // grow works well
  }
  catch(exception e)
  {
    cout << "Fail" << endl;
    return false;
  }
  
}

bool grow_test() // testing grow function
{
  cout << "grow() test: ";
  try
  { 
    mymatrix<int> M1(2,2);
    M1(0,0) = 1;
    M1(0,1) = 2;
    M1(1,0) = 3;
    M1(0,1) = 4;
    M1.grow(5,5);
    cout << "Pass" << endl;
    return true; // grow works well
  }
  catch(exception e)
  {
    cout << "Fail" << endl;
    return false;
  }
}

bool scalar_test() // testing scalar multiplication
{
  cout << "scalar multiplication test: ";
  try
  {
    mymatrix<int> M1;
    
    M1(0, 0) = 2;
    M1(1, 1) = 2;
    M1(2, 2) = 2;
    M1(3, 3) = 2;
    
    M1 = M1*2;
    
    cout << "Pass" << endl << "\nOutput:";
    M1._output();
    return true; // grow works well
  }
  catch(exception e)
  {
    cout << "Fail" << endl;
    return false;
  }
}

void isEqual(mymatrix<int>& M, mymatrix<int>& MA) // checking if the matrix is equal
{
  if(M.numrows() != MA.numrows()){
    throw invalid_argument("isEqual:: Rows does not match");
  }
  
  for (int r = 0; r < M.numrows(); r++)
  {

    if(M.numcols(r) != MA.numcols(r))
    {
      throw invalid_argument("isEqual:: colums does not match");
    }
    for (int c = 0; c < M.numcols(r); c++)
    {
      if(M(r,c) != MA(r,c))
      {
        throw invalid_argument("isEqual:: Matrix is not equal");
      }
    }
    
  }
  
}

bool matmulti_test() //testing matrix multipliction.
{
  cout << "matrix multiplication test: ";
  try
  {
    mymatrix<int> M1(4,5);
    mymatrix<int> M2(5,3);
    
    M1(0, 0) = 2;
    M1(1, 1) = 2;
    M1(2, 2) = 2;
    M1(3, 3) = 2;

    M2(0, 0) = 1;
    M2(1, 1) = 1;
    M2(2, 2) = 1;
    M2(3, 2) = 1;

    M1._output();
    M2._output();

    mymatrix<int> M3 = M1*M2;
    mymatrix<int> MA(4,3);

    MA(0, 0) = 2;
    MA(1, 1) = 2;
    MA(2, 2) = 2;
    MA(3, 2) = 2;

    isEqual(M3,MA);
    cout << "Pass" << endl << "\nOutput:";
    M3._output();
    return true; // grow works well
  }
  catch(const std::exception& e)
  {
    cout << "Fail" << endl;
    std::cerr << e.what() << '\n';
    return false;
  }
}


void run_tests()
{
  int passed = 0;
  int count = 6;


  passed = passed + access_test();
  passed = passed + edit_test();
  passed = passed + growcol_test();
  passed = passed + grow_test();
  passed = passed + scalar_test();
  passed = passed + matmulti_test();

  cout << endl;
  cout << "Total tests passed: " << passed << endl;
  cout << "Total tests failed: " << count - passed << endl;

}


int main() {
  
  run_tests();

  return 0;
  
 
}