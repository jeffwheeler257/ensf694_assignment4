/*
 *  lab4exe_b.cpp
 *  ENSF 694 Lab 4 - Exercise B
 *  Created by Mahmood Moussavi
 *  Completed by Jeff Wheeler
 *  Submission date: July 26, 2024
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

const int size = 6;
using namespace std;
struct City {
    double x, y;
    char name[30];
};

/* PROMISES: attaches an ofstream object to a binary file named "filename" and
 * writes the content of the array cities into the file.
 */
void write_binary_file(City cities[], int size, char* filename);

/* PROMISES: attaches an ifstream object to a binary file named "filename" and
 * reads the content of the file (one record at a time and displays it on the
 * screen.
 */
void print_from_binary(char* filename);

int main() {
    char bin_filename[] = "cities.bin";
    
    City cities[size] = {{100, 50, "Calgary"},
        {100, 150, "Edmonton"},
        {50, 50, "Vancouver"},
        {200, 50, "Regina"},
        {500, 50, "Toronto"},
        {200, 50, "Montreal"}};
    
    write_binary_file(cities, size, bin_filename);
    cout << "\nThe content of the binary file is:" << endl;
    print_from_binary(bin_filename);
    return 0;
}

void write_binary_file(City cities[], int size, char* filename){
    ofstream stream(filename, ios::out | ios::binary);
    if(stream.fail()){
        cerr << "failed to open file: " << filename << endl;
        exit(1);
    }
    
    for(int i =0; i < size; i++)
        stream.write((char*)&cities[i], sizeof(City));
    stream.close();
}

/* PROMISES: attaches an ifstream object to a binary file named "filename" and
 * reads the content of the file (one record at a time and displays it on the
 * screen.
 */
void print_from_binary(char* filename) {
    ifstream stream(filename, ios::in | ios::binary);
    City a[size];

    for (int i = 0; i < size; i++){
        stream.read((char*)&a[i], sizeof(City));
    }

    for (int i = 0; i < size; i++){
        cout << "Name: " << a[i].name << ", x coordinate: " << a[i].x << ", y coordinate: " << a[i].y << endl;
    }

}



