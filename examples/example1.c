#include <ndmath/ndarray.h>
#include <ndmath/array.h>
#include <ndmath/statistics.h>
#include <ndmath/helper.h>
#include <ndmath/random.h>

int main() {
    ndarray_t a = randint(5, 5, 50, 1, 0);
    ndarray_t b = mean(&a, "all");
    print_named_array(b, "mean on all axis", 2);
    clean(&a, NULL);
    return 0;
}