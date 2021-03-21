# Copyright (c) 2009-2019 The Bitcoin Core developers
# Copyright (c) 2014-2019 The DigiByte Core developers
# Copyright (c) 2015-2019 The Auroracoin developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

DIST_SUBDIRS = secp256k1 univalue

AM_LDFLAGS = $(PTHREAD_CFLAGS) $(LIBTOOL_LDFLAGS) $(HARDENED_LDFLAGS) $(GPROF_LDFLAGS) $(SANITIZER_LDFLAGS)
AM_CXXFLAGS = $(DEBUG_CXXFLAGS) $(HARDENED_CXXFLAGS) $(WARN_CXXFLAGS) $(NOWARN_CXXFLAGS) $(ERROR_CXXFLAGS) $(GPROF_CXXFLAGS) $(SANITIZER_CXXFLAGS)
AM_CPPFLAGS = $(DEBUG_CPPFLAGS) $(HARDENED_CPPFLAGS)
AM_LIBTOOLFLAGS = --preserve-dup-deps
EXTRA_LIBRARIES =

if EMBEDDED_UNIVALUE
LIBUNIVALUE = univalue/libunivalue.la

$(LIBUNIVALUE): $(wildcard univalue/lib/*) $(wildcard univalue/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)
else
LIBUNIVALUE = $(UNIVALUE_LIBS)
endif

AURORACOIN_INCLUDES=-I$(builddir) $(BDB_CPPFLAGS) $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS) $(CRYPTO_CFLAGS) $(SSL_CFLAGS)

AURORACOIN_INCLUDES += -I$(srcdir)/secp256k1/include
AURORACOIN_INCLUDES += $(UNIVALUE_CFLAGS)

LIBAURORACOIN_SERVER=libauroracoin_server.a
LIBAURORACOIN_COMMON=libauroracoin_common.a
LIBAURORACOIN_CONSENSUS=libauroracoin_consensus.a
LIBAURORACOIN_CLI=libauroracoin_cli.a
LIBAURORACOIN_UTIL=libauroracoin_util.a
LIBAURORACOIN_CRYPTO_BASE=crypto/libauroracoin_crypto_base.a
LIBAURORACOINQT=qt/libauroracoinqt.a
LIBSECP256K1=secp256k1/libsecp256k1.la

if ENABLE_ZMQ
LIBAURORACOIN_ZMQ=libauroracoin_zmq.a
endif
if BUILD_AURORACOIN_LIBS
LIBAURORACOINCONSENSUS=libauroracoinconsensus.la
endif
if ENABLE_WALLET
LIBAURORACOIN_WALLET=libauroracoin_wallet.a
LIBAURORACOIN_WALLET_TOOL=libauroracoin_wallet_tool.a
endif

LIBAURORACOIN_CRYPTO= $(LIBAURORACOIN_CRYPTO_BASE)
if ENABLE_SSE41
LIBAURORACOIN_CRYPTO_SSE41 = crypto/libauroracoin_crypto_sse41.a
LIBAURORACOIN_CRYPTO += $(LIBAURORACOIN_CRYPTO_SSE41)
endif
if ENABLE_AVX2
LIBAURORACOIN_CRYPTO_AVX2 = crypto/libauroracoin_crypto_avx2.a
LIBAURORACOIN_CRYPTO += $(LIBAURORACOIN_CRYPTO_AVX2)
endif
if ENABLE_SHANI
LIBAURORACOIN_CRYPTO_SHANI = crypto/libauroracoin_crypto_shani.a
LIBAURORACOIN_CRYPTO += $(LIBAURORACOIN_CRYPTO_SHANI)
endif

$(LIBSECP256K1): $(wildcard secp256k1/src/*.h) $(wildcard secp256k1/src/*.c) $(wildcard secp256k1/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)

# Make is not made aware of per-object dependencies to avoid limiting building parallelization
# But to build the less dependent modules first, we manually select their order here:
EXTRA_LIBRARIES += \
  $(LIBAURORACOIN_CRYPTO) \
  $(LIBAURORACOIN_UTIL) \
  $(LIBAURORACOIN_COMMON) \
  $(LIBAURORACOIN_CONSENSUS) \
  $(LIBAURORACOIN_SERVER) \
  $(LIBAURORACOIN_CLI) \
  $(LIBAURORACOIN_WALLET) \
  $(LIBAURORACOIN_WALLET_TOOL) \
  $(LIBAURORACOIN_ZMQ)

lib_LTLIBRARIES = $(LIBAURORACOINCONSENSUS)

bin_PROGRAMS =
noinst_PROGRAMS =
TESTS =
BENCHMARKS =

if BUILD_AURORACOIND
  bin_PROGRAMS += auroracoind
endif

if BUILD_AURORACOIN_CLI
  bin_PROGRAMS += auroracoin-cli
endif
if BUILD_AURORACOIN_TX
  bin_PROGRAMS += auroracoin-tx
endif
if ENABLE_WALLET
if BUILD_AURORACOIN_WALLET
  bin_PROGRAMS += auroracoin-wallet
endif
endif

.PHONY: FORCE check-symbols check-security
# auroracoin core #
AURORACOIN_CORE_H = \
  addrdb.h \
  addressindex.h \
  addrman.h \
  attributes.h \
  banman.h \
  base58.h \
  bech32.h \
  bloom.h \
  blockencodings.h \
  blockfilter.h \
  chain.h \
  chainparams.h \
  chainparamsbase.h \
  chainparamsseeds.h \
  checkqueue.h \
  clientversion.h \
  coins.h \
  compat.h \
  compat/assumptions.h \
  compat/byteswap.h \
  compat/endian.h \
  compat/sanity.h \
  compressor.h \
  consensus/consensus.h \
  consensus/tx_check.h \
  consensus/tx_verify.h \
  core_io.h \
  core_memusage.h \
  cuckoocache.h \
  ecwrapper.h \
  flatfile.h \
  fs.h \
  httprpc.h \
  httpserver.h \
  index/base.h \
  index/blockfilterindex.h \
  index/txindex.h \
  indirectmap.h \
  init.h \
  interfaces/chain.h \
  interfaces/handler.h \
  interfaces/node.h \
  interfaces/wallet.h \
  key.h \
  key_io.h \
  dbwrapper.h \
  limitedmap.h \
  logging.h \
  memusage.h \
  merkleblock.h \
  miner.h \
  net.h \
  net_permissions.h \
  net_processing.h \
  netaddress.h \
  netbase.h \
  netmessagemaker.h \
  node/coin.h \
  node/coinstats.h \
  node/psbt.h \
  node/transaction.h \
  noui.h \
  optional.h \
  outputtype.h \
  policy/feerate.h \
  policy/fees.h \
  policy/policy.h \
  policy/rbf.h \
  policy/settings.h \
  pow.h \
  protocol.h \
  psbt.h \
  random.h \
  reverse_iterator.h \
  reverselock.h \
  rpc/blockchain.h \
  rpc/client.h \
  rpc/protocol.h \
  rpc/rawtransaction_util.h \
  rpc/register.h \
  rpc/request.h \
  rpc/server.h \
  rpc/util.h \
  scheduler.h \
  script/descriptor.h \
  script/keyorigin.h \
  script/sigcache.h \
  script/sign.h \
  script/signingprovider.h \
  script/standard.h \
  shutdown.h \
  streams.h \
  support/allocators/secure.h \
  support/allocators/zeroafterfree.h \
  support/cleanse.h \
  support/events.h \
  support/lockedpool.h \
  sync.h \
  threadsafety.h \
  threadinterrupt.h \
  timedata.h \
  torcontrol.h \
  txdb.h \
  txmempool.h \
  ui_interface.h \
  undo.h \
  util/bip32.h \
  util/bytevectorhash.h \
  util/error.h \
  util/fees.h \
  util/system.h \
  util/memory.h \
  util/moneystr.h \
  util/rbf.h \
  util/string.h \
  util/threadnames.h \
  util/time.h \
  util/translation.h \
  util/url.h \
  util/validation.h \
  validation.h \
  validationinterface.h \
  versionbits.h \
  versionbitsinfo.h \
  walletinitinterface.h \
  wallet/coincontrol.h \
  wallet/crypter.h \
  wallet/db.h \
  wallet/feebumper.h \
  wallet/fees.h \
  wallet/ismine.h \
  wallet/load.h \
  wallet/psbtwallet.h \
  wallet/rpcwallet.h \
  wallet/wallet.h \
  wallet/walletdb.h \
  wallet/wallettool.h \
  wallet/walletutil.h \
  wallet/coinselection.h \
  warnings.h \
  zmq/zmqabstractnotifier.h \
  zmq/zmqconfig.h\
  zmq/zmqnotificationinterface.h \
  zmq/zmqpublishnotifier.h \
  zmq/zmqrpc.h


obj/build.h: FORCE
	@$(MKDIR_P) $(builddir)/obj
	@$(top_srcdir)/share/genbuild.sh "$(abs_top_builddir)/src/obj/build.h" \
	  "$(abs_top_srcdir)"
libauroracoin_util_a-clientversion.$(OBJEXT): obj/build.h

# server: shared between auroracoind and auroracoin-qt
# Contains code accessing mempool and chain state that is meant to be separated
# from wallet and gui code (see node/README.md). Shared code should go in
# libauroracoin_common or libauroracoin_util libraries, instead.
libauroracoin_server_a_CPPFLAGS = $(AM_CPPFLAGS) $(AURORACOIN_INCLUDES) $(MINIUPNPC_CPPFLAGS) $(EVENT_CFLAGS) $(EVENT_PTHREADS_CFLAGS)
libauroracoin_server_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libauroracoin_server_a_SOURCES = \
  addrdb.cpp \
  addrman.cpp \
  banman.cpp \
  blockencodings.cpp \
  blockfilter.cpp \
  chain.cpp \
  consensus/tx_verify.cpp \
  flatfile.cpp \
  httprpc.cpp \
  httpserver.cpp \
  index/base.cpp \
  index/blockfilterindex.cpp \
  index/txindex.cpp \
  interfaces/chain.cpp \
  interfaces/node.cpp \
  init.cpp \
  dbwrapper.cpp \
  miner.cpp \
  net.cpp \
  net_processing.cpp \
  node/coin.cpp \
  node/coinstats.cpp \
  node/psbt.cpp \
  node/transaction.cpp \
  noui.cpp \
  policy/fees.cpp \
  policy/rbf.cpp \
  policy/settings.cpp \
  pow.cpp \
  rest.cpp \
  rpc/blockchain.cpp \
  rpc/mining.cpp \
  rpc/misc.cpp \
  rpc/net.cpp \
  rpc/rawtransaction.cpp \
  rpc/server.cpp \
  script/sigcache.cpp \
  shutdown.cpp \
  timedata.cpp \
  torcontrol.cpp \
  txdb.cpp \
  txmempool.cpp \
  ui_interface.cpp \
  validation.cpp \
  validationinterface.cpp \
  versionbits.cpp \
  $(AURORACOIN_CORE_H)

if ENABLE_WALLET
libauroracoin_server_a_SOURCES += wallet/init.cpp
endif
if !ENABLE_WALLET
libauroracoin_server_a_SOURCES += dummywallet.cpp
endif

if ENABLE_ZMQ
libauroracoin_zmq_a_CPPFLAGS = $(AM_CPPFLAGS) $(AURORACOIN_INCLUDES) $(ZMQ_CFLAGS)
libauroracoin_zmq_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libauroracoin_zmq_a_SOURCES = \
  zmq/zmqabstractnotifier.cpp \
  zmq/zmqnotificationinterface.cpp \
  zmq/zmqpublishnotifier.cpp \
  zmq/zmqrpc.cpp
endif


# wallet: shared between auroracoind and auroracoin-qt, but only linked
# when wallet enabled
libauroracoin_wallet_a_CPPFLAGS = $(AM_CPPFLAGS) $(AURORACOIN_INCLUDES)
libauroracoin_wallet_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libauroracoin_wallet_a_SOURCES = \
  interfaces/wallet.cpp \
  wallet/coincontrol.cpp \
  wallet/crypter.cpp \
  wallet/db.cpp \
  wallet/feebumper.cpp \
  wallet/fees.cpp \
  wallet/ismine.cpp \
  wallet/load.cpp \
  wallet/psbtwallet.cpp \
  wallet/rpcdump.cpp \
  wallet/rpcwallet.cpp \
  wallet/wallet.cpp \
  wallet/walletdb.cpp \
  wallet/walletutil.cpp \
  wallet/coinselection.cpp \
  $(AURORACOIN_CORE_H)

libauroracoin_wallet_tool_a_CPPFLAGS = $(AM_CPPFLAGS) $(AURORACOIN_INCLUDES)
libauroracoin_wallet_tool_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libauroracoin_wallet_tool_a_SOURCES = \
  wallet/wallettool.cpp \
  $(AURORACOIN_CORE_H)

# crypto primitives library
crypto_libauroracoin_crypto_base_a_CPPFLAGS = $(AM_CPPFLAGS)
crypto_libauroracoin_crypto_base_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libauroracoin_crypto_base_a_SOURCES = \
  crypto/aes.cpp \
  crypto/aes_helper.c \
  crypto/aes.h \
  crypto/brg_endian.h \
  crypto/chacha_poly_aead.h \
  crypto/chacha_poly_aead.cpp \
  crypto/chacha20.h \
  crypto/chacha20.cpp \
  crypto/common.h \
  crypto/hkdf_sha256_32.cpp \
  crypto/hkdf_sha256_32.h \
  crypto/hmac_sha256.cpp \
  crypto/hmac_sha256.h \
  crypto/hmac_sha512.cpp \
  crypto/hmac_sha512.h \
  crypto/poly1305.h \
  crypto/poly1305.cpp \
  crypto/KeccakP-800-reference.c \
  crypto/KeccakP-800-SnP.h \
  crypto/ripemd160.cpp \
  crypto/ripemd160.h \
  crypto/sha1.cpp \
  crypto/sha1.h \
  crypto/sha256.cpp \
  crypto/sha256.h \
  crypto/sha512.cpp \
  crypto/sha512.h \
  crypto/siphash.cpp \
  crypto/siphash.h

if USE_ASM
crypto_libauroracoin_crypto_base_a_SOURCES += crypto/sha256_sse4.cpp
endif

crypto_libauroracoin_crypto_sse41_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libauroracoin_crypto_sse41_a_CPPFLAGS = $(AM_CPPFLAGS)
crypto_libauroracoin_crypto_sse41_a_CXXFLAGS += $(SSE41_CXXFLAGS)
crypto_libauroracoin_crypto_sse41_a_CPPFLAGS += -DENABLE_SSE41
crypto_libauroracoin_crypto_sse41_a_SOURCES = crypto/sha256_sse41.cpp

crypto_libauroracoin_crypto_avx2_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libauroracoin_crypto_avx2_a_CPPFLAGS = $(AM_CPPFLAGS)
crypto_libauroracoin_crypto_avx2_a_CXXFLAGS += $(AVX2_CXXFLAGS)
crypto_libauroracoin_crypto_avx2_a_CPPFLAGS += -DENABLE_AVX2
crypto_libauroracoin_crypto_avx2_a_SOURCES = crypto/sha256_avx2.cpp

crypto_libauroracoin_crypto_shani_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libauroracoin_crypto_shani_a_CPPFLAGS = $(AM_CPPFLAGS)
crypto_libauroracoin_crypto_shani_a_CXXFLAGS += $(SHANI_CXXFLAGS)
crypto_libauroracoin_crypto_shani_a_CPPFLAGS += -DENABLE_SHANI
crypto_libauroracoin_crypto_shani_a_SOURCES = crypto/sha256_shani.cpp

# consensus: shared between all executables that validate any consensus rules.
libauroracoin_consensus_a_CPPFLAGS = $(AM_CPPFLAGS) $(AURORACOIN_INCLUDES)
libauroracoin_consensus_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libauroracoin_consensus_a_SOURCES = \
  amount.h \
  arith_uint256.cpp \
  arith_uint256.h \
  consensus/merkle.cpp \
  consensus/merkle.h \
  consensus/params.h \
  consensus/tx_check.cpp \
  consensus/validation.h \
  crypto/blake.c \
  crypto/bmw.c \
  crypto/cubehash.c \
  crypto/echo.c \
  crypto/groestl.cpp \
  crypto/groestl.h \
  crypto/jh.c \
  crypto/keccak.c \
  crypto/luffa.c \
  crypto/qubit.cpp \
  crypto/qubit.h \
  crypto/shavite.c \
  crypto/simd.c \
  crypto/skein.cpp \
  crypto/skein.h \
  crypto/scrypt.cpp \
  crypto/scrypt-sse2.cpp \
  crypto/sph_blake.h \
  crypto/sph_bmw.h \
  crypto/sph_cubehash.h \
  crypto/sph_echo.h \
  crypto/sph_groestl.h \
  crypto/sph_jh.h \
  crypto/sph_keccak.h \
  crypto/sph_luffa.h \
  crypto/sph_shavite.h \
  crypto/sph_simd.h \
  crypto/sph_skein.h \
  crypto/sph_types.h \
  crypto/scrypt.h \
  hash.cpp \
  hash.h \
  prevector.h \
  primitives/block.cpp \
  primitives/block.h \
  primitives/transaction.cpp \
  primitives/transaction.h \
  pubkey.cpp \
  pubkey.h \
  script/auroracoinconsensus.cpp \
  script/interpreter.cpp \
  script/interpreter.h \
  script/script.cpp \
  script/script.h \
  script/script_error.cpp \
  script/script_error.h \
  serialize.h \
  span.h \
  tinyformat.h \
  uint256.cpp \
  uint256.h \
  util/strencodings.cpp \
  util/strencodings.h \
  version.h

# common: shared between auroracoind, and auroracoin-qt and non-server tools
libauroracoin_common_a_CPPFLAGS = $(AM_CPPFLAGS) $(AURORACOIN_INCLUDES)
libauroracoin_common_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libauroracoin_common_a_SOURCES = \
  base58.cpp \
  bech32.cpp \
  bloom.cpp \
  chainparams.cpp \
  coins.cpp \
  compressor.cpp \
  core_read.cpp \
  core_write.cpp \
  ecwrapper.cpp \
  key.cpp \
  key_io.cpp \
  merkleblock.cpp \
  netaddress.cpp \
  netbase.cpp \
  net_permissions.cpp \
  outputtype.cpp \
  policy/feerate.cpp \
  policy/policy.cpp \
  protocol.cpp \
  psbt.cpp \
  rpc/rawtransaction_util.cpp \
  rpc/util.cpp \
  scheduler.cpp \
  script/descriptor.cpp \
  script/sign.cpp \
  script/signingprovider.cpp \
  script/standard.cpp \
  versionbitsinfo.cpp \
  warnings.cpp \
  $(AURORACOIN_CORE_H)

# util: shared between all executables.
# This library *must* be included to make sure that the glibc
# backward-compatibility objects and their sanity checks are linked.
libauroracoin_util_a_CPPFLAGS = $(AM_CPPFLAGS) $(AURORACOIN_INCLUDES)
libauroracoin_util_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libauroracoin_util_a_SOURCES = \
  support/lockedpool.cpp \
  chainparamsbase.cpp \
  clientversion.cpp \
  compat/glibc_sanity_fdelt.cpp \
  compat/glibc_sanity.cpp \
  compat/glibcxx_sanity.cpp \
  compat/strnlen.cpp \
  fs.cpp \
  interfaces/handler.cpp \
  logging.cpp \
  random.cpp \
  rpc/request.cpp \
  support/cleanse.cpp \
  sync.cpp \
  threadinterrupt.cpp \
  util/bip32.cpp \
  util/bytevectorhash.cpp \
  util/error.cpp \
  util/fees.cpp \
  util/system.cpp \
  util/moneystr.cpp \
  util/rbf.cpp \
  util/threadnames.cpp \
  util/strencodings.cpp \
  util/string.cpp \
  util/time.cpp \
  util/url.cpp \
  util/validation.cpp \
  $(AURORACOIN_CORE_H)

if GLIBC_BACK_COMPAT
libauroracoin_util_a_SOURCES += compat/glibc_compat.cpp
AM_LDFLAGS += $(COMPAT_LDFLAGS)
endif

# cli: shared between auroracoin-cli and auroracoin-qt
libauroracoin_cli_a_CPPFLAGS = $(AM_CPPFLAGS) $(AURORACOIN_INCLUDES)
libauroracoin_cli_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libauroracoin_cli_a_SOURCES = \
  rpc/client.cpp \
  $(AURORACOIN_CORE_H)

nodist_libauroracoin_util_a_SOURCES = $(srcdir)/obj/build.h
#

# auroracoind binary #
auroracoind_SOURCES = auroracoind.cpp
auroracoind_CPPFLAGS = $(AM_CPPFLAGS) $(AURORACOIN_INCLUDES)
auroracoind_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
auroracoind_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
auroracoind_SOURCES += auroracoind-res.rc
endif

# Libraries below may be listed more than once to resolve circular dependencies (see
# https://eli.thegreenplace.net/2013/07/09/library-order-in-static-linking#circular-dependency)
auroracoind_LDADD = \
  $(LIBAURORACOIN_SERVER) \
  $(LIBAURORACOIN_WALLET) \
  $(LIBAURORACOIN_SERVER) \
  $(LIBAURORACOIN_COMMON) \
  $(LIBUNIVALUE) \
  $(LIBAURORACOIN_UTIL) \
  $(LIBAURORACOIN_ZMQ) \
  $(LIBAURORACOIN_CONSENSUS) \
  $(LIBAURORACOIN_CRYPTO) \
  $(LIBLEVELDB) \
  $(LIBLEVELDB_SSE42) \
  $(LIBMEMENV) \
  $(LIBSECP256K1)

auroracoind_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(CRYPTO_LIBS) $(MINIUPNPC_LIBS) $(EVENT_PTHREADS_LIBS) $(EVENT_LIBS) $(ZMQ_LIBS)

# auroracoin-cli binary #
auroracoin_cli_SOURCES = auroracoin-cli.cpp
auroracoin_cli_CPPFLAGS = $(AM_CPPFLAGS) $(AURORACOIN_INCLUDES) $(EVENT_CFLAGS)
auroracoin_cli_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
auroracoin_cli_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
auroracoin_cli_SOURCES += auroracoin-cli-res.rc
endif

auroracoin_cli_LDADD = \
  $(LIBAURORACOIN_CLI) \
  $(LIBUNIVALUE) \
  $(LIBAURORACOIN_UTIL) \
  $(LIBAURORACOIN_CRYPTO)

auroracoin_cli_LDADD += $(BOOST_LIBS) $(CRYPTO_LIBS) $(EVENT_LIBS)
#

# auroracoin-tx binary #
auroracoin_tx_SOURCES = auroracoin-tx.cpp
auroracoin_tx_CPPFLAGS = $(AM_CPPFLAGS) $(AURORACOIN_INCLUDES)
auroracoin_tx_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
auroracoin_tx_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
auroracoin_tx_SOURCES += auroracoin-tx-res.rc
endif

auroracoin_tx_LDADD = \
  $(LIBUNIVALUE) \
  $(LIBAURORACOIN_COMMON) \
  $(LIBAURORACOIN_UTIL) \
  $(LIBAURORACOIN_CONSENSUS) \
  $(LIBAURORACOIN_CRYPTO) \
  $(LIBSECP256K1)

auroracoin_tx_LDADD += $(BOOST_LIBS) $(CRYPTO_LIBS)
#

# auroracoin-wallet binary #
auroracoin_wallet_SOURCES = auroracoin-wallet.cpp
auroracoin_wallet_CPPFLAGS = $(AM_CPPFLAGS) $(AURORACOIN_INCLUDES)
auroracoin_wallet_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
auroracoin_wallet_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
auroracoin_wallet_SOURCES += auroracoin-wallet-res.rc
endif

auroracoin_wallet_LDADD = \
  $(LIBAURORACOIN_WALLET_TOOL) \
  $(LIBAURORACOIN_WALLET) \
  $(LIBAURORACOIN_COMMON) \
  $(LIBAURORACOIN_CONSENSUS) \
  $(LIBAURORACOIN_UTIL) \
  $(LIBAURORACOIN_CRYPTO) \
  $(LIBAURORACOIN_ZMQ) \
  $(LIBLEVELDB) \
  $(LIBLEVELDB_SSE42) \
  $(LIBMEMENV) \
  $(LIBSECP256K1) \
  $(LIBUNIVALUE)

auroracoin_wallet_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(CRYPTO_LIBS) $(EVENT_PTHREADS_LIBS) $(EVENT_LIBS) $(MINIUPNPC_LIBS) $(ZMQ_LIBS)
#

# auroracoinconsensus library #
if BUILD_AURORACOIN_LIBS
include_HEADERS = script/auroracoinconsensus.h
libauroracoinconsensus_la_SOURCES = support/cleanse.cpp $(crypto_libauroracoin_crypto_base_a_SOURCES) $(libauroracoin_consensus_a_SOURCES)

if GLIBC_BACK_COMPAT
  libauroracoinconsensus_la_SOURCES += compat/glibc_compat.cpp
endif

libauroracoinconsensus_la_LDFLAGS = $(AM_LDFLAGS) -no-undefined $(RELDFLAGS)
libauroracoinconsensus_la_LIBADD = $(LIBSECP256K1) $(BOOST_LIBS) $(CRYPTO_LIBS)
libauroracoinconsensus_la_CPPFLAGS = $(AM_CPPFLAGS) -I$(builddir)/obj -I$(srcdir)/secp256k1/include -DBUILD_AURORACOIN_INTERNAL $(SSL_CFLAGS)
libauroracoinconsensus_la_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)

endif
#

CTAES_DIST =  crypto/ctaes/bench.c
CTAES_DIST += crypto/ctaes/ctaes.c
CTAES_DIST += crypto/ctaes/ctaes.h
CTAES_DIST += crypto/ctaes/README.md
CTAES_DIST += crypto/ctaes/test.c

CLEANFILES = $(EXTRA_LIBRARIES)

CLEANFILES += *.gcda *.gcno .deps/*.Po .deps/*.Plo
CLEANFILES += compat/*.gcda compat/*.gcno compat/.deps/*.Po compat/.deps/*.Plo
CLEANFILES += consensus/*.gcda consensus/*.gcno consensus/.deps/*.Po consensus/.deps/*.Plo
CLEANFILES += crypto/*.gcda crypto/*.gcno crypto/.deps/*.Po crypto/.deps/*.Plo
CLEANFILES += index/.deps/*.Po
CLEANFILES += interfaces/.deps/*.Po
CLEANFILES += policy/*.gcda policy/*.gcno policy/.deps/*.Po policy/.deps/*.Plo
CLEANFILES += primitives/*.gcda primitives/*.gcno primitives/.deps/*.Po primitives/.deps/*.Plo
CLEANFILES += rpc/.deps/*.Po
CLEANFILES += script/*.gcda script/*.gcno script/.deps/*.Po script/.deps/*.Plo
CLEANFILES += support/*.gcda support/*.gcno support/.deps/*.Po support/.deps/*.Plo
CLEANFILES += univalue/*.gcda univalue/*.gcno univalue/.deps/*.Po univalue/.deps/*.Plo
CLEANFILES += wallet/*.gcda wallet/*.gcno wallet/.deps/*.Po wallet/.deps/*.Plo
CLEANFILES += wallet/test/*.gcda wallet/test/*.gcno wallet/test/.deps/*.Po wallet/test/.deps/*.Plo
CLEANFILES += zmq/*.gcda zmq/*.gcno zmq/.deps/*.Po zmq/.deps/*.Plo
CLEANFILES += obj/build.h

EXTRA_DIST = $(CTAES_DIST)


config/auroracoin-config.h: config/stamp-h1
	@$(MAKE) -C $(top_builddir) $(subdir)/$(@)
config/stamp-h1: $(top_srcdir)/$(subdir)/config/auroracoin-config.h.in $(top_builddir)/config.status
	$(AM_V_at)$(MAKE) -C $(top_builddir) $(subdir)/$(@)
$(top_srcdir)/$(subdir)/config/auroracoin-config.h.in:  $(am__configure_deps)
	$(AM_V_at)$(MAKE) -C $(top_srcdir) $(subdir)/config/auroracoin-config.h.in

clean-local:
	-$(MAKE) -C secp256k1 clean
	-$(MAKE) -C univalue clean
	-rm -f leveldb/*/*.gcda leveldb/*/*.gcno leveldb/helpers/memenv/*.gcda leveldb/helpers/memenv/*.gcno
	-rm -f config.h
	-rm -rf test/__pycache__

.rc.o:
	@test -f $(WINDRES)
	## FIXME: How to get the appropriate modulename_CPPFLAGS in here?
	$(AM_V_GEN) $(WINDRES) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(CPPFLAGS) -DWINDRES_PREPROC -i $< -o $@

check-symbols: $(bin_PROGRAMS)
if GLIBC_BACK_COMPAT
	@echo "Checking glibc back compat..."
	$(AM_V_at) READELF=$(READELF) CPPFILT=$(CPPFILT) $(PYTHON) $(top_srcdir)/contrib/devtools/symbol-check.py < $(bin_PROGRAMS)
endif

check-security: $(bin_PROGRAMS)
if HARDEN
	@echo "Checking binary security..."
	$(AM_V_at) READELF=$(READELF) OBJDUMP=$(OBJDUMP) $(PYTHON) $(top_srcdir)/contrib/devtools/security-check.py < $(bin_PROGRAMS)
endif

if ENABLE_BIP70
%.pb.cc %.pb.h: %.proto
	@test -f $(PROTOC)
	$(AM_V_GEN) $(PROTOC) --cpp_out=$(@D) --proto_path=$(<D) $<
endif

if EMBEDDED_LEVELDB
include Makefile.leveldb.include
endif

if ENABLE_TESTS
include Makefile.test.include
endif

if ENABLE_BENCH
include Makefile.bench.include
endif

if ENABLE_QT
include Makefile.qt.include
endif

if ENABLE_QT_TESTS
include Makefile.qttest.include
endif
