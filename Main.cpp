#include <iostream>
#include <string>
#include <vector>
#include <chrono>

bool is_prime(uint64_t number)
{
  if (number == 2)
    return true;
  if (number < 2 || number % 2 == 0)
    return false;
  for (uint64_t i = 3; i * i <= number; i += 2)
    if (number % i == 0)
      return false;
  return true;
}

auto sieve_of_eratosthenes(uint64_t product)
{
  std::vector<bool> primes(product + 1, true);
  primes[0] = primes[1] = false;
  for (uint64_t p = 2; p * p <= product; ++p)
    if (primes[p])
      for (uint64_t i = p * 2; i <= product; i += p)
        primes[i] = false;
  return primes;
}

auto compute_prime_factors(uint64_t product)
{
  uint64_t inflection_point = 38585507;
  std::vector<bool> primes{};
  if (product > inflection_point)
    primes = sieve_of_eratosthenes(product);

  for (uint64_t current_number = 2; current_number < product; current_number++)
  {
    uint64_t possible_factor = product / current_number;
    auto is_current_prime = false;
    auto is_possible_factor_prime = false;
    if (product > inflection_point)
    {
      is_current_prime = primes[current_number];
      is_possible_factor_prime = primes[possible_factor];
    }
    else
    {
      is_current_prime = is_prime(current_number);
      is_possible_factor_prime = is_prime(possible_factor);
    }
    if (is_current_prime && is_possible_factor_prime && possible_factor != current_number && possible_factor * current_number == product)
      return std::make_pair<std::string, std::string>(std::to_string(current_number), std::to_string(possible_factor));
  }
  return std::make_pair<std::string, std::string>({}, {});
}

auto main(int32_t argc, char const *argv[]) -> int32_t
{
  std::string test_cases{"1"};
  std::cout << "How many test cases? ";
  std::getline(std::cin, test_cases);
  for (uint32_t i = 0; i < std::atoi(test_cases.c_str()); ++i)
  {
    std::putchar(10);
    std::string number;
    std::cout << "Number: ";
    std::getline(std::cin, number);
    auto start_time = std::chrono::high_resolution_clock::now();
    auto factors = compute_prime_factors(std::atoi(number.c_str()));
    auto end_time = std::chrono::high_resolution_clock::now();
    if (factors.first.empty() && factors.second.empty())
      std::cout << "-- Output: - " << std::endl;
    else
      std::cout << "-- Output: " << factors.first << ", " << factors.second << std::endl;
    std::cout << "-- Time: " << std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count() << "s" << std::endl;
  }

  return EXIT_SUCCESS;
}
