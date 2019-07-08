#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <thread>

void createImage(std::string str);
void spinner();

bool isAlive = false;
const int width = 2048, height = 2048;

int main(int argc, char *argv[])
{
	std::string inputText;

	if(argc == 1)
	{
		std::cout << "Please input text to convert to ppm: " << std::endl;
		std::cin >> inputText;
	}
	else if(argc == 2)
	{
		inputText = argv[1];
	}
	else if (argc > 2)
	{
		std::cout << "Too many arguments!" << std::endl;
		std::cout << "Usage:\n$./main StringForProgram" << std::endl;
		return 0;
	}

	std::thread t1(createImage, inputText);
	std::thread t2(spinner);

	t1.join();
	t2.join();

	return 0;
}

void createImage(std::string str)
{
	std::ofstream file;
	file.open("IAMPPM.ppm");
	file << "P3" << std::endl;
	file << width << " " << height << std::endl;
	file << "255" << std::endl;

	int strSize = sizeof(str);
	int seed = 0;
	int r, g, b = 0;

	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			seed = (int)(str[i % strSize]);

			if(seed == 0)
			{
				seed = 1;
			}

			if((i%seed) == 0)
			{
				r = ((j * (unsigned int)seed) % 255);
				g = ((i * (unsigned int)seed) % 255);
				b = (((i * j) * (unsigned int)seed) % 255);
				file << r;
				file << " ";
				file << g;
				file << " ";
				file << b;
				file << " ";
				file << std::endl;
			}
			else if ((i%seed) == 1)
			{
				r = ((j * (unsigned int)seed) % 255);
				g = ((i * (unsigned int)seed) % 255);
				b = (((i * j) * (unsigned int)seed) % 255);
				file << r;
				file << " ";
				file << g;
				file << " ";
				file << b;
				file << " ";
				file << std::endl;
			}
			else if ((i%seed) == 2)
			{
				r = ((i * (unsigned int)seed) % 255);
				g = ((j * (unsigned int)seed) % 255);
				b = (((i * j) * (unsigned int)seed) % 255);
				file << r;
				file << " ";
				file << g;
				file << " ";
				file << b;
				file << " ";
				file << std::endl;
			}
			else
			{
				r = ((j * (unsigned int)seed) % 255);
				g = ((i * (unsigned int)seed) % 255);
				b = (((i * j) * (unsigned int)seed) % 255);
				file << r;
				file << " ";
				file << g;
				file << " ";
				file << b;
				file << " ";
				file << std::endl;
			}

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
	std::cout << "\r************************" << std::endl;
	std::cout << "File \"IAMPPM\" generated" << std::endl;
	std::cout << "************************" << std::endl;
}