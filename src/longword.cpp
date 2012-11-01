/*
 * longword.cpp
 *
 *  Created on: 30.10.2012
 *      Author: bene
 */

#include <stdio.h>

#include "longword.hpp"

using namespace std;

Longword::Longword(int size) {
  this->size = size;
  word = new char[size];
  for (int i = 0; i < size; i++)
    word[i] = '\0';
}

Longword::~Longword() {
  delete word;
}

Longword* Longword::operator++() {
  this->word[0]++;
  if (this->word[0] == '\0')
    for (int j = 1; j < this->size; j++) { // TODO: Catch last overflow!
      this->word[j]++;
      if (this->word[j] != '\0')
        break;
    }
  return this;
}

Longword* Longword::operator+(int i) {
  for (int j = 0; j < i; j++)
    this->operator ++();
  return this;
}

string Longword::toString() {
  string ret;
  for (int i=0;i<size;i++) {
    char* cint;
    sprintf(cint, "%i ", word[i]);
    string sint = cint;
    ret += sint;
  }
  return ret;
}
