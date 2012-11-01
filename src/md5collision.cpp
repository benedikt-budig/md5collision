#include <iostream>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <execinfo.h>
#include <openssl/md5.h>
# include <omp.h>
#include "longword.hpp"

using namespace std;

void convert_to_hex(unsigned char*, size_t, char*);
void handler(int);

int main() {
  signal(SIGSEGV, handler);
  int word_length = 10;
  //string hash = "092f2ba9f39fbc2876e64d12cd662f72";
  string hash = "6887d7394c63f34fec2aac18dc953c5c";
  bool stop = false;
  Longword* word;

  #pragma omp parallel private(word)
  {
  int num_threads = omp_get_num_threads();
  bool first = true;
  for (int i = 0; i < 10000000000000; i++) {
    if (stop)
      break;

    if (first) {
      word = new Longword(word_length);
      word->operator +(omp_get_thread_num());
      first = false;
    }

    //printf("thread %i: %i\n", omp_get_thread_num(), word->word[0]);

    // calculate the md5-hash for the current word
    unsigned char md[MD5_DIGEST_LENGTH];
    MD5((unsigned char *) word->word, strlen(word->word), md);

    // convert the hash to hexadecimal representation
    char hex[2 * MD5_DIGEST_LENGTH];
    convert_to_hex(md, MD5_DIGEST_LENGTH, hex);

    // check if the hash equals the given hash
    if (strcmp(hex, hash.c_str()) == 0) {
      cout << "Success: " << word->word << " results in the given hash.,";
      stop = true;
    }

    // proceed with the next word
    word->operator+(num_threads);
  }
  }
  return 0;
}

void convert_to_hex(unsigned char *data, size_t len, char* hex) {
  char *hex_ptr = hex;

  for (unsigned int i = 0; i < len; i++) {
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
