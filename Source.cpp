#include <iostream>
#include "pthreads-master/pthread.h"
#include <ctime>
#include <chrono>
#include "pthread.h"
#pragma comment(lib, "pthreadVC2.lib")

struct MyData
{
	double a;
	double b;
	double e;
	double (*function)(double x);
	double sum;


};

MyData generateData(double a, double b, double e, double (*function)(double x), double sum)
{
	MyData myData;
	myData.a = a;
	myData.b = b;
	myData.e = e;
	myData.function = function;
	myData.sum = sum;
	return myData;
}

void* calculate(void* args)
{

	MyData myData = *(MyData*)args;

	double a = myData.a;
	double b = myData.b;
	double e = myData.e;
	double h = e;
	double x = a;

	while (x < b)
	{
		myData.sum += h * myData.function(x);
		if (x + h < b)
		{
			x += h;
		}
		else
		{
			x = b;

		}
	}
	((MyData*)args)->sum = myData.sum;
	//std::cout << ((MyData*)args)->sum << std::endl;
	return NULL;

}
double cosinus(double x)
{
	return cos(x);
}



int main()
{
	auto time1 = std::chrono::high_resolution_clock::now();
	const int N = 1;
	double sum = 0;
	double sums[N];
	pthread_t threads[N];
	MyData data[N];
	double a = 0, b = 6000;

	for (int i = 0; i < N; i++)
	{
		data[i] = generateData((a + (i) * (b-a) / N), (a + (i + 1) * (b-a) / N), 0.001, cosinus, 0);
		pthread_create(&threads[i], NULL, calculate, &data[i]);
	}
	
	for (int i = 0; i < N; i++)
	{
		pthread_join(threads[i], NULL);
	}



	for (int i = 0; i < N; i++)
	{
		sum += data[i].sum;
	}
	std::cout << sum<< std::endl;
	auto time2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1).count();
	auto avrDur = duration ;
	std::cout << avrDur << std::endl;
	//13938
	//358k
	return 0;
};

