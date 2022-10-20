#include <array>
#include <ostream>
#include <string>
#include <cstdio>
#include <iostream>

// Re implementation of secure and advanced command execution using standard C++, No logging or output for this code base, this is a rewrite of Raymiorg's resulter written using the tabnine AI https://github.com/RaymiiOrg/cpp-command-output/blob/master/command.h
namespace ExecutionEngine {
    struct Res {
        std::string o;
        int es;
        friend std::ostream & operator<<(std::ostream &ostreamer, const Res &streamer) {
            return ostreamer;
        }
        bool operator==(const Res &other) const {
            return o == other.o && es == other.es;
        }
        bool operator!=(const Res &other) const {
            return!(*this == other);
        }
    };
    class Execution {
        public:
            static Res EngineExec(const std::string &command) {
                int e_code = 0;
                std::array<char, 8192> buf{};
                std::string result;
                #ifdef _WIN32
                    #define popen _popen
                    #define pclose _pclose
                    #define WEXITSTATUS
                #endif
                FILE *pipe = popen(command.c_str(), "r");
                if (pipe == nullptr) {
                     throw std::runtime_error("popen() failed!");
                }
                try {
                    std::size_t br;
                    while (
                            (
                                br = std::fread(
                                                buf.data(), sizeof(
                                                                    buf.at(0)
                                                                ), sizeof(
                                                                            buf
                                                                        ), pipe
                                                                                    )
                                                                                        ) != 0) {
                                                                                                result += std::string(buf.data(), br);
                }
                } catch(...) {
                    pclose(pipe);
                    throw;
                }
                int res = pclose(pipe);
                e_code = WEXITSTATUS(res);
                return Res {
                    result,
                    e_code
                };
            }
    };
};
