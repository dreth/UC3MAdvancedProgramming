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

#6 takes vector, returns vector of (min,max)
cppFunction('
NumericVector my_range(NumericVector x) {    
    NumericVector out(2);
    out[1] = max(x);
    out[0] = min(x);
    return out;
}')

my_range(c(3,1,5,2))

#practicing
cppFunction('
NumericVector my_range_manual(NumericVector x) {    
    NumericVector out(2);
    NumericVector minmax(2);
    int n = x.size();
    int i;

    double maximum = 0;
    double minimum = 0;

    for (i = 0; i < n; i++) {
        minmax[0] = x[i];
        minmax[1] = x[i];
        if (minmax[0] > x[i]) {
            out[0] = x[i];
        }
        if (minmax[1] < x[i]) {
            out[1] = x[i];
        }
    }
    return out;
}')

my_range(c(3,1,5,2,2,3,4,55,6,2,4,3,2,24,1,343,5,4,23,12,32,3,23,23,332,3,2,3,2,-1))

#7 standard deviation per column using sugar mean
cppFunction('
NumericVector rowSd_C(NumericMatrix mt) {
    int nrow = mt.nrow();
    int ncol = mt.ncol();

    NumericVector means(nrow);
    NumericVector out(nrow);
    double total;
    int i,j;

    //loop for rows
    for (i = 0; i < nrow; i++) {
        total = 0;
        //Sugar for computing the row means
        means[i] = mean(mt(i,_));
        //loop for columns
        for (j = 0; j < ncol; j++) {
            // pow is for x^y
            total = total + pow(mt(i,j) - means[i], 2.0);
        }
        out[i] = sqrt(total / (ncol-1));
    }
    return out;
}')

#8 same as 7 but wth more sugar
cppFunction('
NumericVector rowSd_C(NumericMatrix mt) {
    int nrow = mt.nrow();
    int ncol = mt.ncol();

    NumericVector out(nrow);
    double total;
    int i,j;

    //loop for rows
    for (i = 0; i < nrow; i++) {
        out[i] = sd(mt(i,_));
    }
    return out;
}')

#9 max,min,mean,sd for each col, summary statistics
cppFunction('
NumericVector summary_stats(NumericMatrix mt) {
    int nrow = mt.nrow();
    NumericMatrix out(nrow,4);
    int i;

    //loop for rows
    for (i = 0; i < nrow; i++) {
        out(i,0) = max(mt(i,_));
        out(i,1) = min(mt(i,_));
        out(i,2) = mean(mt(i,_));
        out(i,3) = sd(mt(i,_));
    }
    return out;
}')

summary_stats(matrix(c(1,3,2,4,5, 4,5,3,2,8, 1,2,3,45,5, 4,3,2,43,5, 3,4,5,56,3), nrow=5, ncol=5, byrow=T))
summary_stats(matrix(runif(30),nrow=5))


# 10 using dataframes and lists
cppFunction ('
List changeDataframe(DataFrame DF) {
    // we receive a DF data.frame object and access each column by name
    IntegerVector a = DF["a"];
    CharacterVector b = DF["b"];

    // We use clone (copy) so that the original dataframe is not modified
    a = clone(a);
    b = clone(b);

    // do something
    a[2] = 42;
    b[1] = "foo";

    // create a new data frame with two columns named newa and newb
    DataFrame NDF = DataFrame::create(Named("newa")=a,
    Named("newb")=b);

    // and return old and new in list with two elements: origDataFrame and newDataFrame
    return(List::create(Named("origDataFrame")=DF,
    Named("newDataFrame")=NDF));
}')
