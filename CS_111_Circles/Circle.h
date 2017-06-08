#pragma once
#ifndef CIRCLE_H_
#define CIRCLE_H_
#endif

#include <iostream>
#include <sstream>
#include <sstream>

using namespace std;

class Circle
{
	public:
		//constructors for initialization
		Circle();
		Circle(double, double, double);
		~Circle();
		Circle(Circle &other);
		
		//string conversion and outputting the circles
		void toString();
		void dumpCircle();
		
		//setters for the circle
		void setX(double);
		void setY(double);
		void setRadius(double);
		
		//getters for the cirlce
		double getX();
		double getY();
		double getRadius();

		static int getCount();


	private:
		static int circCount;
		double radius, xCoord, yCoord; // double as coordinates can be in decimal form. 

		string xStr, yStr, radStr; // this string is used to store the values of radius, x and y coordinates from above
};

//this variable is initialized only once as it was declared static in declaration
//if not familiar with this method I suggest looking into static declaration 
int Circle::circCount = 0;

//default constructor
//sets everything to to 0 and increments the count by 1
Circle::Circle()
{
	radius = xCoord = yCoord = 0;
	
	xStr = yStr = radStr = "";
}

//3-parameter constructor
//sets the x, y and radius to he respective provided values and 
//increments count by 1
Circle::Circle(double r, double x, double y)
{
	radius = r;
	xCoord = x;
	yCoord = y;
	circCount++;
	xStr = yStr = radStr = "";
}

//copy constructor
//uses a already instantiated object to make a copy 
//this will also increment the count of total circles by 1
Circle::Circle(Circle &other)
{
	radius = other.radius;
	xCoord = other.xCoord;
	yCoord = other.yCoord;
	circCount++;
}

//destructor
//the circle count is decremented by 1
Circle::~Circle()
{
	circCount--;
}

//convert the circles to string for output purposes
//use of string stream(sstream) helps us convert integers, floats and double to 
//strings which can then be used for other purposes. In this situation 
//regurgitate the circle to view for the user
void Circle::toString()
{
	stringstream ss;

	ss << xCoord << " ";
	ss >> xStr;
	ss << yCoord << " ";
	ss >> yStr;
	ss << radius << " ";
	ss >> radStr;

	cout << "(" << xStr << ", " << yStr << ") " << "radius = " << radStr;

}

//dump circle in a series of string made from the toString function
//uses the x, y and radius from instantiation which were converted 
//to string in the toString function
void Circle::dumpCircle()
{
	cout << "(" << xStr << ", " << yStr << ") " << "radius = " << radStr;
}

//get X coordinate of the circle
double Circle::getX()
{
		return xCoord;
}

//get Y coordinate of the circle
double Circle::getY()
{
		return yCoord;
}

//get the radius of the circle
double Circle::getRadius()
{
	double tmp = radius;
	return tmp;
}

//set the X coordinates
void Circle::setX(double x)
{
	this->xCoord = x;
}

//set the Y coordinates
void Circle::setY(double y)
{
	this->yCoord = y;
}

//set radius from the user
void Circle::setRadius(double r)
{
	if (r >= 0)
	{
		this->radius = r;
		circCount++;
	}

	else
		cout << "Please enter a non-negetive number for a radius" << endl;
}

//get total number of circle
int Circle::getCount()
{
	return circCount;
}

