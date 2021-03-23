//Racing time!

#include <ctime>
#include <iostream>
#include <vector>
using namespace std;

//Provided function. DO NOT modify this function.
void time_function(void(*fn)(int), string functionName, int size) {
  time_t start_time, end_time;
  time(&start_time);
  fn(size); //Run the callback function
  time(&end_time);
  cout << "Ran function " << functionName << " with input size " << size;
  cout << " in " << end_time-start_time << " seconds." << endl;
}

//Provided function. You do not need to modify this function.
// You MAY modify it if you want to.
void linear(int size) {
  int var;
  for (int i=0; i<size; i++) {
    var = rand();
  }
}

//Provided function. You do not need to modify this function.
// You MAY modify it if you want to.
void quadratic(int size) {
  int var;
  for (int i=0; i<size; i++) {
    for (int j=0; j<size; j++) {
      var = rand();
    }
  }
}

void fillVector(int size) {
  //TODO complete this method and test its speed in main
  // You MUST use push_back()
  vector<int> var;
  int vari;
  for (int i=0; i<size; i++) {
    vari = rand();
    var.push_back(vari);
  }
  
}

void fillArrayUsingIndices(int size) {
  //TODO complete this method and test its speed in main
  // You MUST use array indexing such as myarray[i]
  int vari;
  int* var = NULL;
  var = new int[size];
  for (int i=0; i<size; i++) {
    vari = rand();
    var[i] = vari;
  }
  delete[] var;
  var = NULL;
}

void fillArrayUsingPointers(int size) {
  //TODO complete this method and test its speed in main
  // You MUST use only pointers to fill data
  int* var = NULL;
  int vari;
  var = new int[size];
  for (int i=0; i<size; i++) {
    vari = rand();
    *(var + i) = vari;
  }
  delete[] var;
  var = NULL;
}

int main() {
  //TODO Replace with your own speed tests.
  // Document each test with the average speed you recorded.
  // Speeds of 0 or 1 are not sufficient for testing.
  
  // 4 times of tests
  time_function(linear, "linear", 1000000000);// 7.75 seconds
  time_function(quadratic, "quadratic", 30000);// 7 seconds
  time_function(fillVector, "fillVector", 1000000000);// 18.75 seconds
  time_function(fillArrayUsingIndices, "fillArrayUsingIndices", 1000000000);// 9 seconds
  time_function(fillArrayUsingPointers, "fillArrayUsingPointers", 1000000000);// 9 seconds
}
