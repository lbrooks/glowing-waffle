load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_library(
    name = "lib_dice_client",
    srcs = ["dice_client.cc"],
    hdrs = ["dice_client.h"],
    defines = ["LIB_DICE_CLIENT"],
    deps = [
        "//dice/proto:dice_cc_grpc",
        "@com_github_grpc_grpc//:grpc++",
        "@com_google_absl//absl/status",
    ],
)

cc_binary(
    name = "client",
    srcs = ["client.cc"],
    defines = ["DICE_CLIENT"],
    deps = [
        ":lib_dice_client",
        "@com_github_gflags_gflags//:gflags",
    ],
)

cc_binary(
    name = "server",
    srcs = ["dice_server.cc"],
    defines = ["DICE_SERVER"],
    deps = [
        "//dice/proto:dice_cc_grpc",
        "@com_github_gflags_gflags//:gflags",
        "@com_github_grpc_grpc//:grpc++",
    ],
)
