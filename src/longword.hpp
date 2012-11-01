/*
 * longword.hpp
 *
 *  Created on: 30.10.2012
 *      Author: bene
 */

#ifndef LONGWORD_HPP_
#define LONGWORD_HPP_

#include <string>

using namespace std;

class Longword {
private:
  int size;
public:
  char* word;
  Longword(int);
  ~Longword();
  Longword* operator++();
  Longword* operator+(int);
  string toString();
};


#endif /* LONGWORD_HPP_ */
