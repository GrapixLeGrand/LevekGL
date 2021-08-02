#include "RenderingEngine.hpp"
#include "input/GLFWInputController.hpp"

namespace Levek {

RenderingEngine::RenderingEngine(int width, int height)
    : windowWidth(width),
    windowHeight(height) {
        /* Initialize the library */
        //int error = glfwInit();
        int err = glfwInit();
        if (!err) {
            //throw "Failed to initialize GLFW";
            LEVEK_RENDERING_FAIL("failed to initialize glfw");
        }

        //LEVEK_INFO(("glew init returned : " + std::to_string(err)).c_str());

        //setup context options
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        //Create a windowed mode window and its OpenGL context
        window = glfwCreateWindow(windowWidth, windowHeight, "Levek Engine", NULL, NULL);
        if (!window) {
            glfwTerminate();
            LEVEK_RENDERING_FAIL("Failed to initialize the window");   
        }

        // Make the window's context current
        glfwMakeContextCurrent(window);
        glfwSwapInterval(0);
        glewExperimental = GL_TRUE;

        if (glewInit() != GLEW_OK) {
            LEVEK_RENDERING_FAIL("failed to initialize glew");
            //throw "Failed to initialized GLEW";
        }
        
        // tell GL to only draw onto a pixel if the shape is closer to the viewer
        GL_CHECK(glEnable(GL_DEPTH_TEST)); // enable depth-testing
        GL_CHECK(glDepthFunc(GL_LESS)); // depth-testing interprets a smaller value as "closer"

    
		GL_CHECK(glEnable(GL_BLEND));
		GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        //glEnable(GL_CULL_FACE);
        //glDisable(GL_CULL_FACE);
        
        inputController = new GLFWInputController(window);

        //initialize ImGui
        imGuiRenderer = new ImGuiRenderer();
        imGuiRenderer->Initialize(window);
        renderer = new Renderer(windowWidth, windowHeight);
        renderer->setClearFlags(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        renderer->setClearColor(glm::vec4(0.0f));
        
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(MessageCallback, 0);
        //warning I m not sure about the parameters exactly see : https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glDebugMessageControl.xhtml
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_FALSE);
        glDebugMessageControl(GL_DEBUG_SOURCE_API, GL_DEBUG_TYPE_ERROR, GL_DONT_CARE, 0, NULL, GL_TRUE);
        glDebugMessageControl(GL_DEBUG_SOURCE_SHADER_COMPILER, GL_DEBUG_TYPE_ERROR, GL_DONT_CARE, 0, NULL, GL_TRUE); 

        lineRenderer = new LineRenderer();
        pointRenderer = new PointRenderer();
    }

    RenderingEngine::~RenderingEngine() {
        delete renderer;
        delete lineRenderer;
        delete pointRenderer;
        delete inputController;
        imGuiRenderer->Destroy();
        delete imGuiRenderer;
        glfwTerminate();
    }
};