#include <eoshare/eoshare.hpp>
// #include <eosiolib/action.hpp>
// #include <eosiolib/crypto.hpp>

#define EOSIO_DISPATCH_EX( TYPE, MEMBERS ) \
extern "C" { \
   void apply( uint64_t receiver, uint64_t code, uint64_t action ) { \
      if( code == receiver ) { \
         switch( action ) { \
            EOSIO_DISPATCH_HELPER( TYPE, MEMBERS ) \
         } \
         /* does not allow destructor of thiscontract to run: eosio_exit(0); */ \
      } \
   } \
} \
 /// @}  dispatcher

namespace eoshare {
    void eoshare::upload(name owner, string artist_name, string content_title, uint8_t content_type, asset price, bool status) {
        require_auth(owner);

        eosio_assert(artist_name.size() <= 64, ""); 
        eosio_assert(content_title.size() <= 64, ""); 
        eosio_assert(content_type > 0, ""); 

        eosio_assert( price.is_valid(), "invalid price" );
        eosio_assert( price.amount > 0, "must retire positive price" );
        eosio_assert( price.symbol == eosio::symbol("SYMBOL", 4), "symbol precision mismatch" );

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
            content.status = status;
        });
    }

    void eoshare::modify(name owner, uint64_t content_id, string artist_name, string content_title, uint8_t content_type, asset price) {
        require_auth(owner);

        eosio_assert(content_id >= 0, ""); 
        eosio_assert(artist_name.size() <= 64, ""); 
        eosio_assert(content_title.size() <= 64, ""); 
        eosio_assert(content_type > 0, ""); 

        eosio_assert( price.is_valid(), "invalid price" );
        eosio_assert( price.amount > 0, "must retire positive price" );
        eosio_assert( price.symbol == eosio::symbol("SYMBOL", 4), "symbol precision mismatch" );

        content_table contents(get_self(), get_self().value);
		auto itr = contents.find(content_id);

		contents.modify(itr, eosio::same_payer, [&](auto& content) {
            content.artist_name = artist_name;
            content.content_title = content_title;
            content.content_type = content_type;
            content.price = price;
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

    void eoshare::download(name user, uint64_t content_id) {

    }

    void eoshare::share(name user, uint64_t content_id) {

    }

    void eoshare::transfer() {
    }

} /// namespace share 

EOSIO_DISPATCH_EX( eoshare::eoshare, (upload)(modify)(changestatus)(download)(share)(transfer) )

