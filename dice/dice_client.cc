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

#include <gflags/gflags.h>
#include <grpcpp/grpcpp.h>

#include <iostream>
#include <memory>
#include <string>

#ifdef BAZEL_BUILD
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

DEFINE_string(dice_server, "localhost:50051",
              "Address for dice_server, default localhost:50051");

namespace brooks {
namespace dice {

class DiceRollClient {
 public:
  DiceRollClient(std::shared_ptr<Channel> channel)
      : stub_(DiceRollService::NewStub(channel)) {}

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  long Roll() {
    // Data we are sending to the server.
    DiceRollRequest request;
    request.add_roll("3d4");
    request.add_roll("2");

    // Container for the data we expect from the server.
    DiceRollResponse reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->Roll(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      return reply.total();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return -1;
    }
  }

 private:
  std::unique_ptr<DiceRollService::Stub> stub_;
};

}  // namespace dice
}  // namespace brooks

int main(int argc, char **argv) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  std::string server_address = FLAGS_dice_server;
  std::cout << "Client querying server address: " << server_address
            << std::endl;

  // Instantiate the client. It requires a channel, out of which the actual RPCs
  // are created. This channel models a connection to an endpoint (in this case,
  // localhost at port 50051). We indicate that the channel isn't authenticated
  // (use of InsecureChannelCredentials()).
  brooks::dice::DiceRollClient client(
      grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials()));

  long reply = client.Roll();
  std::cout << "client received: " << reply << std::endl;

  return 0;
}