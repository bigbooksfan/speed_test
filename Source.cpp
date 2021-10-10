#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include <chrono>

using namespace std;

long long num1;
unsigned num, tmp;
int i, j, k;
vector<unsigned> vec;

void fill(unsigned number)
{

	for (i = 0; i < number; ++i)					// filling vector by numbers 0..N
	{

		vec.push_back(i + 1);

	}
}

void vec_erase(random_device* dev)
{

	uniform_int_distribution<unsigned> dist1(0, vec.size() - 1);

	int a = dist1(*dev);
	vec.erase(vec.begin() + a);		// random value remove, size is (N-1) now
	cout << endl << a + 1 << "-th element erased. N is " << vec.size() << " now.\n";

}

void mix(vector<unsigned>* to_mixer, random_device* dev)
{

	uniform_int_distribution<unsigned> dist2(0, vec.size() - 1);

	for (i = 0; i < vec.size(); ++i)
	{
		j = dist2(*dev);
		k = dist2(*dev);

		//cout << "k = " << k << ", j = " << j;

		if (!(j == k))
		{
			//cout << ", enter\n";

			tmp = (*to_mixer)[j];
			(*to_mixer)[j] = (*to_mixer)[k];
			(*to_mixer)[k] = tmp;
			
		}
		//else cout << ", skip\n";
		
	}
}

void print(vector<unsigned>* to_console)
{

	for (auto& i : *to_console) cout << i << endl;

}

unsigned HIS(unsigned N, vector<unsigned>* input)
{

	long long sum = 0;

	for (i = 1; i < N + 1; ++i) {
		
		sum += i;
		//cout << i << ", sum = " << sum << endl;
	}

	for (auto& i : *input) sum -= i;

	return sum;
}

unsigned MY(unsigned N, vector<unsigned>* input)
{
	auto start = chrono::high_resolution_clock::now();
	vector<bool> check;
	check.resize(N, true);
	auto end = chrono::high_resolution_clock::now();

	chrono::duration<float> duration = end - start;
	cout << "RESIZE time is " << duration.count() << endl;


	for (i = 0; i < N - 1; ++i) 
	{		
		check[(*input)[i] - 1] = false;
	}

	for (i = 0; i < N; ++i) if (check[i]) {

		return i + 1;
	}
	return 999999999;
	   

}


int main() {

	cin >> num1;					// choose N

	num = ((num1 - 1) % 4000000000) + 1;		// set last element possible

	cout << "N set to " << num << ". Good luck!\n";
	
	random_device rd;

	fill(num);

	//print(&vec);

	vec_erase(&rd);

	//print(&vec);
	
	mix(&vec, &rd);

	//print(&vec);

	auto start = chrono::high_resolution_clock::now();
	cout << "MISSED VALUE IS " << HIS(num, &vec) << endl;
	auto end = chrono::high_resolution_clock::now();

	chrono::duration<float> duration = end - start;
	cout << "His time is " << duration.count() << endl;

	start = chrono::high_resolution_clock::now();
	cout << "MISSED VALUE IS " << MY(num, &vec) << endl;
	end = chrono::high_resolution_clock::now();

	duration = end - start;
	cout << "My time is  " << duration.count() << endl;
	
}