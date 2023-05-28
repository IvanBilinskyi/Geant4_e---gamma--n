#include "ProgramOptions.h"

#include <iostream>

using namespace boost::program_options;

ProgramOptions::ProgramOptions(std::string title) : options(title) {}

void ProgramOptions::InitVariablesMap(int argc, char** argv)
{
    store(parse_command_line(argc, argv, options), vm);
    notify(vm);
}

void ProgramOptions::AddSwitchOption(const std::string& name, const std::string& description)
{
    options.add_options()(name.c_str(), description.c_str());
}

bool ProgramOptions::CheckArgs(int argc)
{
    if(vm.count("help") || argc == 1)
    {
        std::cout << options << '\n';
        return false;
    }
    return true;
}

ProgramOptions ProgramOptions::GetDefault()
{
    ProgramOptions opt("Event generation program usage");
    opt.AddSwitchOption("help,h", "produce help message");

    opt.AddValOption<int>("n_events,nev", 1000, "number of events to generate");
    opt.AddSwitchOption("geant4,g4", "run Geant4 simulation");
    opt.AddSwitchOption("geant4gui,gui", "use gui while running Geant4 simulation");
    return opt;
}
