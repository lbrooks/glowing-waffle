#include <gflags/gflags.h>
#include <grpcpp/grpcpp.h>

#include "absl/status/statusor.h"
#include "dice_client.h"

using brooks::dice::DiceRollClient;
using brooks::dice::proto::DiceRollRequest;
using brooks::dice::proto::DiceRollResponse;

DEFINE_string(dice_server, "localhost:50051",
              "Address for dice_server, default localhost:50051");

int main(int argc, char **argv) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  std::string server_address = FLAGS_dice_server;
  std::cout << "Client querying server address: " << server_address
            << std::endl;

  DiceRollClient client(
      grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials()));

  DiceRollRequest request;
  request.add_roll("3d4");
  request.add_roll("2d6");
  request.add_roll("1d20");
  request.add_roll("2");

  absl::StatusOr<DiceRollResponse> reply = client.Roll(request);
  if (reply.ok()) {
    std::cout << "Total: " << reply->total() << "\t";

    std::cout << "Rolls:";
    for (auto r : reply->roll()) {
      std::cout << " " << r;
    }
    std::cout << std::endl;
  } else {
    std::cout << "Problem with request: " << reply.status().message()
              << std::endl;
  }

  return 0;
}