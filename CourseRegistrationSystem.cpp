#include <iostream>
#include <string>
#include <vector>
#include <fstream>

//struct holds info about the courses
struct Courses {
    std::string idPrefix;
    std::string courseNumber;
    std::string courseTitle;
    std::string creditValue;
};
int addToSchedule;

int main(int argc, char* argv[])
{
    Courses course;
    Courses chosenCourse;
    int inputCourseSelection;
    std::vector<Courses>courseFiles; //vector that stores Course objects
    std::string myFileLines; //variable that holds each line from file
    std::vector<Courses>scheduledCourses; //vector stores scheduled courses
    int selectedCourse;
    bool stillSelecting = true;
  
    if (argc > 1)
    {
        std::fstream myFile;
        myFile.open(argv[1], std::ios::in);
        if (!myFile)
        {
            std::cout << "Error opening file.\n";
        }
        else
        {
            while (getline(myFile, myFileLines))
            {                
                course.idPrefix = myFileLines.substr(10, 3);
                course.courseNumber = myFileLines.substr(13, 4);
                course.courseTitle = myFileLines.substr(29, 63);
                course.creditValue = myFileLines.substr(182, 3);
                courseFiles.push_back(course);

            }
        }        
    }
    while (stillSelecting) {
        std::cout << "Do you want to select courses by course title or by department and course number?\n "
            << "(Type 1 for title, 2 for department and course number) " << std::endl;
        std::cin >> inputCourseSelection;
        while (inputCourseSelection != 1 && inputCourseSelection != 2) {
            std::cout << "You must enter 1 for course title or 2 for department and course number.\n"
                << "Do you want to select courses by course title or by department and course number?\n "
                << "(Type 1 for title, 2 for department and course number) " << std::endl;
            std::cin >> inputCourseSelection;
        }
        switch (inputCourseSelection) {
        case 1:
            for (int c = 0; c < courseFiles.size(); c++) {
                std::cout << c << " " << courseFiles[c].courseTitle << std::endl;
            }
            break;
        case 2:
            for (int c = 0; c < courseFiles.size(); c++) {
                std::cout << c << " " << courseFiles[c].idPrefix << " " << courseFiles[c].courseNumber << std::endl;
            }
            break;
        }
        std::cout << "Enter the number of the course you want to select: " << std::endl;
        std::cin >> selectedCourse;
        chosenCourse = courseFiles[selectedCourse]; //new chosen course object to access selected course

        std::cout << "You have chosen:  " << course.idPrefix << " " << course.courseNumber << " " << course.courseTitle << " " << course.creditValue << std::endl;
        std::cout << "Would you like to add this course to your schedule? (1 for YES, 2 for NO)\n";
        std::cin >> addToSchedule;
        while (addToSchedule != 1 && addToSchedule != 2) {
            std::cout << "You must type 1 for YES or 2 for NO\n";
            std::cout << "Would you like to add this course to your schedule? (1 for YES, 2 for NO)\n";
            std::cin >> addToSchedule;
        }
        if (addToSchedule == 1) {
            scheduledCourses.push_back(chosenCourse);
        }
        std::cout << "Do you want to continue selecting courses? (1 for YES, 2 for NO)\n";
        std::cin >> stillSelecting;
        stillSelecting = (stillSelecting == 1);
    }
    std::cout << "Your Schedule:\n";
    int totalCredits = 0;
    for (int i = 0; i < scheduledCourses.size(); i++) {
        std::cout << scheduledCourses[i].idPrefix << " "
            << scheduledCourses[i].courseNumber << " "
            << scheduledCourses[i].courseTitle << " "
            << scheduledCourses[i].creditValue << std::endl;
        totalCredits += std::stoi(scheduledCourses[i].creditValue);
    }
    std::cout << "Total Credits: " << totalCredits << std::endl;

    while (totalCredits < 9 || totalCredits > 15) {
        std::cout << "Total credits must be between 9 and 15. Please add or remove courses.\n";
        std::cout << "Current Schedule:\n";
        for (int i = 0; i < scheduledCourses.size(); i++) {
            std::cout << i << ": " << scheduledCourses[i].idPrefix << " "
                << scheduledCourses[i].courseNumber << " "
                << scheduledCourses[i].courseTitle << " "
                << scheduledCourses[i].creditValue << std::endl;
        }
        std::cout << "Type 1 to add a course, 2 to remove a course: ";
        int choice;
        std::cin >> choice;
        if (choice == 1) {
            std::cout << "Do you want to select courses by course title or by department and course number?\n"
                << "(Type 1 for title, 2 for department and course number) " << std::endl;
            std::cin >> inputCourseSelection;

            while (inputCourseSelection != 1 && inputCourseSelection != 2) {
                std::cout << "You must enter 1 for course title or 2 for department and course number.\n"
                    << "Do you want to select courses by course title or by department and course number?\n"
                    << "(Type 1 for title, 2 for department and course number) " << std::endl;
                std::cin >> inputCourseSelection;
            }

            switch (inputCourseSelection) {
            case 1:
                for (int c = 0; c < courseFiles.size(); ++c) {
                    std::cout << c << " " << courseFiles[c].courseTitle << std::endl;
                }
                break;
            case 2:
                for (int c = 0; c < courseFiles.size(); ++c) {
                    std::cout << c << " " << courseFiles[c].idPrefix << " " << courseFiles[c].courseNumber << std::endl;
                }
                break;
            }

            std::cout << "Enter the number of the course you want to select: " << std::endl;
            std::cin >> selectedCourse;
            chosenCourse = courseFiles[selectedCourse];

            std::cout << "You have chosen: " << chosenCourse.idPrefix << " " << chosenCourse.courseNumber << " "
                << chosenCourse.courseTitle << " " << chosenCourse.creditValue << std::endl;
            std::cout << "Would you like to add this course to your schedule? (1 for YES, 2 for NO)\n";
            std::cin >> addToSchedule;

            while (addToSchedule != 1 && addToSchedule != 2) {
                std::cout << "You must type 1 for YES or 2 for NO\n";
                std::cout << "Would you like to add this course to your schedule? (1 for YES, 2 for NO)\n";
                std::cin >> addToSchedule;
            }

            if (addToSchedule == 1) {
                scheduledCourses.push_back(chosenCourse);
                totalCredits += std::stoi(chosenCourse.creditValue); 
            }
        }
        else if (choice == 2) {
            std::cout << "Enter the number of the course to remove: ";
            int removeIndex;
            std::cin >> removeIndex;
            totalCredits -= std::stoi(scheduledCourses[removeIndex].creditValue);
            scheduledCourses.erase(scheduledCourses.begin() + removeIndex);
        }
    }

    std::cout << "Enter the name of the file to save your schedule: ";
    std::string outFileName;
    std::cin >> outFileName;
    std::fstream outFile(outFileName, std::ios::out);
    if (outFile) {
        for (int i = 0; i < scheduledCourses.size(); ++i) {
            outFile << scheduledCourses[i].idPrefix << " "
                << scheduledCourses[i].courseNumber << " "
                << scheduledCourses[i].courseTitle << " "
                << scheduledCourses[i].creditValue << std::endl;
        }
        outFile.close();
        std::cout << "Schedule saved to " << outFileName << std::endl;
    }
    else {
        std::cout << "Error opening file for writing.\n";
    }

    return 0;
}