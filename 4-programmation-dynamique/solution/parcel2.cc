#include "parcel2.h"

#include <algorithm>

vector<int> OptimalParcels(const vector<int>& gain) {
  vector<int> max_gain(gain.size() + 1, 0);
  vector<bool> pick(gain.size(), false);
  for (int i = 0; i < gain.size(); ++i) {
    int gpick = gain[i] + (i < 2 ? 0 : max_gain[i - 2]);
    int gnopick = i < 1 ? 0 : max_gain[i - 1];
    pick[i] = gpick > gnopick;
    max_gain[i] = max(gpick, gnopick);
  }
  vector<int> picked;
  int i = gain.size() - 1;
  while (i >= 0) {
    if (pick[i]) {
      picked.push_back(i);
      i -= 2;
    } else {
      i--;
    }
  }
  std::reverse(picked.begin(), picked.end());
  return picked;
}

