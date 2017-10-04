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
            { m4c0::shader::vertex,   "#version 330\nin vec2 pos; void main() { gl_Position = vec4(pos, 0, 1); }" },
            { m4c0::shader::fragment, "#version 330\nout vec4 color; void main() { color = vec4(1, 1, 1, 1); }" },
        };

        GLuint vao, vbo;

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        static float vtx[] = { 0, 0, 0, 1, 1, 0, 0.75, 0.75 };

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vtx), vtx, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    }

    void frame() override {
        m4c0::main::frame();

        // Since we don't "use" another program, you could optimize it inside
        // start(), but then you would not see the move constructor in action!
        prog.use();

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }

private:
    m4c0::program prog;
} _main;

