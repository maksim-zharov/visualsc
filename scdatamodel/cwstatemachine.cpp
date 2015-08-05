#include "cwstatemachine.h"

CWStateMachine::CWStateMachine(QString theStateName,QString theEntryRelaySlot, QString theExitRelaySlot, QString theEntryRelaySignal,QString theExitRelaySignal,QString theEntryAction, QString theExitAction):
    CWState( theStateName, theEntryRelaySlot,  theExitRelaySlot,  theEntryRelaySignal, theExitRelaySignal, theEntryAction,  theExitAction)
{

}


CWStateMachine::CWStateMachine(SCState *state):
    CWState()
{

    // a CWStateMachine is a state with children states, so it has all the things a normal state would, but we also want to keep track of each of its states/statemachines
    _myState = state;
    this->setParallel(state->isParallel());

    QString stateName;          // _stateName                       state's name in camel case and preceeding "_"
    stateName =         "_" + toCamel(state->getName())+"_"+state->getUidFirstName();

    // set the function names for this State Machine
    _stateName = stateName;
    _readyRelaySignal = "Signal_StateReady"+stateName+"()";
}

CWStateMachine::CWStateMachine(SCState *state, bool isRoot)
{
    // this constructor is for creating a state machine that is the root machine
    if(isRoot)
    {
        // a CWStateMachine is a state with children states, so it has all the things a normal state would, but we also want to keep track of each of its states/statemachines
        _myState = state;
        this->setParallel(state->isParallel());

        QString stateName;          // _stateName                       state's name in camel case and preceeding "_"
        stateName =         "_" + toCamel(state->getName())+"_"+state->getUidFirstName();

        // set the function names for this State Machine
        _stateName = stateName;
        _readyRelaySignal = "Signal_StateReady"+stateName+"()";
    }
}

CWStateMachine::~CWStateMachine()
{

}

bool CWStateMachine::isParallel()
{
    return _parallel;
}
void CWStateMachine::setParallel(bool parallel)
{
    _parallel = parallel;
}

void CWStateMachine::createSignalsAndSlots()
{
    // link the root machine's state name
    QString stateName;          // _stateName                       state's name in camel case and preceeding "_"
    QString entryRelaySlot;     // Slot_StateEntry_stateName        QState's private corresponding entry slot called when a transition leads to this state
    QString exitRelaySlot;      // Slot_StateExit_stateName         QState's private corresponding exit slot called when a transition exits this state
    QString entryRelaySignal;   // Signal_StateEntry_stateName      QState's public signal connected to its private entered() signal
    QString exitRelaySignal;    // Signal_StateExit_stateName       QState's public signal connected to its private exited() signal
    QString entryAction;        // EntryAction_eventName            signal that is emitted in the entry relay slot
    QString exitAction;         // ExitAction_eventName             signal that is emitted in the exit relay slot

    SCState* state;
    CWState* cwState;


    QList<SCTransition*> transitions;
    SCTransition* trans;
    QString eventName;
    QString relaySignal;
    QString targetName;
    CWTransition* cwTransition;


    QList<SCState*> directChildren;
    _myState->getStates(directChildren);

    // for each child state, determine its QState name, its relay slot function name, and its relay slot signal name.
    // also for each of the out transitions of each child, determine the transition's event name and relay signal name
    for(int i = 0 ; i < directChildren.size();i++)
    {
        state = directChildren.at(i);
        stateName =         "_" + toCamel(state->getName())+"_"+state->getUidFirstName();

        entryRelaySignal =  "Signal_StateEntry"+stateName+"()";
        exitRelaySignal =   "Signal_StateExit"+stateName+"()";

        entryRelaySlot =    "Slot_StateEntry" + stateName+"()";
        exitRelaySlot =     "Slot_StateExit"+ stateName+"()";

        entryAction = state->attributes.value("entryAction")->asString();

        if(!entryAction.isEmpty())
        {
            qDebug()<<"writing entry action: " <<entryAction;
            entryAction =   "EntryAction_"+toCamel(entryAction)+"()";
            qDebug()<<"here's entry action: " <<entryAction;
        }

        exitAction = state->attributes.value("exitAction")->asString();
        if(!exitAction.isEmpty())
        {
            exitAction =    "ExitAction_" +toCamel(exitAction)+"()";
        }

        // create this codewriter state and link them using a QHash
        cwState = new CWState(stateName,entryRelaySlot,exitRelaySlot,entryRelaySignal,exitRelaySignal,entryAction,exitAction);
        cwState->setState(state);   // give it a link back to its data model
        _states.append(cwState);


        // for each out transition, determine the transition's event name and relay signal name
        transitions.clear();
        state->getTransitions(transitions);
        for(int k = 0 ; k < transitions.size(); k++)
        {
            trans = transitions.at(k);
            eventName = "Event_"+toCamel(trans->getEventName())+"_"+trans->getUidFirstName()+"()";
            relaySignal = "Relay_"+eventName;
            targetName = "_"+toCamel(trans->targetState()->getName())+"_"+trans->targetState()->getUidFirstName();

            // create a new codewriter transition and link them with the state's Transition QHash
            cwTransition = new CWTransition(eventName, relaySignal, targetName);
            cwState->insertTransition( cwTransition);
        }

        // determine the inital state
        if(state->isInitial())
        {
            qDebug() << "CWStateMachine setting initial state to: " << state->objectName();
            _initialState = state;
        }
    }
}

