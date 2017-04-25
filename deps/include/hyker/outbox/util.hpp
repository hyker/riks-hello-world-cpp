#pragma once

// Toolbox++
#include "hyker/json_array.hpp"

// std
#include <chrono>
#include <string>

namespace hyker {
    namespace outbox {
        class Util {
        public:
            /**
             * Creates a unique string.
             *
             * @return A randomized unique string.
             */
            static std::string unique();

            /**
             * Creates a unique tag.
             *
             * @return A randomized unique tag.
             */
            static std::string createUniqueTag();

            /**
             * Hashes the string using the given key if it starts with a hashtag.
             *
             * @param string The string to be hashed.
             * @param key    The key to use.
             */
            static std::string hashIfTag(const std::string & string, const std::string & key);

            /**
             * Encodes and signs the object, then creates a HTTP request to the given host.
             *
             * @param object The object.
             * @param pblc   The public key.
             * @param prvt   The private key.
             * @param host   The host.
             */
            static std::string renderHTTPRequest(const Values     & object,
                                                 const std::string & pblc,
                                                 const std::string & prvt,
                                                 const std::string & host);

            /**
             * Base64 encodes the string. Replaces '+', '/', and '=' with '-', '_', and '.', respectively.
             *
             * @param bytes The data to be encoded.
             *
             * @return The encoded data.
             */
            static std::string base64Encode(std::string bytes, bool replace = false);

            /**
             * Base64 decodes the string. Replaces '-', '_', and '.' with '+', '/', and '=', respectively.
             *
             * @param bytes The data to be decoded.
             *
             * @return The decoded data.
             */
            static std::string base64Decode(std::string bytes, bool replace = false);

            /**
             * Hashes a string using a given key, using HMACSHA1.
             *
             * @param bytes The string to be hashed.
             * @param key   The key to be used.
             *
             * @return The hashed string.
             */
            static std::string HMACSHA1(std::string bytes, std::string key);

            /**
             * Peeks at the body of the given data.
             *
             * @param bytes The data.
             *
             * @return The body.
             */
            static std::string peekBody(std::string bytes);

            /**
             *
             *
             * @param bytes The data.
             * @param prvt  The key to be used.
             *
             * @return <b>true</b> if successful.
             */
            static bool auth(std::string bytes, std::string prvt);

            /**
             * Encodes a Values.
             *
             * @param object The object to be encoded.
             *
             * @return The encoded data.
             */
            static std::string encode(const Values & object);

            /**
             * Decodes a string.
             *
             * @param bytes The encoded data.
             *
             * @return The decoded object.
             */
            static Values decode(const std::string & bytes);

            /**
             * Converts a string from PEM to DER encoding.
             *
             * @param pem The PEM encoded string.
             *
             * @return The DER encoded string.
             */
            static std::string fromPEMtoDER(const std::string& pem);

            /**
             *
             * @param num
             *
             * @return
             */
            static std::string pack(long num);

            /**
             *
             * @param str
             *
             * @return
             */
            static long unpack(const std::string& str);

            /**
             * Retrieves the packet length of the data.
             *
             * @param bytes The data from which to retrieve the packet length.
             *
             * @return The packet length.
             */
            static int getPacketLength(const std::string & bytes);

            /**
             * Retrieves the content length of the data.
             *
             * @param bytes The data from which to retrieve the content length.
             *
             * @return The content length.
             */
            static int getContentLength(std::string bytes);

            /**
             * Returns the index of the end of the chuncked transfer encoding.
             *
             * @param bytes The data.
             *
             * @return The index.
             */
            static int getEndOfChunkedTransferEncoding(const std::string & bytes);

            static std::string decodeChunkedTransferEncoding(std::string str);

            /**
             * Decrypts a Values from a packet.
             *
             * @param bytes   The data.
             * @param prvt    The private key.
             * @param message The target Values.
             *
             * @return <b>true</b> if successful.
             */
            static bool fromPacket(const std::string & bytes,
                                   const std::string & prvt,
                                   Values     & message);

            /**
             * Encrypts a Values to a packet.
             *
             * @param object The Values.
             * @param pblc   The public key.
             * @param prvt   The private key.
             *
             * @return The encrypted data.
             */
            static std::string toPacket(const Values     & object,
                                        const std::string & pblc,
                                        const std::string & prvt);

            /**
             * Adds meta information to the data.
             *
             * @param bytes The data
             *
             * @return The data with the added meta information.
             */
            static std::string putMetaInfo(const std::string & bytes);

            /**
             * Strips the meta information from the data.
             *
             * @param bytes The data.
             *
             * @return The stripped data.
             */
            static std::string stripMetaInfo(const std::string & bytes);

            /**
             * Strips the headers from the data.
             *
             * @param bytes The data.
             *
             * @return The stripped headers.
             */
            static std::string stripHeaders(const std::string & bytes);

            /**
             * Adds a signature to the data.
             *
             * @param bytes The data.
             * @param pblc  The public key.
             * @param prvt  The private key.
             *
             * @return The data with the added signature.
             */
            static std::string sign(std::string bytes, const std::string & pblc, const std::string & prvt);

            /**
             * Removes all trailing and leading whitespace from the string
             *
             * @param s The string to trim.
             *
             * @return The trimmed string.
             */
            static std::string trim(std::string s);

            /**
             * Returns the current UNIX time in milliseconds.
             *
             * @return The UNIX time.
             */
            static std::chrono::milliseconds currentTimeMillis();

            /**
             * Checks if the string is a valid API key.
             *
             * @param key The string to check.
             *
             * @return <b>true</b> if valid API key.
             */
            static bool isAPIkey (const std::string & key);

            /**
             * Checks if the string is a valid tag.
             *
             * @param tag The string to check.
             *
             * @return <b>true</b> if valid tag.
             */
            static bool isTag(const std::string & tag);

            /**
             * Checks if the string is a valid user ID.
             *
             * @param uid The string to check.
             *
             * @return <b>true</b> if valid user ID.
             */
            static bool isUID(const std::string & uid);

            /**
             * Checks if the string is a valid keyword.
             *
             * @param keyword The string to check.
             *
             * @return <b>true</b> if valid keyword.
             */
            static bool isKeyword(const std::string & keyword);

            /**
             * Checks if the string is a valid host.
             *
             * @param host The string to check.
             *
             * @return <b>true</b> if valid host.
             */
            static bool isHost(const std::string & host);

            /**
             * Checks if the integer is a valid port.
             *
             * @param port The integer to check.
             *
             * @return <b>true</b> if valid port.
             */
            static bool isPort(int port);
        };
    }
}