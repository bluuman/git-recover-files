#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <regex>
#include <vector>
#include <sstream>
#include <unistd.h>
#include <fstream>

std::string exec(const char *cmd)
{
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe)
        throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get()))
    {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
            result += buffer.data();
    }
    return result;
}

int main(int argc, char *argv[])
{
    std::string cwd;
    if (argc == 2)
    {
        cwd = std::string(argv[1]);
    }
    else
    {
        cwd = std::string(getcwd(NULL, 255));
    }
    std::stringstream prune;
    prune << "cd " << cwd << " && git prune -n" << std::endl;
    std::string search = exec(prune.str().c_str());
    std::vector<std::string> blobs;
    std::smatch matches;
    std::regex blob("(.*) ");
    while (std::regex_search(search, matches, blob))
    {
        blobs.push_back(matches[1]);
        search = matches.suffix();
    }
    std::ofstream out("out.txt");
    for (int i = 0; i < blobs.size(); i++)
    {
        std::stringstream ss;
        ss << "cd " << cwd << " && git cat-file -p " << blobs[i];
        out << "[" << i << "]" << exec(ss.str().c_str()) << std::endl;
    }
}
