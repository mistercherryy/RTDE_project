#include <iostream>
#include <thread>
#include <chrono>

static void try_printing()
//int main(int argc, char* argv[]) 
{

	auto t1 = std::chrono::high_resolution_clock::now();

	std::cout << "printing tutorialle" << std::endl;

	auto t2 = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double, std::milli> ms_double = t2 - t1;
	std::cout << "TIME TAKEN: " << ms_double.count() << "milliseconds" << std::endl;

}