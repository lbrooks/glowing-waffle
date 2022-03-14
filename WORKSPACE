##### Protobuf Rules for Bazel
##### See https://github.com/bazelbuild/rules_proto
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "rules_proto",
    strip_prefix = "rules_proto-0bc8db13f8dc8f5d435be07e276712db1ca11a91",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/rules_proto/archive/0bc8db13f8dc8f5d435be07e276712db1ca11a91.tar.gz",
        "https://github.com/bazelbuild/rules_proto/archive/0bc8db13f8dc8f5d435be07e276712db1ca11a91.tar.gz",
    ],
)
load("@rules_proto//proto:repositories.bzl", "rules_proto_dependencies", "rules_proto_toolchains")
rules_proto_dependencies()
rules_proto_toolchains()

##### gRPC Rules for Bazel
##### See https://github.com/grpc/grpc/blob/master/src/cpp/README.md#make
http_archive(
    name = "com_github_grpc_grpc",
    urls = [
        "https://github.com/grpc/grpc/archive/5d81683faacdb1793d7eaca56cb80102ba2d96e2.tar.gz",
    ],
    strip_prefix = "grpc-5d81683faacdb1793d7eaca56cb80102ba2d96e2",
)
load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")
grpc_deps()
# Not mentioned in official docs... mentioned here https://github.com/grpc/grpc/issues/20511
load("@com_github_grpc_grpc//bazel:grpc_extra_deps.bzl", "grpc_extra_deps")
grpc_extra_deps()

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
git_repository(
    name = "com_github_gflags_gflags",
    remote = "https://github.com/gflags/gflags.git",
    tag = "v2.2.2"
)