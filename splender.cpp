#include "splender.h"

using namespace std;

void init (vector<card> stack_1, vector<card> stack_2, vector<card> stack_3) {}

struct move player_move (struct move m) {
  m.type = 1;
  m.gem[0] = 1;
  m.gem[1] = 1;
  m.gem[2] = 1;
  m.gem[3] = 0;
  m.gem[4] = 0;
  return m;
}
