#include <Rcpp.h>
using namespace Rcpp;

// This is a simple example of exporting a C++ function to R. You can
// source this function into an R session using the Rcpp::sourceCpp 
// function (or via the Source button on the editor toolbar). Learn
// more about Rcpp at:
//
//   http://www.rcpp.org/
//   http://adv-r.had.co.nz/Rcpp.html
//   http://gallery.rcpp.org/
//

// [[Rcpp::export]]
int knn_1(NumericMatrix X, NumericVector X0, NumericVector y) {
  int nrows = X.nrow();
  int ncols = X.ncol();
  
  double closest_distance = 99999999;
  double closest_output = -1;
  double closest_neighbor = -1;
  double difference = 0;
  
  int i;
  int j;
  
  for (i = 0; i < nrows; i++) {
    
    double distance = 0;
    for (j = 0; j < ncols; j++) {
      difference = X(i,j) - X0(j);
      distance = distance + difference * difference;
    }
    
    distance = sqrt(distance);
    
    if (distance < closest_distance) {
      closest_distance = distance;
      closest_output = y(i);
      closest_neighbor = i;
    }
  }
  return closest_output;
}

// [[Rcpp::export]]
int knn_more(NumericMatrix X, NumericVector X0, NumericVector y, int K) {
  int nrows = X.nrow();
  int ncols = X.ncol();
  
  NumericVector distances(nrows);
  NumericVector NN_distances(K);
  NumericVector NN_classif(K);
  double closest_distance = 99999999999999999;
  double closest_output = -1;
  double closest_neighbor = -1;
  double difference;
  
  int i;
  int j;
  
  
  for (i = 0; i < nrows; i++) {
    
    double distance = 0;
    for (j = 0; j < ncols; j++) {
      difference = X(i,j) - X0(j);
      distance = distance + difference * difference;
    }
    
    distance = sqrt(distance);
    distances[i] = distance;
    
    
    if (distance < closest_distance) {
      closest_distance = distance;
      closest_output = y(i);
      closest_neighbor = i;
    }
  }
  
  K = K - 1;
  NN_distances(0) = closest_distance;
  NN_classif(0) = closest_output;
  distances(closest_neighbor) = 99999999999999999;
  
  int idx;
  for (i = 0; i < K; i++) {
    double diff = 0;
    double min_diff = 99999999999999999;
    int index = 0;
    for (idx = 0; idx < nrows; idx++) {
      diff = distances(idx) - NN_distances(i);
      if (diff < min_diff) {
        min_diff = diff;
        index = idx;
      }
    }
    NN_distances(i+1) = distances(index);
    NN_classif(i+1) = y(index);
    distances(index) = 99999999999999999;
  }
  
  NumericVector classifs(unique(y).size());
  for (i = 0; i < unique(y).size(); i++) {
    classifs[i] = i+1;
  }
  
  NumericMatrix cnt(classifs.size(), 2);
  for (i = 0; i < classifs.size(); i++) {
    cnt(i,0) = classifs(i);
    cnt(i,1) = 0;
  }
  for (i = 0; i < NN_classif.size(); i++) {
    cnt(NN_classif(i)-1,1) = cnt(NN_classif(i)-1,1) + 1;
  }
  
  NumericVector count_vector = cnt(_,1);
  NumericVector maxes = count_vector[count_vector == max(count_vector)];
  int group = 0;
  int group_normally = 0;
  int maxes_size = maxes.size();
  if (K % 2 == 0) {
    if (maxes_size > 1) {
      for (i = 0; i < K; i++) {
        if (NN_distances(i) == min(NN_distances)) {
          group = NN_classif(i);
        }
      }
    } else {
      group_normally = 1;
    }
  } else {
    group_normally = 1;
  }
  
  if (group_normally == 1) {
    for (i = 0; i < classifs.size(); i++) {
      if (count_vector(i) == max(count_vector)) {
        group = i+1;
      }
    }
  }
  
  return group;
}

// [[Rcpp::export]]
int knn_inv(NumericMatrix X, NumericVector X0, NumericVector y, int K) {
  int nrows = X.nrow();
  int ncols = X.ncol();
  
  NumericVector distances(nrows);
  NumericVector NN_distances(K);
  NumericVector NN_classif(K);
  double closest_distance = 99999999999999999;
  double closest_output = -1;
  double closest_neighbor = -1;
  double difference;
  
  int i;
  int j;
  
  for (i = 0; i < nrows; i++) {
    
    double distance = 0;
    for (j = 0; j < ncols; j++) {
      difference = X(i,j) - X0(j);
      distance = distance + difference * difference;
    }
    
    distance = sqrt(distance);
    distances[i] = distance;
    
    
    if (distance < closest_distance) {
      closest_distance = distance;
      closest_output = y(i);
      closest_neighbor = i;
    }
  }
  
  K = K - 1;
  NN_distances(0) = closest_distance;
  NN_classif(0) = closest_output;
  distances(closest_neighbor) = 99999999999999999;
  
  int idx;
  for (i = 0; i < K; i++) {
    double diff = 0;
    double min_diff = 99999999999999999;
    int index = 0;
    for (idx = 0; idx < nrows; idx++) {
      diff = distances(idx) - NN_distances(i);
      if (diff < min_diff) {
        min_diff = diff;
        index = idx;
      }
    }
    NN_distances(i+1) = distances(index);
    NN_classif(i+1) = y(index);
    distances(index) = 99999999999999999;
  }
  
  NumericVector classifs(unique(y).size());
  for (i = 0; i < unique(y).size(); i++) {
    classifs[i] = i+1;
  }
  
  NumericMatrix cnt(classifs.size(), 2);
  for (i = 0; i < classifs.size(); i++) {
    cnt(i,0) = classifs(i);
    cnt(i,1) = 0;
  }
  for (i = 0; i < NN_distances.size(); i++) {
    cnt(NN_classif(i)-1,1) = cnt(NN_classif(i)-1,1) + 1/NN_distances(i);
  }
  
  int group;
  for (i = 0; i < cnt(_,1).size(); i++) {
    if (cnt(i,1) == max(cnt(_,1))) {
      group = cnt(i,0);
    }
  }
  
  return group;
}