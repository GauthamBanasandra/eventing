//
// Created by Gautham Banasandra on 2019-02-01.
//
#include <grpc++/grpc++.h>
#include <thread>
#include <string>

#include "notification-client.h"

NotificationClient::NotificationClient(const Constants &constants):const_(constants) {
  auto channel = grpc::CreateChannel("127.0.0.1:" + const_.notification_port,
                                     grpc::InsecureChannelCredentials());
  handle_ = nftp::Notification::NewStub(channel);
}

void NotificationClient::Log(const std::string &message) {
  grpc::ClientContext context;
  nftp::Log log;
  std::hash<std::thread::id> hasher;
  std::size_t thread_id = hasher(std::this_thread::get_id());
  log.set_evaluatorid(const_.evaluator_id + " " + std::to_string(thread_id));
  log.set_msg(message);
  nftp::Void void_resp;
  handle_->Logger(&context, log, &void_resp);
}
