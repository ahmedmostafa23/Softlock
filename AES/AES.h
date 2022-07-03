#pragma once

#include <iostream>
#include <cstring>

#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/conf.h>

namespace std {
    typedef basic_string<unsigned char> ustring;
}
class AES {

private:
    /* A 256 bit key */
    unsigned char *key = (unsigned char *)"01234567890123456789012345678901";
    /* A 128 bit IV */
    unsigned char *iv = (unsigned char *)"0123456789012345";
    /* The encrypted message*/
    std::ustring encrypted;
    // The decrypted message
    std::ustring decrypted;
    // The length of the encrypted text
    int ciphertext_len;
    // The length of the decrypted text
    int decryptedtext_len;
    // cipher buffer
    unsigned char* ciphertext;
    // buffer for decrypted text
    unsigned char* decryptedtext;
    // the algorithm
    std::string aes_algorithm;

    // aborts if encounters an error
    void handleErrors(void);
    int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
                unsigned char *iv, unsigned char *ciphertext);
    int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
                unsigned char *iv, unsigned char *plaintext);

public:
    AES(const std::string& aes_algorithm): ciphertext_len(0), decryptedtext_len(0), aes_algorithm(aes_algorithm) {}
    ~AES();

    std::string cipher(const std::string& message);
    std::string decipher();
    int print_readable_cipher();
    void print_decrypted();
    void set_aes_algorithm(const std::string& aes_algorithm);
};

