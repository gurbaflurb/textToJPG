#ifdef __linux__
#include <unistd.h>
#endif
#ifdef __WIN32__
#include <windows.h>
#endif

void mySleep(int secondsMs)
{
	#ifdef __linux__
		usleep(secondsMs *1000);
	#endif

	#ifdef __WIN32__
		Sleep(secondsMs)
	#endif
}

#include <iostream>
#include <string>
#include <fstream>
#include <thread>

using namespace std;

const int width = 255, height = 255;

void createImage(string str);

void spinner(bool Alive);

int main()
{
	bool isAlive = true;
	string inputText;
	cout << "Please input text to convert to ppm: " << endl;
	cin >> inputText;

	thread t1(createImage, inputText);
//	thread t2(spinner, t1.joinable());

	t1.join();
//	t2.join();

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
}

void spinner(bool alive)
{
	char position = '|';
	//int positionValue = 0;
	while(alive)
	{
		switch (position)
		{
			case '|':
				position = '/';
				cout << "\r" << position << flush;
				break;
			case '/':
				position = '-';
				cout << "\r" << position << flush;
				break;
			case '-':
				position = '\\';
				cout << "\r" << position << flush;
				break;
			case '\\':
				position = '|';
				cout << "\r" << position << flush;
				break;
		}
		mySleep(1);
	}
}
