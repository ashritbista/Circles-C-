#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>

#include "Circle.h"

using namespace std;

//constant value
const double PI = 3.1415;

//distance calculator d = sqrt((x1 - x2)^2 + (y1 - y2)^2)
double calcDistance(double x1, double y1, double x2, double y2)
{
	double distance = 0.0;

	distance = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));

	return distance;
}

/*This function calculates the traingle area inside the circle and the area of sector
it returns an array of number where element indexed 0 and 1 are the area of triangle
and elements indexed 2 and 3 are the area of sector. These values are then used to calculate 
the intersected area*/
double *areaOfTriangleAndSector(Circle a, Circle b)
{
	static double arr[4] = {};
	double r1 = a.getRadius(), r2 = b.getRadius(), d = 0.0, theta1 = 0.0, theta2 = 0.0;

	double a1 = 0.0, s1 = 0.0, s2 = 0.0;
	
	d = calcDistance(a.getX(), a.getY(), b.getX(), b.getY());

	a1 = sqrt((-d + r1 + r2) * (d - r1 + r2) * (d + r1 - r2) * (d + r1 + r2)) / d;

	s1 = (a1 + 2.0 * r1) / 2.0;

	s2 = (a1 + 2.0 * r2) / 2.0;

	arr[0] = sqrt(s1 * (s1 - a1) * (s1 - r1) * (s1 - r1));
	arr[1] = sqrt(s2 * (s2 - a1) * (s2 - r2) * (s2 - r2));

	theta1 = 2 * asin(a1 / (2 * r1));
	theta2 = 2 * asin(a1 / (2 * r2));

	arr[2] = (0.5) * pow(r1, 2) * theta1;
	arr[3] = (0.5) * pow(r2, 2) * theta2;

	return arr;
}

//this function checks to see if the circles in check are tangent to each other
bool isTangent(Circle a, Circle b)
{
	double distance = 0.0;
	distance = calcDistance(a.getX(), a.getY(), b.getX(), b.getY());

	if ((a.getRadius() + b.getRadius()) == distance)
		return true;

	else
		return false;
}

//this function checks to see if one circle is inside another
bool is_inside(Circle a, Circle b)
{
	double distance = 0.0, radA = 0.0, radB = 0.0, xA = 0.0, xB = 0.0, yA = 0.0, yB = 0.0;
	
	xA = a.getX(); xB = b.getX();
	yA = a.getY(); yB = b.getY();
	radA = a.getRadius(); radB = b.getRadius();

	distance = calcDistance(xA, yA, xB, yB);

	if (distance <= fmax(radA, radB))
	{
		return true;
	}

	else
	{
		return false;
	}
}

//this function checks to see if the circles intersect
bool circlesIntersect(Circle a, Circle b)
{
	//get the circle data for the 1st circle
	double radA = a.getRadius();
	double xA = a.getX();
	double yA = a.getY();

	//get the circle data for the 2nd circle
	double radB = b.getRadius();
	double xB = b.getX();
	double yB = b.getY();

	double distance = 0.0;

	distance = calcDistance(xA, yA, xB, yB);

	if (distance < radA + radB)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//this function calculates the area of circle
double calcArea(Circle a[], int count)
{
	double area = 0.0, x = 0.0, y = 0.0, rad = 0.0;

	for (int i = 0; i < count - 1; i++)
	{
		rad = a[i].getRadius();

		area = area + (PI * rad * rad);
	}

	return area;
}

//this function extracts the circle's data from the text file and stores it in the array
void get_circle_data(ifstream &file, double* a, int n, int &count)
{
	string s = "";
	stringstream str;
	int arrCount = count;
	double x = 0.0, y = 0.0, radius = 0.0;
	string tmp = "";
	int my_count = 0;
	for (int i = 0; i < n; i++)
	{
		tmp = "";
		getline(file, s);
		str.clear();

		for (unsigned int j = 0; j < s.length(); j++)
		{
			if (s[0] == '%')
				continue;

			if (s[j] != ' ')
			{
				tmp = tmp + s[j];
			}

			else
			{
				if (my_count == 0)
				{
					str << tmp;
					str >> x;
					a[arrCount] = x;
					arrCount++;
					my_count++;
					tmp = "";
					str.clear();
				}
				else
				{
					str << tmp;
					str >> y;
					a[arrCount] = y;
					arrCount++;
					tmp = "";
					str.clear();
				}
			}
		}
		if (s[0] != '%')
		{
			str << tmp;
			str >> radius;
			a[arrCount] = radius;
			arrCount++;
			str.clear();
		}
	}

	count = arrCount;
}


int main()
{
	int n, arrCount = 0;
	double circArea = 0.0;
	string filename;
	Circle circArr[500] = {};
	cout << "Enter a file name: " << endl;
	cin >> filename;
	cout << endl;

	ifstream myfile;
	myfile.open(filename.c_str());

	if (!myfile.good())
	{
		cout << "Sorry file not found!" << endl;
		return 0;
	}

	string s;
	stringstream ss;
	getline(myfile, s);

	if (s[0] == '%')
		getline(myfile, s);

	ss << s;
	ss >> n;

	//this variable stores the raw data for the circles that will be used to generate circles using the circle class
	double *circle_data = new double[n * 3];

	get_circle_data(myfile, circle_data, n, arrCount);

	Circle mycirc ;
	
	double x = 0.0, y = 0.0, rad = 0.0;
	double *intersectData;
	double overlap = 0.0, totalArea = 0.0;
	int count = 0, circCount = 0;

	//We will now populate the circles in the array
	while (count < arrCount - 1)
	{
		x = circle_data[count];
		count++;
		mycirc.setX(x);
		
		y = circle_data[count];
		count++;
		mycirc.setY(y);
		
		rad = circle_data[count];
		count++;
		if (rad >= 0)
		{
			mycirc.setRadius(rad);
		}
		else
			return 0;

		circArr[circCount] = mycirc;
		circCount++;
	}

	for (int i = 0; i < circCount; i++)
	{
		circArr[i].toString();
		cout << endl;
	}
	cout << endl;

	/*This is where most of the work is done
	the circles are checked to see if there is any overlapping. If there is, then the 
	overlapped areas are calculated and the data is stored in the variable "overlapped."*/
	for (int i = 0; i < circCount; i++)
	{
		totalArea = totalArea + PI * pow(circArr[i].getRadius(), 2);
		if (i != circCount - 1)
		{
			for (int j = i + 1; j < circCount; j++)
			{
				if (circlesIntersect(circArr[i], circArr[j]) && i != j)
				{
					cout << "Circles ";
					circArr[i].toString();
					cout << " and ";
					circArr[j].toString();
					cout << " intersect. " << endl;
					cout << endl;
					
					if (is_inside(circArr[i], circArr[j]))
					{
						cout << endl;
						if (circArr[i].getRadius() > circArr[j].getRadius())
							overlap += PI * pow(circArr[j].getRadius(), 2);

						else
							overlap += PI * pow(circArr[i].getRadius(), 2);
					}

					else if (!isTangent(circArr[i], circArr[j]))
					{
						intersectData = areaOfTriangleAndSector(circArr[i], circArr[j]);

						overlap += abs((*(intersectData + 0) - *(intersectData + 2)));
						overlap += abs((*(intersectData + 1) - *(intersectData + 3)));
					}
				}
			}
		}
	}

	totalArea = totalArea + pow(circArr[circCount].getRadius(), 2);

	cout << "Total area = " << totalArea << endl;
	cout << "Total overlap area = " << overlap << endl;
	cout << "Total area after overlap = " << totalArea - overlap << endl;

	delete [] circle_data;
	cin.ignore();
	cin.ignore();
	return 0;
}