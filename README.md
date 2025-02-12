# dauth
 Based on iotauth
## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Introduction
`dauth` is a C++ project based on `iotauth` designed to provide robust authentication mechanisms for IoT devices.

## Features
- Secure authentication for IoT devices
- Lightweight and efficient
- Easy to integrate with existing systems
- Integrating of WebServices [netpp](https://github.com/lsmon/netpp)
- Integrating custom [json](https://github.com/lsmon/json) reduced to the minimal functionality.
- Integrating custom [logging](https://github.com/lsmon/logpp) taking inspiration from java sl4j
- Integrating custom [cache](https://github.com/lsmon/cache) making a simple light caching that can use LRU, LFU, FIFO
- Integrating custom [scheduler](https://github.com/lsmon/scheduler)


## Installation
To install `dauth`, follow these steps:
1. Clone the repository:
    ```sh
    git clone https://github.com/lsmon/dauth.git
    ```
2. Navigate to the project directory:
    ```sh
    cd dauth
    ```
3. Build the project:
    ```sh
    mkdir build
    cd build
    cmake ../
    make
    ```

## Usage
To use `dauth` in your project, include the necessary headers and link against the compiled library. Example:
```cpp
#include "dauth.h"

int main() {
    /// ENCRYPT | DECRYPT
    std::unique_ptr<AuthCrypto> authCrypto = std::make_unique<AuthCrypto>();
    authCrypto->generateKeyPair("");

    byte* data = StringEncoder::stringToBytes(originalText);
    byte* encryptedData = nullptr;
    byte* decryptedData = nullptr;

    std::cout << "Original length: " << originalText.size() << std::endl;
    size_t encryptedSize = authCrypto->encrypt(data, encryptedData);
    size_t decryptedSize = authCrypto->decrypt(encryptedData, encryptedSize, decryptedData);

    std::string decryptedText = StringEncoder::bytesToString(decryptedData, decryptedSize);

    std::cout << "Original text: " << originalText << std::endl;
    std::cout << "Encrypted text: " << StringEncoder::bytesToString(encryptedData, encryptedSize) << std::endl;
    std::cout << "Decrypted text: " << decryptedText << std::endl;

    assert(originalText == decryptedText);
    std::cout << "Test passed: Decrypted text matches the original text." << std::endl;

    // Clean up
    delete[] data;
    delete[] encryptedData;
    delete[] decryptedData;

    /// HASHING
    byte* data = StringEncoder::stringToBytes(originalText);
    byte* md5Hash = Hash::md5(data);
    byte* sha1Hash = Hash::sha1(data);
    byte* sha256Hash = Hash::sha256(data);

    std::cout << "MD5 hash: " << StringEncoder::bytesToString(md5Hash, EVP_MAX_MD_SIZE) << std::endl;
    std::cout << "SHA1 hash: " << StringEncoder::bytesToString(sha1Hash, SHA_DIGEST_LENGTH) << std::endl;
    std::cout << "SHA256 hash: " << StringEncoder::bytesToString(sha256Hash, SHA256_DIGEST_LENGTH) << std::endl;

    delete[] md5Hash;
    delete[] sha1Hash;
    delete[] sha256Hash;

    return EXIT_SUCCESS;
}
```

## Contributing
Contributions are welcome! Please fork the repository and submit a pull request.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.