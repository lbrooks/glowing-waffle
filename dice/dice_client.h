#pragma once
#include <grpcpp/grpcpp.h>

#include <iostream>
#include <memory>
#include <string>

#include "absl/status/statusor.h"

#ifdef BAZEL_BUILD
#include "proto/dice.grpc.pb.h"
#else
#include "proto/dice.grpc.pb.h"
#endif

using brooks::proto::dice::DiceRollRequest;
using brooks::proto::dice::DiceRollResponse;
using brooks::proto::dice::DiceRollService;
using grpc::Channel;

namespace brooks {
namespace dice {

class DiceRollClient {
 public:
  DiceRollClient(std::shared_ptr<Channel> channel)
      : stub_(DiceRollService::NewStub(channel)) {}

  absl::StatusOr<DiceRollResponse> Roll(DiceRollRequest request);

 private:
  std::unique_ptr<DiceRollService::Stub> stub_;
};

}  // namespace dice
}  // namespace brooks
