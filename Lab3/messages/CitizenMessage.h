// Lab 3 - Bridge: the Abstraction, what city hall tells the citizen, joined to a Notifier (how it travels)

#pragma once

#include <string>

class Notifier;
struct WorkOrder;

// A message city hall sends about a work order. Two things change here, each on its own: what the
// message says (the subclasses of CitizenMessage) and how it travels (the subclasses of Notifier).
// Instead of a class for every mix, like EmailWorkDoneMessage or LetterCrewComingMessage, the
// message keeps a Notifier inside it. That pointer is the bridge between the two hierarchies.
class CitizenMessage {
public:
    explicit CitizenMessage(Notifier* channel);
    virtual ~CitizenMessage() = default;

    // Writes the text of the message and sends it through the channel.
    void sendAbout(const WorkOrder& order);

protected:
    // The text of the message. Each kind of message writes its own.
    virtual std::string text(const WorkOrder& order) const = 0;

private:
    Notifier* channel;  // the Implementor: any Notifier, the message does not know which one
};
