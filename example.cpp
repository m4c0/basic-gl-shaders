/*
 * basic-gl-shaders - Simple C++ wrappers for OpenGL shaders
 * Copyright (C) 2017 - Eduardo Costa
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include <m4c0-bgl-loop.hpp>

#include "m4c0-bgl-shaders.hpp"

static class _ : m4c0::main {
public:
    const char * title() override { return "Hello World"; }

    void start() override {
        m4c0::main::start();

        prog = {
            { m4c0::shader::vertex,   "#version 330" },
            { m4c0::shader::fragment, "#version 330" },
        };
    }

private:
    m4c0::program prog;
} _main;

