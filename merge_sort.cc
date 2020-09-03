#include <vector>
#include <algorithm>
#include <stdio.h>
using namespace std;

class Merge_Sort{
 public:
  typedef vector<int> ARRAY;
  typedef vector<ARRAY> SHARD;

  static bool array_cmp (vector<int> &a, vector<int> &b) { return a[0] < b[0]; }

  ARRAY convert_shard_to_array(SHARD s) {
    ARRAY ret;
    for (auto it = s.begin(); it != s.end(); it++) {
      for (auto array_it = it->begin(); array_it != it->end(); array_it++)
        ret.emplace_back(*array_it);
    }
    return ret;
  }

  ARRAY merge(vector<SHARD> &shards, int begin, int end) {
    if (begin == end)
      return convert_shard_to_array(shards[begin]);

    /* array pending merge */
    ARRAY a,b;
    ARRAY ret;
    if (begin + 1 == end) {
      a = convert_shard_to_array(shards[begin]);
      b = convert_shard_to_array(shards[end]);
    } else {
      int mid = (begin + end) / 2;
      a = merge(shards, begin, mid);
      b = merge(shards, mid+1, end);
    }

    /* merge a,b in ret */
    auto it_a = a.begin();
    auto it_b = b.begin();
    while( it_a != a.end() || it_b != b.end()) {
      if (it_a == a.end() || (it_b != b.end() && *it_b < *it_a)) {
        ret.emplace_back(*it_b);
        it_b++;
      }
      else /* we can't push it_b, so push it_a */
      {
        ret.emplace_back(*it_a);
        it_a++;
      }
    }
    return ret;
  }

  ARRAY merge_sort(vector<SHARD> all_shard) {
    for (auto it = all_shard.begin(); it != all_shard.end(); it++) {
      /* sort array in every shard */
      sort(it->begin(), it->end(), array_cmp);
    } 
    int size = all_shard.size();
    ARRAY ret = merge(all_shard, 0, size-1);
    return ret;
  }

  void test() {
    ARRAY A[5][4];
    A[0][0] = {1,2,3};
    A[0][1] = {105,109};
    A[0][2] = {55,57};
    A[0][3] = {333,555};
    A[1][0] = {3,5};
    A[1][1] = {44,46};
    A[1][2] = {77,101};
    A[1][3] = {222, 333};
    A[2][0] = {1,4,8};
    A[2][1] = {103,106};
    A[2][2] = {156,157};
    A[2][3] = {1333,1555};
    A[3][0] = {13,15};
    A[3][1] = {444,446};
    A[3][2] = {777,1011};
    A[3][3] = {2222, 2333};
    A[4][0] = {333,555};
    A[4][1] = {454,466};
    A[4][2] = {787,1101};
    A[4][3] = {2223, 3333};

    vector<SHARD> IN;
    for (int i = 0; i < 5; i++) {
      SHARD tmp;
      for (int j = 0; j<4; j++) {
        tmp.push_back(A[i][j]);
      }
      IN.push_back(tmp);
    }

    ARRAY result = merge_sort(IN);
    for (auto it = result.begin(); it != result.end(); it++)
      printf("%d ", *it);
    printf("\n");
  }
};

int main() {
  Merge_Sort M;
  M.test();
  return 0;
}
