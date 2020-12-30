#ifndef LEMMATIZATOR_HEADER_
#define LEMMATIZATOR_HEADER_

#include <string>
#include <map>
#include <vector>

class Lemmatizator
{
private:
    static const std::string ENDING_FILE_PATH;
    static const std::string SUFFIX_FILE_PATH;
    static std::vector<std::wstring> getPrefixes(const std::string &prefixesFilePath);
    static void replacePostfix(const std::vector<std::wstring> &postfixes, std::wstring &word);
    [[nodiscard]] static std::vector<std::wstring> getEndings();
    [[nodiscard]] static std::vector<std::wstring> getSuffixes();
public:
    Lemmatizator() = delete;
    ~Lemmatizator() = default;
    static std::map<std::wstring, size_t> lemmatize(std::string path);
};

#endif // LEMMATIZATOR_HEADER_