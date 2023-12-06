#include "ActionHistory.h"



ActionHistory* ActionHistory::sharedInstance = NULL;

ActionHistory* ActionHistory::getInstance()
{
	return sharedInstance;
}

void ActionHistory::startRecordAction(AGameObject* gameObject)
{
	this->currentGameObject = gameObject;
	undoAction = new EditorAction(currentGameObject);
}

void ActionHistory::endRecordAction()
{
	redoAction = new EditorAction(currentGameObject);

	// After ending record, push memento to action stack
	ActionMemento* memento = new ActionMemento(undoAction, redoAction);
	actionsPerformed.push(memento);
}

bool ActionHistory::hasRemainingUndoActions()
{
	if (!actionsPerformed.empty())
		return true;
	
	return false;
}

bool ActionHistory::hasRemainingRedoActions()
{
	if (!actionsUndid.empty())
		return true;

	return false;
}

void ActionHistory::clear()
{
	// Set action performed and undid to new stack
	actionsPerformed = ActionStack();
	actionsUndid = ActionStack();
}

void ActionHistory::undoLatestAction()
{
	if(hasRemainingUndoActions())
	{
		ActionMemento* lastAction = actionsPerformed.top();

		AGameObject* owner = lastAction->getOldAction()->getOwner();

		owner->setScale(lastAction->getOldAction()->getStoredScale());
		owner->setRotation(lastAction->getOldAction()->getStoredRotation());
		owner->setPosition(lastAction->getOldAction()->getStorePos());

		// Push latest memento to undo actions, then pop in performed
		actionsUndid.push(actionsPerformed.top());
		actionsPerformed.pop();
	}
}

void ActionHistory::redoLatestAction()
{
	if (hasRemainingRedoActions())
	{
		ActionMemento* lastAction = actionsUndid.top();

		AGameObject* owner = lastAction->getNewAction()->getOwner();
		owner->setScale(lastAction->getNewAction()->getStoredScale());
		owner->setRotation(lastAction->getNewAction()->getStoredRotation());
		owner->setPosition(lastAction->getNewAction()->getStorePos());

		// Push latest memento to performed actions, then pop in undid
		actionsPerformed.push(actionsUndid.top());
		actionsUndid.pop();
	}
}

ActionHistory::ActionHistory()
{
}

ActionHistory::~ActionHistory()
{
}

void ActionHistory::initialize()
{
	sharedInstance = new ActionHistory();
}

void ActionHistory::destroy()
{
	delete sharedInstance;
}
