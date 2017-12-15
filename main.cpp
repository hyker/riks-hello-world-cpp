#include "hyker/rikskit.hpp"
#include "hyker/log.hpp"
#include "hyker/util/random.hpp"

#include <iostream>
#include <string>
#include <thread>

int main() {
    try {
        using namespace hyker;
        using namespace hyker::riks;

        const auto uid = "Mr. ☃ " + util::random_string(10);
        const auto uid_2 = "Beagle boy " + util::random_string(10);
        //const auto uid = "#alice-0004";
        //const auto uid_2 = "#bob-0004";

        //Log::setLogConditions(Log::LEVEL_VERBOSE);
        
        // Then, let's generate a UID for you.
        
        // Then, give your password.
        const auto password = "asdqwe"; // No way.

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
        const auto encrypted_message = rikskit_1.encrypt(message, message_namespace);

        // DONE! You are ready to do whatever you wish with this data, nothing more needs to be done.
        // But what about decrypting it? Let's start another RIKS kit.
        // Generate another UID.
        
        // Give the password
        const auto password_2 = "asdqwe";
        
        // Define another whitelist.
        Whitelist whitelist_2{[](std::string uid, std::string message_namespace, std::string key_id) -> bool {
            // Don't let any Martians read your messages.
            if (message_namespace != "Earth 3") return false;
            
            // Only allow users with an ID starting with #hyker:
            if (uid.find("#hyker") != 0) return false;
            
            // They are good. Give them access to the key.
            return true;
        }};

        // Create your second RIKS kit. (Use custom config.)
        RiksKit rikskit_2(uid_2, password_2, whitelist_2);/*, {
            {"storage_path",                 "../test_data"},
            {"msg_host",                     "dev.msg.hykr.io"},
            {"msg_port",                     1443},
            {"msg_api_key",                  "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"},
            {"kds_host",                     "alpha.kds.hykr.io"},
            {"kds_port",                     8443},
            {"kds_cache_expiration",         -1},
            {"kds_api_key",                  "UNTRUSTED_API_KEY"},
            {"kds_root_certificate",         "root_certificate.pem"},
            {"replay_protector_window_size", 1000},
            {"key_relay_enabled",            false}
        });*/
        
        // NOW! Let's try decrypting the message.
        const Message decrypted_message = rikskit_2.decrypt(encrypted_message);
        for (int i = 0; i < 1; ++i) {
            struct SecretData {
                int a;
                double b;
                bool c;
            };

            SecretData secret_data_struct;
            secret_data_struct.a = 13;
            secret_data_struct.b = 546.123;
            secret_data_struct.c = true;
		
            if (i % (1 * 128) == 0) {
	    	rikskit_1.rekey("namespace2");
            }

            const auto encrypted_message = rikskit_1.encrypt({{&secret_data_struct, sizeof(SecretData)}, "immutable data", "mutable data"}, "namespace2");
            const auto decrypted_message = rikskit_2.decrypt(encrypted_message).get();

            const auto secret_data           = *reinterpret_cast<const SecretData*>(decrypted_message.secret_data.begin());
            const std::string immutable_data = decrypted_message.immutable_data;
            const std::string mutable_data   = decrypted_message.mutable_data;

            //std::cout << '\n';
            //std::cout << "Secret data.a   " << secret_data.a  << '\n';
            //std::cout << "Secret data.b:  " << secret_data.b  << '\n';
            //std::cout << "Secret data.c:  " << secret_data.c  << '\n';
            //std::cout << "Immutable data: " << immutable_data << '\n';
            //std::cout << "Mutable data:   " << mutable_data   << '\n';
            std::cout << encrypted_message.get().c_str() << '\n';

            //std::this_thread::sleep_for(std::chrono::milliseconds(500));
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
