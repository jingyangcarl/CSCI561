#include "InputGenerator.h"

InputGenerator::InputGenerator(Input& input) : 
	input(input) {
}

void InputGenerator::SetParameter(int width, int height, int destinations, int zMean, int zStddev) {
	this->width = width;
	this->height = height;
	this->destinations = destinations;
	this->zMean = zMean;
	this->zStddev = zStddev;
}

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

void InputGenerator::Output() {
	// landing position;
	cout << "Landing Position: " << "(" << input.landingLocation.first << ", " << input.landingLocation.second << ")" << endl;

	// landing destinations;
	int count(0);
	for (auto i = input.destinations.begin(); i != input.destinations.end(); i++) {
		cout << "Destination[" << count << "]" << "(" << (*i).first.first << ", " << (*i).first.second << ")" << endl;
		count++;
	}

	// max slope
	cout << "Max Slope: " << input.maxSlope << endl;

	// map;
	cout << "Map: " << endl;
	for (int i = 0; i < input.height; i++) {
		for (int j = 0; j < input.width; j++) {
			cout << input.map[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
