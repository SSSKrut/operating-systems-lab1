#include <iostream>
#include <vector>

double emaInt(const std::vector<int>& data, double alpha) {
    if (data.empty()) return 0;
    double ema = data[0];
    for (size_t i = 1; i < data.size(); ++i) {
        ema = alpha * data[i] + (1.0 - alpha) * ema;
    }
    return ema;
}

int main(int argc, char* argv[]) {
    size_t repeats = 1;
    if (argc > 1) repeats = std::stoi(argv[1]);

    double result = 0;
    for (; repeats > 0; repeats--) {
        std::vector<int> samples = {0, 1, 2, 3, 4, 5, 6, 7, (int)repeats};
        double alpha = 0.5;
        result += emaInt(samples, alpha);
    }

    std::cout << "Result: " << result << std::endl;

    return 0;
}