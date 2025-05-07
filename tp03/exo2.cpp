#include <iostream>
#include <string>
#include <vector>
// Return the number of occurrences of 'a' found in string 's'.
int count_a_occurrences(const std::string& s);

// Update function of a rendering program.
// - dt (delta time) is read by the function to know the time elapsed since the last frame.
// - errors is a string filled by the function to indicate what errors have occured.
void update_loop(const float& dt, std::string& errors_out);

// Return whether all numbers in 'values' are positive.
// If there are negative values in it, fill the array 'negative_indices_out' with the indices
// of these values and set its size in 'negative_count_out'.
// ex: auto res = are_all_positive({ 1, -2, 3, -4 }, negative_indices, negative_count);
//    -> res is false, since not all values are positive
//    -> negative_indices contains { 1, 3 } because values[1] = -2 and values[3] = -4
//    -> negative_count is 2
bool are_all_positives(const std::vector<int>& values, int negative_indices_out[],
                       size_t& negative_count_out) {
    negative_count_out = 0;
    for (auto i = 0; i < values.size(); ++i)
    {
        if (values[i] < 0)
        {
            negative_indices_out[negative_count_out] = i;
            negative_count_out++;
        }
    }
    return negative_count_out == 0;
}

// Concatenate 'str1' and 'str2' and return the result.
// The input parameters are not modified by the function.
std::string concatenate(const char* str1, const char* str2) {
    return std::string(str1) + str2;
}

int main(int argc, char const* argv[]) {
    // std::vector<int> values = { 1, -2, 3, -4 };
    // int              negative_indices[10];
    // size_t           negative_count = 0;

    // bool result = are_all_positives(values, negative_indices, negative_count);

    // std::cout << "Test are_all_positives: " << (result ? "Passed" : "Failed") << std::endl;
    // std::cout << "Negative indices: ";
    // for (size_t i = 0; i < negative_count; ++i)
    // {
    //     std::cout << negative_indices[i] << " ";
    // }
    // std::cout << std::endl;
    // std::cout << "Negative count: " << negative_count << std::endl;

    const char* str1   = "Hello, ";
    const char* str2   = "World!";
    std::string result = concatenate(str1, str2);
    std::cout << "Concatenate result: " << result << std::endl;

    return 0;
}
