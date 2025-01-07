// #include "commands/command.h"

// class ExitCommandProvider : public console::CommandProvider {
//    public:
//     std::unique_ptr<console::Command> create() override { return std::make_unique<ExitCommand>();
//     }
// };

// class ExitCommand : public console::Command {
//    public:
//     int execute(const std::vector<std::string>& args) override {
//         std::cout << args[0] << std::endl;
//         exit(0);
//     }
// };

// class HistoryCommand : public console::Command {
//    public:
//     int execute(const std::vector<std::string>& args) override {
//         for (const auto& arg : args) {
//             std::cout << arg << " ";
//         }
//         std::cout << std::endl;
//         return 0;
//     }
// };

// class LsCommand : public console::Command {
//    public:
//     int execute(const std::vector<std::string>& args) override {
//         if (args.size() > 1) {
//             std::cerr << "ls: too many arguments\n";
//             return 1;
//         }
//         system("ls");
//         return 0;
//     }
// }