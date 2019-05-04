#include <iostream>
#include <iomanip>
#include <string>
#include <string.h>
#include <fstream>

#include "version.hpp"

#define NOT_SET -1
#define ENABLED 1
#define DISABLED 0

using std::endl;

void showHelp();

void invalid_command(const char *argument);

void invalid_version_file(int version);

int main(int argc, char **argv)
{
    std::string prefix = "PROGRAM", version_definition = ".version", version_file = "version";
    int major = 0, minor = 0, patch = 0, build = 0, allBuilds = 0,
            use_major = NOT_SET, use_minor = NOT_SET, use_patch = NOT_SET, use_build = NOT_SET,
            update_major = NOT_SET, update_minor = NOT_SET, update_patch = NOT_SET, update_build = NOT_SET,
            count_all_builds = NOT_SET, prefix_set = NOT_SET, version_file_set = NOT_SET;
    bool require_update = false;

    for (int it = 1; it < argc; ++it) {
        if (strcmp(argv[it], "-h") == 0 || strcmp(argv[it], "--help") == 0) {
            showHelp();

            return 0;
        } else if (strcmp(argv[it], "major") == 0) {
            update_major = ENABLED;
            require_update = true;
        } else if (strcmp(argv[it], "minor") == 0) {
            update_minor = ENABLED;
            require_update = true;
        } else if (strcmp(argv[it], "patch") == 0) {
            update_patch = ENABLED;
            require_update = true;
        } else if (strcmp(argv[it], "build") == 0) {
            update_build = ENABLED;
            require_update = true;
        } else if (strncmp(argv[it], "-i=", 3) == 0) {
            version_definition.assign(argv[it] + 3);
        } else if (strncmp(argv[it], "-o=", 3) == 0) {
            version_file.assign(argv[it] + 3);
            version_file_set = ENABLED;
            require_update = true;
        } else if (strncmp(argv[it], "-p=", 3) == 0) {
            prefix.assign(argv[it] + 3);
            prefix_set = ENABLED;
            require_update = true;
        } else if (strcmp(argv[it], "--enable-major") == 0) {
            use_major = ENABLED;
            require_update = true;
        } else if (strcmp(argv[it], "--disable-major") == 0) {
            use_major = DISABLED;
            require_update = true;
        } else if (strcmp(argv[it], "--enable-minor") == 0) {
            use_minor = ENABLED;
            require_update = true;
        } else if (strcmp(argv[it], "--disable-minor") == 0) {
            use_minor = DISABLED;
            require_update = true;
        } else if (strcmp(argv[it], "--enable-patch") == 0) {
            use_patch = ENABLED;
            require_update = true;
        } else if (strcmp(argv[it], "--disable-patch") == 0) {
            use_patch = DISABLED;
            require_update = true;
        } else if (strcmp(argv[it], "--enable-build") == 0) {
            use_build = ENABLED;
            require_update = true;
        } else if (strcmp(argv[it], "--disable-build") == 0) {
            use_build = DISABLED;
            require_update = true;
        } else if (strcmp(argv[it], "--enable-build-counter") == 0) {
            count_all_builds = ENABLED;
            require_update = true;
        } else if (strcmp(argv[it], "--disable-build-counter") == 0) {
            count_all_builds = DISABLED;
            require_update = true;
        } else {
            invalid_command(argv[it]);

            return 1;
        }
    }

    if (argc <= 1) {
        showHelp();

        return 0;
    }

    {
        std::ifstream vdef(version_definition, std::ios::in | std::ios::binary);
        if (vdef.is_open()) {
            int tmp = 0;
            std::string stmp;

            vdef >> tmp;
            if (tmp != 1) {
                invalid_version_file(tmp);
                return 2;
            }

#define LOAD_BOOL(x) if (x == NOT_SET) { vdef >> x; x = x != 0 ? ENABLED : DISABLED; } else { vdef >> tmp; }
            LOAD_BOOL(use_major);
            LOAD_BOOL(use_minor);
            LOAD_BOOL(use_patch);
            LOAD_BOOL(use_build);
            LOAD_BOOL(count_all_builds);
#undef LOAD_BOOL

            vdef >> major >> minor >> patch >> build >> allBuilds;

            if (prefix_set == NOT_SET) {
                vdef >> prefix;
            } else {
                vdef >> stmp;
            }
            if (version_file_set == NOT_SET) {
                vdef >> version_file;
            } else {
                vdef >> stmp;
            }
        } else {
            require_update = true;
        }
    }

    if (update_major != NOT_SET || update_minor != NOT_SET || update_patch != NOT_SET || update_build != NOT_SET) {
        if (update_build == ENABLED) {
            build++;
        }

        if (update_patch == ENABLED) {
            patch++;
            build = 0;
        }

        if (update_minor == ENABLED) {
            minor++;
            patch = build = 0;
        }

        if (update_major == ENABLED) {
            major++;
            minor = patch = build = 0;
        }

        if (count_all_builds == ENABLED) {
            allBuilds++;
        }
    }

    if (require_update) {
        std::ofstream vdef(version_definition, std::ios::out | std::ios::binary);

        vdef << "1" << endl;

        vdef << (use_major == NOT_SET ? 1 : use_major) << ' '
             << (use_minor == NOT_SET ? 1 : use_minor) << ' '
             << (use_patch == NOT_SET ? 1 : use_patch) << ' '
             << (use_build == NOT_SET ? 1 : use_build) << ' '
             << (count_all_builds == NOT_SET ? 0 : count_all_builds) << endl;

        vdef << major << ' ' << minor << ' ' << patch << ' ' << build << ' ' << allBuilds << endl;

        vdef << prefix << endl;
        vdef << version_file << endl;
    }

    // regenerate file
    {
        std::ofstream hfile(version_file + ".hpp", std::ios::out | std::ios::binary);
        int time = ::time(nullptr);

        hfile << "//\n"
              << "// file autogenerated by version utility\n"
              << "//\n"
              << "\n"
              << "#ifndef VERSION_FILE_HPP_AUTOGENERATED_" << time << "\n"
              << "#define VERSION_FILE_HPP_AUTOGENERATED_" << time << " " << time << "\n"
              << "\n";
        if (use_major) {
            hfile << "\t#define " << prefix << "_VERSION_MAJOR\t" << major << "\n";
        }
        if (use_minor) {
            hfile << "\t#define " << prefix << "_VERSION_MINOR\t" << minor << "\n";
        }
        if (use_patch) {
            hfile << "\t#define " << prefix << "_VERSION_PATCH\t" << patch << "\n";
        }
        if (use_build) {
            hfile << "\t#define " << prefix << "_VERSION_BUILD\t" << build << "\n";
        }

        hfile << "\n";

        hfile << "\t#define " << prefix << "_VERSION_ENCODED_WIN\t\t\""
              << (use_major ? major : 0) << '.'
              << (use_minor ? minor : 0) << '.'
              << (use_patch ? patch : 0) << '.'
              << (use_build ? build : 0)
              << "\"\n";

        hfile << "\t#define " << prefix << "_VERSION_ENCODED_INT\t\t0x"
              << std::hex
              << ((((unsigned)(use_major ? major : 0) & 0xff) << 24) +
                  (((unsigned)(use_minor ? minor : 0) & 0xff) << 16) +
                  (((unsigned)(use_patch ? patch : 0) & 0xff) << 8)  +
                  (((unsigned)(use_build ? build : 0) & 0xff) << 0))
              << std::dec
              << "U\n";
        hfile << "\t#define " << prefix << "_VERSION_ENCODED_LONG\t0x"
              << std::hex
              << (((unsigned long long)((use_major ? major : 0) & 0xffff) << 48) +
                  ((unsigned long long)((use_minor ? minor : 0) & 0xffff) << 32) +
                  ((unsigned long long)((use_patch ? patch : 0) & 0xffff) << 16)  +
                  ((unsigned long long)((use_build ? build : 0) & 0xffff) << 0))
              << std::dec
              << "ULL\n";

        if (count_all_builds) {
            hfile << "\n"
                  << "\t#define " << prefix << "_VERSION_BUILD_COUNT\t" << allBuilds << "\n";
        }

        hfile << "\n";

        if (use_major || use_minor || use_patch || use_build) {
            hfile << "\t#define " << prefix << "_VERSION_PRETTY\t\"";

            bool have_build = use_build && build > 0;
            bool have_patch = use_patch && patch > 0;
            bool have_minor = use_minor && minor > 0;

            if (use_major) {
                hfile << major;

                if (have_minor || have_patch) {
                    hfile << '.';
                }
            }

            if (use_minor && (have_minor || have_patch)) {
                hfile << minor;

                if (have_patch || have_build) {
                    hfile << '.';
                }
            }

            if (use_patch && (have_patch)) {
                hfile << patch;
            }

            if (use_build && have_build) {
                hfile << '#' << build;
            }

            hfile << "\"";
        }

        hfile << "\n"
              << "#endif // VERSION_FILE_HPP_AUTOGENERATED_" << time << "\n";
    }
}

using std::cout;

void showHelp()
{
    cout << "version v" << VERSION_VERSION_PRETTY << " (" << VERSION_VERSION_BUILD_COUNT << ")\n"
         << "usage:\n"
         << "  version [OPTIONS] [VERSION]\n"
         << "options are:\n"
         << "  -i=FILE                   Which FILE should hold information about version\n"
         << "  -o=FILE                   To what file we should put cpp version defines\n"
         << "  -p=PREFIX                 Prefix for defines\n"
         << "  --enable-major            Enable major release\n"
         << "  --disable-major           Disable major release\n"
         << "  --enable-minor            Enable minor release\n"
         << "  --disable-minor           Disable minor release\n"
         << "  --enable-patch            Enable patch release\n"
         << "  --disable-patch           Disable patch release\n"
         << "  --enable-build            Enable build release\n"
         << "  --disable-build           Disable build release\n"
         << "  --enable-build-counter    Enable build counter for all builds\n"
         << "  --disable-build-counter   Disable build counger for all builds\n"
         << endl;
}

void invalid_command(const char *argument)
{
}

void invalid_version_file(int v)
{
}