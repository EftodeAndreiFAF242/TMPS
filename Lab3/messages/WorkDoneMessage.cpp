// Lab 3 - Bridge: a Refined Abstraction, tells the citizen that the work is done

#include "Lab3/messages/WorkDoneMessage.h"

#include "Lab2/workorders/WorkOrder.h"

using namespace std;

WorkDoneMessage::WorkDoneMessage(Notifier* channel) : CitizenMessage(channel) {}

string WorkDoneMessage::text(const WorkOrder& order) const {
    return "The work at " + order.address + " is done. Thank you for report #"
           + to_string(order.reportId) + ".";
}
