#pragma once

#include <eosiolib/asset.hpp>
#include <eosiolib/eosio.hpp>
#include <string>

namespace eoshare {
    using std::string;
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
        string storage_url;
        asset price;
        uint64_t primary_key() const { return content_id; }
        uint64_t by_name() const { return owner.value; }
    };

    typedef eosio::multi_index< "contents"_n, content,
        indexed_by< "name"_n, const_mem_fun<content, uint64_t, &content::by_name>  >
    > contents;
} /// namespace eoshare
