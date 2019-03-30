#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <time.h>
#include <float.h>
#include <iomanip>

#define N  5

using namespace std;

////////////////////////////////////////////functions//////////////////////////////////////////

int Search(float * temp , float r) 
// search for first number in temp array which is
//bigger than a random number between 0 and 1
{
	for (int i = 0; i < N; i++)
	{
		if (temp[i] >= r) 
		{
			return i;
		}
	}
}


void Update_Foromon( float f [N][N], int * instance) 
//Updates Foromon matrix after each instance is created
{
	for (int k = 0; k < N; k++)
	{
		for (int i = 0; i < N; i++)
		{
			f[k][i] *= 0.98; //Zarib tabkhir = 0.02
		}
	}
	
	for (int i = 0; i < N-1; i++)
	{
		int a = instance[i];
		int b = instance[i + 1];
		f[a][b] += 0.1; //add
	}

	f[instance[N-1]][instance[0]] += 0.1;
}


float Fitness(float p[N][N] ,int * instance)
//Calculate fitness of the instance(Length of the road)
{
		float L = 0;
		for (int i = 0; i < N - 1; i++)
		{
			L += p[instance[i]][instance[i + 1]];
		}
		L += p[instance[N - 1]][instance[0]];

		return L;
}



void Print_Ans(int * instance, float f ,float Foromon[N][N])
//a func to show answer in proper way
{
	cout << "=>> a valid answer is : " << endl << endl;
	for (int i = 0; i < N; i++)
	{
		cout << instance[i] << "  ";
	}
	cout << endl << endl << "=>> its fitness is :  " << f  << endl << endl;

	cout << "=>> new Foromon matrix is :" <<endl <<endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << setprecision(2);
			cout << fixed;
			cout << Foromon[i][j] << "  "; 
		}
		cout << endl;
	}
	cout <<endl;

}


void Read_File(float  Path[N][N])
//Reading and loading Path matrix from a text file
{
		//initialize Path matrix 
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				Path[i][j] = FLT_MAX;
		//loading
		int x, y, des;
		ifstream ff;
		ff.open("C:\\Test\\Path2.txt");

		if (!ff) {
			cout << "Unable to open file";
			exit(1);
		}
		while (!ff.eof())
		{
			ff >> x >> y >> des;
			Path[x][y] = des;
			Path[y][x] = des;
		}
		ff.close();

}

void Make_Foromon(float Foromon[N][N])
//initialiaze Foromon matrix
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (i == j)
			{
				Foromon[i][j] = 0.0;
			}
			else
			Foromon[i][j] = 1.0;
		}
	}
}


void Run()
{
	clock_t tStart = clock();
	float Path[N][N];
	float Foromon[N][N];

	Make_Foromon(Foromon);
	Read_File(Path);

	int sum;
	int go = 1;
	float temp[N];
	int instance[N];
	int help[N];


	for (int i = 0; i < N; i++)
	{
		temp[i] = 0;
		instance[i] = 0;
		help[i] = 0;
	}


	srand((int)time(0));
	int R = rand() % N;
	instance[0] = R;
	help[R] = 1;

	for (int k = 1; k < N; k++)
	{
		sum = 0;
		go = 1;

		for (int i = 0; i < N; i++)
		{
			temp[i] = Path[R][i] * Foromon[R][i];
			sum += Path[R][i];
		}


		for (int i = 0; i < N; i++)
		{
			temp[i] /= sum;
		}


		for (int i = 1; i < N; i++)
		{
			temp[i] += temp[i - 1];
		}

		while (go)
		{

			float r = ((float)rand() / (RAND_MAX));//random number between 0 and 1

			int next_city = Search(temp, r);

			R = next_city;

			if (help[R] != 1)
			{
				go = 0;
				help[R] = 1;
				instance[k] = next_city;
			}

		}

	}

	Update_Foromon(Foromon, instance);

	float fit = Fitness(Path, instance);

	Print_Ans(instance, fit, Foromon);

	cout << endl << endl << endl <<
		"=>> Time taken: " << (double)(clock() - tStart) / CLOCKS_PER_SEC <<
		endl << endl << endl;

}
///////////////////////////////////////////////Main/////////////////////////////////////////////

int main()
{
	Run();
}