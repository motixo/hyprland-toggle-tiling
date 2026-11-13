#include "../include/Client.hpp"

void from_json(const json& j, WorkspaceSignature& ws) {
  j.at("id").get_to(ws.id);
  j.at("name").get_to(ws.name);
}

void from_json(const json& j, Client& client) {
  j.at("address").get_to(client.address);
  j.at("workspace").get_to(client.workspace);
  j.at("floating").get_to(client.floating);
}
