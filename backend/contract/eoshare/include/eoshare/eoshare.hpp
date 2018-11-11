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
    using eosio::symbol;
    using eosio::asset;

    name eoshare_token = "eosharetoken"_n;
    symbol eoshare_symbol = eosio::symbol("EOSHARE", 4);

   class [[eosio::contract("eoshare")]] eoshare : public contract {
        public:
            using contract::contract;
            
            eoshare(name receiver, name code, datastream<const char*> ds) : contract(receiver, code, ds), m_env(receiver, receiver.value) {
                if (m_env.exists() == false) {
                    m_env.set( env(), _self );
                }
            }

            [[eosio::action]]
            void upload(name owner, string artist_name, string content_title, uint8_t content_type, asset price, string storage_uri, bool status);

            [[eosio::action]]
            void modify(name owner, uint64_t content_id, string artist_name, string content_title, uint8_t content_type, asset price, string storage_uri);

            [[eosio::action]]
            void changestatus(name owner, uint64_t content_id, bool status);

            [[eosio::action]]
            void download(name user, uint64_t content_id, string random);

            [[eosio::action]]
            void share(name user, uint64_t content_id);

            [[eosio::action]]
            void transfer(uint64_t sender, uint64_t receiver); //  notify

        private:
            struct [[eosio::table]] env {
                uint64_t current_content_id = 0;
                EOSLIB_SERIALIZE( env, (current_content_id) )
            };

            typedef eosio::singleton< "env"_n, env > env_singleton_t;
            env_singleton_t m_env;

            // taken from eosio.token.hpp
            struct nt_transfer {
                name from;
                name to;
                asset quantity;
                string memo;
            };
    };

} /// namespace eoshare
