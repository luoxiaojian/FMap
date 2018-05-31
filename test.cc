#include "fmap.h"

#include <iostream>
#include <vector>

int main() {

  std::vector<unsigned> oid, gid;
  oid.push_back(1);
  oid.push_back(7);
  oid.push_back(3);
  oid.push_back(18);
  gid.push_back(13);
  gid.push_back(72);
  gid.push_back(35);
  gid.push_back(183);

  FMap<unsigned, unsigned> fm;

  int size = oid.size();

  for(int i = 0; i < size; i++) {
    fm[oid[i]] = gid[i];
  }

  for(int i = 0; i < size; i++) {
    std::cout << i << ": " << oid[i] << " -> " << fm[oid[i]] << std::endl;
  }

  return 0;
}
