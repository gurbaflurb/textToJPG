#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <thread>

using namespace std;

const int width = 2048, height = 2048;

void createImage(string str);

void spinner();

bool isAlive = false;

int main(int argc, char *argv[])
{
	string inputText;

	if(argc == 1)
	{
		cout << "Please input text to convert to ppm: " << endl;
		cin >> inputText;
	}
	else if(argc == 2)
	{
		inputText = argv[1];
	}
	else if (argc > 2)
	{
		std::cout << "Too many arguments!" <<endl;
		std::cout << "Usage:\n$./main StringForProgram" << std::endl;
		return 0;
	}

	thread t1(createImage, inputText);
	thread t2(spinner);

	t1.join();
	t2.join();

	return 0;
}

void createImage(string str)
{
	ofstream file;
	file.open("IAMPPM.ppm");
	file << "P3" << endl;
	file << width << " " << height << endl;
	file << "255" << endl;

	int strSize = sizeof(str);
	int seed = 0;

	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			seed = str[i % strSize];

			int r = (j * (unsigned int)seed) % 255;
			int g = (i * (unsigned int)seed) % 255;
			int b = ((i * j) * (unsigned int)seed) % 255;
			file << r << " " << g << " " << b << endl;
		}
	}

	file.close();
	isAlive = true;
}

void spinner()
{
	char spinPos = '|';
	unsigned int positionVal = 0;
	while(!isAlive)
	{
		switch (positionVal)
		{
			case 0:
				spinPos = '/';
				positionVal++;
				break;
			case 1:
				spinPos = '-';
				positionVal++;
				break;
			case 2:
				spinPos = '\\';
				positionVal++;
				break;
			default:
				spinPos = '|';
				positionVal = 0;
				break;
		}
		std::cout << "\rGenerating " << spinPos << std::flush;
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
	}
}
