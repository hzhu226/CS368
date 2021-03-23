#include <iostream>
#include <string>
using namespace std;

int main() { 
	cout << "Your name here ";
  // first line 
  string myName;
  getline(cin, myName); 
  // read the name from cin
  if (myName == "") {
    myName = "CS368 Student";
  }
  cout << "" << endl;
  
  int nameLength = myName.length();
  // get the length of the name in order to print right number of "*"
  
  for (int i = 0; i < 30 + nameLength; i++) {
    cout << "*";
  }
  cout << "" << endl;
  // print right number of "*" for second line
  
  cout << "*";
  for (int i = 0; i < 28 + nameLength; i++) {
    cout << " ";
  }
  cout << "*" << endl;
  // third line; print right number of "*" and blankspace
  
  cout << "* Welcome " + myName + "! Enjoy the class! *" << endl;
  // forth line;
  
  cout << "*";
  for (int i = 0; i < 28 + nameLength; i++) {
    cout << " ";
  }
  cout << "*" << endl;
  // fifth line, same as the thrid line
  
  for (int i = 0; i < 30 + nameLength; i++) {
    cout << "*";
  }
  cout << "" << endl;
  // last line, same as the second line;
}
