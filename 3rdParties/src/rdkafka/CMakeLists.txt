

set(WITH_ZLIB ON)
set(WITH_SNAPPY ON)
set(WITH_LIBDL OFF)
set(WITH_PLUGINS OFF)
set(WITH_ZSTD_STATIC ON)
set(WITH_SASL_OAUTHBEARER ON)
set(WITH_HDRHISTOGRAM ON)

#set(ENABLE_DEVEL ON)


include_directories(AFTER 
	./
)


if(WIN32)
    add_definitions("-DSOLIB_EXT=\".dll\"")
else()
    set(HAVE_REGEX ON)
    add_definitions("-DHAVE_REGEX=1")
    set(HAVE_STRNDUP ON)
    add_definitions("-DHAVE_STRNDUP=1")
    add_definitions("-DSOLIB_EXT=\".so\"")
endif()


if(WIN32)

    #add_definitions("-DWITH_SASL_SCRAM=1")
    include_directories(AFTER 
        ../openssl/buildWindows/openssl/include
    )

elseif(ANDROID_PLATFORM)

elseif(IOS)

elseif(UNIX)

endif()


set(SRC_FILES
    librdkafka/src/crc32c.h
    librdkafka/src/crc32c.c
    librdkafka/src/rdaddr.h
    librdkafka/src/rdaddr.c
    librdkafka/src/rd.h
    librdkafka/src/rdatomic.h
    librdkafka/src/rdavg.h
    librdkafka/src/rdavl.h
    librdkafka/src/rdavl.c
    librdkafka/src/rdbuf.h
    librdkafka/src/rdbuf.c
    librdkafka/src/rdcrc32.h
    librdkafka/src/rdcrc32.c
    librdkafka/src/rdgz.h
    librdkafka/src/rdgz.c
    librdkafka/src/rdhdrhistogram.h
    librdkafka/src/rdhdrhistogram.c
    librdkafka/src/rdkafka.h
    librdkafka/src/rdkafka.c
    librdkafka/src/rdkafka_assignor.c
    librdkafka/src/rdkafka_background.c
    librdkafka/src/rdkafka_broker.c
    librdkafka/src/rdkafka_buf.h
    librdkafka/src/rdkafka_buf.c
    librdkafka/src/rdkafka_cert.h
    librdkafka/src/rdkafka_cert.c
    librdkafka/src/rdkafka_cgrp.h
    librdkafka/src/rdkafka_cgrp.c
    librdkafka/src/rdkafka_conf.h
    librdkafka/src/rdkafka_conf.c
    librdkafka/src/rdkafka_event.h
    librdkafka/src/rdkafka_event.c
    librdkafka/src/rdkafka_feature.h
    librdkafka/src/rdkafka_feature.c
    librdkafka/src/rdkafka_header.h
    librdkafka/src/rdkafka_header.c
    librdkafka/src/rdkafka_idempotence.h
    librdkafka/src/rdkafka_idempotence.c
    librdkafka/src/rdkafka_interceptor.h
    librdkafka/src/rdkafka_interceptor.c
    librdkafka/src/rdkafka_lz4.h
    librdkafka/src/rdkafka_lz4.c
    librdkafka/src/rdkafka_metadata.h
    librdkafka/src/rdkafka_metadata.c
    librdkafka/src/rdkafka_metadata_cache.c
    librdkafka/src/rdkafka_mock.h
    librdkafka/src/rdkafka_mock_int.h
    librdkafka/src/rdkafka_mock.c
    librdkafka/src/rdkafka_mock_handlers.c
    librdkafka/src/rdkafka_msg.h
    librdkafka/src/rdkafka_msg.c
    librdkafka/src/rdkafka_msgbatch.h
    librdkafka/src/rdkafka_msgset.h
    librdkafka/src/rdkafka_msgset_reader.c
    librdkafka/src/rdkafka_msgset_writer.c
    librdkafka/src/rdkafka_offset.h
    librdkafka/src/rdkafka_offset.c
    librdkafka/src/rdkafka_op.h
    librdkafka/src/rdkafka_op.c
    librdkafka/src/rdkafka_partition.h
    librdkafka/src/rdkafka_partition.c
    librdkafka/src/rdkafka_pattern.h
    librdkafka/src/rdkafka_pattern.c
    librdkafka/src/rdkafka_queue.c
    librdkafka/src/rdkafka_range_assignor.c
    librdkafka/src/rdkafka_request.c
    librdkafka/src/rdkafka_roundrobin_assignor.c
    librdkafka/src/rdkafka_sasl.h
    librdkafka/src/rdkafka_sasl_int.h
    librdkafka/src/rdkafka_sasl.c
    librdkafka/src/rdkafka_sasl_oauthbearer.h
    librdkafka/src/rdkafka_sasl_oauthbearer.c
    librdkafka/src/rdkafka_sasl_plain.c
    librdkafka/src/rdkafka_subscription.c
    librdkafka/src/rdkafka_timer.c
    librdkafka/src/rdkafka_topic.c
    librdkafka/src/rdkafka_transport.c
    librdkafka/src/rdkafka_interceptor.c
    librdkafka/src/rdlist.c
    librdkafka/src/rdlog.c
    librdkafka/src/rdmurmur2.h
    librdkafka/src/rdmurmur2.c
    librdkafka/src/rdports.h
    librdkafka/src/rdports.c
    librdkafka/src/rdrand.h
    librdkafka/src/rdrand.c
    librdkafka/src/rdregex.h
    librdkafka/src/rdregex.c
    librdkafka/src/rdstring.h
    librdkafka/src/rdstring.c
    librdkafka/src/rdunittest.c
    librdkafka/src/rdvarint.c
    librdkafka/src/tinycthread.h
    librdkafka/src/tinycthread.c
    librdkafka/src/tinycthread_extra.h
    librdkafka/src/tinycthread_extra.c
    librdkafka/src/xxhash.h
    librdkafka/src/xxhash.c
    librdkafka/src/lz4.c
    librdkafka/src/lz4frame.c
    librdkafka/src/lz4hc.c
	librdkafka/src-cpp/ConfImpl.cpp
    librdkafka/src-cpp/ConsumerImpl.cpp
    librdkafka/src-cpp/HeadersImpl.cpp
    librdkafka/src-cpp/HandleImpl.cpp
    librdkafka/src-cpp/KafkaConsumerImpl.cpp
    librdkafka/src-cpp/MessageImpl.cpp
    librdkafka/src-cpp/MetadataImpl.cpp
    librdkafka/src-cpp/ProducerImpl.cpp
    librdkafka/src-cpp/QueueImpl.cpp
    librdkafka/src-cpp/RdKafka.cpp
    librdkafka/src-cpp/TopicImpl.cpp
    librdkafka/src-cpp/TopicPartitionImpl.cpp
)

if(WITH_SNAPPY)
    add_definitions("-DWITH_SNAPPY=1")
    list(APPEND SRC_FILES librdkafka/src/snappy.c)
endif()


if(WITH_LIBDL)
    add_definitions("-DWITH_LIBDL=1")
    list(APPEND SRC_FILES librdkafka/src/rddl.c)
endif()

if(WITH_PLUGINS)
    add_definitions("-DWITH_PLUGINS=1")
    list(APPEND SRC_FILES librdkafka/src/rdkafka_plugin.c)
endif()

if(WITH_SASL_SCRAM OR WIN32)
  list(APPEND SRC_FILES librdkafka/src/rdkafka_sasl_win32.c)
elseif(WITH_SASL_CYRUS)
  list(APPEND SRC_FILES librdkafka/src/rdkafka_sasl_cyrus.c)
endif()

if(WITH_ZLIB)
    add_definitions("-DWITH_ZLIB=1")
  list(APPEND SRC_FILES librdkafka/src/rdgz.h)
  list(APPEND SRC_FILES librdkafka/src/rdgz.c)
endif()

if(NOT HAVE_REGEX)
  list(APPEND SRC_FILES librdkafka/src/regexp.c)
endif()

if(WITH_ZSTD_STATIC)
    add_definitions("-DWITH_ZSTD_STATIC=1")
endif()

if(WITH_SASL_OAUTHBEARER)
    add_definitions("-DWITH_SASL_OAUTHBEARER=1")
endif()

if(WITH_HDRHISTOGRAM)
    add_definitions("-DWITH_HDRHISTOGRAM=1")
endif()

if(ENABLE_DEVEL)
    add_definitions("-DENABLE_DEVEL=1")
endif()


set(INSTALL_FILES
    rdkafka_config.h
    librdkafka/src/rdcrc32.h
    librdkafka/src/rddl.h
    librdkafka/src/rdendian.h
    librdkafka/src/rdfloat.h
    librdkafka/src/rdgz.h
    librdkafka/src/rdhdrhistogram.h
    librdkafka/src/rdinterval.h
    librdkafka/src/rdkafka.h
    librdkafka/src/rdkafka_admin.h
    librdkafka/src/rdkafka_assignor.h
    librdkafka/src/rdkafka_aux.h
    librdkafka/src/rdkafka_broker.h
    librdkafka/src/rdkafka_buf.h
    librdkafka/src/rdkafka_cert.h
    librdkafka/src/rdkafka_cgrp.h
    librdkafka/src/rdkafka_conf.h
    librdkafka/src/rdkafka_confval.h
    librdkafka/src/rdkafka_event.h
    librdkafka/src/rdkafka_feature.h
    librdkafka/src/rdkafka_header.h
    librdkafka/src/rdkafka_idempotence.h
    librdkafka/src/rdkafka_int.h
    librdkafka/src/rdkafka_interceptor.h
    librdkafka/src/rdkafka_lz4.h
    librdkafka/src/rdkafka_metadata.h
    librdkafka/src/rdkafka_mock.h
    librdkafka/src/rdkafka_mock_int.h
    librdkafka/src/rdkafka_msg.h
    librdkafka/src/rdkafka_msgbatch.h
    librdkafka/src/rdkafka_msgset.h
    librdkafka/src/rdkafka_offset.h
    librdkafka/src/rdkafka_op.h
    librdkafka/src/rdkafka_partition.h
    librdkafka/src/rdkafka_pattern.h
    librdkafka/src/rdkafka_plugin.h
    librdkafka/src/rdkafka_proto.h
    librdkafka/src/rdkafka_queue.h
    librdkafka/src/rdkafka_request.h
    librdkafka/src/rdkafka_sasl.h
    librdkafka/src/rdkafka_sasl_oauthbearer.h
    librdkafka/src/rdkafka_ssl.h
    librdkafka/src/rdkafka_timer.h
    librdkafka/src/rdkafka_topic.h
    librdkafka/src/rdkafka_transport.h
    librdkafka/src/rdkafka_zstd.h
    librdkafka/src/rdlist.h
    librdkafka/src/rdlog.h
    librdkafka/src/rdmurmur2.h
    librdkafka/src/rdports.h
    librdkafka/src/rdposix.h
    librdkafka/src/rdrand.h
    librdkafka/src/rdregex.h
    librdkafka/src/rdsignal.h
    librdkafka/src/rdstring.h
    librdkafka/src/rdsysqueue.h
    librdkafka/src/rdtime.h
    librdkafka/src/rdtypes.h
    librdkafka/src/rdunittest.h
    librdkafka/src/rdvarint.h
    librdkafka/src/rdwin32.h
    librdkafka/src/regexp.h
    librdkafka/src/snappy.h
    librdkafka/src/snappy_compat.h
    librdkafka/src/tinycthread.h
    librdkafka/src/tinycthread_extra.h
    librdkafka/src/win32_config.h
    librdkafka/src/xxhash.h
	librdkafka/src-cpp/rdkafkacpp.h
)




add_definitions(-DLIBRDKAFKA_STATICLIB)


add_library(rdkafka ${SRC_FILES})



install (TARGETS rdkafka
         ARCHIVE DESTINATION lib COMPONENT SF3rdParties
         LIBRARY DESTINATION lib COMPONENT SF3rdParties
         RUNTIME DESTINATION bin COMPONENT SF3rdParties)

install (FILES ${INSTALL_FILES} DESTINATION include/rdkafka COMPONENT SF3rdParties)




