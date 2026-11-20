// Lab 3 - Composite: the Composite, a team of crews that works like one crew

#include "Lab3/crews/CrewTeam.h"

#include <iostream>
#include <utility>

using namespace std;

void CrewTeam::add(unique_ptr<Crew> member) {
    // A unique_ptr can't be copied, only moved, so the team becomes the only owner of the crew.
    members.push_back(move(member));
}

void CrewTeam::work(const WorkOrder& order) const {
    cout << "a team of " << members.size() << " crews goes out:\n";

    // The team does not do the job itself and never asks what kind of crew a member is. It calls
    // work() on each member, and a member that is a team does the same with its own crews.
    for (const unique_ptr<Crew>& member : members) {
        cout << "  - ";
        member->work(order);
    }
}
