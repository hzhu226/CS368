#include <iostream>
#include <unordered_map>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include "p3.hpp"

//Create a new student with the given name
//DO NOT MODIFY THIS CONSTRUCTOR
Student::Student(std::string name) {
  std::ifstream ifs(name+".txt");
  if(!ifs.is_open()) {
    std::cout << "ERROR: Unable to open student data file " + name + ".txt" << std::endl;
    return;
  }
  this->name = name;
  std::string line,grade;
  int courseNum;
  while(getline(ifs,line)) {
//    std::cout << "Read line: " << line << std::endl;
    std::stringstream stst;
    stst << line;
    stst >> courseNum >> grade;
    grades[courseNum] = grade;
  }
}

//DO NOT MODIFY THIS CONSTRUCTOR
ClassList::ClassList(std::string name) {
  std::ifstream ifs(name+".txt");
  if(!ifs.is_open()) {
    std::cout << "ERROR: Unable to open classlist data file " + name + ".txt" << std::endl;
    return;
  }
  this->name = name;
  std::string line,courseName;
  int courseNum,credits;
  while(getline(ifs,line)) {
//    std::cout << "Read line: " << line << std::endl;
    std::stringstream stst;
    stst << line;
    stst >> courseNum >> credits;
    getline(stst,courseName); //Remainder of the line is course name
    courses[courseNum] = {courseName, credits};
  }
}

//TODO Add methods as necessary for compatability with p3.hpp
// You may add additional helper methods
// You may NOT change the required method signatures in p3.hpp
// You are encouraged to use method stubs so that your code will compile and
//   you can test the early pieces of your program.

void ClassList::printClassList() {
  //print out the size of the list
  std::cout<<"Size: "<<courses.size()<<std::endl;
  
  //print out each line properly
  for (std::unordered_map<int,std::pair<std::string,int>>::iterator it = courses.begin(); it != courses.end(); ++it) {
     int courseNum = it->first;
     int credits = courses[courseNum].second;
     std::string courseName = courses[courseNum].first;
     std::cout<<courseName<<" "<<courseNum<<" "<<credits<<std::endl;
  }
}

std::string ClassList::getCourseName(int courseNumber) {
  //if the course number exists in the list, then print out the name of the course
  if (courses.count(courseNumber) == 1)
    return courses[courseNumber].first;
}

void Student::printStudent(ClassList& cl) {
  //print out each line properly
  for (std::map<int,std::string>::iterator it = grades.begin(); it != grades.end(); ++it) {
    int courseNum = it->first;
    //get the course name from the class list
    std::string courseName = cl.getCourseName(courseNum);
    std::string grade = it->second;
    std::cout<<courseName<<" "<<grade<<std::endl;
  }
}

OutsideClassList::OutsideClassList(std::string name) : ClassList(name) {
}

void OutsideClassList::printClassList() {
  //print out the size of the list
  std::cout<<"Size: "<<courses.size()<<std::endl;
  
  //print out each line properly, only print out the name and number of the courses of the 
  //old school
  for (std::unordered_map<int,std::pair<std::string,int>>::iterator it = courses.begin(); it != courses.end(); ++it) {
    int courseNum = it->first;
    std::string courseName = courses[courseNum].first;
    std::cout<<courseName<<" "<<courseNum<<std::endl;
  }
}

void OutsideClassList::printClassList(ClassList& cl) {
  //print out the size of the list
  std::cout<<"Size: "<<courses.size()<<std::endl;
  
  //print out each line properly
  for (std::unordered_map<int,std::pair<std::string,int>>::iterator it = courses.begin(); it != courses.end(); ++it) {
    int outsideNum = it->first; 
    int courseNum = courses[outsideNum].second;
    
    //if the course has new school equivalents, then print out the name and number of the course 
    //of the new school
    if (courseNum != 0) {
      std::string outsideName = courses[outsideNum].first;
      std::string courseName = cl.getCourseName(courseNum);
      std::cout<<courseNum<<" "<<courseName<<" "<<outsideName<<std::endl;
    }
  }
}

int OutsideClassList::getCourseEquivalent(int courseNumber) {
  //return the number of courses of the new school
  int courseNum = courses[courseNumber].second;
  return courseNum;
}

StudentWithTransferCredit::StudentWithTransferCredit(std::string name, std::string schoolName) : Student(name) {
  this->schoolName = schoolName;
}

std::string StudentWithTransferCredit::getSchoolName() {
  return schoolName;
}

void StudentWithTransferCredit::printStudent(OutsideClassList& oldSchool, ClassList& newSchool) {
  //print out each line properly
  for (std::map<int,std::string>::iterator it = grades.begin(); it != grades.end(); ++it) {
    int outsideNum = it->first;
    //get the number of the course of the new school
    int courseNum = oldSchool.getCourseEquivalent(outsideNum);
    
    //if the course has new school equivalents, then print out the name (new school) 
    //and the grade for the courses
    if (courseNum != 0) {
      std::string courseName = newSchool.getCourseName(courseNum);
      std::string grade = it->second;
      std::cout<<" "<<courseName<<": "<<grade<<std::endl;
    }
  }
}

int main() {
  //TODO Your code here
  std::string newSchoolName;
  std::string oldSchoolName;
  std::string studentName;
  std::cout<<"WELCOME TO THE PREREQ-CHECKER"<<std::endl;
  std::cout<<"Classlist: ";
  //type in new school's name
  std::cin>>newSchoolName;
  std::cout<<newSchoolName<<std::endl;
  ClassList x(newSchoolName);
  x.printClassList();
  
  std::cout<<"Classlist: ";
  //type in old school's name
  std::cin>>oldSchoolName;
  std::cout<<oldSchoolName<<std::endl;
  OutsideClassList y(oldSchoolName);
  y.printClassList();
  std::cout<<oldSchoolName<<std::endl;
  y.printClassList(x);
  
  std::cout<<"Name of student: ";
  //type in student's name
  std::cin>>studentName;
  std::cout<<"New student's name is: "<<studentName<<std::endl;
  StudentWithTransferCredit z(studentName, oldSchoolName);
  z.printStudent(y, x);
}
