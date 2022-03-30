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

#include <cstdlib>
#include <ctime>
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
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

DEFINE_string(port, "50051",
              "Port number for service to run on, default 50051");

namespace brooks {
namespace dice {

// Logic and data behind the server's behavior.
class DiceRollServiceImpl final : public DiceRollService::Service {
  Status Roll(ServerContext *context, const DiceRollRequest *request,
              DiceRollResponse *reply) override {
    long res = 0;

    std::cout << "Roll: ";
    for (int i = 0; i < request->roll_size(); i++) {
      if (i != 0) {
        std::cout << " + ";
      }
      std::cout << request->roll(i);
    }
    std::cout << std::endl;

    for (auto d : request->roll()) {
      std::size_t found = d.find("d");
      if (found != std::string::npos) {
        int quantity = std::stoi(d.substr(0, found));
        int sides = std::stoi(d.substr(found + 1));

        std::cout << "d" << sides << ": [";

        for (int r = 0; r < quantity; r++) {
          auto roll = (rand() % sides) + 1;
          res += roll;
          reply->add_roll(roll);

          if (r != 0) {
            std::cout << ", ";
          }
          std::cout << roll;
        }

        std::cout << "]" << std::endl;
      } else {
        res += std::stoi(d);
      }
    }

    reply->set_total(res);
    return Status::OK;
  }
};

void RunServer() {
  std::string address = "0.0.0.0";
  std::string port = FLAGS_port;
  std::string server_address = address + ":" + port;
  DiceRollServiceImpl service;

  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  // Finally assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
}
}  // namespace dice
}  // namespace brooks

int main(int argc, char **argv) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  std::srand(std::time(0));  // Initialize random number generator.

  brooks::dice::RunServer();

  return 0;
}