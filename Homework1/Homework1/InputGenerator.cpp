#include "InputGenerator.h"

/*
Description:
This function is a constructor;
Input:
@ Input& input: a defined input structure;
Output:
@ InputGenerator returnValue: a InputGenerator;
*/
InputGenerator::InputGenerator(Input& input) : 
	input(input) {
}

/*
Description:
This function is used to prepare parameters for input generation. The generator for z values is a Gaussian generator, which make sure 68% z values are within [mu-sigma,mu+sigma], 95% z values are within [mu-2*sigma,mu+2*sigma], and 99.7% z values are within [mu-3*sigma,mu+3*sigma];
Input:
@ int width: map width;
@ int height: map height;
@ int destinations: the number of destinations;
@ int zMean: Gaussian mean value (mu) for all z values;
@ int zStddev: Gaussian standard deviation (sigma) for all z values;
*/
void InputGenerator::SetParameter(int width, int height, int destinations, int zMean, int zStddev) {
	this->width = width;
	this->height = height;
	this->destinations = destinations;
	this->zMean = zMean;
	this->zStddev = zStddev;
}

/*
Description:
This function is used to generate data based on the given parameters;
Input:
@ void parameter: void;
Output:
@ void returnValue: void;
*/
void InputGenerator::Generate() {

	// generate width and height;
	input.width = width;
	input.height = height;

	// generate landing location;
	srand(time(NULL));
	input.landingLocation.first = rand() % height;
	input.landingLocation.second = rand() % width;

	// generate maximum slope;
	input.maxSlope = zStddev;

	// generate destinations;
	input.destinations.clear();
	for (int i = 0; i < destinations; i++) {
		Location destination;
		destination.first = rand() % height;
		destination.second = rand() % width;
		input.destinations.insert(pair<Location, vector<Location>>(destination, vector<Location>(input.height * input.width)));
	}

	// generate map;
	default_random_engine generator;
	normal_distribution<float> distribution(zMean, zStddev);

	input.map = new int* [input.height];
	for (int i = 0; i < input.height; i++) {
		input.map[i] = new int[input.width];
		for (int j = 0; j < input.width; j++) {
			input.map[i][j] = distribution(generator);
		}
	}
}

/*
Description:
This function is used to print generated data;
Input:
@ void parameter: void;
Output:
@ void returnValue: void;
*/
void InputGenerator::Output() {
	// landing position;
	cout << "Landing Position: " << "(" << input.landingLocation.second << ", " << input.landingLocation.first << ")" << endl;

	// landing destinations;
	int count(0);
	for (auto i = input.destinations.begin(); i != input.destinations.end(); i++) {
		cout << "Destination[" << count << "]" << "(" << (*i).first.second << ", " << (*i).first.first << ")" << endl;
		count++;
	}

	// max slope
	cout << "Max Slope: " << input.maxSlope << endl;

	// map;
	cout << "Map: " << endl;
	for (int i = 0; i < input.height; i++) {
		for (int j = 0; j < input.width; j++) {
			cout << input.map[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}
