#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm> 
using namespace std;

// Getline() and GetInterger() methods introduced in the Streams
string GetLine() {        
  string result;        
  getline(cin, result);        
  return result;    
}    
int GetInteger() {        
  while(true) {             
    stringstream converter;            
    converter << GetLine();                                
    int result;            
    if(converter >> result) {                
      char remaining;                
      if(converter >> remaining)                     
        cout << "Unexpected character: " << remaining << endl;                
      else                     
        return result;             
    } else                
      cout << "Please enter an integer." << endl;            
    cout << "Retry: ";        
  }    
}


void printVector(vector<int> v) {
  // print out every vector
  for (size_t i = 0; i < v.size(); ++i) {
    cout << "value at pos ";
    cout << i ;
    cout << ": is " ;
    cout << v[i] << endl;
  }
}

/*
 * This method implements the vector by saving user's inputs.
 */
void task1(vector<int> &v) {
  for (int i = 0;; ++i) {            
    cout << "Enter a value for the vector ";            
    int val = GetInteger();
    // if user gives negative integers, task1 finishes
    if (val < 0)
      break;            
    // save the integers in the vector
    v.push_back(val);
  }
  return;
}

/*
 * This method add new integer into the vector.
 */
void task2(vector<int> &v, int num, int posInsert) {
  // if the given position less than 0, insert the number into position 0
  if (num < 0)
    v.insert(v.begin(), num);
  else
    v.insert(v.begin() + posInsert, num);
  return;
}

/*
 * This method remove the integer.
 */
void task3(vector<int> &v, int posRemove) {
  // if the vector is empty, do nothing about it
  if (v.size() == 0) {
  return;
  }
  // if the given position less than 0, remove the integer at position 0
  else if (posRemove <= 0) {
    v.erase(v.begin());
  }
  // if the given position bigger than the vector size, remove the integer at the end
  else if (posRemove >= v.size()) {
    v.erase(v.end() - 1);
  }
  else {
    v.erase(v.begin() + posRemove);
  }
  return;
}

/*
 * This method sort the vector and remove the duplication.
 */
void task4(vector<int> v) {
  sort(v.begin(), v.end());
  // print out format
  cout << "" << endl;
  cout << "" << endl;
  cout << "sorted vector is" << endl;
  printVector(v);;
  
  // Remove the duplications
  v.erase(unique(v.begin(), v.end()), v.end());
  // print out format
  cout << "" << endl;
  cout << "" << endl;
  cout << "Sorted vector after duplicate removal is" << endl;
  printVector(v);
  
  return;
}

int main() {
  vector<int> values;
  
  // Call task1 and print out the vector
  task1(values);
  cout << " The elements of the continer are" << endl;
  printVector(values);
  
  // print out format
  cout << "" << endl;
  cout << "" << endl;
  cout << "Enther the value of the element you want to enter" << endl;
  int num = GetInteger();
  cout << "enter the position" << endl;
  int posInsert = GetInteger();
  
  // Call task2 and print out the vector
  task2(values, num, posInsert);
  cout << " the vector after insertion of a new value is" << endl;
  printVector(values);
  
  // print out format
  cout << "" << endl;
  cout << "" << endl;
  cout << " Enter the position of the element you want to delete" << endl;
  int posRemove = GetInteger();
  // Call task3 and print out the vector
  task3(values, posRemove);
  printVector(values);
  
  // Call task4 and print out the vector, task4 is pass-by-value
  task4(values);
}

