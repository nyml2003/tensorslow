#include "Terminal.h"
#include "TerminalStrategy.h"

namespace tensorslow {
ConsoleTerminal::ConsoleTerminal()
  : Terminal(std::make_unique<StardardTerminalStrategy>()) {}
}  // namespace tensorslow