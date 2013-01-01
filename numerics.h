#ifndef GUARD_numerics_h
#define GUARD_numerics_h

#include <vector>
#include "suffstats.h"

const static double LOG_2PI = log(2.0 * M_PI);
const static double HALF_LOG_2PI = .5 * LOG_2PI;
const static double LOG_2 = log(2.0);

int draw_sample_unnormalized(std::vector<double> unorm_logps, double rand_u);

int draw_sample_with_partition(std::vector<double> unorm_logps,
			       double log_partition, double rand_u);

int crp_draw_sample(std::vector<int> counts, int sum_counts, double alpha,
		    double rand_u);

double calc_cluster_crp_logp(double cluster_weight, double sum_weights,
			   double alpha, double data_weight=1);

/* double data_log_probability(std::vector<double> data_values, */
/* 			    std::vector<suffstats<double> > suffstats_v, */
/* 			    std::map<std::string, double> hypers, double alpha); */

/* double cluster_vector_joint(std::vector<double> vector_values, */
/* 			    std::vector<suffstats<double> > suffstats_v, */
/* 			    std::map<std::string, double> hypers, double alpha); */

// FIXME: should move suffstats updates from suffstats to here?

double calc_crp_alpha_conditional(std::vector<int> counts, double alpha,
			      int sum_counts=-1, bool absolute=false);
std::vector<double> calc_crp_alpha_conditionals(std::vector<double> grid,
					    std::vector<int> counts,
					    bool absolute=false);
double calc_beta_conditional();

double calc_continuous_logp(const double count,
			    const double r, const double nu, const double s,
			    const double log_Z_0);

#endif //GUARD_numerics_h
