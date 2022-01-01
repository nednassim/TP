#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/x509.h>
 
int main() {
  unsigned char result[SHA_DIGEST_LENGTH];
  const char *string = "Rosetta Code";
 
  SHA1(string, strlen(string), result);
 
  for(int i = 0; i < SHA_DIGEST_LENGTH; i++)
    printf("%02x%c", result[i], i < (SHA_DIGEST_LENGTH-1) ? '-' : '\n');
 
  return EXIT_SUCCESS;
}
