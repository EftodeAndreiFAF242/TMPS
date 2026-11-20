// Lab 3 - Bridge: a Refined Abstraction, tells the citizen that a crew is on its way

#pragma once

#include <string>

#include "Lab3/messages/CitizenMessage.h"

// Sent when a crew goes out: where it goes and in how many days the work will be done.
class CrewComingMessage : public CitizenMessage {
public:
    explicit CrewComingMessage(Notifier* channel);

protected:
    std::string text(const WorkOrder& order) const override;
};
