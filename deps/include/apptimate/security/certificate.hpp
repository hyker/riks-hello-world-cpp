#pragma once

#include "apptimate/cryptobox/exception.hpp"

// std
#include <string>
#include <vector>

// Boost.Serialization
#include <boost/serialization/string.hpp>

namespace boost { namespace serialization { class access; } }

namespace apptimate {
	namespace cryptobox {
		class Certificate {
            friend class boost::serialization::access;

        public:
            Certificate();

            /**
             * Creates a certificate from the given ??? encoded string.
             */
            Certificate(const std::string& encoded);

            /**
             * Returns the certificate, as a ??? encoded string.
             *
             * @return The ??? encoded certificate.
             */
            const std::string& getEncoded() const;

            /**
             * Returns the public key of the certificate, as a ??? encoded string.
             *
             * @return The public key of the certificate.
             */
            const std::string& getPublicKey() const;

            /**
             * Returns the alias of the certificate.
             *
             * @return The alias of the certificate.
             */
            const std::string& getAlias() const;

            /**
             * Verifies the certificate chain using this certificate as root certificate.
             *
             * @param certificateChain The certificate chain to verify.
             *
             * @return <b>true</b> if verified successfully.
             */
            bool verifyChain(const std::vector<Certificate>& certificateChain) const;

        protected:
            std::string encoded;
            std::string publicKey;
            std::string alias;

        private:
            void decode(const std::string& encoded);

            template<typename Archive>
            void serialize(Archive& ar, const unsigned version) {
                ar & encoded;
                ar & publicKey;
                ar & alias;
            }
		};
	};
};