
#include<iostream>
#include<algorithm> // for std::sort
#include<string>
#include<vector>

struct Students
{
    std::string name{};
    int grade{};
};

bool greater(Students& a, Students& b) // custom greater function with arguments type of struct Students to sort in descending order
{
    return(a.grade > b.grade);
}

std::vector<Students>& inputStudentsList(std::vector<Students>& arr) // pass by refernece and return by refernce to avoid making copies
{
    for (std::size_t i{ 0 }; i < arr.size(); ++i)
    {
        std::cout << " Enter student name: ";
        std::cin >> arr[i].name;
        std::cout << " Enter student grade: ";
        std::cin >> arr[i].grade;
    }
    return arr;

}

int main()
{

    std::cout << " Enter the number of students: ";
    std::size_t count; // or we can use std::array::size_type
    std::cin >> count;

    std::vector<Students>student(count); // empty vector initialized as per number of students to be entered
/*
    for (int i{ 0 }; i < count; ++i)
    {
        std::cout << " Enter student name: ";
        std::cin >> student[i].name;
        std::cout << " Enter student grade: ";
        std::cin >> student[i].grade;
    }  */

    inputStudentsList(student);

   std::sort( &student[0], (&student[0] + count), greater); // custom greater function to sort as per grades of students


    for (auto& i : student)
        std::cout << i.name << " got a grade of " << i.grade << '\n';  

    return 0;
}