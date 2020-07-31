/*
 * Render.cc
 *
 *  Created on: Apr 7, 2019
 *      Author: user1
 */

#include "Render.h"
#include "Logging.h"

namespace bsk {

/*************************************************/
Render::Render() {
}

/*************************************************/
Render::~Render() {
}

/*************************************************/
void Render::initialize(uint width, uint height) {

   LOGD("GL_VERSION: " << glGetString(GL_VERSION));
   LOGD("GL_RENDERER: " << glGetString(GL_RENDERER));

   //shader_program = common_get_shader_program(vertex_shader_source, fragment_shader_source);
   //pos = glGetAttribLocation(shader_program, "position");

   glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
   glViewport(0, 0, width, height);

   //glGenBuffers(1, &vbo);
   //glBindBuffer(GL_ARRAY_BUFFER, vbo);
   //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
   //glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*) 0);
   //glEnableVertexAttribArray(pos);
   //glBindBuffer(GL_ARRAY_BUFFER, 0);

}

/*************************************************/
bool Render::render() {
   glClear(GL_COLOR_BUFFER_BIT);
   //glUseProgram(shader_program);


  // glDrawArrays(GL_TRIANGLES, 0, 3);

   return true;

}

/*************************************************/
void Render::dispose() {
   //glDeleteBuffers(1, &vbo);
}


}
