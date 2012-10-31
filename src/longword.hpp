/*
 * longword.hpp
 *
 *  Created on: 30.10.2012
 *      Author: bene
 */

#ifndef LONGWORD_HPP_
#define LONGWORD_HPP_

using namespace std;

class Longword {
private:
  int size;
public:
  char* word;
  Longword(int);
  ~Longword();
  Longword* operator ++();
  Longword* operator +(int);
};


#endif /* LONGWORD_HPP_ */
