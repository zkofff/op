#include <stdio.h>
#include <stdlib.h>
#include <vector\vectorVoid.h>

typedef struct{
    int coefficient;
    int exponent;
} term_t;


int compare(const void *pa, const void *pb){
    const term_t a = *(term_t *)pa;
    const term_t b = *(term_t *)pb;

    return b.exponent - a.exponent;
}

void sanitize(vectorVoid *terms){
    term_t zero;
    zero.coefficient = 0;
    zero.exponent = 0;

    term_t a, b;
    for (size_t i = 0u; i < terms->size; ++i){
        getVectorValueV(terms, i, &a);
        for (size_t j = i + 1; j < terms->size; ++j){
            getVectorValueV(terms, j, &b);

            if (a.exponent == b.exponent && b.coefficient != 0){
                a.coefficient += b.coefficient;
                setVectorValueV(terms, i, &a);
                setVectorValueV(terms, j, &zero);
            }
        }
    }

    qsort(terms->data, terms->size, terms->baseTypeSize, compare);
}

void task(vectorVoid *poly1, vectorVoid *poly2, vectorVoid *res){
    term_t a, b;
    for (size_t i = 0u; i < poly1->size; ++i){
        getVectorValueV(poly1, i, &a);
        for (size_t j = 0u; j < poly2->size; ++j){
            getVectorValueV(poly2, j, &b);

            term_t l;
            l.coefficient = a.coefficient * b.coefficient;
            l.exponent = a.exponent + b.exponent;

            pushBackV(res, &l);
        }
    }

    sanitize(res);
}

int main(){
    vectorVoid poly1 = createVectorV(0, sizeof(term_t));
    vectorVoid poly2 = createVectorV(0, sizeof(term_t));
    vectorVoid result = createVectorV(0, sizeof(term_t));

    // 3x^2+5x+6
    term_t tmp;
    tmp.coefficient = 5;
    tmp.exponent = 1;
    pushBackV(&poly1, &tmp);

    tmp.coefficient = 3;
    tmp.exponent = 2;
    pushBackV(&poly1, &tmp);

    tmp.coefficient = 6;
    tmp.exponent = 0;
    pushBackV(&poly1, &tmp);

    // 2x+4
    tmp.coefficient = 2;
    tmp.exponent = 1;
    pushBackV(&poly2, &tmp);

    tmp.coefficient = 4;
    tmp.exponent = 0;
    pushBackV(&poly2, &tmp);

    task(&poly1, &poly2, &result);

    for (size_t i = 0u; i < result.size; ++i){
        term_t t;
        getVectorValueV(&result, i, &t);

        if (!(t.coefficient == 0 && t.exponent == 0)){
            if (t.exponent != 0)
                printf("%dx^%d", t.coefficient, t.exponent);
            else
                printf("%d", t.coefficient);

            printf("\t");
        }
    }

    vectorVoid assertion = createVectorV(0, sizeof(term_t));

    tmp.coefficient = 6;
    tmp.exponent = 3;
    pushBackV(&assertion, &tmp);

    tmp.coefficient = 22;
    tmp.exponent = 2;
    pushBackV(&assertion, &tmp);

    tmp.coefficient = 32;
    tmp.exponent = 1;
    pushBackV(&assertion, &tmp);

    tmp.coefficient = 24;
    tmp.exponent = 0;
    pushBackV(&assertion, &tmp);

    tmp.coefficient = 0;
    tmp.exponent = 0;
    pushBackV(&assertion, &tmp);

    tmp.coefficient = 0;
    tmp.exponent = 0;
    pushBackV(&assertion, &tmp);

    assert(assertion.size == result.size);
    for (size_t i = 0u; i < assertion.size; ++i){
        term_t a, b;
        getVectorValueV(&result, i, &a);
        getVectorValueV(&assertion, i, &b);

        assert(a.coefficient == b.coefficient && a.exponent == b.exponent);
    }

    return 0;
}
