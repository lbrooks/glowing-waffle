#pragma once
#include <grpcpp/grpcpp.h>

#include <iostream>
#include <memory>
#include <string>

#include "absl/status/statusor.h"

#ifdef LIB_DICE_CLIENT
#include "dice/proto/dice.grpc.pb.h"
#else
#include "dice/proto/dice.grpc.pb.h"
#endif

using brooks::dice::proto::DiceRollRequest;
using brooks::dice::proto::DiceRollResponse;
using brooks::dice::proto::DiceRollService;
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
