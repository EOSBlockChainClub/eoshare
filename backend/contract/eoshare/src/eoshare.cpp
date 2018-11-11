#include <eoshare/eoshare.hpp>

#define EOSIO_DISPATCH_EX( TYPE, MEMBERS ) \
extern "C" { \
    void apply( uint64_t receiver, uint64_t code, uint64_t action ) { \
        if( code == receiver || code == eoshare::eoshare_token.value) { \
            if( action == "transfer"_n.value){ \
                eosio_assert( code == eoshare::eoshare_token.value, "muse transfer EOSHARE"); \
            } \
            switch( action ) { \
                EOSIO_DISPATCH_HELPER( TYPE, MEMBERS ) \
            } \
        /* does not allow destructor of thiscontract to run: eosio_exit(0); */ \
        } \
    } \
} \

namespace eoshare {

    void eoshare::upload(name owner, string artist_name, string content_title, uint8_t content_type, asset price, string storage_uri, bool status) {
        require_auth(owner);

        eosio_assert(artist_name.size() <= 64, ""); 
        eosio_assert(content_title.size() <= 64, ""); 
        eosio_assert(content_type > 0, ""); 

        eosio_assert( price.is_valid(), "invalid price" );
        eosio_assert( price.amount > 0, "must retire positive price" );
        eosio_assert( price.symbol == eoshare_symbol, "symbol precision mismatch" );

        auto env = m_env.get();
		env.current_content_id += 1;
		m_env.set(env, get_self() );

        content_table contents(get_self(), get_self().value);
		contents.emplace(_self, [&](auto& content) {
            content.owner = owner;
            content.content_id = env.current_content_id;
            content.artist_name = artist_name;
            content.content_title = content_title;
            content.content_type = content_type;
            content.price = price;
            content.storage_uri = storage_uri;
            content.status = status;
        });
    }

    void eoshare::modify(name owner, uint64_t content_id, string artist_name, string content_title, uint8_t content_type, asset price, string storage_uri) {
        require_auth(owner);

        eosio_assert(content_id > 0, "must be over 0"); 
        eosio_assert(artist_name.size() <= 64, ""); 
        eosio_assert(content_title.size() <= 64, ""); 
        eosio_assert(content_type > 0, "must be over 0"); 

        eosio_assert( price.is_valid(), "invalid price" );
        eosio_assert( price.amount > 0, "must retire positive price" );
        eosio_assert( price.symbol == eoshare_symbol, "symbol precision mismatch" );

        content_table contents(get_self(), get_self().value);
		auto itr = contents.find(content_id);

		contents.modify(itr, eosio::same_payer, [&](auto& content) {
            content.artist_name = artist_name;
            content.content_title = content_title;
            content.content_type = content_type;
            content.price = price;
            content.storage_uri = storage_uri;
        });
    }
    
    void eoshare::changestatus(name owner, uint64_t content_id, bool status) {
        require_auth(owner);

        eosio_assert(content_id >= 0, ""); 

        content_table contents(get_self(), get_self().value);
		auto itr = contents.find(content_id);
		contents.modify(itr, eosio::same_payer, [&](auto& content) {
            content.status = status;
        });
    }


    void eoshare::share(name user, uint64_t content_id) {
        require_auth(user);
        eosio_assert(content_id > 0, "must be over 0"); 

        seed_table seeds(get_self(), get_self().value);
		auto itr = seeds.find(content_id);
        if (itr == seeds.end()) {
		    seeds.emplace(get_self(), [&](auto& seed) {
                seed.content_id= content_id;
                seed.names.emplace_back(user);
            });
        } else {
		    seeds.modify(itr, eosio::same_payer, [&](auto& seed) {
                auto itr_ = std::find(seed.names.begin(), seed.names.end(), user);                                
                eosio_assert(itr_ == seed.names.end(), "duplicate purchase");
                seed.names.emplace_back(user);
            });
        }
    }

    void eoshare::transfer(uint64_t sender, uint64_t receiver) {
        auto trx_data = eosio::unpack_action_data<nt_transfer>();
        eosio_assert(trx_data.to == get_self(), "must be incoming or outgoing transfer");

        uint64_t content_id = std::stoull(trx_data.memo.c_str());
        eosio_assert(content_id >= 0, "must be over 0"); 

        content_table contents(get_self(), get_self().value);
		auto itr_ = contents.find(content_id);
        eosio_assert(itr_ != contents.end(), "content not exist"); 

        //eosio_assert((*itr_).price != trx_data.quantity, "price mismatch"); 
        eosio_assert((*itr_).price.amount == trx_data.quantity.amount, "price mismatch"); 

        purchase_table purchases(get_self(), get_self().value);
		auto itr = purchases.find(trx_data.from.value);
        if (itr == purchases.end()) {
		    purchases.emplace(get_self(), [&](auto& purchase) {
                purchase.owner = trx_data.from;
                purchase.content_ids.emplace_back(content_id);
            });
        } else {
		    purchases.modify(itr, eosio::same_payer, [&](auto& purchase) {
                auto itr_ = std::find(purchase.content_ids.begin(), purchase.content_ids.end(), content_id);
                eosio_assert(itr_ == purchase.content_ids.end(), "duplicate purchase");
                purchase.content_ids.emplace_back(content_id);
            });
        }
    }

    void eoshare::download(name user, uint64_t content_id, string random) {
        require_auth(user);

        eosio_assert(content_id > 0, "must be over 0"); 

        purchase_table purchases(get_self(), get_self().value);
		auto itr = purchases.find(user.value);
        eosio_assert(itr != purchases.end(), "not purchased"); 

        // seed_table seeds(get_self(), get_self().value);
		// auto itr_ = seeds.find(content_id);
    }

} /// namespace share 

EOSIO_DISPATCH_EX( eoshare::eoshare, (upload)(modify)(changestatus)(share)(transfer)(download) )