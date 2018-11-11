#pragma once

#include <eosiolib/asset.hpp>
#include <eosiolib/eosio.hpp>
#include <string>
#include <vector>

namespace eoshare {
    using std::string;
    using std::vector;
    using eosio::name;
    using eosio::asset;
    using eosio::indexed_by;
    using eosio::const_mem_fun;

    struct [[eosio::table, eosio::contract("eoshare")]] content {
        uint64_t content_id;
        name owner;
        string artist_name;
        string content_title;
        uint8_t content_type;
        string storage_uri;
        asset price;
        bool status;
        uint64_t primary_key() const { return content_id; }
        uint64_t by_name() const { return owner.value; }
    };
    typedef eosio::multi_index< "contents"_n, content,
        indexed_by< "name"_n, const_mem_fun<content, uint64_t, &content::by_name>  >
    > content_table;

    struct [[eosio::table, eosio::contract("eoshare")]] purchase {
        name owner;
        vector<uint64_t> content_ids;
        uint64_t primary_key() const { return owner.value; }
    };
    typedef eosio::multi_index< "purchases"_n, purchase> purchase_table;

    struct [[eosio::table, eosio::contract("eoshare")]] seed {
        uint64_t content_id;
        vector<name> names;
        uint64_t primary_key() const { return content_id; }
    };
    typedef eosio::multi_index< "seeds"_n, seed> seed_table;
} /// namespace eoshare
