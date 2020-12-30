#include "Lemmatizator.h"
#include <filesystem>
#include <regex>
#include <iostream>
#include "FileReader.h"

namespace fs = std::filesystem;

const std::string Lemmatizator::ENDING_FILE_PATH = "../postfixes/endings.dat";

const std::string Lemmatizator::SUFFIX_FILE_PATH = "../postfixes/suffixes.dat";

std::vector<std::wstring> Lemmatizator::getPrefixes(const std::string &prefixesFilePath)
{
    std::vector<std::wstring> endings;
    FileReader *reader = nullptr;
    try
    {
        reader = new FileReader(prefixesFilePath);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return {};
    }
    while (reader->hasNextWord())
    {
        endings.push_back(reader->getNextWord());
    }
    delete reader;
    return endings;
}

std::vector<std::wstring> Lemmatizator::getEndings()
{
    return getPrefixes(Lemmatizator::ENDING_FILE_PATH);
}

std::vector<std::wstring> Lemmatizator::getSuffixes()
{
    return getPrefixes(Lemmatizator::SUFFIX_FILE_PATH);
}

void Lemmatizator::replacePostfix(const std::vector<std::wstring> &postfixes, std::wstring &word)
{
    std::wstring postfixKey;

    for (const auto &postfix : postfixes)
    {
        postfixKey += std::wstring(postfix) + std::wstring(L"|");
    }
    postfixKey.pop_back();
    std::wstring key = L"(" + postfixKey + L")$";
    std::wstring repl(L"");
    word = std::regex_replace(word, std::wregex(key), repl);
}

std::map<std::wstring, size_t> Lemmatizator::lemmatize(std::string path)
{
    std::map<std::wstring, size_t> lexems;
    FileReader *reader = nullptr;

    try
    {
        reader = new FileReader(path);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return {};
    }

    auto endings = getEndings();
    auto suffixes = getSuffixes();
    while (reader->hasNextWord())
    {
        std::wstring word = reader->getNextWord();
        replacePostfix(endings, word);
        replacePostfix(suffixes, word);

        if (lexems.find(word) != lexems.end())
            lexems.find(word)->second++;
        else
            lexems.insert(std::pair(word, 1));
    }

    delete reader;
    return lexems;
}