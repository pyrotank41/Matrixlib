	
/*mymatrix.h*
 
/*
  Karan Singh Kochar
  U. of Illinois, Chicago
  CS 251: Spring 2020
  Project #02
*/
 
/*
  mymatrix

  The mymatrix class provides a matrix (2D array) abstraction.
  The size can grow dynamically in both directions (rows and
  cols).  Also, rows can be "jagged" --- i.e. rows can have
  different column sizes, and thus the matrix is not necessarily
  rectangular.  All elements are initialized to the default value
  for the given type T.  Example:

*/

/*    
  // Sample use case.
  mymatrix<int>  M;  // 4x4 matrix, initialized to 0
 
  M(0, 0) = 123;
  M(1, 1) = 456;
  M(2, 2) = 789;
  M(3, 3) = -99;

  M.growcols(1, 8);  // increase # of cols in row 1 to 8

  for (int r = 0; r < M.numrows(); ++r)
  {
     for (int c = 0; c < M.numcols(r); ++c)
        cout << M(r, c) << " ";
     cout << endl;
  }

  Output:
    123 0 0 0
    0 456 0 0 0 0 0 0
    0 0 789 0
    0 0 0 -99
*/
 
#pragma once
 
#include <iostream>
#include <exception>
#include <stdexcept>
 
using namespace std;
 
template<typename T>
class mymatrix
{
private:
  // Variables ------------------------------------------------------------------------
  struct ROW
  {
    T*  Cols;     // dynamic array of column elements
    int NumCols;  // total # of columns (0..NumCols-1)
  };
 
  ROW* Rows;     // dynamic array of ROWs
  int  NumRows;  // total # of rows (0..NumRows-1)

  // private functions -----------------------------------------------------------------
  
  // isRectangular
  // Checking of a matrix is rectangular
  bool isRectangular(const mymatrix<T>& other){
    
    int numCols = Rows[0].NumCols; // number of columns of 1st row.
    for( int r = 1; r < NumRows; r++)
    { 
      if(numCols != Rows[r].NumCols ){ // checking #columns v/s row's #columns
        return false; // false if there is a missmatch.
      }
    }
    return true; // returns true if not missmatch.
  }

  // isMultipliable:
  //
  // Can we multiply two matrix?  Only if M1 is R1xN and M2 is NxC2. 
  // This yields a result that is R1xC2.
  // Here other is one matrix and "This" object is another.
  // Example: 3x4 * 4x2 => 3x2
  
  bool isMultipliable(const mymatrix<T>& other){

    if(Rows[0].NumCols == other.NumRows) //size RxN and NxC check.
    { 
      return true;
    }
    else 
    {
      return false;
    }
  } 

  // private ends here -------------------------------------------------------------------
 
public:
  
  
  
  // default constructor: ----------------------------------------------------------------
  //
  // Called automatically by C++ to construct a 4x4 matrix.  All
  // elements are initialized to the default value of T.
  
  mymatrix()
  {
    Rows = new ROW[4];  // an array with 4 ROW structs:
    NumRows = 4;
 
    // initialize each row to have 4 columns:
    for (int r = 0; r < NumRows; ++r)
    {
      Rows[r].Cols = new T[4];  // an array with 4 elements of type T:
      Rows[r].NumCols = 4;
 
      // initialize the elements to their default value:
      for (int c = 0; c < Rows[r].NumCols; ++c)
      {
        Rows[r].Cols[c] = T{};  // default value for type T:
      }
    }
  }
 
  // parameterized constructor: ------------------------------------------------------------
  //
  // Called automatically by C++ to construct a matrix with R rows,
  // where each row has C columns. All elements are initialized to
  // the default value of T.
  //
  mymatrix(int R, int C)
  {
    if (R < 1)
      throw invalid_argument("mymatrix::constructor: # of rows");
    if (C < 1)
      throw invalid_argument("mymatrix::constructor: # of cols");

    
    Rows = new ROW[R];
    NumRows = R;

    for(int r = 0; r < NumRows; ++r)
    {
      Rows[r].Cols = new T[C];
      Rows[r].NumCols = C;
      for(int c = 0; c < C; ++c)
      {
        Rows[r].Cols[c] = T{}; // T{} refers to the default value for type T.
      }
    }
  }
 
  // copy constructor: -------------------------------------------------------------------------
  //
  // Called automatically by C++ to construct a matrix that contains a
  // copy of an existing matrix.  Example: this occurs when passing
  // mymatrix as a parameter by value
  //
  //   void somefunction(mymatrix<int> M2)  <--- M2 is a copy:
  //   { ... }
  //
  mymatrix(const mymatrix<T>& other)
  { 
    this->Rows = new ROW[other.NumRows]; //Creating And array of ROW struct.
    this->NumRows = other.NumRows;      

    for (int r = 0; r < NumRows; ++r)
    { 
      int NumCols = other.Rows[r].NumCols;
      this->Rows[r].Cols = new T[NumCols]; // creating new Cols array
      this->Rows[r].NumCols = NumCols;

      //copying over all the elements from other matrix over to prevent shallow copy.
      for (int c = 0; c < other.NumRows; ++c)
      {
        this->Rows[r].Cols[c] = other.Rows[r].Cols[c];        
      } 
    }
  }
 
  // numrows: -----------------------------------------------------------------------------------
  //
  // Returns the # of rows in the matrix.  The indices for these rows
  // are 0..numrows-1.
  //
  int numrows() const
  {
    return NumRows;
  }
   
 

  // numcols: ------------------------------------------------------------------------------------
  
  // Returns the # of columns in row r.  The indices for these columns
  // are 0..numcols-1.  Note that the # of columns can be different
  // row-by-row since "jagged" rows are supported --- matrices are not
  // necessarily rectangular.

  int numcols(int r) const
  { 
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::numcols: row");

    return Rows[r].NumCols;
  }

  //  growcols: ----------------------------------------------------------------------------------
    
  //   Grows the # of columns in row r to at least C.  If row r contains
  //   fewer than C columns, then columns are added; the existing elements
  //   are retained and new locations are initialized to the default value
  //   for T.  If row r has C or more columns, then all existing columns
  //   are retained -- we never reduce the # of columns.
    
  //   Jagged rows are supported, i.e. different rows may have different
  //   column capacities -- matrices are not necessarily rectangular.

  void growcols(int r, int C)
  {
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::growcols: row");
    if (C < 1)
      throw invalid_argument("mymatrix::growcols: columns");

    if(C > Rows[r].NumCols){ //making sure Colums are grater than current NumCols.
      T *newCol = new T[C];
      
      int i;
      for ( i = 0; i < numcols(r); i++) // copying over existing values.
        newCol[i] = Rows[r].Cols[i]; 
    
      for( int c = i; c < C; c++) // initializing value to default.
        newCol[c] = T{};
      
      delete[] Rows[r].Cols;
      Rows[r].Cols = newCol;
      Rows[r].NumCols = C;
    }

    
  }

  // grow : ----------------------------------------------------------------------------------------
  
  // Grows the size of the matrix so that it contains at least R rows,
  // and every row contains at least C columns.
  
  // If the matrix contains fewer than R rows, then rows are added
  // to the matrix; each new row will have C columns initialized to
  // the default value of T.  If R <= numrows(), then all existing
  // rows are retained -- we never reduce the # of rows.
  
  // If any row contains fewer than C columns, then columns are added
  // to increase the # of columns to C; existing values are retained
  // and additional columns are initialized to the default value of T.
  // If C <= numcols(r) for any row r, then all existing columns are
  // retained -- we never reduce the # of columns.
  
  void grow(int R, int C)
  {
    if (R < 1)
      throw invalid_argument("mymatrix::grow: # of rows");
    if (C < 1)
      throw invalid_argument("mymatrix::grow: # of cols");
    
    
    for(int r = 0; r < NumRows; ++r) // growing columns in already existing rows.
        growcols(r,C);

    if(R > NumRows) //if rows to grow is more than current rows. we add new rows.
    { 
      ROW* tempRows = new ROW[R]; //new temp Rows for growing matrix.
  
      
      int r;
      for( r = 0; r < R; ++r) 
      {
        tempRows[r].Cols = new T[C];
        tempRows[r].NumCols = C;
        
        if(r < NumRows) // storing previous rows to the tempRows.
        {
          for( int c = 0; c < C; ++c)
          tempRows[r].Cols[c] = at(r, c);
        }
        else // Storing default values in rest of the remaining places.
        {
          for( int c = 0; c < C; ++c)
          tempRows[r].Cols[c] = T{};
        }
        
      } 

      delete[] Rows; // Deleting old rows for new Rows.
      this->Rows = tempRows;
      NumRows = R;
    }
    
  }
 
 
  
  // size: -------------------------------------------------------------------------------------
  // 
  // Returns the total # of elements in the matrix.
  
  int size() const
  {
    int size = 0; 
    for(int r = 0; r < NumRows; r++)
    {
      size = size + Rows[r].NumCols;
    }
 
    return size;
  }
 
  // at : ----------------------------------------------------------------------------------------
  //
  // Returns a reference to the element at location (r, c); this
  // allows you to access the element or change it:
  //  
  //   M.at(r, c) = ...
  //   cout << M.at(r, c) << endl;

  T& at(int r, int c)
  {
    if (r < 0 || r >= NumRows)
    {
      //cout << "** error: trying to access rowIndex = " << r << " where maxRows = " << NumRows<< endl; 
      throw invalid_argument("mymatrix::at: row");
    }
      
      
    if (c < 0 || c >= Rows[r].NumCols)
    { 
      //cout << "** error: trying to access colIndex = " << c << " where maxCols = " << Rows[r].NumCols << endl; 
      throw invalid_argument("mymatrix::at: col");
    }
      

    return Rows[r].Cols[c];
  }
 
 
  // () : --------------------------------------------------------------------------------------------
  
  // Returns a reference to the element at location (r, c); this
  // allows you to access the element or change it:
  
  //   M(r, c) = ...
  //   cout << M(r, c) << endl;

  T& operator()(int r, int c)
  {
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::(): row");
    if (c < 0 || c >= Rows[r].NumCols)
      throw invalid_argument("mymatrix::(): col");
 
    return Rows[r].Cols[c];
  }

  // scalar multiplication : ---------------------------------------------------------------------------
  
  // Multiplies every element of this matrix by the given scalar value,
  // producing a new matrix that is returned.  "This" matrix is not
  // changed.
  
  // Example:  M2 = M1 * 2;  

  mymatrix<T> operator*(T scalar)
  {
    mymatrix<T> result;
    result.Rows = Rows;
    result.NumRows = NumRows;
 
    for(int r = 0; r < NumRows; ++r){
      int numCols = Rows[r].NumCols;
      for (int c = 0; c < numCols; ++c)
      {
        result.at(r,c) = result.at(r,c)*scalar;
      }
    }
    return result;
  }

  
  
  
  // matrix multiplication: --------------------------------------------------------------------------------
  
  // Performs matrix multiplication M1 * M2, where M1 is "this" matrix and
  // M2 is the "other" matrix.  This produces a new matrix, which is returned.
  // "This" matrix is not changed, and neither is the "other" matrix.
  
  // Example:  M3 = M1 * M2;
  
  // NOTE: M1 and M2 must be rectangular, if not an exception is thrown.  In
  // addition, the sizes of M1 and M2 must be compatible in the following sense:
  // M1 must be of size RxN and M2 must be of size NxC.  In this case, matrix
  // multiplication can be performed, and the resulting matrix is of size RxC.
  
  mymatrix<T> operator*(const mymatrix<T>& other)
  {
    
    // both matrices must be rectangular for this to work:
    if (!isRectangular(*this))
      throw runtime_error("mymatrix::*: this not rectangular");
    
    if (!isRectangular(other))
      throw runtime_error("mymatrix::*: other not rectangular");
 
   

    if (!isMultipliable(other))
      throw runtime_error("mymatrix::*: size mismatch");
  
    mymatrix<T> result(1,1); // keeping result matrix to minimum.
    mymatrix<T> matrix2(1,1); // "

    // creating a shallow copy of other matrix to get arround Const.
    matrix2.Rows = other.Rows;
    matrix2.NumRows = other.NumRows;

    int resRows = this->NumRows; // this will be our new NumRows.
    int resCols = other.Rows[0].NumCols; // this will be our new NumCols.
    
    result.grow(resRows,resCols); // resizing output matrix.


    for(int i = 0; i < resRows; ++i)
    {
      for(int j = 0; j < resCols; ++j)
      { 
        T sum = T{};
        for(int k = 0; k < this->Rows[0].NumCols; ++k){
          
          T a = at(i,k);
          T b = matrix2.at(k,j);
          sum = sum + (a * b);
        }
        result(i,j) = sum;  
      }
    }
    
    return result;
  }

  // _output : ---------------------------------------------------------------------------
  //
  // Outputs the contents of the matrix; for debugging purposes.

  void _output()
  { 
    cout <<endl;

    for (int r = 0; r < this->NumRows; ++r)
    {
      for (int c = 0; c < this->Rows[r].NumCols; ++c)
      {
        cout << this->Rows[r].Cols[c] << " ";
      }
      cout << endl;
    }

    cout <<endl;
  }
 
};
