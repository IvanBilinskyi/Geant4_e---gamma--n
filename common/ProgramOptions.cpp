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
    opt.AddSwitchOption("generate_pp,pp", "generate p-><-p events");
    opt.AddSwitchOption("generate_pp_boosted,ppb",
                        "generate p-><-p events boosted as one of the protons is inside Pb");
    opt.AddSwitchOption("generate_old_pp,old_pp",
                        "generate p-><-p events in the old setup: beam energy = 40 AGeV, cut "
                        "at production vertex");
    opt.AddSwitchOption("generate_na60p,na60p", "generate na60p p->p events");
    opt.AddSwitchOption("generate_angantyr,ang",
                        "generate Pb->Pb collision events using Angantyr model");
    opt.AddSwitchOption("generate_angantyr_high_energy,angHE",
                        "generate Pb->Pb collision events using Angantyr model with 2.76 TeV "
                        "beam energy per nucleon.");
    opt.AddSwitchOption("generate_pythia_cascade,pytCasc",
                        "generate Pb->Pb collision events using Pythia cascade model");
    opt.AddSwitchOption("generate_maryna,mar", "generate events with Maryna's script");

    opt.AddValOption<int>("n_events,nev", 1000, "number of events to generate");
    opt.AddSwitchOption("openvdb,ovdb", "output particles to openvdb volume");
    opt.AddSwitchOption("plot,p", "run plotting");
    opt.AddSwitchOption("geant4gui,gui", "use gui while running Geant4 simulation");
    opt.AddSwitchOption("geant4,g4", "run Geant4 simulation");
    return opt;
}
