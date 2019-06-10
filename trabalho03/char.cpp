#include <iostream>
#include <fstream>
using std::ofstream; using std::ifstream;

using namespace std;


int main(int argc, char const *argv[])
{
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
	return 0;
}