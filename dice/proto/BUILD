load("@rules_proto//proto:defs.bzl", "proto_library")
load("@rules_cc//cc:defs.bzl", "cc_proto_library")
load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")

# The following three rules demonstrate the usage of the cc_grpc_library rule in
# in a mode compatible with the native proto_library and cc_proto_library rules.
proto_library(
    name = "dice_proto",
    srcs = ["dice.proto"],
)

cc_proto_library(
    name = "dice_cc_proto",
    deps = [":dice_proto"],
)

cc_grpc_library(
    name = "dice_cc_grpc",
    srcs = [":dice_proto"],
    grpc_only = True,
    visibility = ["//visibility:public"],
    deps = [":dice_cc_proto"],
)
