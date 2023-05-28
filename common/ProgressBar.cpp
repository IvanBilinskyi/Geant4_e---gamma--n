#include "ProgressBar.h"

#include <indicators/cursor_control.hpp>

using namespace indicators;

::ProgressBar::ProgressBar(int nEntries)
    : bar{option::BarWidth{50}, option::Fill{"-"}, option::ForegroundColor{Color::green},
          option::FontStyles{std::vector<FontStyle>{FontStyle::bold}},
          option::MaxProgress{nEntries}},
      nEntries(nEntries)
{
    show_console_cursor(false);
}

void ::ProgressBar::Tick(int iEntry)
{
    bar.set_option(
        option::PostfixText{std::to_string(iEntry + 1) + "/" + std::to_string(nEntries)});
    // increment the progress bar
    bar.tick();
}

void ::ProgressBar::Complete()
{
    bar.mark_as_completed();
    // Show cursor
    show_console_cursor(true);
}
