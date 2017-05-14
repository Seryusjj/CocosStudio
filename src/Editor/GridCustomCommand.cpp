#include "stdafx.h"
#include "GridCustomCommand.h"

GridCustomCommand::GridCustomCommand()
{
	_type = RenderCommand::Type::CUSTOM_COMMAND;//force ordering in the way we want?¿
}

GridCustomCommand::~GridCustomCommand()
{
}