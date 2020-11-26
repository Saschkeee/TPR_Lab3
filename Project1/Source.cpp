#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;



int read_file_v(int voice[5]) {
	ifstream in("number of voters.txt");
	if (in.is_open())
	{

		for (int i = 0; i < 5; i++)
			in >> voice[i];

		for (int i = 0; i < 5; i++)
		{
			cout << voice[i] << "\t";
		}
		cout << endl;
		in.close();
		return *voice;
	}
	else
	{
		cout << "Файл не знайдено.";
	}
}

char read_file_c(char cand[3][5]) {
	ifstream in("benefits.txt");
	if (in.is_open())
	{

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 5; j++) {
				in >> cand[i][j];
			}
		}
		cout << endl;

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 5; j++) {
				cout << cand[i][j] << "\t";
			}
			cout << endl;
		}
		cout << endl << endl;
		in.close();
		return **cand;
	}
	else
	{
		cout << "Файл не знайдено.";
	}
}

int Board(int voice[5], char cand[3][5]) {
	cout << "\t\tМетод Борда" << endl;

	int sum[] = { 0,0,0 }, max = 0;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			switch (cand[i][j])
			{
			case 'A':
				switch (i)
				{
				case 0:
					sum[0] = sum[0] + 2 * voice[j];
					break;
				case 1:
					sum[0] += voice[j];
					break;
				}
				break;
			case 'B':
				switch (i)
				{
				case 0:
					sum[1] += 2 * voice[j];
					break;
				case 1:
					sum[1] += voice[j];
					break;
				}
				break;
			case 'C':
				switch (i)
				{
				case 0:
					sum[2] += 2 * voice[j];
					break;
				case 1:
					sum[2] += voice[j];
					break;
				}
				break;
			}
		}
	}

	for (int i = 0; i < 3; i++) {
		if (max < sum[i]) {
			max = sum[i];
		}
	}
	cout << "\tКандидат А: " << sum[0] << " очок\n";
	cout << "\tКандидат B: " << sum[1] << " очок\n";
	cout << "\tКандидат C: " << sum[2] << " очок\n";
	cout << "Переможцем є кандидат, що набрав " << max << " очок\n";

	return 0;
}

int Condorse(int voice[5], char cand[3][5]) {
	cout << "\n\t\tМетод Кондорсе:\n";

	int sum[] = { 0, 0 }, max[] = { 0, 0, 0 };
	char c[3];

	cout << "\tA > B OR B > A" << endl;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 2; j++) {
			if (cand[j][i] == 'A' && cand[j++][i] != 'B' && cand[j + 2][i] != 'B') {
				sum[0] += voice[i];
			}
			else if (cand[j][i] == 'B' && cand[j++][i] != 'A' && cand[j + 2][i] != 'A') {
				sum[1] += voice[i];
			}
		}
	}

	for (int i = 0; i < 2; i++) {
		if (max[0] < sum[i]) {
			max[0] = sum[i];
			switch (i)
			{
			case 0:
				cout << "A > B\t A = " << sum[i] << endl;
				c[0] = 'A';
				break;
			case 1:
				cout << "B > A\t B = " << sum[i] << endl;
				c[0] = 'B';
				break;
			}
		}
		sum[i] = 0;
	}

	cout << "\tB > C OR C > B" << endl;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 2; j++) {
			if (cand[j][i] == 'B' && cand[j++][i] != 'C' && cand[j + 2][i] != 'C') {
				sum[0] += voice[i];
			}
			else if (cand[j][i] == 'C' && cand[j++][i] != 'B' && cand[j + 2][i] != 'B') {
				sum[1] += voice[i];
			}
		}
	}

	for (int i = 2; i > 0; i--) {
		if (max[1] < sum[i]) {
			max[1] = sum[i];
			switch (i)
			{
			case 0:
				cout << "B > C\t B = " << sum[i] << endl;
				c[1] = 'B';
				break;
			case 1:
				cout << "C > B\t C = " << sum[i] << endl;
				c[1] = 'C';
				break;
			}
		}
		sum[i] = 0;
	}

	cout << "\tA > C OR C > A" << endl;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 2; j++) {
			if (cand[j][i] == 'A' && cand[j++][i] != 'C' && cand[j + 2][i] != 'C') {
				sum[0] += voice[i];
			}
			else if (cand[j][i] == 'C' && cand[j++][i] != 'A' && cand[j + 2][i] != 'A') {
				sum[1] += voice[i];
			}
		}
	}

	for (int i = 0; i < 2; i++) {
		if (max[2] < sum[i]) {
			max[2] = sum[i];
			switch (i)
			{
			case 0:
				cout << "A > C\t A = " << sum[i] << endl;
				c[2] = 'A';
				break;
			case 1:
				cout << "C > A\t C = " << sum[i] << endl;
				c[2] = 'C';
				break;
			}
		}
		sum[i] = 0;
	}

	for (int i = 0; i < 3; i++) {
		if (c[i] == c[i + 1] || c[i] == c[i + 2]) {
			cout << "Переможцем є кандидат " << c[i] << endl << endl;
			break;
		}
	}

	return 0;
}

void main() {
	setlocale(LC_ALL, "Ukrainian");
	int voice[5];
	char cand[3][5];

	read_file_v(voice);
	for (int i = 0; i < 34; i++) {
		cout << "_";
	}
	read_file_c(cand);
	Board(voice, cand);
	Condorse(voice, cand);

	system("pause");
}
