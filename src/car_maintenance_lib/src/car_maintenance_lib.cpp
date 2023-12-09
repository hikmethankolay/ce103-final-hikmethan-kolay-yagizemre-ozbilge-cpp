#include "../include/car_maintenance_lib.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <codecvt>
using namespace std;

fstream myFile;

int file_write(string file_name, string text) {
  text = "0-)" + text + "\r" + "\n";
  myFile.open(file_name, ios::out | ios::binary | ios::trunc); //Opens file with output tag
  myFile.write(text.c_str(), text.length()); //Deletes everything inside file and writes text variable
  myFile.close();
  return 0;
}

string file_read(string file_name) {
  string line;
  myFile.open(file_name, ios::in | ios::binary);//Opens file with input tag

  if (myFile.is_open()) {
    char i;

    while (myFile.get(i)) { // Takes all line one by one and prints them to console
      line = line + i;
    }

    cout << line;
    myFile.close();
  } else {
    cout << "File operation failed,There is no record\n";
    return "-1";
  }

  return line; //This is a variable for tests to run since function needs to return someting for them to run properly
}

int file_append(string file_name,string text) {
  myFile.open(file_name, ios::in | ios::binary);//Opens file with input tag
  string lastLine;
  string currentLine;
  char i;

  if (myFile.is_open()) { // Update lastLine for each line and finds actual last line
    while (myFile.get(i)) {
      if (i == '\n') {
        currentLine = currentLine + i;
        lastLine = currentLine;
        currentLine = "";
        continue;
      }

      currentLine = currentLine + i;
    }

    myFile.close();
  } else {
    cout << "File operation failed\n";
    return -1;
  }

  size_t pos = lastLine.find("-)"); // Finds location of "-)" inn last line
  int lineNumber = stoi(lastLine.substr(0, pos))+1; //Finds number for the appended line
  text = to_string(lineNumber) + "-)" + text + "\r" + "\n";
  myFile.open(file_name, ios::app | ios::binary);//Opens file with append tag
  myFile.write(text.c_str(), text.length()); //Appends text with its line number
  myFile.close();
  return 0;
}


int file_edit(string file_name, int line_number_to_edit, string new_line) {
  const int max_line_count = 100; // An variable for array
  char i;
  myFile.open(file_name, ios::in | ios::binary);//Opens file with read tag

  if (myFile.is_open()) {
    string lines[max_line_count]; // A array to to store lines
    string line;
    int line_count = 0; // A variable for if statement to check if the line that user wants to edit exist

    while (myFile.get(i)) {
      if (i == '\n') {
        line = line + i;
        lines[line_count++] = line;
        line = "";
        continue;
      }

      line = line + i;
    }

    myFile.close();

    if (line_number_to_edit > 0 && line_number_to_edit <= line_count) {
      lines[line_number_to_edit] = to_string(line_number_to_edit) + "-)" + new_line + "\r" + "\n"; // Changes a member of Lines array to new line with its line number
    } else {
      cout << "You can only edit existing lines\n";
      return -1;
    }

    myFile.open(file_name, ios::out | ios::binary); // Opens file in write mode

    for (const string &updated_lines : lines) {  // writes every member of lines array to file
      if (updated_lines == "") {
        break; // Stops if there is nothing on next line since arrays have fixed slots inside them from start
      }

      myFile.write(updated_lines.c_str(), updated_lines.length());
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
  char i;
  myFile.open(file_name, ios::in | ios::binary);// Opens file in read mode

  if (myFile.is_open()) {
    string lines[max_line_count]; // A array to to store lines
    string line;
    int line_count = 0; // A variable for if statement to check if there is a line that user wants to edit

    while (myFile.get(i)) {// gets lines one by one and assaign them to line variable
      if (i == '\n') {
        line = line + i;
        lines[line_count++] = line; // Adds line variable to lines array and increase line_count after operation
        line = "";
        continue;
      }

      line = line + i;
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
    myFile.open(file_name, ios::out | ios::binary); // Opens file in write mode

    for (const string &updated_lines : lines) {
      if (updated_lines == "") {
        break; // Stops if there is nothing on next line since arrays have fixed slots inside them from start
      }

      size_t pos = updated_lines.find("-)"); // Finds postion of "-)"
      int lineNumber = stoi(updated_lines.substr(0, pos)); // Finds each lines line number

      if (lineNumber > line_number_to_delete) { // decrase a lines line number if its bigger than deleted lines line number
        string updated_line_with_new_number = to_string(lineNumber - 1) + updated_lines.substr(pos);
        myFile.write(updated_line_with_new_number.c_str(), updated_line_with_new_number.length());
      } else {
        myFile.write(updated_lines.c_str(), updated_lines.length());
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
