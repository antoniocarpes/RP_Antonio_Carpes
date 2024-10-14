#include <iostream>

int main(){
    float* ptr = nullptr;
    ptr = new float[3];
    //ptr[0] = 20;
    std::cout << ptr[0] << std::endl;
    delete [] ptr;
}