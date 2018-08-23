#include <iostream>
#include <vector>
#include <thread>

#include "benchmarks/BenchmarkECS_Entity.hpp"
#include "benchmarks/BenchmarkECS_Component.hpp"
#include "benchmarks/BenchmarkECS_System.hpp"

int main()
{
	int user_select(0);
	std::vector<std::pair<std::string, Benchmark*>> bench_table;
	bench_table.push_back(std::make_pair("[E]ntity", new BenchmarkECS_Entity));
	bench_table.push_back(std::make_pair("[C]omponent", new BenchmarkECS_Component));
	bench_table.push_back(std::make_pair("[S]ystem", new BenchmarkECS_System));

	do
	{
		std::cout << "[ECS BENCHMARKS TABLE]" << std::endl;
		for(size_t i=0; i<bench_table.size(); i++)
		{
			std::cout << "#" << (i+1) << " " << bench_table[i].first << std::endl;
		}
		std::cout << std::endl << "#0 [ -] Exit" << std::endl;
		std::cout << "$ ";
		std::cin >> user_select;
		if(user_select == 0)
			user_select = -1;
		else
			user_select--;

		if(user_select >= 0 && user_select < static_cast<int>(bench_table.size()))
		{
			std::cout << "BENCHMARK SELECTED: " << bench_table[user_select].first << std::endl;
			std::cout << "(Note: The benchmark could take several minutes)" << std::endl;
			std::cout << "---------------------------------------------------------------" << std::endl << std::endl;

			bench_table[user_select].second->Run(Benchmark::HIGH_BENCH_SETTINGS);
			bench_table[user_select].second->Print();
			bench_table[user_select].second->SaveCSV("benchmark.csv");

			std::cout << "---------------------------------------------------------------" << std::endl << std::endl;
		}

	}while(user_select != -1);

    return 0;
}
