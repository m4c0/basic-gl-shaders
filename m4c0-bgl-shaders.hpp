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
#ifndef M4C0BGLSHADERS_HPP
#define M4C0BGLSHADERS_HPP

#include <GL/glcorearb.h>
#include <string>

namespace m4c0 {
    class shader {
    public:
        /// !brief Wraps shader constants into a type-safe enum
        enum type {
            compute         = GL_COMPUTE_SHADER,
            fragment        = GL_FRAGMENT_SHADER,
            geometry        = GL_GEOMETRY_SHADER,
            tess_evaluation = GL_TESS_EVALUATION_SHADER,
            tess_control    = GL_TESS_CONTROL_SHADER,
            vertex          = GL_VERTEX_SHADER,
        };

        shader(type t, const std::string & src);
        ~shader();

        shader(const shader &) = delete;
        shader & operator=(const shader &) = delete;
        shader(shader &&);
        shader & operator=(shader &&);

    private:
        friend class program;

        GLuint handler;
    };

    class program {
    public:
        program();
        program(std::initializer_list<shader> shaders);
        ~program();

        program(const program &) = delete;
        program & operator=(const program &) = delete;
        program(program &&);
        program & operator=(program &&);

    private:
        GLuint handler;
    };
}

#endif

