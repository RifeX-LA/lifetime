#include <flow/lifetime.hpp>

int main() {
    flow::lifetime l1;
    flow::lifetime l2;

    l1 == l2;
    l1 = l2;
    l1 = std::move(l2);

    return 0;
}
