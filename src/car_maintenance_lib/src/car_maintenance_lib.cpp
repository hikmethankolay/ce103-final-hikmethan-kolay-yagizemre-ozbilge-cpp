#include "../include/car_maintenance_lib.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

fstream myFile;

int file_write(string file_name, string text) {
  myFile.open(file_name, ios::out); //Opens file with output tag

  if (myFile.is_open()) {
    myFile << "0-)" << text << "\n"; //Deletes everting inside file and inserts Text with "0-)" line number
    myFile.close();
    return 0;
  } else {
    return -1;
  }
}

int file_append(string file_name,string text) {
  myFile.open(file_name, ios::in);//Opens file with input tag
  string lastLine;
  string currentLine;

  if (myFile.is_open()) {
    while (getline(myFile, currentLine)) {
      lastLine = currentLine;  // Update lastLine for each line and finds actual last line
    }

    myFile.close();
  } else {
    cout << "File operation failed\n";
    return -1;
  }

  size_t pos = lastLine.find("-)"); // Finds location of "-)" inn last line
  int lineNumber = stoi(lastLine.substr(0, pos))+1; //Finds number for the appended line
  myFile.open(file_name, ios::app);//Opens file with append tag

  if (myFile.is_open()) {
    myFile << lineNumber << "-)" << text << "\n"; //Appends text with its line number
    myFile.close();
    return 0;
  } else {
    cout << "File operation failed\n";
    return -1;
  }
}

string file_read(string file_name) {
  string stringForTest; //This is a variable for tests to run properly since function needs to retrun someting
  myFile.open(file_name, ios::in);//Opens file with input tag

  if (myFile.is_open()) {
    string line;

    while (getline(myFile, line)) { // Takes all line one by one and prints them to console
      cout << line << endl;
      stringForTest = stringForTest + line + "\n";
    }

    myFile.close();
  } else {
    cout << "File operation failed,There is no record\n";
    return "-1";
  }

  return stringForTest; //This is a variable for tests to run since function needs to retrun someting for them to run properly
}

int file_edit(string file_name, int line_number_to_edit, string new_line) {
  const int max_line_count = 100; // An variable for array
  myFile.open(file_name, ios::in);//Opens file with read tag

  if (myFile.is_open()) {
    string lines[max_line_count]; // A array to to store lines
    string line;
    int line_count = 0; // A variable for if statement to check if there is a line that user wants to edit

    while (getline(myFile, line)) { // gets lines one by one and assaign them to line variable
      lines[line_count++] = line; // Adds line variable to lines array and increase line_count after operation
    }

    myFile.close();

    if (line_number_to_edit > 0 && line_number_to_edit <= line_count) {
      lines[line_number_to_edit] = to_string(line_number_to_edit) + "-)" + new_line; // Changes a member of Lines array to new line with its line number
    } else {
      cout << "You can only edit existing lines\n";
      return -1;
    }

    myFile.open(file_name, ios::out); // Opens file in write mode

    for (const string &updated_line : lines) {  // writes every member of lines array to file
      if (updated_line == "") {
        break; // Stops if there is nothing on next line since arrays have fixed slots inside tehem fromm start
      }

      myFile << updated_line << '\n';
    }

    myFile.close();
    cout << "\nData succesfully edited\n\n";
    return 0;
  } else {
    cout << "File operation failed" << endl;
    return -1;
  }
}

int file_line_delete(string file_name, int line_number_to_delete) {
  const int max_line_count = 100; // An variable for array to work properly
  myFile.open(file_name, ios::in);// Opens file in read mode

  if (myFile.is_open()) {
    string lines[max_line_count]; // A array to to store lines
    string line;
    int line_count = 0; // A variable for if statement to check if there is a line that user wants to edit

    while (getline(myFile, line)) { // gets lines one by oone and assaign them to line variable
      lines[line_count++] = line; // Adds line variable to lines array and increase line_count after operation
    }

    if (line_number_to_delete > 0 && line_number_to_delete < line_count) {
      // Shift elements to "erase" the line at line_number_to_delete
      for (int i = line_number_to_delete; i < line_count - 1; ++i) {
        lines[i] = lines[i + 1];
      }

      lines[line_count - 1] = ""; // clears last element of lines so same thing wouldn't write to file twice
    } else {
      cout << "You can only erase existing lines" << endl;
      myFile.close();
      return -1;
    }

    myFile.close();
    myFile.open(file_name, ios::out); // Opens file in write mode

    for (const string &updated_line : lines) {
      if (updated_line == "") {
        break; // Stops if there is nothing on next line since arrays have fixed slots inside them from start
      }

      size_t pos = updated_line.find("-)"); // Finds postion of "-)"
      int lineNumber = stoi(updated_line.substr(0, pos)); // Finds each lines line number

      if (lineNumber > line_number_to_delete) { // decrase a lines line number if its bigger than deleted line's line number
        string updated_line_with_new_number = to_string(lineNumber - 1) + updated_line.substr(pos);
        myFile << updated_line_with_new_number << '\n';
      } else {
        myFile << updated_line << '\n';
      }
    }

    cout << "\nData succesfully deleted\n\n";
    myFile.close();
    return 0;
  } else {
    cout << "File operation failed\n";
    return -1;
  }
}
