#include "scanner.hpp"
#include <fstream>
#include <gtest/gtest.h>

using namespace util;

const std::string TEST_DIR = std::string(TEST_DATA_DIR) + "/";

TEST(UnitTests, TestHash) {
  std::string path = "testfile.txt";

  std::ofstream ofs(path);
  ofs << "test";
  ofs.close();

  std::string md5 = computeMD5(path);
  std::filesystem::remove(path);

  EXPECT_EQ(md5, "098f6bcd4621d373cade4e832627b4f6");
}

TEST(UnitTests, DetectInfectedFile) {
  std::ofstream file("infected.txt");
  file << "test";
  file.close();

  std::ofstream csv("base.csv");
  csv << "098f6bcd4621d373cade4e832627b4f6;Virus" << std::endl;
  csv.close();

  Scanner scanner;

  auto result = scanner.run("./", "base.csv", "report.log");

  std::filesystem::remove("infected.txt");
  std::filesystem::remove("base.csv");
  std::filesystem::remove("report.log");

  EXPECT_TRUE(result.infected == 1);
}

TEST(UnitTests, HandleFileError) {
  Scanner scanner;

  std::ofstream file1("report.log");
  file1.close();

  std::ofstream file2("base.csv");
  file2.close();

  auto result = scanner.run("no_file.txt", "base.csv", "report.log");

  std::filesystem::remove("no_file");
  std::filesystem::remove("base.csv");
  std::filesystem::remove("report.log");

  EXPECT_TRUE(!result.total);
}

TEST(ProgramTest, e2e) {
  Scanner scanner;

  auto result = scanner.run(TEST_DIR + "/files", TEST_DIR + "base.csv",
                            TEST_DIR + "report.log");

  EXPECT_TRUE(result.errors == 0 && result.infected == 17 &&
              result.total == 100);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
