#include "Benchmark.hpp"

using namespace std::chrono;

const BenchmarkSettings Benchmark::LOW_BENCH_SETTINGS		= BenchmarkSettings(20, 25000);
const BenchmarkSettings Benchmark::MEDIUM_BENCH_SETTINGS	= BenchmarkSettings(20, 50000);
const BenchmarkSettings Benchmark::HIGH_BENCH_SETTINGS		= BenchmarkSettings(20, 75000);
const BenchmarkSettings Benchmark::EXTREME_BENCH_SETTINGS	= BenchmarkSettings(20, 100000);

Benchmark::Benchmark() :
	benchChrono_(), results_()
{
}


Benchmark::~Benchmark()
{
}


void Benchmark::Print()
{
	double average(0.0);

	for(auto itResults = results_.begin(); itResults != results_.end(); ++itResults)
	{
		average = 0.0;
		std::cout << itResults->first << std::endl;

		for(size_t i=0; i<itResults->second.size(); ++i)
		{
			std::cout << "\t#" << (i+1) << ": " << itResults->second[i].count() << " seconds" << std::endl;
			average += itResults->second[i].count();
		}
		std::cout << std::endl << "Average: " << static_cast<double>(average/itResults->second.size()) << " seconds" << std::endl;
		std::cout << "---------------------------------------------------------------" << std::endl;
	}
}


void Benchmark::SaveCSV(std::string filename)
{
	std::fstream file(filename.c_str(), std::ios::out | std::ios::trunc);
	if(file.is_open())
	{
		double average(0.0);
		for(auto itResults = results_.begin(); itResults != results_.end(); ++itResults)
		{
			file << itResults->first << std::endl;

			average = 0.0;
			for(size_t i=0; i<itResults->second.size(); ++i)
				file << "\"#" << (i+1) << "\";";
			file << std::endl;
			for(size_t i=0; i<itResults->second.size(); ++i)
			{
				file << itResults->second[i].count() << ";";
				average += itResults->second[i].count();
			}

			file << std::endl << std::endl << std::endl;
		}

		file.close();
	}
}


void Benchmark::start_bench(std::string name)
{
	std::cout << "BENCHMARK:\t" << name << "\t\t\t[START]" << std::endl;
    if(!benchChrono_.count(name))
		benchChrono_.insert(std::make_pair(name, std::pair<steady_clock::time_point, steady_clock::time_point>()));

    benchChrono_[name].first = steady_clock::now();
    benchChrono_[name].second = steady_clock::now();
}


void Benchmark::stop_bench(std::string name)
{
	if(benchChrono_.count(name))
	{
		benchChrono_[name].second = steady_clock::now();
		if(!results_.count(name))
			results_.insert(std::make_pair(name, std::vector<std::chrono::duration<double>>()));

		results_[name].push_back(duration_cast<duration<double>>(benchChrono_[name].second - benchChrono_[name].first));

		std::cout << "BENCHMARK:\t" << name << "\t\t\t[STOP]" << std::endl;
	}
}
