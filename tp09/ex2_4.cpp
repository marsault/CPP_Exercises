#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

std::string upper(const std::string& word) {
    std::string result;
    std::transform(word.begin(), word.end(), std::back_inserter(result), [](const char& c) {return std::toupper(c);});
    return result;
}

std::string op(const std::string& a, const std::string& b) {
    return a + " " + b;
}

std::string concat_in_caps(const std::vector<std::string>& words)
{
    std::vector<std::string> upperd;
    std::transform(words.begin(), words.end(), std::back_inserter(upperd), [](const std::string& word) {return upper(word);});

    auto acc = std::accumulate(upperd.begin(), upperd.end(), std::string(), op);
    return acc;
}

int main()
{
    std::vector<std::string> words { "ARRETE", "De", "criEr", "steuplAIt" };
    std::cout << concat_in_caps(words) << std::endl;
    return 0;
}

