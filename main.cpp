#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main() {
    // ��ʼ�� GLFW
    if (!glfwInit()) {
        std::cerr << "GLFW ��ʼ��ʧ�ܣ�" << std::endl;
        return -1;
    }

    // ��������
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Example", nullptr, nullptr);
    if (!window) {
        std::cerr << "�޷��������ڣ�" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // ��ʼ�� GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "GLEW ��ʼ��ʧ�ܣ�" << std::endl;
        return -1;
    }

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    // ��Ⱦѭ��
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // ��Ⱦ����...

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
