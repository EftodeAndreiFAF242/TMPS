// Lab 3 - Bridge: a Refined Abstraction, tells the citizen that the work is done

#pragma once

#include <string>

#include "Lab3/messages/CitizenMessage.h"

// Sent when the crew has finished: where the work was done and for which report.
class WorkDoneMessage : public CitizenMessage {
public:
    explicit WorkDoneMessage(Notifier* channel);

protected:
    std::string text(const WorkOrder& order) const override;
};
