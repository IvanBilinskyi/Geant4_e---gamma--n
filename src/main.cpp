#include <exception>

#include "Geant4Application.h"
#include "ProgramOptions.h"

void RunGeant4(int argc, char** argv, bool useUI = false)
{
    std::unique_ptr<Geant4Application> app =
        std::make_unique<Geant4Application>(argc, argv, useUI);
    std::string command =
        useUI ? "/control/execute run_vis.mac" : "/control/execute run.mac";
    app->Execute(command);
    app->Run();
    app.reset();
}

int main(int argc, char* argv[])
{
    try
    {
        auto opt = ProgramOptions::GetDefault();
        opt.InitVariablesMap(argc, argv);
        if(opt.CheckArgs(argc) and opt.Get("geant4"))
            RunGeant4(argc, argv, opt.Get("geant4gui"));
    }
    catch(const std::exception& ex)
    {
        std::cerr << ex.what() << '\n';
    }

    return 0;
}
