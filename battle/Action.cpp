#include "Action.h"

Action* ActionSet::getAction(string name)
{
    if (actions.find(name) != actions.end()) {
        return actions[name].get();
    }
    else {
        return nullptr;
    }
}

Action* ActionSet::getAction(int index)
{
    return getAction(names.at(index));
}
