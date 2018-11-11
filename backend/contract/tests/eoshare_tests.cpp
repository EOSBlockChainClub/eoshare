#include <boost/test/unit_test.hpp>
#include <eosio/testing/tester.hpp>
#include <eosio/chain/abi_serializer.hpp>

#include "Runtime/Runtime.h"

#include <fc/variant_object.hpp>

#include "contracts.hpp"
#include "test.hpp"

using namespace eosio::testing;
using namespace eosio;
using namespace eosio::chain;
using namespace eosio::testing;
using namespace fc;
using namespace std;

using mvo = fc::mutable_variant_object;

class eoshare_tester : public tester {
public:
    eoshare_tester() {
        produce_blocks( 2 );

        create_accounts( { N(artist1), N(artist2), N(user1), N(user2), N(user3), N(eosharetoken), N(eoshareagent)} );
        produce_blocks( 2 );

        set_code( N(eosharetoken), contracts::token_wasm() );
        set_abi( N(eosharetoken), contracts::token_abi().data() );

        set_code( N(eoshareagent), contracts::eoshare_wasm() );
        set_abi( N(eoshareagent), contracts::eoshare_abi().data() );

        produce_blocks();

        init_abi_ser(abi_ser_token, N(eosharetoken));
        init_abi_ser(abi_ser_agent, N(eoshareagent));

        auto token = create( N(eosharetoken), asset::from_string("100000.0000 EOSHARE"));
        produce_blocks(1);
        issue( N(eosharetoken), N(eosharetoken), asset::from_string("1000.0000 EOSHARE"), "test" );

        push_action( N(eosharetoken), N(transfer), N(eosharetoken), mvo()
            ("from", "eosharetoken") 
            ("to", "user1") 
            ("quantity", "20.0000 EOSHARE")
            ("memo", "test")
        );

        push_action( N(eosharetoken), N(transfer), N(eosharetoken), mvo()
            ("from", "eosharetoken") 
            ("to", "user2") 
            ("quantity", "20.0000 EOSHARE")
            ("memo", "test")
        );

        push_action( N(eosharetoken), N(transfer), N(eosharetoken), mvo()
            ("from", "eosharetoken") 
            ("to", "user3") 
            ("quantity", "20.0000 EOSHARE")
            ("memo", "test")
        );
    }

    void init_abi_ser(abi_serializer& abi_ser, account_name name) {
        const auto& accnt = control->db().get<account_object,by_name>( name );
        abi_def abi;
        // BOOST_REQUIRE_EQUAL(abi_serializer::to_abi(accnt.abi, abi), true);
        abi_serializer::to_abi(accnt.abi, abi);
        abi_ser.set_abi(abi, abi_serializer_max_time);
    }

    bool get_content(content_t& content, uint64_t content_id) {
        return get_table_entry(content, N(eoshareagent), N(eoshareagent), N(contents), content_id);
    }

    bool get_purchase(purchase_t& purchase, account_name name) {
        return get_table_entry(purchase, N(eoshareagent), N(eoshareagent), N(purchases), name);
    }

   bool get_seed(seed_t& seed, uint64_t content_id) {
        return get_table_entry(seed, N(eoshareagent), N(eoshareagent), N(seeds), content_id);
    }
    transaction_trace_ptr create( account_name issuer, asset maximum_supply ) {
        return base_tester::push_action( N(eosharetoken), N(create), N(eosharetoken), mvo()
           ( "issuer", issuer)
           ( "maximum_supply", maximum_supply)
        );
    }

    transaction_trace_ptr issue( account_name issuer, account_name to, asset quantity, string memo ) {
        return base_tester::push_action( issuer, N(issue), issuer, mvo()
           ( "to", to)
           ( "quantity", quantity)
           ( "memo", memo)
        );
    }

    transaction_trace_ptr transfer( account_name from,
                  account_name to,
                  asset        quantity,
                  string       memo ) {
        return base_tester::push_action( from, N(transfer), from, mvo()
            ( "from", from)
            ( "to", to)
            ( "quantity", quantity)
            ( "memo", memo)
        );
    }

   abi_serializer abi_ser_token;
   abi_serializer abi_ser_agent;
};

BOOST_AUTO_TEST_SUITE(eoshare_tests)

BOOST_FIXTURE_TEST_CASE( upload_tests, eoshare_tester ) try {
    push_action( N(eoshareagent), N(upload), N(artist1), mvo()
        ("owner", "artist1") 
        ("artist_name", "artest1-display")
        ("content_title", "content-display")
        ("content_type", 1)
        ("price", "1.0000 EOSHARE")
        ("storage_uri", "/xxx/yyy")
        ("status", false)
    );
    produce_blocks(1);

    push_action( N(eoshareagent), N(upload), N(artist1), mvo()
        ("owner", "artist1") 
        ("artist_name", "artest1-display")
        ("content_title", "content2-display")
        ("content_type", 1)
        ("price", "2.0000 EOSHARE")
        ("storage_uri", "/xxx/yyy")
        ("status", false)
    );

    content_t content;
    get_content(content, 1);

    BOOST_TEST_MESSAGE( fc::json::to_pretty_string(content) );
} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( modify_tests, eoshare_tester ) try {
    push_action( N(eoshareagent), N(upload), N(artist1), mvo()
        ("owner", "artist1") 
        ("artist_name", "artest1-display")
        ("content_title", "content-display")
        ("content_type", 1)
        ("price", "1.0000 EOSHARE")
        ("storage_uri", "/xxx/yyy")
        ("status", false)
    );
    produce_blocks(1);

    push_action( N(eoshareagent), N(upload), N(artist1), mvo()
        ("owner", "artist1") 
        ("artist_name", "artest1-display")
        ("content_title", "content2-display")
        ("content_type", 1)
        ("price", "2.0000 EOSHARE")
        ("storage_uri", "/xxx/yyy")
        ("status", false)
    );
    produce_blocks(1);

    push_action( N(eoshareagent), N(upload), N(artist1), mvo()
        ("owner", "artist1") 
        ("artist_name", "artest1-display")
        ("content_title", "content3-display")
        ("content_type", 1)
        ("price", "3.0000 EOSHARE")
        ("storage_uri", "/xxx/yyy")
        ("status", false)
    );
    produce_blocks(1);

    content_t content;
    get_content(content, 3);

    push_action( N(eoshareagent), N(modify), N(artist1), mvo()
        ("content_id", content.content_id)
        ("owner", "artist1") 
        ("artist_name", "artest1-display")
        ("content_title", "content-display")
        ("content_type", 1)
        ("price", "2.0000 EOSHARE")
        ("storage_uri", "/xxx/ii")
        ("status", false)
    );
    get_content(content, content.content_id);
    BOOST_TEST_MESSAGE( fc::json::to_pretty_string(content) );

} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( changestatus_tests, eoshare_tester ) try {
    push_action( N(eoshareagent), N(upload), N(artist1), mvo()
        ("owner", "artist1") 
        ("artist_name", "artest1-display")
        ("content_title", "content-display")
        ("content_type", 1)
        ("price", "1.0000 EOSHARE")
        ("storage_uri", "/xxx/yyy")
        ("status", false)
    );
    produce_blocks(1);

    content_t content;
    get_content(content, 1);

    push_action( N(eoshareagent), N(changestatus), N(artist1), mvo()
        ("content_id", content.content_id)
        ("owner", "artist1") 
        ("status", true)
    );
    get_content(content, content.content_id);
    BOOST_TEST_MESSAGE( fc::json::to_pretty_string(content) );
} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( purchase_test, eoshare_tester ) try {
    push_action( N(eoshareagent), N(upload), N(artist1), mvo()
        ("owner", "artist1") 
        ("artist_name", "artest1-display")
        ("content_title", "content-display")
        ("content_type", 1)
        ("price", "1.0000 EOSHARE")
        ("storage_uri", "/xxx/yyy")
        ("status", true)
    );
    produce_blocks(1);

    push_action( N(eoshareagent), N(upload), N(artist1), mvo()
        ("owner", "artist1") 
        ("artist_name", "artest1-display")
        ("content_title", "content-display")
        ("content_type", 1)
        ("price", "1.0000 EOSHARE")
        ("storage_uri", "/xxx/yyy")
        ("status", true)
    );
    produce_blocks(1);

    push_action( N(eoshareagent), N(upload), N(artist2), mvo()
        ("owner", "artist2") 
        ("artist_name", "artest2-display")
        ("content_title", "content-display")
        ("content_type", 1)
        ("price", "1.0000 EOSHARE")
        ("storage_uri", "/xxx/yyy")
        ("status", true)
    );
    produce_blocks(1);

     push_action( N(eoshareagent), N(upload), N(artist2), mvo()
        ("owner", "artist2") 
        ("artist_name", "artest2-display")
        ("content_title", "content2-display")
        ("content_type", 1)
        ("price", "2.0000 EOSHARE")
        ("storage_uri", "/xxx/yyy")
        ("status", true)
    );
    produce_blocks(1);

    push_action( N(eosharetoken), N(transfer), N(user1), mvo()
        ("from", "user1") 
        ("to", "eoshareagent") 
        ("quantity", "1.0000 EOSHARE")
        ("memo", "1")
    );
    produce_blocks(1);

    push_action( N(eosharetoken), N(transfer), N(user1), mvo()
        ("from", "user1") 
        ("to", "eoshareagent") 
        ("quantity", "1.0000 EOSHARE")
        ("memo", "2")
    );
    produce_blocks(1);

    push_action( N(eosharetoken), N(transfer), N(user1), mvo()
        ("from", "user1") 
        ("to", "eoshareagent") 
        ("quantity", "1.0000 EOSHARE")
        ("memo", "3")
    );
    produce_blocks(1);

    push_action( N(eosharetoken), N(transfer), N(user1), mvo()
        ("from", "user1") 
        ("to", "eoshareagent") 
        ("quantity", "2.0000 EOSHARE")
        ("memo", "4")
    );
    produce_blocks(1);

    purchase_t purchase;
    get_purchase(purchase, N(user1));

    BOOST_TEST_MESSAGE( fc::json::to_pretty_string(purchase) );

} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( share_test, eoshare_tester ) try {
    push_action( N(eoshareagent), N(upload), N(artist1), mvo()
        ("owner", "artist1") 
        ("artist_name", "artest1-display")
        ("content_title", "content-display")
        ("content_type", 1)
        ("price", "1.0000 EOSHARE")
        ("storage_uri", "/xxx/yyy")
        ("status", true)
    );
    produce_blocks(1);

    push_action( N(eoshareagent), N(upload), N(artist1), mvo()
        ("owner", "artist1") 
        ("artist_name", "artest1-display")
        ("content_title", "content-display")
        ("content_type", 1)
        ("price", "1.0000 EOSHARE")
        ("storage_uri", "/xxx/yyy")
        ("status", true)
    );
    produce_blocks(1);

    push_action( N(eoshareagent), N(upload), N(artist2), mvo()
        ("owner", "artist2") 
        ("artist_name", "artest2-display")
        ("content_title", "content-display")
        ("content_type", 1)
        ("price", "1.0000 EOSHARE")
        ("storage_uri", "/xxx/yyy")
        ("status", true)
    );
    produce_blocks(1);

     push_action( N(eoshareagent), N(upload), N(artist2), mvo()
        ("owner", "artist2") 
        ("artist_name", "artest2-display")
        ("content_title", "content2-display")
        ("content_type", 1)
        ("price", "2.0000 EOSHARE")
        ("storage_uri", "/xxx/yyy")
        ("status", true)
    );
    produce_blocks(1);

    push_action( N(eosharetoken), N(transfer), N(user1), mvo()
        ("from", "user1") 
        ("to", "eoshareagent") 
        ("quantity", "1.0000 EOSHARE")
        ("memo", "1")
    );
    produce_blocks(1);

    push_action( N(eosharetoken), N(transfer), N(user1), mvo()
        ("from", "user1") 
        ("to", "eoshareagent") 
        ("quantity", "1.0000 EOSHARE")
        ("memo", "2")
    );
    produce_blocks(1);

    push_action( N(eosharetoken), N(transfer), N(user1), mvo()
        ("from", "user1") 
        ("to", "eoshareagent") 
        ("quantity", "1.0000 EOSHARE")
        ("memo", "3")
    );
    produce_blocks(1);

    push_action( N(eosharetoken), N(transfer), N(user1), mvo()
        ("from", "user1") 
        ("to", "eoshareagent") 
        ("quantity", "2.0000 EOSHARE")
        ("memo", "4")
    );
    produce_blocks(1);

    push_action( N(eosharetoken), N(transfer), N(user2), mvo()
        ("from", "user2") 
        ("to", "eoshareagent") 
        ("quantity", "1.0000 EOSHARE")
        ("memo", "1")
    );
    produce_blocks(1);

    push_action( N(eosharetoken), N(transfer), N(user2), mvo()
        ("from", "user2") 
        ("to", "eoshareagent") 
        ("quantity", "1.0000 EOSHARE")
        ("memo", "2")
    );
    produce_blocks(1);

    push_action( N(eosharetoken), N(transfer), N(user2), mvo()
        ("from", "user2") 
        ("to", "eoshareagent") 
        ("quantity", "1.0000 EOSHARE")
        ("memo", "3")
    );
    produce_blocks(1);

    push_action( N(eosharetoken), N(transfer), N(user2), mvo()
        ("from", "user2") 
        ("to", "eoshareagent") 
        ("quantity", "2.0000 EOSHARE")
        ("memo", "4")
    );
    produce_blocks(1);

    push_action( N(eosharetoken), N(transfer), N(user3), mvo()
        ("from", "user3") 
        ("to", "eoshareagent") 
        ("quantity", "1.0000 EOSHARE")
        ("memo", "1")
    );
    produce_blocks(1);

    push_action( N(eosharetoken), N(transfer), N(user3), mvo()
        ("from", "user3") 
        ("to", "eoshareagent") 
        ("quantity", "1.0000 EOSHARE")
        ("memo", "2")
    );
    produce_blocks(1);

    push_action( N(eosharetoken), N(transfer), N(user3), mvo()
        ("from", "user3") 
        ("to", "eoshareagent") 
        ("quantity", "1.0000 EOSHARE")
        ("memo", "3")
    );
    produce_blocks(1);

    push_action( N(eosharetoken), N(transfer), N(user3), mvo()
        ("from", "user3") 
        ("to", "eoshareagent") 
        ("quantity", "2.0000 EOSHARE")
        ("memo", "4")
    );
    produce_blocks(1);
    
    push_action( N(eoshareagent), N(share), N(user1), mvo()
        ("user", "user1") 
        ("content_id", 4)
    );
    produce_blocks(1);

    push_action( N(eoshareagent), N(share), N(user2), mvo()
        ("user", "user2") 
        ("content_id", 4)
    );
    produce_blocks(1);

    push_action( N(eoshareagent), N(share), N(user3), mvo()
        ("user", "user3") 
        ("content_id", 4)
    );
    produce_blocks(1);
      
    seed_t seed ;
    get_seed(seed, 4);

    BOOST_TEST_MESSAGE( fc::json::to_pretty_string(seed) );    
} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( download_test, eoshare_tester ) try {
    push_action( N(eoshareagent), N(upload), N(artist1), mvo()
        ("owner", "artist1") 
        ("artist_name", "artest1-display")
        ("content_title", "content-display")
        ("content_type", 1)
        ("price", "1.0000 EOSHARE")
        ("storage_uri", "/xxx/yyy")
        ("status", true)
    );
    produce_blocks(1);

    push_action( N(eoshareagent), N(upload), N(artist1), mvo()
        ("owner", "artist1") 
        ("artist_name", "artest1-display")
        ("content_title", "content-display")
        ("content_type", 1)
        ("price", "1.0000 EOSHARE")
        ("storage_uri", "/xxx/yyy")
        ("status", true)
    );
    produce_blocks(1);

    push_action( N(eoshareagent), N(upload), N(artist2), mvo()
        ("owner", "artist2") 
        ("artist_name", "artest2-display")
        ("content_title", "content-display")
        ("content_type", 1)
        ("price", "1.0000 EOSHARE")
        ("storage_uri", "/xxx/yyy")
        ("status", true)
    );
    produce_blocks(1);

     push_action( N(eoshareagent), N(upload), N(artist2), mvo()
        ("owner", "artist2") 
        ("artist_name", "artest2-display")
        ("content_title", "content2-display")
        ("content_type", 1)
        ("price", "2.0000 EOSHARE")
        ("storage_uri", "/xxx/yyy")
        ("status", true)
    );
    produce_blocks(1);

    push_action( N(eosharetoken), N(transfer), N(user1), mvo()
        ("from", "user1") 
        ("to", "eoshareagent") 
        ("quantity", "1.0000 EOSHARE")
        ("memo", "1")
    );
    produce_blocks(1);

    push_action( N(eosharetoken), N(transfer), N(user1), mvo()
        ("from", "user1") 
        ("to", "eoshareagent") 
        ("quantity", "1.0000 EOSHARE")
        ("memo", "2")
    );
    produce_blocks(1);

    push_action( N(eosharetoken), N(transfer), N(user1), mvo()
        ("from", "user1") 
        ("to", "eoshareagent") 
        ("quantity", "1.0000 EOSHARE")
        ("memo", "3")
    );
    produce_blocks(1);

    push_action( N(eosharetoken), N(transfer), N(user1), mvo()
        ("from", "user1") 
        ("to", "eoshareagent") 
        ("quantity", "2.0000 EOSHARE")
        ("memo", "4")
    );
    produce_blocks(1);

    push_action( N(eosharetoken), N(transfer), N(user2), mvo()
        ("from", "user2") 
        ("to", "eoshareagent") 
        ("quantity", "1.0000 EOSHARE")
        ("memo", "1")
    );
    produce_blocks(1);

    push_action( N(eosharetoken), N(transfer), N(user2), mvo()
        ("from", "user2") 
        ("to", "eoshareagent") 
        ("quantity", "1.0000 EOSHARE")
        ("memo", "2")
    );
    produce_blocks(1);

    push_action( N(eosharetoken), N(transfer), N(user2), mvo()
        ("from", "user2") 
        ("to", "eoshareagent") 
        ("quantity", "1.0000 EOSHARE")
        ("memo", "3")
    );
    produce_blocks(1);

    push_action( N(eosharetoken), N(transfer), N(user2), mvo()
        ("from", "user2") 
        ("to", "eoshareagent") 
        ("quantity", "2.0000 EOSHARE")
        ("memo", "4")
    );
    produce_blocks(1);

    push_action( N(eosharetoken), N(transfer), N(user3), mvo()
        ("from", "user3") 
        ("to", "eoshareagent") 
        ("quantity", "1.0000 EOSHARE")
        ("memo", "1")
    );
    produce_blocks(1);

    push_action( N(eosharetoken), N(transfer), N(user3), mvo()
        ("from", "user3") 
        ("to", "eoshareagent") 
        ("quantity", "1.0000 EOSHARE")
        ("memo", "2")
    );
    produce_blocks(1);

    push_action( N(eosharetoken), N(transfer), N(user3), mvo()
        ("from", "user3") 
        ("to", "eoshareagent") 
        ("quantity", "1.0000 EOSHARE")
        ("memo", "3")
    );
    produce_blocks(1);

    push_action( N(eosharetoken), N(transfer), N(user3), mvo()
        ("from", "user3") 
        ("to", "eoshareagent") 
        ("quantity", "2.0000 EOSHARE")
        ("memo", "4")
    );
    produce_blocks(1);
    
    push_action( N(eoshareagent), N(share), N(user1), mvo()
        ("user", "user1") 
        ("content_id", 4)
    );
    produce_blocks(1);

    push_action( N(eoshareagent), N(share), N(user2), mvo()
        ("user", "user2") 
        ("content_id", 4)
    );
    produce_blocks(1);

    push_action( N(eoshareagent), N(share), N(user3), mvo()
        ("user", "user3") 
        ("content_id", 4)
    );
    produce_blocks(1);
      
    push_action( N(eoshareagent), N(download), N(user3), mvo()
        ("user", "user3") 
        ("content_id", 4)
        ("random", "randomhex")
    );
    produce_blocks(1);

} FC_LOG_AND_RETHROW()

BOOST_AUTO_TEST_SUITE_END()