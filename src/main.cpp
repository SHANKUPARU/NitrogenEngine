#include <nitrogen/Triangle.h>
int main() {
    Triangle triangle;

    try {
        triangle.run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
