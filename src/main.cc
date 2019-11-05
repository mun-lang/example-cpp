#include <iostream>
#include <string>

#include "mun/runtime.h"

// How to run?
// 1. On the CLI, navigate to the `example-cpp` directory.
// 2. Run the compiler daemon from the CLI: `/path/to/mun build resources/fibonacci.mun --watch`
// 3. Run the application from the CLI: `main /path/to/fibonacci.dll`
int main(int argc, char* argv[]) {
    if (argc < 2) {
        return 1;
    }

    std::cout << "lib: " << argv[1] << std::endl;

    mun::Error error;
    if (auto runtime = mun::make_runtime(argv[1], &error)) {
        while (true) {
            auto n = mun::invoke_fn<int64_t>(*runtime, "nth").wait();
            auto result = mun::invoke_fn<int64_t>(*runtime, "fibonacci", n).wait();

            std::cout << "fibonacci(" << std::to_string(n) << ") = " << result << std::endl;

            mun::Error update_error;
            if (!runtime->update(&update_error) && update_error) {
                std::cerr << "Failed to update runtime due to error: " << update_error.message() << std::endl;
            }
        }
    }

    std::cerr << "Failed to construct Mun runtime due to error: " << error.message() << std::endl;
    return 2;
}
