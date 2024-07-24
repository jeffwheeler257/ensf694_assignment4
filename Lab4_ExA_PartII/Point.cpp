/*
 *  Point.cpp
 *  ENSF 694 Lab 4 - Exercise A Part 2
 *  Created by Jeff Wheeler
 *  Submission date: July 26, 2024
 */

#include "Point.h"
#include <cstring>

Point::Point(int x, int y, const char* label) {
    this->x = x;
    this->y = y;
    this->label = new char[strlen(label) + 1];
    strcpy(this->label, label);
}

Point::~Point() {
    delete[] label;
}

Point::Point(const Point& src) {
    this->x = src.x;
    this->y = src.y;
    this->label = new char[strlen(src.label) + 1];
    strcpy(this->label, src.label);
}

Point& Point::operator=(const Point& rhs) {
    if(this != &rhs){ 
		this->x = rhs.x;
		this->y = rhs.y;
		delete[] label;
		this->label = new char[strlen(rhs.label) + 1];
		strcpy(this->label, rhs.label);		
	}
	return *this;
}

int Point::getx() const {
    return x;
}

int Point::gety() const {
    return y;
}

char* Point::get_label() const {
    return label;
}
