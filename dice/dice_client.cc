/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "dice_client.h"

#include <grpcpp/grpcpp.h>

#include <iostream>
#include <memory>
#include <string>

#include "absl/status/statusor.h"

#ifdef LIB_DICE_CLIENT
#include "proto/dice.grpc.pb.h"
#else
#include "proto/dice.grpc.pb.h"
#endif

using brooks::proto::dice::DiceRollRequest;
using brooks::proto::dice::DiceRollResponse;
using brooks::proto::dice::DiceRollService;
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

namespace brooks {
namespace dice {

// Assembles the client's payload, sends it and presents the response back
// from the server.
absl::StatusOr<DiceRollResponse> DiceRollClient::Roll(DiceRollRequest request) {
  // Container for the data we expect from the server.
  DiceRollResponse reply;

  // Context for the client. It could be used to convey extra information to
  // the server and/or tweak certain RPC behaviors.
  ClientContext context;

  // The actual RPC.
  Status status = stub_->Roll(&context, request, &reply);

  // Act upon its status.
  if (status.ok()) {
    return reply;
  } else {
    std::cout << status.error_code() << ": " << status.error_message()
              << std::endl;
    return absl::InternalError(status.error_message());
  }
}

}  // namespace dice
}  // namespace brooks
