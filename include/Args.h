/**
 * @brief Structures for argument parsing
 *
 * @file Args.h
 * @author xkrizv03
 * @author xkocic02
 */

#ifndef ARGS_H
#define ARGS_H

#include <string_view>

struct ProgramDesc {
public:
    ProgramDesc(int argc, char *argv[]);

public:
    bool verbose = false;
};

#endif