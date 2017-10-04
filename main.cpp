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
#include "m4c0-bgl-shaders.hpp"

namespace m4c0 {
    class info_log_error : public std::exception {
    public:
        typedef void (*get_fn)(GLuint, GLenum, GLint *);
        typedef void (*info_fn)(GLuint, GLsizei, GLsizei *, GLchar *);

        info_log_error(GLuint obj, get_fn g, info_fn i) {
            GLint len;

            g(obj, GL_INFO_LOG_LENGTH, &len);

            char * buf = new char[len];
            i(obj, len, nullptr, buf);
            msg = buf;
            delete[] buf;
        }

        const char * what() const noexcept {
            return msg.c_str();
        }

    private:
        std::string msg;
    };
}

m4c0::shader::shader(m4c0::shader::type t, const std::string & src) {
    handler = glCreateShader((GLenum)t);

    const GLchar * csrc = src.c_str();
    GLint len = src.length();
    glShaderSource(handler, 1, &csrc, &len);
    glCompileShader(handler);

    GLint status;
    glGetShaderiv(handler, GL_COMPILE_STATUS, &status);
    if (!status) throw info_log_error(handler, glGetShaderiv, glGetShaderInfoLog);
}
m4c0::shader::~shader() {
    if (handler) glDeleteShader(handler);
}

m4c0::shader::shader(m4c0::shader && o) {
    handler = o.handler;
    o.handler = 0;
}
m4c0::shader & m4c0::shader::operator=(m4c0::shader && o) {
    handler = o.handler;
    o.handler = 0;
    return *this;
}

m4c0::program::program() : handler(0) {
}
m4c0::program::program(std::initializer_list<shader> shaders) : handler(0) {
    handler = glCreateProgram();
    for (const shader & shader : shaders) {
        glAttachShader(handler, shader.handler);
    }
    glLinkProgram(handler);

    GLint status;
    glGetProgramiv(handler, GL_LINK_STATUS, &status);
    if (!status) throw info_log_error(handler, glGetProgramiv, glGetProgramInfoLog);
}
m4c0::program::~program() {
    if (handler) glDeleteProgram(handler);
}

m4c0::program::program(m4c0::program && o) {
    handler = o.handler;
    o.handler = 0;
}
m4c0::program & m4c0::program::operator=(m4c0::program && o) {
    handler = o.handler;
    o.handler = 0;
    return *this;
}

