#include "scanner.hpp"
#include <boost/program_options.hpp>
#include <chrono>
#include <iostream>

namespace po = boost::program_options;

int main(int argc, char *argv[]) {
  std::string csv;
  std::string log;
  std::string directory;

  try {
    po::options_description desc("Allowed options");
    desc.add_options()("help,h", "produce help message")(
        "base", po::value<std::string>(&csv)->required(),
        "path to CSV base of malicious hashes")(
        "log", po::value<std::string>(&log)->required(), "path to log file")(
        "path", po::value<std::string>(&directory)->required(),
        "path to directory to scan");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);

    if (vm.count("help")) {
      std::cout << desc << std::endl;
      return 0;
    }

    po::notify(vm);

    util::Scanner scanner;

    auto start = std::chrono::steady_clock::now();
    auto result = scanner.run(directory, csv, log);
    auto end = std::chrono::steady_clock::now();

    std::cout << "===== Scan Report =====\n";
    std::cout << "Processed files: " << result.total << std::endl;
    std::cout << "Malicious files: " << result.infected << std::endl;
    std::cout << "Errors: " << result.errors << std::endl;
    std::cout << "Elapsed time: "
              << std::chrono::duration<double>(end - start).count()
              << std::endl;
  } catch (const po::error &ex) {
    std::cerr << "Error parsing command line: " << ex.what() << "\n";
    return 1;
  } catch (const std::exception &ex) {
    std::cerr << "Ошибка: " << ex.what() << "\n";
    return 1;
  }

  return 0;
}