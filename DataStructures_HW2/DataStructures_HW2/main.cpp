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

using namespace std;

int rowLength = 0;
vector<int> steps;

//function to click "lights" that are currently lit
//the goal is to "push" all of the lights to the left
void clickLight(vector<int> inputArray, int n)
{
	if (n >= 0)
	{
		if (inputArray[n] == 0)
		{
			//call the function again with the next number down
			clickLight(inputArray, n - 1);
		}
		else if (inputArray[n] == 1)
		{
			//check the number just before it
			//if it is a 0 we should click the current button then recursively call this function again
			//if it is a 1 we should recursively call this function again
			if (n > 0)
			{
				if (inputArray[n - 1] == 0 || inputArray[n + 1] == 1)
				{
					//"click" light then call function
					inputArray[n] = (inputArray[n] + 1) % 2;
					//add this number to our "step" vector
					steps.push_back(n + 1);
					//change the light to the right unless we are on the last light
					if (n < rowLength - 1)
						inputArray[n + 1] = (inputArray[n + 1] + 1) % 2;
					inputArray[n - 1] = (inputArray[n - 1] + 1) % 2;
					clickLight(inputArray, n - 1);
				}
				else
					//if (inputArray[n - 1] == 0 || inputArray[n - 1] == 1)
					clickLight(inputArray, n - 1);
			}
			else //n=0
			{
				//"click" light then call function
				inputArray[n] = (inputArray[n] + 1) % 2;
				steps.push_back(n + 1);
				//change the light to the right unless we are on the last light
				if (n < rowLength - 1)
					inputArray[n + 1] = (inputArray[n + 1] + 1) % 2;
				clickLight(inputArray, n - 1);
			}
		}
	}
	else
	{
		cout << "\nFinal Row: ";
		for (int i = 0; i < rowLength; i++)
			cout << inputArray[i];

		cout << "\nSteps Taken: ";
		for (int i = steps.size() - 1; i >= 0; i--)
			cout << steps[i] << " ";
	}
}


int main()
{
	int n = 0;
	char input[20] = {};

	//determine length of string input
	cin >> rowLength;
	
	//read in "row" of lights
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

	clickLight(lightRow, rowLength - 1);

	cin.get();
	cin.get();
}


