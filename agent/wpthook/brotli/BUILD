# Description:
#   Brotli is a generic-purpose lossless compression algorithm.

package(
    default_visibility = ["//visibility:public"],
)

licenses(["notice"])  # MIT

exports_files(["LICENSE"])

STRICT_C_OPTIONS = [
    "--pedantic-errors",
    "-Wall",
    "-Wconversion",
    "-Werror",
    "-Wextra",
    "-Wlong-long",
    "-Wmissing-declarations",
    "-Wmissing-prototypes",
    "-Wno-strict-aliasing",
    "-Wshadow",
    "-Wsign-compare",
]

filegroup(
    name = "public_headers",
    srcs = glob(["include/brotli/*.h"]),
)

filegroup(
    name = "common_headers",
    srcs = glob(["common/*.h"]),
)

filegroup(
    name = "common_sources",
    srcs = glob(["common/*.c"]),
)

filegroup(
    name = "dec_headers",
    srcs = glob(["dec/*.h"]),
)

filegroup(
    name = "dec_sources",
    srcs = glob(["dec/*.c"]),
)

filegroup(
    name = "enc_headers",
    srcs = glob(["enc/*.h"]),
)

filegroup(
    name = "enc_sources",
    srcs = glob(["enc/*.c"]),
)

cc_library(
    name = "brotli",
    hdrs = [":public_headers"],
    copts = STRICT_C_OPTIONS,
    includes = ["include"],
)

cc_library(
    name = "brotli_common",
    srcs = [":common_sources"],
    hdrs = [":common_headers"],
    copts = STRICT_C_OPTIONS,
    deps = [":brotli"],
)

cc_library(
    name = "brotli_dec",
    srcs = [":dec_sources"],
    hdrs = [":dec_headers"],
    copts = STRICT_C_OPTIONS,
    deps = [":brotli_common"],
)

cc_library(
    name = "brotli_enc",
    srcs = [":enc_sources"],
    hdrs = [":enc_headers"],
    copts = STRICT_C_OPTIONS,
    linkopts = ["-lm"],
    deps = [":brotli_common"],
)

cc_binary(
    name = "bro",
    srcs = ["tools/bro.c"],
    copts = STRICT_C_OPTIONS,
    linkstatic = 1,
    deps = [
        ":brotli_dec",
        ":brotli_enc",
    ],
)
