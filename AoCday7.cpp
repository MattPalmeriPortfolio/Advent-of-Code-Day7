#include <fstream>
#include <vector>
#include <string>
#include <iostream>
//declare functions
void quickSort(std::vector<int>& intVector, int leftIndex, int rightIndex);
//quicksorts an int vector.
int fuelCalculator(const int firstPosition, const int secondPosition);
//given two positions, finds the fuel cost to travel between them, given the fuel cost is sum of n, where n is the difference.

//main
int main()
{
	using namespace std;
	//init var
	int fuelConsumption(0), currentCost, bestPosition;
	vector<int> crabbos; crabbos.reserve(300);
	ifstream inStream("input7.txt");
	if (inStream.fail())
		exit(1);
	//clean input and add
	char next = 'f';
	string dirtyInput;
	int temp, swap;
	bool pastFirst = false;
	while ((!(isspace(next))) && (!(inStream.eof())))
	{
		dirtyInput = "";
		inStream.get(next);
		while (next != ',' && next != '\n')
		{
			dirtyInput.push_back(next);
			inStream.get(next);
		}
		//minimal filter while adding
		temp = stoi(dirtyInput);
		if (pastFirst) //vector has read in its first value
		{
			if (temp < crabbos[crabbos.size() - 1])
			{
				swap = crabbos[crabbos.size() - 1];
				crabbos[crabbos.size() - 1] = temp;
				crabbos.push_back(swap);
			}
			else
				crabbos.push_back(temp);
		}
		else //vector has not yet read in its first value
		{
			crabbos.push_back(temp);
			pastFirst = true;
		}
	}
	//sort array
	quickSort(crabbos, 0, crabbos.size() - 1);
	//part 1: ez clap
	const int median = crabbos.size() / 2, quartered = crabbos.size() / 4;
	bestPosition = median;
	pastFirst = false;
	for (int i = 0; i < crabbos.size(); i++)
		fuelConsumption += abs(crabbos[i] - crabbos[median]);
	for (int currentPosition = quartered * 2; currentPosition < quartered * 3; currentPosition++)
	{
		currentCost = 0;
		if (pastFirst)
		{
			if (crabbos[currentPosition] == crabbos[currentPosition - 1]);
			else
			{
				for (int i = 0; i < crabbos.size(); i++)
					currentCost += abs(crabbos[i] - crabbos[currentPosition]);
				if (currentCost < fuelConsumption)
				{
					fuelConsumption = currentCost;
					bestPosition = currentPosition;
				}
			}
		}
		else
		{
			for (int i = 0; i < crabbos.size(); i++)
				currentCost += abs(crabbos[i] - crabbos[currentPosition]);
			if (currentCost < fuelConsumption)
			{
				fuelConsumption = currentCost;
				bestPosition = currentPosition;
			}
			pastFirst = true;
		}
	}
	cout << "Part 1:\nBest position: " << crabbos[bestPosition] << "\nTotal fuel consumption: " << fuelConsumption << endl;
	//part 2
	pastFirst = false;
	for (int currentPosition = crabbos[quartered * 2]; currentPosition < crabbos[quartered * 3]; currentPosition++)
	{
		currentCost = 0;
		if (pastFirst)
		{
			for (int currentIndex = 0; currentIndex < crabbos.size(); currentIndex++)
				currentCost += fuelCalculator(currentPosition, crabbos[currentIndex]);
			if (currentCost < fuelConsumption)
			{
				bestPosition = currentPosition;
				fuelConsumption = currentCost;
			}
		}
		else
		{
			for (int currentIndex = 0; currentIndex < crabbos.size(); currentIndex++)
				currentCost += fuelCalculator(currentPosition, crabbos[currentIndex]);
			bestPosition = currentPosition;
			fuelConsumption = currentCost;
			pastFirst = true;
		}
	}
	cout << "Part 2:\nBest position: " << bestPosition << "\nTotal fuel consumption: " << fuelConsumption << endl;
	return 0;
}
//define functions
void quickSort(std::vector<int>& intVector, int leftIndex, int rightIndex)
{
	unsigned int i = leftIndex, j = rightIndex;
	int pivot = intVector[(leftIndex + rightIndex) / 2];
	while (i <= j)
	{
		while (intVector[i] < pivot)
			i += 1;
		while (intVector[j] > pivot)
			j -= 1;
		if (i <= j)
		{
			const int temp = intVector[i];
			intVector[i] = intVector[j];
			intVector[j] = temp;
			i += 1;
			j -= 1;
		}
	}
	if (leftIndex < j)
		quickSort(intVector, leftIndex, j);
	if (i < rightIndex)
		quickSort(intVector, i, rightIndex);
	return;
}

int fuelCalculator(const int firstPosition, const int secondPosition)
{
	const int difference = abs(firstPosition - secondPosition);
	if (difference == 0)
		return 0;
	else
		return ((difference * (difference + 1)) / 2);
}