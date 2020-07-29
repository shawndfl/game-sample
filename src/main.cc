
#if 0

#include "BskDisplay.h"
#include "BskLogging.h"
#include "BskRender.h"
#include "BskHttpServer.h"

//TODO Test json content using cJSON

void Handler(ClientContext* clientContext, void* userdata) {
//   std::shared_ptr<Render> render = std::shared_ptr<Render>((Render*)userdata);

   LOGI("uri: %s", clientContext->request.getUri().c_str());
   LOGI("uriPath: %s", clientContext->request.getUriPath().c_str());
   LOGI("uriQuery: %s", clientContext->request.getUriQuery().c_str());

   std::string body = "<html><head><title>Testing</title></head><body> <b> Hello!!</b><br>";

   for (size_t i = 0; i < clientContext->request.getQueryParameters().size(); i++) {
      KeyValue pair = clientContext->request.getQueryParameters().at(i);

      //LOGI("%d: \"%s\" == \"%s\"", i, pair.key.c_str(), pair.value.c_str());
      body += pair.key + " = " + pair.value + "<br>";
   }

   body += "</body></html>";

   clientContext->response.statusCode = Response::CODE200;

   clientContext->response.appendHeader("Content-Type", "text/html; charset=ISO-8859-1");
   clientContext->response.body = body;
   clientContext->SendResponse();

   //LOGI("Is render initialized %i", render->isInitialized());

}

int main(int argc, char *argv[]) {

   std::shared_ptr<Render> render = std::shared_ptr<Render>(new Render());

   render->initialize();

   BskHttpServer server;
   server.StartServer(8080);
   server.setRequestHandler(&Handler);

   server.setUserData(render.get());

   server.JoinAcceptThread();
   //display disp;
   //disp.createWindow(1280, 1024, render.get());

   LOGI("Exit ");

   return 0;
}
#endif


#include <stdio.h>
#include <stdlib.h>

#define GLFW_INCLUDE_ES2
#include <GLFW/glfw3.h>

static const GLuint WIDTH = 800;
static const GLuint HEIGHT = 600;
static const GLchar* vertex_shader_source =
    "#version 100\n"
    "attribute vec3 position;\n"
    "void main() {\n"
    "   gl_Position = vec4(position, 1.0);\n"
    "}\n";
static const GLchar* fragment_shader_source =
    "#version 100\n"
    "void main() {\n"
    "   gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
    "}\n";
static const GLfloat vertices[] = {
        0.0f,  0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
};

GLint common_get_shader_program(const char *vertex_shader_source, const char *fragment_shader_source) {
    enum Consts {INFOLOG_LEN = 512};
    GLchar infoLog[INFOLOG_LEN];
    GLint fragment_shader;
    GLint shader_program;
    GLint success;
    GLint vertex_shader;

    /* Vertex shader */
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex_shader, INFOLOG_LEN, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
    }

    /* Fragment shader */
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment_shader, INFOLOG_LEN, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog);
    }

    /* Link shaders */
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_program, INFOLOG_LEN, NULL, infoLog);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    return shader_program;
}

int main(void) {
    GLuint shader_program, vbo;
    GLint pos;
    GLFWwindow* window;

    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    window = glfwCreateWindow(WIDTH, HEIGHT, __FILE__, NULL, NULL);
    glfwMakeContextCurrent(window);

    printf("GL_VERSION  : %s\n", glGetString(GL_VERSION) );
    printf("GL_RENDERER : %s\n", glGetString(GL_RENDERER) );

    shader_program = common_get_shader_program(vertex_shader_source, fragment_shader_source);
    pos = glGetAttribLocation(shader_program, "position");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glViewport(0, 0, WIDTH, HEIGHT);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(pos);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shader_program);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
    }
    glDeleteBuffers(1, &vbo);
    glfwTerminate();
    return EXIT_SUCCESS;
}
