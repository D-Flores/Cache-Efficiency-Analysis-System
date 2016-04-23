#include <fstream>
using std::ifstream; using std::ofstream;
#include <iostream>
using std::cout; using std::endl;
#include <string>
using std::string; using std::stol;

int main()
{
	ifstream ifs("memory_trace.out");
	ofstream ofs("memory_trace.reform");
	string line;
	bool in_func = false;

	while (ifs >> line)
	{
		if (line == "fc")
		{
			cout << "Yes" << endl;
			in_func = true;
			while (in_func == true)
			{
				ifs >> line;
				if (line == "r" || line == "w")
				{
					if (line == "r")
					{
						ofs << 0 << " ";
					}
					else if (line == "w")
					{
						ofs << 1 << " ";
					}

					ifs >> line;
					ofs << "0x" << std::hex << stol(line) << endl;
				}
				else if (line == "fr")
				{
					in_func = false;
				}
			}
		}
		
	}
}
