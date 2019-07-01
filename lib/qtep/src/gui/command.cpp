#include "command.h"

Command::Command(const QString & id)
  : mId(id)
{
}

QString Command::commandId() const
{
  return mId;
}

void Command::redo()
{
  execute();
}

void Command::undo()
{
  unexecute();
}
