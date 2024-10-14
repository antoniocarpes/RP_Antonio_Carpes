#include <iostream>
#include "in_class.cpp"

struct Matrix {

    float* data;
    int dim_x, dim_y;

    //Default constructor
    Matrix(){
        std::cout << "I am the default constructor of: " << this << std::endl;
        data = nullptr;
        dim_x = 0;
        dim_y = 0;
    }

    //Constructor introducing dimension values on declaration
    Matrix(int dim_x, int dim_y){
        std::cout << "I am the constructor of: " << this << std::endl;
        this -> dim_x = dim_x;
        this -> dim_y = dim_y;
        data = new float[dim_x * dim_y];
    }

    //Constructor which copies from preexisting matrix
    Matrix(const Matrix& src){
        this -> dim_x = src.dim_x;
        this -> dim_y = src.dim_y;
        data = new float[dim_x*dim_y];

        std::cout << "I am the constructor which copies src" << &src << "in " << this << std::endl;
        for (int i = 0; i < dim_x*dim_y; i++){
            data[i] = src.data[i];
        }
    }

    ~Matrix() {
    std::cout << "I am the DESTRUCTOR of" << this <<  std::endl;
    if (data)
      delete [] data;
    }

    void print(){
        std::cout << "[";
        for (int i = 0; i < dim_x; i++){
            for (int j = 0; j < dim_y - 1; j++){
                std::cout << data[i*dim_y + j] << " ";
            }
            if (i == dim_x - 1){
                std::cout << data[(i+1)*dim_y - 1] << "]" << std::endl;
            }
            else{
            std::cout << data[(i+1)*dim_y - 1] << std::endl;
            }
        }
    }


    //Overloading equal operator
    Matrix& operator=(const Matrix& src){
        for (int i = 0; i < dim_x*dim_y; i++){
            data[i] = src.data[i];
        }
        return *this;
    }



    //Overloading addition + operator
    Matrix operator+(const Matrix& src){
        std::cout << "+ operator invoked\n";
        Matrix other(*this);
        for (int i = 0; i < dim_x*dim_y; i++){
            other.data[i] += src.data[i];
        }
        return other;
    }

    //Overloading substraction - operator
    Matrix operator-(const Matrix& src){
        std::cout << "- operator invoked\n";
        Matrix other(*this);
        for (int i = 0; i < dim_x*dim_y; i++){
            other.data[i] -= src.data[i];
        }
        return other;
    }

    //Overloading multiplication by scalar
    Matrix operator*(float scl){
        Matrix other(*this);
        for (int i = 0; i < dim_x*dim_y; i++){
            other.data[i] *= scl;
        }
        return other;
    }

    //Defining multiplication matrix by vector
    VecF operator*(const VecF& vector){
        VecF result(vector.dim);
        if (dim_y != vector.dim) {
            throw std::invalid_argument("Error: Las dimensiones de la matriz y el vector no coinciden.");
            }
        for (int i = 0; i < vector.dim; i++){
            for (int j = 0; j < dim_y; j++){
                result.data[i]+=data[i*dim_y+j]*vector.data[j];
            }
        }
        return result;
    }

    Matrix operator*(const Matrix& src){
        Matrix result(dim_x, src.dim_y);
        if (dim_y != src.dim_x){
            throw std::invalid_argument("Error: Mismatch in dimension for matrix multiplication.");
        }
        for (int i = 0; i < dim_x; i++){
            for (int j = 0; j < src.dim_y; j++){
                result.data[i*src.dim_y + j] = 0;
                for (int k = 0; k < dim_y; k++){
                    result.data[i*src.dim_y + j] += data[i*dim_y+k]*src.data[j+k*src.dim_y];
                }
            }
        }
        return result;
    }

    







};

int main(){
    Matrix A(2,2), B(2,2);
    for (int i = 0; i < 4; i++){
        A.data[i] = i;
        B.data[i] = 3*i*3-1;
        std::cout << A.data[i] << ' ' << B.data[i] << std::endl;
    }

    A.print();
    B.print();
    
    /*for (int i = 0; i < 3*4; i++){
        std::cout << A.data[i] << std::endl;
    }*/

    //Matrix C(3,4);
    //C = A+B;
    //C= A - B;
    //C = A*3.4;
    //VecF vector(4), result(3);

    /*for (int i = 0; i< 4; i++){
        vector.data[i] = 1;
    }
    result = A*vector;
    for (int i = 0; i < 3; i++){
        std::cout << result.data[i] << std::endl;
    }*/

    /*Matrix C(3,3);
    C = A*B;
    for (int i = 0; i < 4; i++){
        std::cout<< C.data[i] << std::endl;
    }*/
}