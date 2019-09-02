/* 
Implementation of the clas My_matrix
*/

#include "My_matrix.h"
#include <stdexcept>

My_matrix::My_matrix()
{
  n=0; m=0;
  ptr = nullptr;
}

void My_matrix::allocate_memory()
{
  ptr = new int* [n];
  for(int i=0; i< n; i++){
      ptr[i]=new int [m];
  }
}

My_matrix::My_matrix(int n1, int m1){ 
  n = n1;
  m = m1;
  ptr = new int*[n1];
  for(int i=0; i< n1;i++){
      ptr[i]=new int [m1];
  }

  for (int i=0; i < n1; i++){
    for (int j=0; j < m1; j++){
      ptr[i][j]=0;
    }
  }
}

void My_matrix::fillmat(){
  //FILLING THE MATRIX
  int x;
  for (int i=0; i < n; i++){
    cout<< "Row: " << i+1 << endl;
    for (int j=0; j < m; j++){
      cout << "\t Column: " << j+1 << endl;
      cout << "\t Number wanted: " << endl;
      cin >> x;
      ptr[i][j]=x;
    }
  }

}

My_matrix::My_matrix(const My_matrix& mat)
{ n = mat.number_of_rows();
  m = mat.number_of_columns();
  this-> allocate_memory();
  for(int i=0; i < n; i++){
    for(int j=0; j < m; j++){
      ptr[i][j] = mat.elem(i,j);
    }
  }
}

// move constructor (optional)
My_matrix::My_matrix(My_matrix&& mat)
{
  this->ptr = mat.ptr;
  mat.ptr = nullptr;
}

My_matrix::~My_matrix()
{
  for(int i=0; i < n; i++){
    delete[] ptr[i];
  }
  delete [] ptr;
}

My_matrix& My_matrix::operator=(const My_matrix& mat)
{
  n = mat.number_of_rows() ;
  m = mat.number_of_columns();
  this->allocate_memory();
  for(int i=0; i < n; i++){
    for(int j=0; j < m; j++){
      ptr[i][j] = mat(i,j);
    }
  }
}

// move assignment operator (optional)
My_matrix& My_matrix::operator=(My_matrix&& mat)
{
  this -> ptr = nullptr;
  this-> ptr = mat.ptr;
  mat.ptr = nullptr;
  
}

int My_matrix::number_of_rows() const
{
  return n;
}

int My_matrix::number_of_columns() const
{
  return m;
}

int* My_matrix::operator()(int i) const
{
  return ptr[i];
}

int My_matrix::operator()(int i, int j) const
{
  return ptr[i][j];
}

int& My_matrix::operator()(int i, int j)
{
  return ptr[i][j];
}

int My_matrix::elem(int i, int j) const
{

  if (i < 0 || i >= n) throw out_of_range("Out of range");
  if (j < 0 || j >= m) throw out_of_range("Out of range");
  return ptr[i][j];
}

int& My_matrix::elem(int i, int j)
{
  return ptr[i][j];
}

ostream& operator<<(ostream& out, const My_matrix& mat)
{
  for (int i=0; i < mat.number_of_rows(); i++){
    for (int j=0; j < mat.number_of_columns(); j++){
      out << mat(i,j) << " ";
    }
    out << "\n";
  }
}

istream& operator>>(istream& in, My_matrix& mat)
{ 
  int x, n, m, amountline=0, size;
  float word = 1.0;
  in >> n >> m; 
  string line;

  //GET NUMBER OF LINES AKA ROWS + 1
  while (getline(in,line)) {
    amountline ++;
  }
  
  //GO TO BEGINNING OF FILE
  in.clear();
  in.seekg(0, ios::beg);
 
  //GO THROUGH FILE
  in.seekg(0,ios::end);
  size=in.tellg();
  in.seekg(0,ios::beg);

  //GET WORDS AKA THINGS SEPERATED BY SPACES OR NEW LINES
  char ch;
  while(in){
    in.get(ch);
    if(ch==' '||ch=='\n')
      word++;
  }

  cout << "----- " << word << endl;

  //THROW INVALID INPUT IF ROWS OR COLUMNS ARE WRONG LENGTH
  
  float r, q, o;
  o = n;
  r = ((word-2)/n);
  q = m;
  //cout << "r-- " << r << "   q----" << q << endl;
 

  if (n != amountline - 1 || q != r) {
    throw invalid_input();
  }

  //GO TO BEGINNING OF FILE
  in.clear();
  in.seekg(0, ios::beg);
  in >> n >> m;

  //CREATE TEMP MATRIX TO FILL DATA INFO INTO
  My_matrix tempmat(n,m);

  for (int i=0; i < n; i++){
    for(int j=0; j < m; j++){
      in >> tempmat(i,j);
    }
  }

  // COPY ASSIGNMENT
  mat = tempmat; 
}

My_matrix operator+(const My_matrix& mat1, const My_matrix& mat2)
{
  int row1, row2, col1, col2;
  row1 = mat1.number_of_rows();
  row2 = mat2.number_of_rows();
  col1 = mat1.number_of_columns();
  col2 =  mat2.number_of_columns();

  if (row1 != row2 || col1 != col2){
    throw incompatible_matrices();
  }

  My_matrix temp2(row1,col1);
  for (int i=0; i < row1; i++){
    for (int j=0; j < col1; j++){
      temp2(i,j) = mat1(i,j) + mat2(i,j);
    }
  }
  cout << "rows: " << row1 << endl;
  cout << "columns: " << col1 << endl;
  return temp2;
}

My_matrix operator*(const My_matrix& mat1, const My_matrix& mat2)
{ 
  int row1, row2, col1, col2;
  row1 = mat1.number_of_rows();
  row2 = mat2.number_of_rows();
  col1 = mat1.number_of_columns();
  col2 =  mat2.number_of_columns();

  if (col1 != row2){
    throw incompatible_matrices();
  }

  My_matrix temp(row1, col2);
  for (int i=0; i < row1; i++){
    for (int j=0; j < col2; j++){
      for (int k=0; k < col1; k++){
        temp(i,j) += mat1(i,k) * mat2(k,j);
      }
    }
  }
  cout << "rows: " << row1 << endl;
  cout << "columns: " << col2 << "\n";
  return temp;
}