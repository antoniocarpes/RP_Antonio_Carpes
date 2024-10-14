#include <iostream>

using namespace std;

struct VecF {
  float* data;
  int dim;

  VecF() {
    cout << "I am the default constructor of" << this << endl;
    data=nullptr;
    dim=0;
  }

  VecF(int dim){
    cout << "I am the fancy constructor of" << this << endl;
    data = nullptr;
    this->dim = 0;
    resize(dim);
  }

  VecF(const VecF& src):
    VecF(src.dim)
  {
    cout << "I am the copy ctor " << this << " src:" << &src << endl;
    for (int i=0; i<dim; ++i) {
      data[i]=src.data[i];
    }
  }

  ~VecF() {
    cout << "I am the DESTRUCTOR of" << this <<  endl;
    if (data)
      delete [] data;
  }


  VecF operator+(const VecF& src ) {
    cout << "I am + op" << this << " src: "<< &src << endl;
    VecF other(*this);
    for (int i=0; i<dim; ++i)
      other.data[i]+=src.data[i];
    return other;
  }

  VecF& operator=(const VecF& src ) {
    cout << "I am assignment op" << this << " src: "<< &src << endl;
    resize(src.dim);
    for (int i=0; i<dim; ++i) {
      data[i]=src.data[i];
    }
    return *this;
  }

  void resize(int new_dim) {
    if (new_dim==dim)
      return;

    if (new_dim==0) {
      delete [] data;
      data=nullptr;
      dim=0;
      return;
    }

    float* new_data=new float[new_dim];

    int min_dim = new_dim;
    if (min_dim>dim)
      min_dim=dim;

    for (int i=0; i<min_dim; ++i)
      new_data[i]=data[i];

    delete[] data;
    data=new_data;
    dim=new_dim;
  }
              
  void print() {
    cout << "[";
    
    for (int i=0; i<dim; ++i) {
      cout << data[i] << " ";
    }

    cout << "]" << endl;
  }

  //Elements access. Redefinition of the operator [] for VecF struct
  float& operator[](int index){
  if (index >= dim || index < 0){
    throw std::out_of_range("Index out of bounds");
  }
  return data[index];
}

//Substraction operator
VecF operator-(const VecF& src){
  VecF other(*this);
  for (int i = 0; i < dim; i++){
    other.data[i] -= src.data[i]; 
  }
  return other;
}

//Multiplication by a scalar
VecF operator * (double scl){
  VecF other(*this);
  for (int i = 0; i < dim; i++){
    other.data[i] *= scl;
  }
  return other;
}

//Dot product

double operator *(const VecF& src){
  double result = 0;
  for (int i = 0; i < dim; i++){
    result += data[i]*src.data[i];
  }
  return result;
}


};

/*int main() {
  //VecF v(5);
  //for (int i=0; i<5; ++i)
    //v.data[i]=i;
  //v.print();

  //VecF v2=v;
  //v2.print();

  //VecF v3(3);
  //v3=v2;

  //(v3+v2).print();

  //std::cout << v[2] << std::endl;
  
  // VecF v0; // 
  // VecF v(5);
  // v[4]=10;
  // VecF v2=v;
  // v=v2+v;
  VecF v(5), w(5);
  for (int i=0; i<5; ++i){
    //std::cout << i << std::endl;
    v[i]=i;
    w[i] = 2*i;
  }
  //std::cout << v[0] << std::endl;

  VecF z(5);

  //z = w - v;
  z.print();

  // = v*2.0;
  z.print();//

  std::cout <<"Dot product: " << v*w << std::endl;

  
}*/
