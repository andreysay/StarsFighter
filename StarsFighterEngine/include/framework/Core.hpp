#pragma once
#include <memory>
#include "helpers/Logger.hpp"

static auto GLog = Helpers::Logger::GetLogger();
static Helpers::LogLevel GLoglevel = Helpers::LogLevel::Debug;
