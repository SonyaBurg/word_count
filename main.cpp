#include <iostream>
#include <cstring>
#include <fstream>
#include <streambuf>
#include <map>
#include <functional>

class WordCount {
    bool show_lines = false, show_words = false, show_bytes = false;
    int lines = 0, words = 0, bytes = 0;
    const std::map<std::string, std::function<void()>> choose_mode = {
            {"-l",   [this]() { show_lines = true; }},
            {"-lc",  [this]() {
                show_lines = true;
                show_bytes = true;
            }},
            {"-cl",   [this]() {
                show_lines = true;
                show_bytes = true;
            }},
            {"-lw",  [this]() {
                show_words = true;
                show_lines = true;
            }},
            {"-wl",  [this]() {
                show_words = true;
                show_lines = true;
            }},
            {"-w",   [this]() {
                show_words = true;
            }},
            {"-wc",  [this]() {
                show_words = true;
                show_bytes = true;
            }},
            {"-cw",  [this]() {
                show_words = true;
                show_bytes = true;
            }},
            {"-c",   [this]() {
                show_bytes = true;
            }},
            {"-cwl", [this]() {
                show_words = true;
                show_bytes = true;
                show_lines = true;
            }},
            {"-clw", [this]() {
                show_words = true;
                show_bytes = true;
                show_lines = true;
            }},
            {"-wcl", [this]() {
                show_words = true;
                show_bytes = true;
                show_lines = true;
            }},
            {"-wlc", [this]() {
                show_words = true;
                show_bytes = true;
                show_lines = true;
            }},
            {"-lwc", [this]() {
                show_words = true;
                show_bytes = true;
                show_lines = true;
            }},
            {"-lcw", [this]() {
                show_words = true;
                show_bytes = true;
                show_lines = true;
            }}
    };
public:
    bool set_mode(const char *mode) {
        auto it = choose_mode.find(mode);
        if (it != choose_mode.end()) {
            it->second();
            return false;
        }
        return true;
    }

    inline void count(std::istream &in) {
        char cur = '\0';
        char last = '\0';
        while (in.get(cur)) {
            if (cur == '\n' || (cur == '\f' && last == '\r')) {
                lines++;
            } else {
                bytes++;
            }
            if (!std::isalnum(cur) && std::isalnum(last)) {
                words++;
            }
            last = cur;
        }
        if (bytes > 0) {
            if (std::isalnum(last)) {
                words++;
            }
        }
        if (!show_bytes && !show_lines && !show_words) show_bytes = show_words = show_lines = true;
        if (show_lines) std::cout << lines << " ";
        if (show_words) std::cout << words << " ";
        if (show_bytes) std::cout << bytes << " ";
    }
};


int main(int argc, char **argv) {

    bool from_file = false;
    bool res;
    WordCount wordCount;
    for (int i = 1; i < argc; ++i) {
        res = wordCount.set_mode(argv[i]);
        if (i < argc - 1 && res) {
            std::cout << "Unknown command" << std::endl;
            exit(1);
        }
        from_file |= res;
    }

    if (from_file) {
        std::ifstream input_file(argv[argc - 1]);
        if (!input_file) {
            std::cerr << "File not found" << std::endl;
            return 1;
        }
        wordCount.count(input_file);
        std::cout << argv[argc - 1];
    } else {
        wordCount.count(std::cin);
    }
    return 0;
}
