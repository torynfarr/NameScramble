#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>    
#include <ctime>
#include <algorithm>

using namespace std;

int random(int max);
string jumble1(string name);
string jumble2(string name);
char getRndChar(vector<char> characters);

int main()
{
	string first, last;

	cout << "Enter your first name: ";
	cin >> first;
	cout <<  "Enter your last name: ";
	cin >> last;
	cout << endl;
	cout << "Slow way" << endl;
	cout << first << " " << last << endl;
	cout << endl << jumble1(first) << " " << jumble1(last) << endl << endl;
	cout << "Fast way" << endl;
	cout << first << " " << last << endl;
	cout << endl << jumble2(first) << " " << jumble2(last) << endl;
	return 0;

}

int random(int max)
{

	srand(time(NULL));
	cout << ".";
	this_thread::sleep_for(chrono::milliseconds(200));
	return rand() % max + 1;
	
}

string jumble1(string name) 
{

	int size = name.length();
	vector<int> myRandoms;
	string jumbledName = "";
	bool unique = false;

	int num = random(size);

	// Put the 1st random number into the vector
	myRandoms.push_back(num);

	// Generate a number of unique random numbers equal to the remaining characters in the name
	for (int r = 1; r <= size - 1; r++)
	{
		unique = false;

		while (!unique)
		{

			num = random(size);
			
			// Random number is treated as unique until proven otherwise
			myRandoms.push_back(num);
			
			// Crawl through the vector of random numbers from the end to the beginning
			for (size_t i = myRandoms.size() - 2; i >= 0; i--)
			{

				// If the random number is not unique remove it from the vector and restart the loop
				if (myRandoms[i] == num) { myRandoms.pop_back(); unique = false; break; }

				// If the beginning of the vector has been reached and random number is unique, leave it
				if (i == 0 && myRandoms[i] != num) { unique = true; break;}
			
			}
			
		}

	}
	
	// Iterate through the vector and assemble a string of randomized characters
	for (int r = 0; r <= size - 1; r++)
	{
		jumbledName = jumbledName + name[myRandoms[r] - 1];
	}

	// Adust the capitalization to title case
	transform(jumbledName.begin(), jumbledName.end(), jumbledName.begin(), ::tolower);
	jumbledName[0] = toupper(jumbledName[0]);

	return jumbledName;
}

string jumble2(string name)
{

	vector<char> characters;
	string jumbledName = "";

	// Convert the string into a vector
	for (int x = 0; x <= name.length(); x++)
	{
		characters.push_back(name[x]);
	}

	// Iterate through the vector constructing a new jumbled string
	for (int y = 0; y < name.length(); y++)
	{
		char character = getRndChar(characters);
		jumbledName = jumbledName + character;

		// Remove that character from the vector of characters
		for (size_t z = 0; z <= characters.size(); z++)
		{
			if (characters[z] == character) { characters.erase(characters.begin() + z); characters.shrink_to_fit(); break; }
		
		}


	}

	// Adust the capitalization to title case
	transform(jumbledName.begin(), jumbledName.end(), jumbledName.begin(), ::tolower);
	jumbledName[0] = toupper(jumbledName[0]);

	return jumbledName;
}

char getRndChar(vector<char> characters) {

	size_t size = characters.size() - 1;
	int num = random(size);
	char character = characters[num - 1];
	return character;

}