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
    ndarray_t f = ravel(&d);
    ndarray_t g = scaler(&d, 2, '/');
    ndarray_t h = std(&a, "y");
    ndarray_t i = divide(&b, &a);
    ndarray_t j = zeros(10, 10);
    ndarray_t k = ones(10, 10);
    ndarray_t l = linspace(100, 1, 0.1, 10, 15);
    ndarray_t m = arange(100, 50, 10, 10, "dsc");
    ndarray_t n = arange(100, 50, 10, 10, "asc");
    ndarray_t o = argmax(&l, "x");
    ndarray_t p = argmin(&l, "y");
    ndarray_t q = trill(-1, 10, 10);
    ndarray_t r = trilup(1, 10, 10);
    ndarray_t s = randn(10, 10, 5);
    ndarray_t t = randint(10, 10, 100, 9, 5);
    ndarray_t u = shuffle(&r, 0);
    ndarray_t v = inv(&a);
    ndarray_t w = matmul(&a, &v);
    ndarray_t x = norm(&k, "all");
    
    ndarray_t y = rslice(&l, 7, 8);
    
    ndarray_t z = cslice(&l, 4, 5);

    ndarray_t aa = cassign(&q, &o, 9);

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
    printf("\n A ");
    print_array(a, 2);

    printf("\n adds ");
    print_array(b, 2);

    printf("\n subs ");
    print_array(c, 2);

    printf("\n matmul ");
    print_array(d, 2);

    printf("\n T ");
    print_array(e, 2);

    printf("\n ravel ");
    print_array(f, 2);

    printf("\n scaler ");
    print_array(g, 2);
    
    printf("\n std ");
    print_array(h, 2);

    printf("\n divide ");
    print_array(i, 2);

    printf("\n zeros ");
    print_array(j, 2);

    printf("\n ones ");
    print_array(k, 2);

    printf("\n linspace ");
    print_array(l, 2);

    printf("\n arrange ");
    print_array(m, 2);

    printf("\n arrange ");
    print_array(n, 2);

    printf("\n argmax ");
    print_array(o, 2);

    printf("\n argmin ");
    print_array(p, 2);


    printf("\n trill ");
    print_array(q, 2);

    printf("\n trillup ");
    print_array(r, 2);


    printf("\n randn ");
    print_array(s, 2);


    printf("\n randint ");
    print_array(t, 2);


    printf("\n shuffle ");
    print_array(u, 2);

    save_ndarray(&l, "./file2.csv");
    load_ndarray("file2.csv");

    printf("\n Inverse ");
    print_array(v, 2);

    printf("\n Product of x and inv(x) ");
    print_array(w, 2);

    printf("\n det(x)  = %lf \n", det(&a));

    printf("\n Norm of k ");
    print_array(x, 2);

    printf("\n row sclice of l ");
    print_array(y, 2);

     printf("\n linspace ");
    print_array(l, 2);


    printf("\n col slice of l ");
    print_array(z, 2);

    printf(".................................................\n");
    printf("\n Q ");
    print_array(Q, 2);


    printf("\n R ");
    print_array(R, 2);

    printf("\n XX ");
    print_array(t, 2);

    printf("\n Assign ");
    print_array(aa, 2);

    printf("\n test Q-R ");
    print_array(test, 2);

    printf("eig val ");
    print_array(eig_v, 2);


    clean(&a, NULL);
    clean(&b, NULL);
    clean(&c, NULL);
    clean(&d, NULL);
    clean(&e, NULL);
    clean(&f, NULL);
    clean(&g, NULL);
    clean(&h, NULL);
    clean(&i, NULL);
    clean(&j, NULL);
    clean(&l, NULL);
    clean(&m, NULL);
    clean(&n, NULL);
    clean(&o, NULL);
    clean(&p, NULL);
    clean(&q, NULL);
    clean(&r, NULL);

    clean(&s, NULL);
    clean(&t, NULL);
    clean(&u, NULL);

   
    clean(&v, NULL);
    clean(&w, NULL);

    clean(&x, NULL);

    clean(&Q, NULL);
    clean(&R, NULL);
    clean(&XX, NULL);
    clean(&test, NULL);
    clean(&svd_v, NULL);
    clean(&eig_v, NULL);
    clean(&aa, NULL);
    clean(&h, NULL);
    clean(&z, NULL);
    clean(&y, NULL);
    clean(&k, NULL);        



    stop = clock();
    double t2 = ((double)(stop-start))/CLOCKS_PER_SEC;
    printf("Liberation terminer\n\n");
    printf("Temps d'execution = %.12lf\n", t2);
    return 0;
}
