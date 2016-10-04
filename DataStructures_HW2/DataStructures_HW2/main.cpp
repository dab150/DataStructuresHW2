/*
* Data Structures Assignment #2
* Recursive Algorithm - Single Row Lights Out
* Daniel Barber-Cironi
* September 27, 2016
*/

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int rowLength = 0;
bool solutionFound = false;
vector<int> steps;
vector<int> outputArray;


//this is similar to traverseBackToFront except this goes from front to back
//therefore it "pushes" the lights to the right
void traverseFrontToBack(vector<int> inputArray, int n)
{
	if (n < rowLength)
	{
		if (inputArray[n] == 0)
		{
			//ignore this light and call the function again with the next number down
			traverseFrontToBack(inputArray, n + 1);
		}
		else if (inputArray[n] == 1)
		{
			//check the number just after this one
			//if it is a 0 we should click the current button then recursively call this function again
			//if it is a 1 we should recursively call this function again
			if (n > 0 && n < rowLength - 1) //not at the first or last element
			{
				if (inputArray[n + 1] == 0 || inputArray[n - 1] == 1)
				{
					//"click" light then call function
					inputArray[n] = (inputArray[n] + 1) % 2;
					//add this number to our "step" vector
					steps.push_back(n + 1);
					//change the light to the right (we know we aren't on the last light
					inputArray[n + 1] = (inputArray[n + 1] + 1) % 2;
					//change the light to the left (we know we aren't on the first light)
					inputArray[n - 1] = (inputArray[n - 1] + 1) % 2;

					traverseFrontToBack(inputArray, n + 1);
				}
				else
					//if (inputArray[n - 1] == 0 || inputArray[n - 1] == 1)
					traverseFrontToBack(inputArray, n + 1);
			}
			else if (n == rowLength - 1) //we are the last light
			{
				if (inputArray[n - 1] == 1)
				{
					//"click" light
					inputArray[n] = (inputArray[n] + 1) % 2;
					//add this buttons index to our list of steps
					steps.push_back(n + 1);
					//change the light to the left of this one unless we are on the first light
					//notice we don't change the light to the right because there isn't one since we are at the last index
					if (n > 0)
						inputArray[n - 1] = (inputArray[n - 1] + 1) % 2;
					//call function again
					traverseFrontToBack(inputArray, n + 1);
				}
				else
				{
					traverseFrontToBack(inputArray, n + 1);
				}
			}
			else if (n == 0) //we are at the first light
			{
				//"click" light
				inputArray[n] = (inputArray[n] + 1) % 2;
				//add this buttons index to our list of steps
				steps.push_back(n + 1);
				//change the light to the right of this one unless we are on the last light
				//notice we don't change the light to the left because there isn't one since we are at index 0
				if (n < rowLength - 1)
					inputArray[n + 1] = (inputArray[n + 1] + 1) % 2;



				//check to see if a 1 is still in the light row
				//if there is, the the puzzle cannot be solved
				for (int i = 0; i < rowLength; i++)
				{
					if (inputArray[i] == 1)
					{
						cout << "\nNo Solution\n";
					}
				}

				//else call function again to exit
				traverseFrontToBack(inputArray, n + 1);
			}
		}
	}
	else
	{
		outputArray = inputArray;
		bool oneRemaining = false;
		for (int i = 0; i < rowLength; i++)
		{
			if (outputArray[i] == 1)
				oneRemaining = true;
		}

		if (oneRemaining) //no solution found, there is no solution for this puzzle
			solutionFound = false;
		else			 //solution found
			solutionFound = true;    
	}
}


//function to click "lights" that are currently lit
//the goal is to "push" all of the lights to the left
//this operates from back to front
void traverseBackToFront(vector<int> inputArray, int n)
{
	if (n >= 0)
	{
		if (inputArray[n] == 0)
		{
			//ignore this light and call the function again with the next number down
			traverseBackToFront(inputArray, n - 1);
		}
		else if (inputArray[n] == 1)
		{
			//check the number just before it
			//if it is a 0 we should click the current button then recursively call this function again
			//if it is a 1 we should recursively call this function again
			if (n > 0 && n < rowLength - 1) //not at the first or last element
			{
				if (inputArray[n - 1] == 0 || inputArray[n + 1] == 1)
				{
					//"click" light then call function
					inputArray[n] = (inputArray[n] + 1) % 2;
					//add this number to our "step" vector
					steps.push_back(n + 1);
					//change the light to the right (we know we aren't on the last light
					inputArray[n + 1] = (inputArray[n + 1] + 1) % 2;
					//change the light to the left (we know we aren't on the first light)
					inputArray[n - 1] = (inputArray[n - 1] + 1) % 2;

					traverseBackToFront(inputArray, n - 1);
				}
				else
					//if (inputArray[n - 1] == 0 || inputArray[n - 1] == 1)
					traverseBackToFront(inputArray, n - 1);
			}
			else if (n == rowLength - 1) //we are the last light
			{
				if (inputArray[n - 1] == 0)
				{
					//"click" light
					inputArray[n] = (inputArray[n] + 1) % 2;
					//add this buttons index to our list of steps
					steps.push_back(n + 1);
					//change the light to the left of this one unless we are on the first light
					//notice we don't change the light to the right because there isn't one since we are at the last index
					if (n > 0)
						inputArray[n - 1] = (inputArray[n - 1] + 1) % 2;
					//call function again
					traverseBackToFront(inputArray, n - 1);
				}
				else
				{
					traverseBackToFront(inputArray, n - 1);
				}
			}
			else if (n == 0) //we are at the first light
			{
				//"click" light
				inputArray[n] = (inputArray[n] + 1) % 2;
				//add this buttons index to our list of steps
				steps.push_back(n + 1);
				//change the light to the right of this one unless we are on the last light
				//notice we don't change the light to the left because there isn't one since we are at index 0
				if (n < rowLength - 1)
					inputArray[n + 1] = (inputArray[n + 1] + 1) % 2;


				/*
				//check to see if a 1 is still in the light row
				//if there is, traverse the row from fron to back
				for (int i = 0; i < rowLength; i++)
				{
					if (inputArray[i] == 1)
					{
						traverseFrontToBack(inputArray, 0);
						break;
					}
				}*/

				//else call function again to exit
				traverseBackToFront(inputArray, n - 1);
			}
		}
	}
	else
	{
		outputArray = inputArray;
		bool oneRemaining = false;
		for (int i = 0; i < rowLength; i++)
		{
			if (outputArray[i] == 1)
				oneRemaining = true;
		}

		if (oneRemaining) //no solution found, try going front to Back
			traverseFrontToBack(inputArray, 0);
		else			 //solution found
			solutionFound = true;
	}
}


int main()
{
	int n = 0;
	char input[20] = {};

	//determine length of string input
	cout << "\nPlease enter the length of the row of lights: ";
	cin >> rowLength;
	
	//read in "row" of lights
	cout << "\nPlease enter the row of lights: ";
	cin >> input;

	//vector to store row in
	vector<int> lightRow(rowLength);

	//convert char array input to array of ints
	for (int i = 0; i < rowLength; i++)
	{
		if (input[i] == '1')
			lightRow[i] = 1;
		else if (input[i] == '0')
			lightRow[i] = 0;
	}

	traverseBackToFront(lightRow, rowLength - 1);

	if (solutionFound)
	{
		//print out the final row
		cout << "\nFinal Row: ";
		for (int i = 0; i < rowLength; i++)
		cout << outputArray[i];

		//reorder the steps to be in order
		sort(steps.begin(), steps.end());

		//remove duplicates as these count as not clicking at all
		//unique(steps.begin(), steps.end());
		//steps.erase(unique(steps.begin(), steps.end()), steps.end());

		//print out the steps
		cout << "\nButtons Pressed: ";
		for (int i = 0; i < steps.size(); i++)
			cout << steps[i] << " ";
	}
	else
	{
		cout << "\nNo Solution\n";
	}


	cout << "\n \n \nPress enter to exit...";
	cin.get();
	cin.get();
	return 0;
}


