#pragma once

#include <eosiolib/eosio.hpp>
#include <eosiolib/singleton.hpp>

#include <string>

#include <eoshare/content.hpp>

namespace eoshare {
    using std::string;
    using eosio::contract;
    using eosio::datastream;
    using eosio::name;
    using eosio::asset;


   class [[eosio::contract("eoshare")]] eoshare : public contract {
        public:
            using contract::contract;

            eoshare(name receiver, name code, datastream<const char*> ds) : contract(receiver, code, ds), m_env(receiver, receiver.value) {
                if (m_env.exists() == false) {
                    m_env.set( env(), _self );
                }
            }

            [[eosio::action]]
            void upload(name owner, string artist_name, uint64_t content_id, string content_title, uint8_t content_type, asset quantity);

            [[eosio::action]]
            void download(name user, uint64_t content_id);

            [[eosio::action]]
            void share(name user, uint64_t content_id);

            [[eosio::action]]
            void transfer();

        private:
            struct [[eosio::table]] env {
                uint64_t current_content_id = 0;
                EOSLIB_SERIALIZE( env, (current_content_id) )
            };

            typedef eosio::singleton< "env"_n, env > env_singleton_t;
            env_singleton_t m_env;
    };

} /// namespace eoshare
