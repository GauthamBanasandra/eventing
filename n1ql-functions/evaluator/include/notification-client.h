//
// Created by Gautham Banasandra on 2019-02-01.
//

#ifndef NOTIFICATION_CLIENT_H
#define NOTIFICATION_CLIENT_H

#include <memory>
#include <string>

#include "constants.h"
#include "evaluator.grpc.pb.h"

class NotificationClient {
 public:
  explicit NotificationClient(const Constants &constants);

  void Log(const std::string& message);

 private:
  const Constants &const_;
  std::unique_ptr<nftp::Notification::Stub> handle_;
};

#endif //NOTIFICATION_CLIENT_H
