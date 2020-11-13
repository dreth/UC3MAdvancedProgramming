library(Rcpp)

# testing Rcpp

# 1 test
cppFunction('
int one() {
    return 1;
}
')

x <- one()

#2 summing elements in vector
cppFunction('
double sumC(NumericVector x) {
    int n = x.size();
    double total = 0;
    int i;
    for (i = 0; i < n; i++) {
        total = total + x[i];
    }
    return total;
}')

test = 1:100
sumC(test)

#3 calculating simple mean of vector
cppFunction('
double my_mean(NumericVector x) {
    int n = x.size();
    double mean = 0;
    int i;
    for (i = 0; i < n; i++) {
        mean = mean + x[i];
    }
    mean = mean / n;
    return mean;
}')

my_mean(c(1,2,3))

#4 vector is input and outputs a vector with elements that are >c as the same
# and elements that are <c are returned as 0
cppFunction('
NumericVector my_check_C(NumericVector x, double c) {
    int n = x.size();


    // this works the same way as python
    // clone must be used for this otherwise
    // the variable points to the same element in memory
    NumericVector out = clone(x);
    int i;

    for (i = 0; i < n; i++) {
        if (x[i] <= c) {
            out[i] = 0;
        }
    }
    return out;
}')

my_check_C(c(1,3,5,5,3,2,2,4,3,4,7,6,4,3,5,5), 3)

#5 calculate cumulative sum of elements in vector
# and return as another vector
cppFunction('
NumericVector my_cumsum(NumericVector x) {
    int n = x.size();

    NumericVector out = clone(x);
    double total = 0;
    int i;

    for (i = 0; i < n; i++) {
        total = total + x[i];
        out[i] = total;
    }
    return out;
}')

my_cumsum(1:10)

#6