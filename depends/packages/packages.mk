packages:=boost libevent

qt_packages = zlib

qrencode_packages = qrencode

qt_linux_packages:=qt expat libxcb xcb_proto libXau xproto freetype fontconfig

qt_darwin_packages=qt
qt_mingw32_packages=qt

bdb_packages=bdb
sqlite_packages=sqlite

zmq_packages=zeromq

upnp_packages=miniupnpc

multiprocess_packages = libmultiprocess capnp
multiprocess_native_packages = native_libmultiprocess native_capnp

darwin_native_packages = native_ds_store native_mac_alias

$(host_arch)_$(host_os)_native_packages += native_b2

ifneq ($(build_os),darwin)
darwin_native_packages += native_cctools native_libdmg-hfsplus
endif
