# sagakar-clang
The encryption program is a stream cipher, meaning the input is encrypted by a stream of bytes from a PRNG seeded with the key (which in my implementation is first hashed). The exact same process is used to encrypt and decrypt a message, so the encryption program also works to decrypt files. To avoid making two near-identical programs, I included the decryption mode as an optional flag in the encryption instead (it really just changes the name of the output file).

Usage: ./encrypt \[-d] &lt;filename> &lt;key>
