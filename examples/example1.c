#include <ndmath/ndarray.h>
#include <ndmath/array.h>
#include <ndmath/statistics.h>

int main() {
    ndarray a = array(5, 5);
    printf("Mean: %f\n", mean(&a, "all"));
    clean(&a);
    return 0;
}