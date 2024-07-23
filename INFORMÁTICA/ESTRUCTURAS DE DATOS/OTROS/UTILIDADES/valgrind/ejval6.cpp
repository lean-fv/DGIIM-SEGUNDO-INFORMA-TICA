#include <iostream>
using namespace std;

int *reserva(int n) {
  return new int [n];
}

int *funcion() {
  return reserva(4);
}

int main(int argc, char *argv[]) {
  int *ptr=funcion();
}
