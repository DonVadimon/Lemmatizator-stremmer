#include "gtest/gtest.h"
#include <filesystem>
#include <string>
#include "Lemmatizator.h"

namespace fs = std::filesystem;

TEST(lemmatize, onLemm)
{
    std::string filePath = "test.txt";
    auto lemm = Lemmatizator::lemmatize(filePath);
    EXPECT_EQ(lemm.size(), 2);
    size_t count = lemm.find(L"read")->second;
    EXPECT_EQ(count, 21);
    fs::remove(filePath);
}