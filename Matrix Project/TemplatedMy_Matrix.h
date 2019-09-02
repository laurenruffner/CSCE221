#include <iostream>
#include <exception>

using namespace std;

// Definitions of user defined type exceptions 
struct invalid_input : public exception {
  virtual const char* what() const throw()
  { return "Invalid matrix input"; }
};

struct incompatible_matrices : public exception {
  virtual const char* what() const throw()
  { return "Incompatible matrices"; }
};

template <class T>

class My_matrix {
	
  //member variables
  int n, m;
  T **ptr;
  void allocate_memory();  // optional
  
public:	
  //member functions
  My_matrix();  // default constructor
  My_matrix(int n1, int m1); // parameter constructor
  ~My_matrix(); // destructor
  My_matrix(const My_matrix<T>& mat); // copy constructor
  My_matrix(My_matrix<T>&& mat);  // move constructor (optional)
  My_matrix<T>& operator=(const My_matrix<T>& mat); //copy assignment operator
  My_matrix<T>& operator=(My_matrix<T>&& mat); // move assignment operator (optional)
  int number_of_rows() const; 
  int number_of_columns() const;
  T* operator()(int i) const; // overloaded to access to ith row
  T& operator()(int i, int j); // overloaded to access (i,j) element
  T operator()(int i, int j) const; // overloaded to access (i,j) element
  T elem(int i, int j) const; // overloaded to access (i,j) element
  T& elem(int i, int j); // overloaded to access (i,j) element
  void fillmat();
};

// see the handout for the description of these operators
template <typename T>
ostream& operator<<(ostream& out, const My_matrix<T>& mat);
template <typename T>
istream& operator>>(istream& in, My_matrix<T>& mat);
template <typename T>
My_matrix<T> operator+(const My_matrix<T>& mat1, const My_matrix<T>& mat2);
template <typename T>
My_matrix<T> operator*(const My_matrix<T>& mat1, const My_matrix<T>& mat2);

template <typename T>
My_matrix<T>::My_matrix()
{
  n=0; m=0;
  ptr = nullptr;
}

template <typename T>
void My_matrix<T>::allocate_memory()
{
  ptr = new T* [n];
  for(int i=0; i< n; i++){
      ptr[i]=new T [m];
  }
}

template <typename T>
My_matrix<T>::My_matrix(int n1, int m1){ 
  n = n1;
  m = m1;
  ptr = new T*[n1];
  for(int i=0; i< n1;i++){
      ptr[i]=new T [m1];
  }


  for (int i=0; i < n1; i++){
    for (int j=0; j < m1; j++){
      ptr[i][j]=0;
    }
  }
}

template <typename T>
void My_matrix<T>::fillmat(){
  //FILLING THE MATRIX
  T x;
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

template <typename T>
My_matrix<T>::My_matrix(const My_matrix<T>& mat)
{ n = mat.number_of_rows();
  m = mat.number_of_columns();
  this-> allocate_memory();
  for(int i=0; i < n; i++){
    for(int j=0; j < m; j++){
      ptr[i][j] = mat.elem(i,j);
    }
  }
}

template <typename T>
// move constructor (optional)
My_matrix<T>::My_matrix(My_matrix<T>&& mat)
{
  this -> n = mat.n;
  this -> m = mat.m;
  this->ptr = mat.ptr;
  mat.ptr = nullptr;
  mat.m = 0;
  mat.n = 0;
}

template <typename T>
My_matrix<T>::~My_matrix()
{
  for(int i=0; i < n; i++){
    delete[] ptr[i];
  }
  delete [] ptr;
}

template <typename T>
My_matrix<T>& My_matrix<T>::operator=(const My_matrix& mat)
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

template <typename T>
// move assignment operator (optional)
My_matrix<T>& My_matrix<T>::operator=(My_matrix<T>&& mat)
{
  for(int i = 0; i < n; i++){
    delete[] ptr[i];
  }

  this -> n = mat.n;
  this -> m = mat.m;
  this-> ptr = mat.ptr;
  mat.n = 0;
  mat.m = 0;
  mat.ptr = nullptr;
  
}

template <typename T>
int My_matrix<T>::number_of_rows() const
{
  return n;
}

template <typename T>
int My_matrix<T>::number_of_columns() const
{
  return m;
}

template <typename T>
T* My_matrix<T>::operator()(int i) const
{
  return ptr[i];
}

template <typename T>
T My_matrix<T>::operator()(int i, int j) const
{
  return ptr[i][j];
}

template <typename T>
T& My_matrix<T>::operator()(int i, int j)
{
  return ptr[i][j];
}

template <typename T>
T My_matrix<T>::elem(int i, int j) const
{

  if (i < 0 || i >= n) throw out_of_range("Out of range");
  if (j < 0 || j >= m) throw out_of_range("Out of range");
  return ptr[i][j];
}

template <typename T>
T& My_matrix<T>::elem(int i, int j)
{
  return ptr[i][j];
}

template <typename T>
ostream& operator<<(ostream& out, const My_matrix<T>& mat)
{
  for (int i=0; i < mat.number_of_rows(); i++){
    for (int j=0; j < mat.number_of_columns(); j++){
      out << mat(i,j) << " ";
    }
    out << "\n";
  }
}

template <typename T>
istream& operator>>(istream& in, My_matrix<T>& mat)
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
  My_matrix<T> tempmat(n,m);

  for (int i=0; i < n; i++){
    for(int j=0; j < m; j++){
      in >> tempmat(i,j);
    }
  }

  // COPY ASSIGNMENT
  mat = tempmat; 
}

template <typename T>
My_matrix<T> operator+(const My_matrix<T>& mat1, const My_matrix<T>& mat2)
{
  int row1, row2, col1, col2;
  row1 = mat1.number_of_rows();
  row2 = mat2.number_of_rows();
  col1 = mat1.number_of_columns();
  col2 =  mat2.number_of_columns();

  if (row1 != row2 || col1 != col2){
    throw incompatible_matrices();
  }

  My_matrix<T> temp2(row1,col1);
  for (int i=0; i < row1; i++){
    for (int j=0; j < col1; j++){
      temp2(i,j) = mat1(i,j) + mat2(i,j);
    }
  }
  cout << "rows: " << row1 << endl;
  cout << "columns: " << col1 << endl;
  return temp2;
}

template <typename T>
My_matrix<T> operator*(const My_matrix<T>& mat1, const My_matrix<T>& mat2)
{ 
  int row1, row2, col1, col2;
  row1 = mat1.number_of_rows();
  row2 = mat2.number_of_rows();
  col1 = mat1.number_of_columns();
  col2 =  mat2.number_of_columns();

  if (col1 != row2){
    throw incompatible_matrices();
  }

  My_matrix<T> temp(row1, col2);
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