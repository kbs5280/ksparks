/* $RoughId: rmd160init.c,v 1.3 2001/07/13 20:00:43 knu Exp $ */
/* $Id: rmd160init.c 52694 2015-11-21 04:35:57Z naruse $ */

#include <ruby/ruby.h>
#include "../digest.h"
#if defined(RMD160_USE_OPENSSL)
#include "rmd160ossl.h"
#else
#include "rmd160.h"
#endif

static const rb_digest_metadata_t rmd160 = {
    RUBY_DIGEST_API_VERSION,
    RMD160_DIGEST_LENGTH,
    RMD160_BLOCK_LENGTH,
    sizeof(RMD160_CTX),
    (rb_digest_hash_init_func_t)RMD160_Init,
    (rb_digest_hash_update_func_t)RMD160_Update,
    (rb_digest_hash_finish_func_t)RMD160_Finish,
};

/*
 * A class for calculating message digests using RIPEMD-160
 * cryptographic hash function, designed by Hans Dobbertin, Antoon
 * Bosselaers, and Bart Preneel.
 */
void
Init_rmd160(void)
{
    VALUE mDigest, cDigest_Base, cDigest_RMD160;

    rb_require("digest");

#if 0
    mDigest = rb_define_module("Digest"); /* let rdoc know */
#endif
    mDigest = rb_path2class("Digest");
    cDigest_Base = rb_path2class("Digest::Base");

    cDigest_RMD160 = rb_define_class_under(mDigest, "RMD160", cDigest_Base);

#undef RUBY_UNTYPED_DATA_WARNING
#define RUBY_UNTYPED_DATA_WARNING 0
    rb_iv_set(cDigest_RMD160, "metadata",
	      Data_Wrap_Struct(0, 0, 0, (void *)&rmd160));
}
