//
//  AudioMetrics.h
//  LoadVideoApp
//
//  Created by Matthew Owen on 8/14/13.
//
//

#pragma once

using namespace cinder;

class AudioMetrics {
public:
  
  // Types of metrics to compute
  enum AUDIO_METRIC { METRIC_QUADRATICFFTAVG, METRIC_LOGARYTHMICFFTAVG, METRIC_FFTAVG, METRIC_VOLUME };
  
  // Create the class
  AudioMetrics() : mBandCount(512) {};
  void update(float *fftRef, uint16_t bandCount);
  void enable(AUDIO_METRIC metric);
  void disable(AUDIO_METRIC metric);
  float get(AUDIO_METRIC metric);
  
  std::vector<float> getAveragedData() {
    return mAveragedFft.left;
  }
  
  int getBandCount() {
    return mBandCount;
  }
 
private:
  void quadraticFftAverage(bool normalize);
  void logarithmicFftAverage(bool normalize);
  float *mFftRef;
  int mBandCount;
  
  struct AveragedFftDataChannels {
    std::vector<float> left;
    std::vector<float> right;
  } mAveragedFft;
  
  enum FftAverageMode {
		fftQuadraticAverage,
		fftLogarithmicAverage
	} mFftAverageMode;
};

void AudioMetrics::update(float *fftRef, uint16_t bandCount) {
  mBandCount = bandCount;
  mFftRef = fftRef;
  //
  quadraticFftAverage(true);
}

/**
 * Compute Quadratic Average of FTT
 * Computer the Quadratic Average of the FFT and store inside the mAveragedFft variable.
 */
void AudioMetrics::quadraticFftAverage(bool normalize = true) {
  struct FftBandsChannels {
    float *left;
    float *right;
  } bands = {
    mFftRef,
    mFftRef
  };
  
  if (!bands.left || !bands.right)
    return;
  mAveragedFft.left.clear();
  mAveragedFft.right.clear();
  
  // Inspired by:
  // https://github.com/kineme/AudioTools/blob/master/AudioToolsFFT.m
  
  int lowerFrequency = 1, upperFrequency;
  int k;
  struct SumChannels {
    float left;
    float right;
  } sum;
  bool done = false;
  int i = 0;
  while (!done) {
    upperFrequency = lowerFrequency + i;
    sum.left = 0.0f;
    sum.right = 0.0f;
    if (upperFrequency >= mBandCount/2 )
    {
      upperFrequency = mBandCount/2-1;
      done = true;
    }
    for (k = lowerFrequency; k <= upperFrequency; ++k)
    {
      sum.left += bands.left[k];
      sum.right += bands.right[k];
    }
    sum.left /= (float)(upperFrequency - lowerFrequency + 1);
    sum.right /= (float)(upperFrequency - lowerFrequency + 1);
    sum.left *= i * 2.0f + 1.0f;
    sum.right *= i * 2.0f + 1.0f;
    mAveragedFft.left.push_back(sum.left);
    mAveragedFft.right.push_back(sum.right);
    lowerFrequency = upperFrequency;
    ++i;
  }
}

/**
 * Compute Logarithmic Average of FTT
 *
 */
void AudioMetrics::logarithmicFftAverage(bool normalize = false) {
  struct FftBandsChannels {
    float *left;
    float *right;
  } bands = {
    mFftRef,
    mFftRef
  };
  if (!bands.left || !bands.right) return;
  mAveragedFft.left.clear();
  mAveragedFft.right.clear();
  
  // Inspired by:
  // https://github.com/kineme/AudioTools/blob/master/AudioToolsFFT.m
  
  const float log2BandCount = log2f(mBandCount);
  int numBuckets = log2BandCount;
  int lowerFrequency, upperFrequency;
  int k;
  struct SumChannels {
    float left;
    float right;
  } sum;
  for (int i = 0; i < numBuckets; ++i)
  {
    lowerFrequency = (mBandCount/2) / powf(2.0f, log2BandCount-i  )+1;
    upperFrequency = (mBandCount/2) / powf(2.0f, log2BandCount-i-1)+1;
    sum.left = 0.0f;
    sum.right = 0.0f;
    if (upperFrequency >= mBandCount/2) upperFrequency = mBandCount/2-1;
    for (k = lowerFrequency; k <= upperFrequency; ++k)
    {
      sum.left += bands.left[k];
      sum.right += bands.right[k];
    }
    sum.left /= (float)(upperFrequency - lowerFrequency + 1);
    sum.right /= (float)(upperFrequency - lowerFrequency + 1);
    sum.left *= powf(i, 1.5f) + 1.0f;
    sum.right *= powf(i, 1.5f) + 1.0f;
    mAveragedFft.left.push_back(sum.left);
    mAveragedFft.right.push_back(sum.right);
  }
}
