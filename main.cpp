#include "hyker/rikskit.hpp"
#include "hyker/util/random.hpp"
#include "hyker/log.hpp"

#include <iostream>
#include <string>

using namespace hyker;

int main() {
    // Tell RIKS to be verbose and log everything.
    Log::setLogConditions(LOG_LEVEL_VERBOSE, LOG_CONTEXT_ALL);
    
    // Then, let's generate a UID for you.
    std::string uid = "#hyker" + (std::string)util::random::generateString(10);
    
    // Then, give your password.
    std::string password = "guest";
    
    // Then, define your whitelist.
    riks::Whitelist whitelist(
        [](std::string uid, std::string message_namespace, std::string key_id) -> bool {
            // We are very naïve, we trust everyone.
            return true;
        },
        [](std::string key_id) {
            // Here we are notified each time we have a new key.
        }
    );
    
    // Then, define your configurations file. (Optional)
    std::string config = "default.config";
    
    // Finally, create a RIKS kit.
    riks::RiksKit rikskit(uid, password, whitelist, config);
    
    // Now, we are ready to begin encrypting! Create a message.
    riks::Message message("some secret data", "some immutable plaintext", "some mutable plaintext");

    // Define the namespace of the message.
    std::string message_namespace = "Earth";
    
    // Encrypt your message:
    auto encrypted_message = rikskit.encryptMessage(message, message_namespace);
    
    // DONE! You are ready to do whatever you wish with this data, nothing more needs to be done.
    // But what about decrypting it? Let's start another RIKS kit.
    
    // Generate another UID.
    std::string uid_2 = "#gamer-" + (std::string)util::random::generateString(10);
    
    // Give the password
    std::string password_2 = "hunter2";
    
    // Define another whitelist.
    riks::Whitelist whitelist_2(
        [](std::string uid, std::string message_namespace, std::string key_id) -> bool {
            // Don't let any Martians read your messages.
            if (message_namespace != "Earth") return false;
            
            // Only allow users with an ID starting with #hyker:
            if (uid.find("#hyker") != 0) return false;
            
            // They are good. Give them access to the key.
            return true;
        },
        [](std::string key_id) {
            // Here we are notified each time we have a new key.
        }
    );

    // Create your second RIKS kit. (Use default config.)
    riks::RiksKit rikskit_2(uid_2, password_2, whitelist);
    
    // NOW! Let's try decrypting the message.
    auto decrypted_message = rikskit_2.decryptMessage(encrypted_message);
    
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
}
