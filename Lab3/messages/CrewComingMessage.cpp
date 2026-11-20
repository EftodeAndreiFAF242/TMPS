// Lab 3 - Bridge: a Refined Abstraction, tells the citizen that a crew is on its way

#include "Lab3/messages/CrewComingMessage.h"

#include "Lab2/workorders/WorkOrder.h"

using namespace std;

CrewComingMessage::CrewComingMessage(Notifier* channel) : CitizenMessage(channel) {}

string CrewComingMessage::text(const WorkOrder& order) const {
    return "A crew is on its way to " + order.address + ". The work will be done within "
           + to_string(order.deadlineDays) + " days.";
}
