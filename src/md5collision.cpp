#include <iostream>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <execinfo.h>
#include <openssl/md5.h>
#include "longword.hpp"

using namespace std;

void convert_to_hex(unsigned char*, size_t, char*);
void handler(int);

int main() {
  signal(SIGSEGV, handler);
  int word_length = 10;
  string hash = "092f2ba9f39fbc2876e64d12cd662f72";

  Longword* word = new Longword(word_length);

  for (int i = 0; i < 100000000; i++) {
    // calculate the md5-hash for the current word
    unsigned char md[MD5_DIGEST_LENGTH];
    MD5((unsigned char *) word->word, strlen(word->word), md);

    // convert the hash to hexadecimal representation
    char hex[2 * MD5_DIGEST_LENGTH];
    convert_to_hex(md, MD5_DIGEST_LENGTH, hex);

    // check if the hash equals the given hash
    if (strcmp(hex, hash.c_str()) == 0) {
      cout << "Success: " << word->word << " results in the given hash." << endl;
      break;
    }

    // proceed with the next word
    word->operator ++();
  }

  return 0;
}

void convert_to_hex(unsigned char *data, size_t len, char* hex) {
  char *hex_ptr = hex;

  for (int i = 0; i < len; i++) {
    hex_ptr += sprintf(hex_ptr, "%02x", data[i]);
  }
}

void handler(int sig) {
  void *array[10];
  size_t size;

  // get void*'s for all entries on the stack
  size = backtrace(array, 10);

  // print out all the frames to stderr
  fprintf(stderr, "Error: signal %d:\n", sig);
  backtrace_symbols_fd(array, size, 2);
  exit(1);
}
