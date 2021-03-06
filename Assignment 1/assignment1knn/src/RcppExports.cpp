// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// knn_1
int knn_1(NumericMatrix X, NumericVector X0, NumericVector y);
RcppExport SEXP _assignment1knn_knn_1(SEXP XSEXP, SEXP X0SEXP, SEXP ySEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericMatrix >::type X(XSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type X0(X0SEXP);
    Rcpp::traits::input_parameter< NumericVector >::type y(ySEXP);
    rcpp_result_gen = Rcpp::wrap(knn_1(X, X0, y));
    return rcpp_result_gen;
END_RCPP
}
// knn_more
int knn_more(NumericMatrix X, NumericVector X0, NumericVector y, int K);
RcppExport SEXP _assignment1knn_knn_more(SEXP XSEXP, SEXP X0SEXP, SEXP ySEXP, SEXP KSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericMatrix >::type X(XSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type X0(X0SEXP);
    Rcpp::traits::input_parameter< NumericVector >::type y(ySEXP);
    Rcpp::traits::input_parameter< int >::type K(KSEXP);
    rcpp_result_gen = Rcpp::wrap(knn_more(X, X0, y, K));
    return rcpp_result_gen;
END_RCPP
}
// knn_inv
int knn_inv(NumericMatrix X, NumericVector X0, NumericVector y, int K);
RcppExport SEXP _assignment1knn_knn_inv(SEXP XSEXP, SEXP X0SEXP, SEXP ySEXP, SEXP KSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericMatrix >::type X(XSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type X0(X0SEXP);
    Rcpp::traits::input_parameter< NumericVector >::type y(ySEXP);
    Rcpp::traits::input_parameter< int >::type K(KSEXP);
    rcpp_result_gen = Rcpp::wrap(knn_inv(X, X0, y, K));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_assignment1knn_knn_1", (DL_FUNC) &_assignment1knn_knn_1, 3},
    {"_assignment1knn_knn_more", (DL_FUNC) &_assignment1knn_knn_more, 4},
    {"_assignment1knn_knn_inv", (DL_FUNC) &_assignment1knn_knn_inv, 4},
    {NULL, NULL, 0}
};

RcppExport void R_init_assignment1knn(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
