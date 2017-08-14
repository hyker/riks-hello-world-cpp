#include "hyker/rikskit.hpp"

#include "hyker/util/random.hpp"
#include "hyker/log.hpp"

#include <chrono>
#include <iostream>
#include <string>
#include <thread>

int main() {
    try {
        using namespace hyker;
        using namespace hyker::riks;

        // Then, let's generate a UID for you.
        auto uid = "#hyker-" + (std::string)util::random::generateString(10);
        
        // Then, give your password.
        auto password = "guest"; // No way.
        
        // Then, define your whitelist.
        Whitelist whitelist = [](std::string uid, std::string message_namespace, std::string key_id) -> Future<bool> {
            Future<bool> access_granted;
            std::thread{[access_granted]() {
                std::cout << "Granting access in ";
                for (int i = 5; i > 0; --i) {
                    std::cout << std::to_string(i) << "...";
                    std::this_thread::sleep_for(std::chrono::seconds{1});
                }
                std::cout << "\n\n";
                access_granted = true;
            }}.detach();
            // We are very naïve, we trust everyone.
            return access_granted;
        };

        // Then, define your configurations file. (Optional)
        auto config = "default.config";
        
        // Finally, create a RIKS kit.
        RiksKit rikskit(uid.c_str(), password, whitelist, config);
        
        // Now, we are ready to begin encrypting! Create a message.
        Message message("some secret data", "some immutable plaintext", "some mutable plaintext");

        // Define the namespace of the message.
        auto message_namespace = "Earth";
        
        // Encrypt your message:
        auto encrypted_message = rikskit.encryptMessage(message, message_namespace);

        // DONE! You are ready to do whatever you wish with this data, nothing more needs to be done.
        // But what about decrypting it? Let's start another RIKS kit.
        
        // Generate another UID.
        auto uid_2 = "#gamer-" + (std::string)util::random::generateString(10);
        
        // Give the password
        auto password_2 = "hunter2";
        
        // Define another whitelist.
        Whitelist whitelist_2 = [](std::string uid, std::string message_namespace, std::string key_id) -> bool {
            // Don't let any Martians read your messages.
            if (message_namespace != "Earth") return false;
            
            // Only allow users with an ID starting with #hyker:
            if (uid.find("#hyker") != 0) return false;
            
            // They are good. Give them access to the key.
            return true;
        };

        // Create your second RIKS kit. (Use default config.)
        RiksKit rikskit_2(uid_2.c_str(), password_2, whitelist);
        
        // NOW! Let's try decrypting the message.
        Message decrypted_message = rikskit_2.decryptMessage(encrypted_message);
        
        // Extract its precious secrets
        std::string secret_data    = decrypted_message.secret_data;
        std::string immutable_data = decrypted_message.immutable_data;
        std::string mutable_data   = decrypted_message.mutable_data;
        
        std::cout << "Secret data:    " << secret_data    << std::endl;
        std::cout << "Immutable data: " << immutable_data << std::endl;
        std::cout << "Mutable data:   " << mutable_data   << std::endl;
        
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
        std::cout << e.what() << '\n';
    }

}
