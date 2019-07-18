#include <iostream>
#include <fstream>
using std::ofstream; using std::ifstream;
#include <sstream>
using std::istringstream; 

using namespace std;


int main(int argc, char const *argv[])
{


	string s = "|||-1||-2";
	istringstream f(s);
	string s2;
	getline(f, s, '|');
	cout << s << endl;
	getline(f, s, '|');
	cout << s << endl;
	getline(f, s, '|');
	cout << s << endl;
	
	/*
	string test_string = "01100001";
	string sub1 = test_string.substr(0, 8);
	string sub2 = test_string.substr(8, test_string.size());

	unsigned char a = 0;
	int i = 0;
	for (auto s : sub1)
	{
		cout << (int) a << endl;
		if ( i != 0) a = (a << 1) | (s - 48);
		else a = a | (s-48);
		i++;
	}

	cout << a << endl;

	*/

	
	/*
	char teste = 40;
	char teste1 = (teste << 1) | 1;
	char teste2 = teste1 >> 1;
	char teste3 = teste << 1;

	cout << teste << endl;
	cout << teste1 << endl;
	cout << teste2 << endl;
	cout << teste3 << endl;

	int* testa = new int[10];

	for (int* i = testa; i < testa + 10; i++) cout << *i << endl;


	ofstream wf("binario.bin", ios::out);

	char bin = 0b10001011;
	char bin2 = 0b00000001;

	wf << bin;

	wf.close();

	ifstream rf("binario.bin", ios::in);

	char c;

	while (rf.get(c))
	{
		int i = 0;

		cout << (int) c << endl;

		while (i < 8)
		{
			cout << ( (c >> (7-i))  & 0b01);
			//c = c >> 1;
			i++;
		}
	}

	*/
	return 0;
}