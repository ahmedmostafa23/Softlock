#include "AES.h"

AES::~AES() {
    // deleting ciphertext
    if (ciphertext_len == 1) {
        delete ciphertext;
        ciphertext = nullptr;
    } else if (ciphertext_len > 1) {
        delete[] ciphertext;
    }
    ciphertext = nullptr;

    // deleting the key
    delete key;
    
    // deleting the iv
    delete iv;
    
    // deleting the decrypted text
    if (decryptedtext_len == 1) {
        delete decryptedtext;
        decryptedtext = nullptr;
    } else if (decryptedtext_len > 1) {
        delete[] decryptedtext;
    }
    decryptedtext = nullptr;
}

void AES::set_aes_algorithm(const std::string& aes_algorithm) {
    this->aes_algorithm = aes_algorithm;
}

std::string AES::cipher(const std::string& message) {
    // Message to be encrypted
    unsigned char *plaintext = (unsigned char *) message.data();

    /* Buffer for ciphertext. Ensure the buffer is long enough for the algorithm & message.
     * Free the memory every time you use a new buffer */
    if (ciphertext_len == 1) {
        delete ciphertext;
        ciphertext = nullptr;
    } else if (ciphertext_len > 1) {
        delete[] ciphertext;
    }
    ciphertext = nullptr;
    ciphertext = new unsigned char[message.length() * 10];

    /* Buffer for decrypted text.
     * Free the memory each time you start over to avoid a leak */
    if (decryptedtext_len == 1) {
        delete decryptedtext;
        decryptedtext = nullptr;
    } else if (decryptedtext_len > 1) {
        delete[] decryptedtext;
    }
    decryptedtext = nullptr;
    decryptedtext = new unsigned char[message.length() * 10];

    // The encryption.
    ciphertext_len = encrypt(plaintext, strlen((char *) plaintext), key, iv, ciphertext);

    // storing the encrypted message in a class attribute
    encrypted = ciphertext;

    return std::string(reinterpret_cast<char*>(encrypted.data()));
}

std::string AES::decipher() {
    // Decryption
    decryptedtext_len = decrypt(ciphertext, ciphertext_len, key, iv,
                                decryptedtext);

    // Add an end of string character for printable text.
    decryptedtext[decryptedtext_len] = '\0';

    // assigns the decrypted text to a class attribute
    decrypted = decryptedtext;

    return std::string(reinterpret_cast<char*>(decrypted.data()));
}

void AES::print_decrypted() {
    printf("%s\n", decryptedtext);
}

int AES::print_readable_cipher() {
    return BIO_dump_fp (stdout, (const char *)encrypted.data(), ciphertext_len);
}

void AES::handleErrors(void)
{
    ERR_print_errors_fp(stderr);
    abort();
}

int AES::encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
            unsigned char *iv, unsigned char *ciphertext) {
    EVP_CIPHER_CTX *ctx;

    int len;

    int ciphertext_len;

    /* Create and initialise the context */
    if (!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();

    /*
     * Initialise the encryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 256 bit AES (i.e. a 256 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits
     */

    decltype(EVP_aes_128_ecb()) aes_argument;

    if (aes_algorithm == "AES") {
        aes_argument = EVP_aes_128_ecb();
    }
    else if (aes_algorithm == "AES-256") {
        aes_argument = EVP_aes_256_ecb();
    }
    else if (aes_algorithm == "AES-CBC") {
        aes_argument = EVP_aes_128_cbc();
    }

    if (1 != EVP_EncryptInit_ex(ctx, aes_argument, NULL, key, iv))
        handleErrors();

    /*
     * Provide the message to be encrypted, and obtain the encrypted output.
     * EVP_EncryptUpdate can be called multiple times if necessary
     */
    if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
        handleErrors();
    ciphertext_len = len;

    /*
     * Finalise the encryption. Further ciphertext bytes may be written at
     * this stage.
     */
    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
        handleErrors();
    ciphertext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return ciphertext_len;
}

int AES::decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
            unsigned char *iv, unsigned char *plaintext) {
    EVP_CIPHER_CTX *ctx;

    int len;

    int plaintext_len;

    /* Create and initialise the context */
    if (!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();

    /*
     * Initialise the decryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 256 bit AES (i.e. a 256 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits
     */

    decltype(EVP_aes_128_ecb()) aes_argument;

    if (aes_algorithm == "AES") {
        aes_argument = EVP_aes_128_ecb();
    }
    else if (aes_algorithm == "AES-256") {
        aes_argument = EVP_aes_256_ecb();
    }
    else if (aes_algorithm == "AES-CBC") {
        aes_argument = EVP_aes_128_cbc();
    }

    if (1 != EVP_DecryptInit_ex(ctx, aes_argument, NULL, key, iv))
        handleErrors();

    /*
     * Provide the message to be decrypted, and obtain the plaintext output.
     * EVP_DecryptUpdate can be called multiple times if necessary.
     */
    if (1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
        handleErrors();
    plaintext_len = len;

    /*
     * Finalise the decryption. Further plaintext bytes may be written at
     * this stage.
     */
    if (1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len))
        handleErrors();
    plaintext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return plaintext_len;
}
