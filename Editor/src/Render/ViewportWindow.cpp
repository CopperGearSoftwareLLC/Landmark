#include "ViewportWindow.hpp"
void ViewportWindow::GLTriangleTest()
{
    // ---- Minimal OpenGL setup for a triangle ----

    surface->MakeCurrent();
    // 1. Vertex data
    float vertices[] = {
        0.0f,  0.5f,  0.0f, // top
        -0.5f, -0.5f, 0.0f, // bottom left
        0.5f,  -0.5f, 0.0f  // bottom right
    };

    // 2. Create VAO & VBO
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // 3. Simple shader program
    const char *vertexShaderSrc = R"(
                #version 330 core
                layout(location = 0) in vec3 aPos;
                void main() { gl_Position = vec4(aPos, 1.0); }
            )";

    const char *fragmentShaderSrc = R"(
                #version 330 core
                out vec4 FragColor;
                void main() { FragColor = vec4(1.0, 0.0, 0.0, 1.0); }
            )";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSrc, nullptr);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSrc, nullptr);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // 4. Draw the triangle immediately
    glViewport(0, 0, surface->GetSurfaceSize().x, surface->GetSurfaceSize().y);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    // Swap buffers if your IGraphicsSurface supports it
    surface->SwapBuffers();
}
void ViewportWindow::exposeEvent(QExposeEvent *)
{
    if (!surface && isExposed())
    {
        // Create your EGL surface
        EGLNativeWindowType eglWin = (EGLNativeWindowType)winId();
        IGraphicsBackend::SurfaceParams surfParams{.nativeWindow = &eglWin};
        surface = LandmarkEngine::Get().GetGraphicsBackend().CreateSurface(
            surfParams);

        const char *session = std::getenv("XDG_SESSION_TYPE");
        if (session)
            std::printf("Session type: %s\n", session);

        std::cerr << std::format("IGraphicsSurface Size {}\n",
                                 glm::to_string(surface->GetSurfaceSize()));
                                 GLTriangleTest();
    }
}
