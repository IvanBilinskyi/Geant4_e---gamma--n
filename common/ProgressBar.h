#pragma once

#include <indicators/progress_bar.hpp>

class ProgressBar
{
  public:
    ProgressBar(int nEntries = 100);
    void Tick(int iEntry);
    void Complete();
  private:
    indicators::ProgressBar bar;
    int nEntries;
};
