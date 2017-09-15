#include "hyker/rikskit.hpp"
#include "hyker/log.hpp"

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>
#include <string.h>
#include <thread>

std::string randomString(size_t length, const char* character_set = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") {
    std::srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    auto character_set_length = strlen(character_set);
    std::string text;
    text.reserve(character_set_length);
    for (size_t i = 0; i < length; ++i) {
        text += character_set[std::rand() % character_set_length];
    }
    return text;
}

int main() {
    try {
        using namespace hyker;
        using namespace hyker::riks;

        //Log::setLogConditions(Log::LEVEL_VERBOSE);
        
        // Then, let's generate a UID for you.
        const auto uid = "#hyker-23434t57a9a" + randomString(10);
        
        // Then, give your password.
        const auto password = "guest"; // No way.

        // Then, define your whitelist.
        Whitelist whitelist{[](std::string uid, std::string message_namespace, std::string key_id) -> Future<bool> {
            Future<bool> access_granted;
            std::thread{[access_granted]() mutable {
                // std::cout << "Granting access in ";
                // for (int i = 5; i > 0; --i) {
                //     std::cout << std::to_string(i) << "...";
                //     std::this_thread::sleep_for(std::chrono::seconds{1});
                // }
                // std::cout << "\n\n";
                
                // We are very naïve, we trust everyone.
                access_granted = true;
            }}.detach();

            return access_granted;
        }};

        // Then, define your configurations file. (Optional)
        const auto config = "default.config";
        
        // Finally, create a RIKS kit.
        RiksKit rikskit_1(uid, password, whitelist, config);
        
        // Now, we are ready to begin encrypting! Create a message.
        const Message message("some secret data", "some immutable plaintext", "some mutable plaintext");

        // Define the namespace of the message.
        const auto message_namespace = "Earth 3";

        // Encrypt your message:
        const auto encrypted_message = rikskit_1.encryptMessage(message, message_namespace);

        // DONE! You are ready to do whatever you wish with this data, nothing more needs to be done.
        // But what about decrypting it? Let's start another RIKS kit.
        // Generate another UID.
        const auto uid_2 = "#gamer-1453453abdc4578" + randomString(10);
        
        // Give the password
        const auto password_2 = "hunter2";
        
        // Define another whitelist.
        Whitelist whitelist_2{[](std::string uid, std::string message_namespace, std::string key_id) -> bool {
            // Don't let any Martians read your messages.
            if (message_namespace != "Earth 3") return false;
            
            // Only allow users with an ID starting with #hyker:
            if (uid.find("#hyker") != 0) return false;
            
            // They are good. Give them access to the key.
            return true;
        }};

        // Create your second RIKS kit. (Use default config.)
        RiksKit rikskit_2(uid_2, password_2, whitelist_2);
        
        // NOW! Let's try decrypting the message.
        const Message decrypted_message = rikskit_2.decryptMessage(encrypted_message);
        
        // Extract its precious secrets
        const std::string secret_data    = decrypted_message.secret_data;
        const std::string immutable_data = decrypted_message.immutable_data;
        const std::string mutable_data   = decrypted_message.mutable_data;
        
        std::cout << "Secret data:    " << secret_data    << std::endl;
        std::cout << "Immutable data: " << immutable_data << std::endl;
        std::cout << "Mutable data:   " << mutable_data   << std::endl;

    	while (true) {
                const auto encrypted_message = rikskit_1.encryptMessage({"secret data", "immutable data", "mutable data"}, "namespace");
                const auto decrypted_message = rikskit_2.decryptMessage(encrypted_message).get();

                const std::string secret_data    = decrypted_message.secret_data;
                const std::string immutable_data = decrypted_message.immutable_data;
                const std::string mutable_data   = decrypted_message.mutable_data;

                std::cout << "Secret data:    " << secret_data    << std::endl;
                std::cout << "Immutable data: " << immutable_data << std::endl;
                std::cout << "Mutable data:   " << mutable_data   << std::endl;
    	}
        
        // Now you know the basics. Here are some exercises for you:
        // 
        // - a) Change the namespace you encrypt in. What happens?
        //   b) Change the allowed namespaces in the second rikskit.
        // 
        // - a) Change your user IDs. What happens?
        //   b) Change the allowed user IDs in the second rikskit.
        // 
        // - Encrypt and return a message to the first rikskit, then decrypt it.
        // 
        // - Make the whitelist of the first rikskit more restrictive. 
        // 
        // - Trigger a rekey event. You can do this by doing the following call:
        //       std::string message_namespace = "Earth";
        //       rikskit2.rekey(message_namespace);
    } catch (hyker::Exception& e) {
        std::cout << "Error: " << e.what() << '\n';
    }

}
