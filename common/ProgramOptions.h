#pragma once

#include <boost/program_options.hpp>

class ProgramOptions
{
  public:
    static ProgramOptions GetDefault();
    ProgramOptions(std::string title);
    void AddSwitchOption(const std::string& name, const std::string& description);

    template <typename T>
    void AddValOption(const std::string& name, T defaultValue, const std::string& description)
    {
        options.add_options()(name.c_str(),
                              boost::program_options::value<T>()->default_value(defaultValue),
                              description.c_str());
    }

    void InitVariablesMap(int argc, char** argv);
    bool CheckArgs(int argc);

    template <typename T>
    T Get(const std::string& name)
    {
        static_assert(!std::is_same_v<T, bool>);
        return vm[name].template as<T>();
    }

    bool Get(const std::string& name)
    {
        return vm.count(name);
    }

  private:
    boost::program_options::options_description options;
    boost::program_options::variables_map vm;
};
