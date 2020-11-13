library(Rcpp)

# testing Rcpp

# 1
cppFunction('
int one() {
    return 1;
}
')

x <- one()

#2
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

#3
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

#4
