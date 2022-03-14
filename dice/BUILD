load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "client",
    srcs = ["dice_client.cc"],
    defines = ["BAZEL_BUILD"],
    deps = [
        "//proto:dice_cc_grpc",
        # http_archive made this label available for binding
        "@com_github_grpc_grpc//:grpc++",
        "@com_github_gflags_gflags//:gflags",
    ],
)

cc_binary(
    name = "server",
    srcs = ["dice_server.cc"],
    defines = ["BAZEL_BUILD"],
    deps = [
        "//proto:dice_cc_grpc",
        # http_archive made this label available for binding
        "@com_github_grpc_grpc//:grpc++",
        "@com_github_gflags_gflags//:gflags",
    ],
)

