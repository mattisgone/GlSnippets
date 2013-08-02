/**
 * Compute Online Mean, Variance, and M2 Statistics
 * This is useful for not having to iterate through an
 * entire data-set to get statistics.
 * @author Matt Owen
 * @since 2013-08-02
 */

#pragma once

class OnlineStatistics {
public:
  stats() : mMean(0.), mM2(0.), mVariance(0.), mNumPoints(0) {}
  /**
   * Return Mean of Data-set
   * @return online variance of data-set
   */
  double mean() {
    return mMean;
  }
  /**
   * Return Variance of Data-set
   * @return online variance of data-set
   */
  double var() {
    return mVariance;
  }
  /**
   * Return Second Moment of Data-set
   * @return online m2 of data-set
   */
  double m2() {
    return mM2;
  }
  /**
   * Update the Online Mean, M2, and Variance Statistics
   * @param x double a number to add to the online mean
   */
  void update(const double x) {
    double delta = x - mMean;
    mNumPoints++;
    mMean += delta/mNumPoints;
    mM2 += delta * (x - mMean);
    mVariance = mM2/(mNumPoints-1);
  }
private:
  double mMean, mM2, mVariance;
  int mNumPoints;
};