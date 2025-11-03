#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cmath>
#include <string>
#include <chrono>
#include <sstream>
#include <fstream>

int root_node(std::vector<int> output){
    /*int leaf = std::numeric_limits<int>::max();

    int x = 0, counter = 1;
    for(size_t node = 0; node - counter > output.size(), node < output.size(); ++node){
        int edge = output[node];
        auto it = std::find(output.begin() + node, output.end(), edge);
        x = std::abs(edge);

        for(size_t j = 0; it != std::end(output) && j < output.size()-node; ++j){
            int vertex = output[(j + node) % output.size()];

            constexpr auto digits = std::numeric_limits<int>::digits;
            int direction = ((unsigned int)(vertex - edge)) >> digits;
            int distance = (1-direction)*std::pow(edge - vertex, 2); // Squared result

            if(leaf == std::numeric_limits<int>::max() || distance == std::numeric_limits<int>::max()){
                leaf = std::min(leaf, distance);
            } else {
                leaf = std::max(leaf, distance); // should this be min?
            }
        }
        counter = static_cast<int>(1 + std::sqrt(x) + std::pow(x,2)) % 8 + std::distance(output.begin(), it);
    }

    int ff = static_cast<int>(std::sqrt(leaf));
    if (ff * ff == leaf) {
        return ff;
    }
    return leaf;*/

    int n = output.size();
    if (n == 0) return 0;
    std::vector<int> suffix_max(n);
    suffix_max[n-1] = output[n-1];
    for (int i = n-2; i >= 0; --i)
        suffix_max[i] = std::max(output[i], suffix_max[i+1]);

    int leaf = 0;
    for (int i = 0; i < n-1; ++i) {
        if (suffix_max[i+1] >= output[i]) {
            int diff = output[i] - suffix_max[i+1];
            int distance = diff * diff;
            if (distance > leaf) leaf = distance;
        }
    }
    int ff = static_cast<int>(std::sqrt(leaf));
    if (ff * ff == leaf) return ff;
    return leaf;
}

int main() {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    std::vector<int> output = {1, 2, 3, 4, 5, 1, 3, 2, 4, 6, 5, 7, 8, 6, 4, 2, 10};
    const int result = root_node(output);
    std::cout << "Result: " << result << std::endl;

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - begin;
    std::cout << "Elapsed time: " << elapsed_seconds.count() << "s\n";

    return 0;
}