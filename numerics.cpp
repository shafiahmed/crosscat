#include "numerics.h"

#include <cmath>
#include <algorithm>
#include <numeric>
#include "assert.h"
using namespace std;


// subtract minimum value, logaddexp residuals, pass residuals and partition to
// draw_sample_with_partition
int draw_sample_unnormalized(vector<double> unorm_logps, double rand_u) {
  double max_el = *std::max_element(unorm_logps.begin(), unorm_logps.end());
  double partition = 0;
  vector<double>::iterator it = unorm_logps.begin();
  for(; it!=unorm_logps.end(); it++) {
    *it -= max_el;
    partition += exp(*it);
  }
  double log_partition = log(partition);
  int draw = draw_sample_with_partition(unorm_logps, log_partition, rand_u);
  return draw;
}

int draw_sample_with_partition(vector<double> unorm_logps,
			       double log_partition, double rand_u) {
  int draw = 0;
  vector<double>::iterator it = unorm_logps.begin();
  for(; it!=unorm_logps.end(); it++) {
    rand_u -= exp(*it - log_partition);
    if(rand_u < 0) {
      return draw;
    }
    draw++;
  }
  // FIXME: should this fail?
  assert(rand_u < 1E-10);
  return draw;
}

int crp_draw_sample(vector<int> counts, int sum_counts, double alpha,
		    double rand_u) {
  int draw = 0;
  double partition = sum_counts + alpha;

  vector<int>::iterator it = counts.begin();
  for(; it!=counts.end(); it++) {
    rand_u -= (*it / partition);
    if(rand_u <0) {
      return draw;
    }
    draw++;
  }
  // new cluster
  return draw;
}

double calc_alpha_conditional(std::vector<int> counts, double alpha, int sum_counts, bool absolute) {
  int num_clusters = counts.size();
  if(sum_counts==-1) {
    sum_counts = std::accumulate(counts.begin(), counts.end(), 0);
  }
  double logp = lgamma(alpha)			\
    + num_clusters * log(alpha)			\
    - lgamma(alpha + sum_counts);
  // absolute necessary for determining true distribution
  if(absolute) {
    double sum_log_gammas = 0;
    std::vector<int>::iterator it = counts.begin();
    for(; it!=counts.end(); it++) {
      sum_log_gammas += lgamma(*it);
    }
    logp += sum_log_gammas;
  }
  return logp;
}

std::vector<double> calc_alpha_conditionals(std::vector<double> grid,
					    std::vector<int> counts,
					    bool absolute) {
  int sum_counts = std::accumulate(counts.begin(), counts.end(), 0);
  std::vector<double> logps;
  std::vector<double>::iterator it = grid.begin();
  for(; it!=grid.end(); it++) {
    double alpha = *it;
    double logp = calc_alpha_conditional(counts, alpha, sum_counts, absolute);
    logps.push_back(logp);
  }
  // note: prior distribution must still be added
  return logps;
}

double calc_beta_conditional() {
  // FIXME: implement
  assert(1==0);
  return -1;
}