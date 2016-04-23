#include <random>
using std::random_device; using std::mt19937; using std::uniform_int_distribution;
#include <algorithm>
using std::shuffle;
#include <vector>
using std::vector;

long seq_search(vector<long long> &v, vector<long long> &ind, long key)
{
	for (auto i = 0u; i < v.size(); i++)
	{
		if (v.at(ind.at(i)) == key)
		{
			return i;
		}
	}
	return -1;
}

long shuffle_search(vector<long long> &v, vector<long long> &ind, long key)
{
	for (auto i = 0u; i < v.size(); i++)
	{
		if (v.at(ind.at(i)) == key)
		{
			return i;
		}
	}
	return -1;
}

int main()
{
	vector<long long> v(100000);
		
	for (auto i = 0u; i < v.size(); i++)
	{
		v.at(i) = i;
	}

	vector<long long> ind = v;

	random_device rd;
	mt19937 g(rd());
	uniform_int_distribution<long> dist(0,99999);

	for (auto j = 0; j < 1; j++)
	{
		long key = dist(g);
		seq_search(v, ind, key);
	}

	shuffle(ind.begin(), ind.end(), g);

	for (auto l = 0; l < 1; l++)
	{
		long key = dist(g);
		shuffle_search(v, ind, key);
	}
	
}
