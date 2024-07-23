#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
  int *vec = new int [5];
  for (int i=0; i<5; i++)
    vec[i] = 0;
  delete vec;
}
