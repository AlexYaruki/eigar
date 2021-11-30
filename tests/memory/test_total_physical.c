#include <eigar.h>
#include <assert.h>

int main() {
    int64_t total_physical = eigar_memory_total_physical();
    assert(total_physical > 0);
}