#pragma once
#include <stack>

#include "ActionMemento.h"
#include "EditorAction.h"

class ActionMemento;
class EditorAction;
class AGameObject;
class ActionHistory
{
public:
	typedef std::stack<ActionMemento*> ActionStack;
	static ActionHistory* getInstance();
	static void initialize();
	static void destroy();

	void startRecordAction(AGameObject* gameObject);
	void endRecordAction();
	bool hasRemainingUndoActions();
	bool hasRemainingRedoActions();
	EditorAction* undoAction;
	EditorAction* redoAction;
	void clear();

	void undoLatestAction();
	void redoLatestAction();

private:
	ActionHistory();
	~ActionHistory();
	ActionHistory(ActionHistory const&) {};
	ActionHistory& operator=(ActionHistory const&) {};

	static ActionHistory* sharedInstance;

	AGameObject* currentGameObject;

	ActionStack actionsPerformed;
	ActionStack actionsUndid;
};

