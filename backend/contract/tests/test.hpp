#include <boost/test/unit_test.hpp>

#include <eosio/testing/tester.hpp>
#include <eosio/chain/abi_serializer.hpp>
#include <eosio/chain/wast_to_wasm.hpp>

#include <fc/variant_object.hpp>

#include <Runtime/Runtime.h>

#include "contracts.hpp"

using namespace eosio::testing;
using namespace eosio;
using namespace eosio::chain;
using namespace eosio::testing;
using namespace fc;

using mvo = fc::mutable_variant_object;

struct content_t {
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
FC_REFLECT( content_t, (content_id)(owner)(artist_name)(content_title)(content_type)(storage_uri)(price)(status) );

struct purchase_t {
    name owner;
    vector<uint64_t> content_ids;
    uint64_t primary_key() const { return owner.value; }
};
FC_REFLECT( purchase_t, (owner)(content_ids));

struct seed_t {
    uint64_t content_id;
    vector<name> names;
    uint64_t primary_key() const { return content_id; }
};
FC_REFLECT(seed_t, (content_id)(names) );