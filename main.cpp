#include <iostream>
#include "mymatrix.h"

using namespace std;

int access_test()
{
  mymatrix<int> M;
  
  return M.at(3,3);
}

void edit_test(mymatrix<int>& M, int newDefault = 1) // checking if the the elements of the vector is editing or not.
{
  int numRow = M.numrows();

  for(int r =0; r < numRow; ++r)
  {
    int numCol = M.numcols(r);
    for(int c =0; c < numCol; ++c){
      // cout << r << "," << c << "  "; 
      M(r,c) = newDefault;
    }
    // cout << endl;
  }
}


int main() {
  
  cout << "Matrix1 is:" << endl; 
  mymatrix<int> yo(3,3);
  
  yo.grow(3, 4);
  edit_test(yo);
  yo._output();
  // yo._output();
  
  // cout << "Matrix size is " << yo.size() << endl;

  cout << "Matrix2 is:" << endl; 
  mymatrix<int> multi(3,3);
  edit_test(multi, 3); 
  multi.grow(4,3);
  multi._output();
  
  cout << "Matrix2 * Matrix1 is:" << endl;
  
  mymatrix<int> multi1 = yo*multi;
  // multi._output();
  return 0;
 
}