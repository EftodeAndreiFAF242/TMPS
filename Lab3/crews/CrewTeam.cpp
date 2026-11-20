// Lab 3 - Composite: the Composite, a team of crews that works like one crew

#include "Lab3/crews/CrewTeam.h"

#include <iostream>
#include <utility>

using namespace std;

void CrewTeam::add(unique_ptr<Crew> member) {
    // unique_ptr can only be moved
    members.push_back(move(member));
}

void CrewTeam::work(const WorkOrder& order) const {
    cout << "a team of " << members.size() << " crews goes out:\n";

    // Fiecare echipaj își face treaba
    for (const unique_ptr<Crew>& member : members) {
        cout << "  - ";
        member->work(order);
    }
}
