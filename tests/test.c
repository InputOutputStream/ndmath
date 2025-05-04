#include <ndmath/ndarray.h>
#include <ndmath/array.h>
#include <ndmath/conditionals.h>
#include <ndmath/error.h>
#include <ndmath/io.h>
#include <ndmath/linalg.h>
#include <ndmath/operations.h>
#include <ndmath/helper.h>
#include <ndmath/random.h>
#include <ndmath/trig.h>
#include <ndmath/statistics.h>

int main()
{
    clock_t start, stop;

    ndarray_t a = array(2,2);

    
    printf("Lecture des valeures du ndarray_t\n"); // arrive ici
    for(size_t i=0; i<a.shape[0]; i++)
    {
        for(size_t j=0; j<a.shape[1]; j++)
            scanf("%lf",  &a.data[i][j]);
    }
    
    start = clock();
    ndarray_t b = sum(&a, &a);
    ndarray_t c = subtract(&b, &a);
    ndarray_t d = matmul(&b, &c);

    ndarray_t e = transpose(&d);
    printf("..................Here.......................\n");

    ndarray_t f = ravel(&d);

    ndarray_t g = scaler(&d, 2, '/');

    ndarray_t h = std(&a, "y");
    //printf("..................Here.......................\n");

    ndarray_t i = divide(&b, &a);
    ndarray_t j = zeros(10, 10);
    ndarray_t k = ones(10, 10);
    ndarray_t l = linspace(100, 1, 0.1, 10, 15);
    ndarray_t m = arange(100, 50, 10, 10, "dsc");
    ndarray_t n = arange(100, 50, 10, 10, "asc");
    ndarray_t o = argmax(&l, "x");
    ndarray_t p = argmin(&l, "y");
    ndarray_t q = lower_triangle(-1, 10, 10);
    ndarray_t r = upper_triangle(1, 10, 10);
    //printf("..................Here.......................\n");

    ndarray_t s = randn(10, 10, 5);
    ndarray_t t = randint(10, 10, 100, 9, 5);
    ndarray_t u = shuffle(&r, 0);
    ndarray_t v = inv(&a);
    ndarray_t w = matmul(&a, &v);
    ndarray_t x = norm(&k, "all");

    ndarray_t y = rslice(&l, 7, 8);
    
    ndarray_t z = cslice(&l, 4, 5);

    ndarray_t aa = cassign(&q, &o, 9, 1);

    ndarray_t XX = array(3, 3);


    XX.data[0][0] = -133;
    XX.data[0][1] = 150;
    XX.data[0][2] = -45;

    XX.data[1][0] = -90;
    XX.data[1][1] = 102;
    XX.data[1][2] = -30;
    
    XX.data[2][0] =  90;
    XX.data[2][1] = -100;
    XX.data[2][2] =  32;

    ndarray_t R;
    ndarray_t Q;   

    printf("Am in QR\n");

    qr(&t, &Q, &R);

    printf("Am out\n");

    ndarray_t test = matmul(&Q, &R);

    printf("Am in eig\n");

    printf("Affichage des valeures du ndarray_t\n\n"); // arrive ici

    ndarray_t eig_v = eig(&t, 1000); 
    printf("Affichage des valeures du ndarray_t\n\n"); // arrive ici

    printf("Am in SVD\n");
    ndarray_t svd_v = svd(&t);

    printf("Affichage des valeures du ndarray_t\n\n"); // arrive ici
    
    named_array_t arrays[] = {
        {"A", &a}, {"adds", &b}, {"subs", &c}, {"matmul", &d},
        {"T", &e}, {"ravel", &f}, {"scaler", &g}, {"std", &h},
        {"divide", &i}, {"zeros", &j}, {"ones", &k}, {"linspace", &l},
        {"arrange", &m}, {"arrange", &n}, {"argmax", &o}, {"argmin", &p},
        {"trill", &q}, {"trillup", &r}, {"randn", &s}, {"randint", &t},
        {"shuffle", &u}, {"Inverse", &v}, {"Product of x and inv(x)", &w},
        {"Norm of k", &x}, {"row slice of l", &y}, {"col slice of l", &z},
        {"Q", &Q}, {"R", &R}, {"XX", &XX},{"test Q-R", &test}, {"Assign", &aa},
        {"eig val", &eig_v}, {"svd", &svd_v}
    };

    print_all_arrays(arrays, sizeof(arrays) / sizeof(arrays[0]));

    printf("after printing\n\n");

    clean_all_arrays(arrays, sizeof(arrays) / sizeof(arrays[0]));

    stop = clock();
    double t2 = ((double)(stop-start))/CLOCKS_PER_SEC;
    printf("Liberation terminer\n\n");
    printf("Temps d'execution = %.12lf\n", t2);
    return 0;
}
