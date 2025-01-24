#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

double emaInt(const std::vector<int>& data, double alpha) {
    if (data.empty()) return 0;
    double ema = data[0];
    for (size_t i = 1; i < data.size(); ++i) {
        ema = alpha * data[i] + (1.0 - alpha) * ema;
    }
    return ema;
}

void emaWorker(size_t repeats, std::atomic<int>& result) {
    for (; repeats > 0; repeats--) {
        std::vector<int> samples = {0, 1, 2, 3, 4, 5, 6, 7};
        double alpha = 0.5;
        int val = emaInt(samples, alpha);
        result.fetch_add(val);
    }
}

int main(int argc, char* argv[]) {
    size_t repeats = 1;
    size_t threadCount = 1;
    if (argc > 1) repeats = std::stoi(argv[1]);
    if (argc > 2) threadCount = std::stoi(argv[2]);

    std::atomic<int> totalResult{0};
    std::vector<std::thread> threads;

    for (size_t i = 0; i < threadCount; ++i) {
        threads.emplace_back(emaWorker, repeats, std::ref(totalResult));
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Result: " << static_cast<double>(totalResult.load()) << std::endl;
    return 0;
}