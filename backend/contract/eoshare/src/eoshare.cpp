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

    void eoshare::upload(name owner,
            string artist_name,
            uint64_t content_id,
            string content_title,
            uint8_t content_type,
            asset quantity) {

    }
    
    void eoshare::download(name user, uint64_t content_id) {

    }

    void eoshare::share(name user, uint64_t content_id) {

    }

    void eoshare::transfer() {
    }

} /// namespace share 

EOSIO_DISPATCH_EX( eoshare::eoshare, (upload)(download)(share)(transfer) )

