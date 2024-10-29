#include <iostream>
#include <cmath>
using namespace std;

using Scalar=float;

struct Vec2f {
  static constexpr int Dim=2;
  Scalar values[Dim];
  inline Vec2f& operator+=(const Vec2f& src) {
    for (int i=0; i<Dim; ++i)
      values[i]+=src.values[i];
    return *this;
  };
  inline Vec2f& operator-=(const Vec2f& src) {
    for (int i=0; i<Dim; ++i)
      values[i]-=src.values[i];
    return *this;
  };
  
  inline void fill(const Scalar v=Scalar(0)) {
    for (int i=0; i<Dim; ++i)
      values[i]=v;
  };
  
  inline Scalar dot(const Vec2f& src) const {
    Scalar acc=Scalar(0);
    for (int i=0; i<Dim; ++i)
      acc += values[i]*src.values[i];
    return acc;
  };

  inline Vec2f operator+(const Vec2f& other) const {
    Vec2f v=*this;
    v+=other;
    return v;
  }

  inline Vec2f operator-(const Vec2f& other) const {
    Vec2f v=*this;
    v-=other;
    return v;
  }

  /*inline Vec2f& operator=(const Vec2f& src){
    values[0] = src.values[0];
    values[1] = src.values[1];
    return *this;
  }*/
};

  
ostream& operator << (ostream& os, const Vec2f& src){
  os << "V2 [" <<&src << "] [ ";
  for (int i =0; i<Vec2f::Dim; ++i) {
    os << src.values[i] << " ";
  }
  os << " ]";
  return os;
}

struct Rotation2f {
  static constexpr int Dim=2;
  Scalar R[Dim][Dim];
  void setIdentity(){
    R[0][0] = 1;
    R[1][1] = 1;
  }

  //returns the inverse (transposed)
  inline Rotation2f inverse() const {
    //TODO
    Rotation2f other;
    for (int i = 0; i < Dim; i++){
      for (int j = 0; j < Dim; j++){
        other.R[i][j] = R[j][i];
      }
    }
    return other;
  }
  
  // multiplies two matrices
  inline Rotation2f operator*(const Rotation2f & other) const {
    //TODO
    Rotation2f result;
    for (int i = 0; i < Dim; i++){
      for (int j = 0; j < Dim; j++){
        result.R[i][j] = 0;
        for (int k = 0; k < Dim; k++){
          result.R[i][j] += R[i][k]*other.R[k][j];
        }
      }
    }
    return result;
  }

  // computes the angle
  Scalar toAngle() const {
    return atan2(R[1][0],R[0][0]);
  }
  
  void setAngle(Scalar angle) {
    Scalar s=sin(angle), c=cos(angle);
    R[0][0] = c;
    R[1][0] = s;
    R[0][1] = -s;
    R[1][1] = c;
    /*R={ {c, -s},
        {s,  c}*/
        
    } // initializer list
  

  // returns R*src;
  Vec2f operator*(const Vec2f& src) const{
    Vec2f result;
    for (int i = 0; i < Dim; i++){
      result.values[i] = 0;
      for (int j = 0; j < Dim; j++){
        result.values[i] += R[i][j]*src.values[j];
      }
    }
    return result;
  }

  const Rotation2f& transposeInPlace() {
    for (int r=0; r<Dim; ++r) {
      for (int c=r+1; c<Dim; ++c){
        std::swap(R[r][c],R[c][r]);
      }
    }
    return *this;
  }
};


struct Isometry2f{
  Vec2f t;
  Rotation2f R;
  Isometry2f(){}
  Isometry2f(Scalar x, Scalar y, Scalar theta){
    // todo;
    t.values[0] = x;
    t.values[1] = y;
    R.setAngle(theta);
  }

  Isometry2f(const Vec2f& translation,
             const Rotation2f& rotation){
    // todo;
    t = translation;
    R = rotation;
  }

  inline void setIdentity(){
    // todo
    t.values[0] = 0;
    t.values[1] = 0;
    R.setIdentity();
  }

  inline Isometry2f operator*(const Isometry2f& src) const {
    //todo
    Isometry2f result;
    result.t = src.t + t;
    result.R = R*src.R;
    return result;
  }

  inline Isometry2f inverse() const {
    // todo
    Isometry2f result;
    Vec2f t_neg;
    t_neg = t - t;
    t_neg = t_neg - t;
    result.t = R.inverse()*t_neg;
    result.R = R.inverse();
    return result;
  }

  inline Vec2f operator*(const Vec2f& src) const {
    // todo
    Vec2f product;
    product = R*src + t;
    return product;
  }
  
};

//Define method to print isometry in console
  ostream& operator <<(ostream& os, const Isometry2f src){
    os << "Isometry being printed : \n";
    os << "[";
    for (int i = 0; i < src.R.Dim; i++){
      for (int j = 0; j < src.R.Dim; j++){
        os << src.R.R[i][j] << ' ';
        if (j == 1){
          if (i == 1){
            os << "]";
            os << endl;
          }
          else{
            os << endl;
          }
          }
        }
      }
    os << endl;
    os << src.t.values[0] << '\n';
    os << src.t.values[1] << '\n';
    return os;
  }

int main (int argc, char** argv) {
  Vec2f v1;
  v1.fill();
  cout << v1;
  Vec2f v2=v1;
  cout << v2;
  v2.fill(0.1);
  cout << v2;
  cout << (v1-=v2);

  /*Rotation2f test;
  for (int i = 0; i < test.Dim; i++){
    for (int j = 0; j < test.Dim; j++){
      test.R[i][j] = i;
    }
  }

  Rotation2f test2;
  test2.R[0][0] = 1;
  test2.R[1][0] = 2;
  test2.R[0][1] = 3;
  test2.R[1][1] = 1;*/

  /*Rotation2f result;
  result = test*test2;*/

  /*for (int i = 0; i < test.Dim; i++){
    for (int j = 0; j < test.Dim; j++){
      cout << result.R[i][j] << endl;
    }
  }*/
  

  /*for (int i = 0; i < test.Dim; i++){
    for (int j = 0; j < test.Dim; j++){
      cout << test.R[i][j] << endl;
    }
  }*/


  /*Rotation2f inversed;
  inversed = test.inverse();
  for (int i = 0; i < test.Dim; i++){
    for (int j = 0; j < test.Dim; j++){
      cout << inversed.R[i][j];
    }
  }*/
  
  /*Vec2f v;
  v.values[0] = 1;
  v.values[1] = 0;
  cout << v;
  Vec2f result;
  result = test*v;
  cout << result;*/

  //TEST ISOMETRIES PRINT
  /*Isometry2f iso(1,1,0);
  cout << iso;

  Isometry2f iso1(1,1,M_PI/2);
  cout << iso1;*/
  
  /*Isometry2f iso_result;
  iso_result = iso*iso1;
  cout << iso_result;*/

  /*Isometry2f iso1_inv;
  iso1_inv = iso1.inverse();
  cout << iso1_inv;*/

  /*Vec2f v;
  v.values[0] = 1;
  v.values[1] = 1;

  Vec2f result;
  result = iso1*v;
  cout << result.values[0] << ' ' << result.values[1] << endl;*/







  // todo: write the rest to test the above functions
  // hint: comment the todoes and address them one by one
  //       after each is done add a lil test

  // at the end uncomment the following
  
  Isometry2f iso(0.1,0, 0.01);
  Isometry2f pose;
  pose.setIdentity();
  Isometry2f point;
  point.t.values[0]=0;
  point.t.values[1]=0.1;
  
  for (int i=0; i<1000000; ++i) {
    pose=pose*iso;
  }

  cout << pose;
  
}
