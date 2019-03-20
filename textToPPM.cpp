#ifdef __linux__
#include <unistd.h>
#endif
#ifdef __WIN32__
#include <windows.h>
#endif

void mySleep(int secondsMs)
{
	#ifdef LINUX
		usleep(secondsMs *1000);
	#endif

	#ifdef WINDOWS
		Sleep(secondsMs)
	#endif
}


#include <iostream>
#include <string>
#include <fstream>
#include <thread>

using namespace std;

const int width = 1024, height = 1024;

void createImage(int strLen);

void spinner();

int main()
{
	int strLen = 0;

	string inputText;
	cout << "Please input text to convert to ppm: " << endl;
	cin >> inputText;

	strLen = sizeof(inputText);

	//spinner();

	thread t1(createImage, strLen);
	thread t2(spinner);

	t1.join();
	t2.joinable();

	return 0;
}

void createImage(int strLen)
{
	ofstream file;
	file.open("IAMPPM.ppm");
	file << "P3" << endl;
	file << width << " " << height << endl;
	file << "255" << endl;

	for(int i = 0; i < height; i++)
	{
		strLen * 3 % 255;
		for(int j = 0; j < width; j++)
		{
			int r = j % 255;
			int g = i * strLen % 255;
			int b = i * j * strLen % 255;
			file << r << " " << g << " " << b << endl;
		}
	}

	file.close();
}

void spinner()
{
	char position = '|';
	//int positionValue = 0;
	while(true)
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
		//mySleep(1);
	}
}