#pragma once

#include <chrono>
#include <utility>
#include <functional>

template <typename TimePeriod = std::milli, typename Func, typename... Args>

double measure_time(Func &&fn, Args&&... args)
{
  auto t1 = std::chrono::high_resolution_clock::now();
  std::invoke(std::forward<Func>(fn), std::forward<Args>(args)...);
  auto t2 = std::chrono::high_resolution_clock::now();
  
  std::chrono::duration<double, TimePeriod> duration{t2 - t1};
  return duration.count();
}

#define SETUP_BENCHMARK() \
  std::vector<std::pair<std::string, double>> benchmarks
  
#define BENCHMARK(fn) \
  benchmarks.emplace_back(std::string{#fn}, fn())
