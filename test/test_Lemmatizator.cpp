#include "gtest/gtest.h"
#include <filesystem>
#include <fstream>
#include <string>
#include "Lemmatizator.h"

namespace fs = std::filesystem;

TEST(lemmatize, onLemm)
{
    std::fstream fileDescriptor;
    std::string filePath = "test.txt";
    fileDescriptor.open(filePath, std::ios_base::out);
    fileDescriptor << "readed readed readed readed readed readed readed readed "
                      "reading reading reading reading reading "
                      "reads reads reads reads reads "
                      "readors readers readens ";
    fileDescriptor.close();
    auto lemm = Lemmatizator::lemmatize(filePath);
    EXPECT_EQ(lemm.size(), 2);
    size_t count = lemm.find(L"read")->second;
    EXPECT_EQ(count, 21);
    fs::remove(filePath);
} 