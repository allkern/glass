#pragma once

#ifndef GLASS_USE_GL_LOADER
#include "gl.hpp"
#endif

#include "log.hpp"

#include <cstring>
#include <algorithm>

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <initializer_list>

namespace glass {
#ifndef GLASS_USE_GL_LOADER
    typedef void* (*get_proc_address_t)(const char*);

    PFNGLCREATESHADERPROC            __glassCreateShader;
    PFNGLSHADERSOURCEPROC            __glassShaderSource;
    PFNGLCOMPILESHADERPROC           __glassCompileShader;
    PFNGLGETSHADERIVPROC             __glassGetShaderiv;
    PFNGLGETSHADERINFOLOGPROC        __glassGetShaderInfoLog;
    PFNGLDELETESHADERPROC            __glassDeleteShader;
    PFNGLATTACHSHADERPROC            __glassAttachShader;
    PFNGLCREATEPROGRAMPROC           __glassCreateProgram;
    PFNGLLINKPROGRAMPROC             __glassLinkProgram;
    PFNGLVALIDATEPROGRAMPROC         __glassValidateProgram;
    PFNGLGETPROGRAMIVPROC            __glassGetProgramiv;
    PFNGLGETPROGRAMINFOLOGPROC       __glassGetProgramInfoLog;
    PFNGLUSEPROGRAMPROC              __glassUseProgram;
    PFNGLBINDFRAGDATALOCATIONPROC    __glassBindFragDataLocation;
    PFNGLGETUNIFORMLOCATIONPROC      __glassGetUniformLocation;
    PFNGLUNIFORM1FPROC               __glassUniform1f;
    PFNGLUNIFORM2FPROC               __glassUniform2f;
    PFNGLUNIFORM3FPROC               __glassUniform3f;
    PFNGLUNIFORM4FPROC               __glassUniform4f;
    PFNGLUNIFORM1IPROC               __glassUniform1i;
    PFNGLUNIFORM2IPROC               __glassUniform2i;
    PFNGLUNIFORM3IPROC               __glassUniform3i;
    PFNGLUNIFORM4IPROC               __glassUniform4i;
    PFNGLUNIFORM1UIPROC              __glassUniform1ui;
    PFNGLUNIFORM2UIPROC              __glassUniform2ui;
    PFNGLUNIFORM3UIPROC              __glassUniform3ui;
    PFNGLUNIFORM4UIPROC              __glassUniform4ui;
    PFNGLGENVERTEXARRAYSPROC         __glassGenVertexArrays;
    PFNGLBINDVERTEXARRAYPROC         __glassBindVertexArray;
    PFNGLGENBUFFERSPROC              __glassGenBuffers;
    PFNGLBINDBUFFERPROC              __glassBindBuffer;
    PFNGLBUFFERDATAPROC              __glassBufferData;
    PFNGLVERTEXATTRIBPOINTERPROC     __glassVertexAttribPointer;
    PFNGLENABLEVERTEXATTRIBARRAYPROC __glassEnableVertexAttribArray;
    PFNGLACTIVETEXTUREPROC           __glassActiveTexture;
    PFNGLGENFRAMEBUFFERSPROC         __glassGenFramebuffers;
    PFNGLBINDFRAMEBUFFERPROC         __glassBindFramebuffer;
    PFNGLFRAMEBUFFERTEXTUREPROC      __glassFramebufferTexture;
    PFNGLFRAMEBUFFERTEXTURE2DPROC    __glassFramebufferTexture2D;
    PFNGLDRAWBUFFERSPROC             __glassDrawBuffers;
    PFNGLCHECKFRAMEBUFFERSTATUSPROC  __glassCheckFramebufferStatus;
    PFNGLGETTEXTUREIMAGEEXTPROC      __glassGetTextureImage;
    PFNGLGENTEXTURESPROC             __glassGenTextures;
    PFNGLBINDTEXTUREPROC             __glassBindTexture;
    PFNGLTEXPARAMETERIPROC           __glassTexParameteri;
    PFNGLTEXPARAMETERFPROC           __glassTexParameterf;
    PFNGLTEXIMAGE2DPROC              __glassTexImage2D;
    PFNGLTEXSUBIMAGE2DPROC           __glassTexSubImage2D;
    PFNGLDRAWARRAYSPROC              __glassDrawArrays;
    PFNGLCLEARCOLORPROC              __glassClearColor;
    PFNGLCLEARPROC                   __glassClear;
    PFNGLREADPIXELSPROC              __glassReadPixels;

#define glCreateShader               __glassCreateShader
#define glShaderSource               __glassShaderSource
#define glCompileShader              __glassCompileShader
#define glGetShaderiv                __glassGetShaderiv
#define glGetShaderInfoLog           __glassGetShaderInfoLog
#define glDeleteShader               __glassDeleteShader
#define glAttachShader               __glassAttachShader
#define glCreateProgram              __glassCreateProgram
#define glLinkProgram                __glassLinkProgram
#define glValidateProgram            __glassValidateProgram
#define glGetProgramiv               __glassGetProgramiv
#define glGetProgramInfoLog          __glassGetProgramInfoLog
#define glUseProgram                 __glassUseProgram
//#define glBindFragDataLocation       __glassBindFragDataLocation
#define glGetUniformLocation         __glassGetUniformLocation
#define glUniform1f                  __glassUniform1f
#define glUniform2f                  __glassUniform2f
#define glUniform3f                  __glassUniform3f
#define glUniform4f                  __glassUniform4f
#define glUniform1i                  __glassUniform1i
#define glUniform2i                  __glassUniform2i
#define glUniform3i                  __glassUniform3i
#define glUniform4i                  __glassUniform4i
#define glUniform1ui                 __glassUniform1ui
#define glUniform2ui                 __glassUniform2ui
#define glUniform3ui                 __glassUniform3ui
#define glUniform4ui                 __glassUniform4ui
#define glGenVertexArrays            __glassGenVertexArrays
#define glBindVertexArray            __glassBindVertexArray
#define glGenBuffers                 __glassGenBuffers
#define glBindBuffer                 __glassBindBuffer
#define glBufferData                 __glassBufferData
#define glVertexAttribPointer        __glassVertexAttribPointer
#define glEnableVertexAttribArray    __glassEnableVertexAttribArray
#define glActiveTexture              __glassActiveTexture
#define glGenFramebuffers            __glassGenFramebuffers
#define glBindFramebuffer            __glassBindFramebuffer
#define glFramebufferTexture         __glassFramebufferTexture
#define glFramebufferTexture2D       __glassFramebufferTexture2D
#define glDrawBuffers                __glassDrawBuffers
#define glCheckFramebufferStatus     __glassCheckFramebufferStatus
//#define glGetTextureImage            __glassGetTextureImage
#define glGenTextures                __glassGenTextures
#define glBindTexture                __glassBindTexture
#define glTexParameteri              __glassTexParameteri
#define glTexParameterf              __glassTexParameterf
#define glTexImage2D                 __glassTexImage2D
#define glTexSubImage2D              __glassTexSubImage2D
#define glDrawArrays                 __glassDrawArrays
//#define glClearColor                 __glassClearColor
//#define glClear                      __glassClear
#define glReadPixels                 __glassReadPixels
#endif

    /**
	 *  \brief Initialize Glass, this loads all necessary OpenGL functions.
     *         If GLASS_USE_GL_LOADER is defined, then only the logger will
     *         be initialized
	 *  
	 *  \param get_proc_address_fn Pointer to a function that gets the
     *                             address of an OpenGL function given a
     *                             const char*.
	 */
    void init(get_proc_address_t get_proc_address_fn = nullptr) {
#ifndef GLASS_USE_GL_LOADER
        glCreateShader              = (PFNGLCREATESHADERPROC)get_proc_address_fn("glCreateShader");
        glShaderSource              = (PFNGLSHADERSOURCEPROC)get_proc_address_fn("glShaderSource");
        glCompileShader             = (PFNGLCOMPILESHADERPROC)get_proc_address_fn("glCompileShader");
        glGetShaderiv               = (PFNGLGETSHADERIVPROC)get_proc_address_fn("glGetShaderiv");
        glGetShaderInfoLog          = (PFNGLGETSHADERINFOLOGPROC)get_proc_address_fn("glGetShaderInfoLog");
        glDeleteShader              = (PFNGLDELETESHADERPROC)get_proc_address_fn("glDeleteShader");
        glAttachShader              = (PFNGLATTACHSHADERPROC)get_proc_address_fn("glAttachShader");
        glCreateProgram             = (PFNGLCREATEPROGRAMPROC)get_proc_address_fn("glCreateProgram");
        glLinkProgram               = (PFNGLLINKPROGRAMPROC)get_proc_address_fn("glLinkProgram");
        glValidateProgram           = (PFNGLVALIDATEPROGRAMPROC)get_proc_address_fn("glValidateProgram");
        glGetProgramiv              = (PFNGLGETPROGRAMIVPROC)get_proc_address_fn("glGetProgramiv");
        glGetProgramInfoLog         = (PFNGLGETPROGRAMINFOLOGPROC)get_proc_address_fn("glGetProgramInfoLog");
        glUseProgram                = (PFNGLUSEPROGRAMPROC)get_proc_address_fn("glUseProgram");
        //glBindFragDataLocation      = (PFNGLBINDFRAGDATALOCATIONPROC)get_proc_address_fn("glBindFragDataLocation");
        glGetUniformLocation        = (PFNGLGETUNIFORMLOCATIONPROC)get_proc_address_fn("glGetUniformLocation");
        glUniform1f                 = (PFNGLUNIFORM1FPROC)get_proc_address_fn("glUniform1f");
        glUniform2f                 = (PFNGLUNIFORM2FPROC)get_proc_address_fn("glUniform2f");
        glUniform3f                 = (PFNGLUNIFORM3FPROC)get_proc_address_fn("glUniform3f");
        glUniform4f                 = (PFNGLUNIFORM4FPROC)get_proc_address_fn("glUniform4f");
        glUniform1i                 = (PFNGLUNIFORM1IPROC)get_proc_address_fn("glUniform1i");
        glUniform2i                 = (PFNGLUNIFORM2IPROC)get_proc_address_fn("glUniform2i");
        glUniform3i                 = (PFNGLUNIFORM3IPROC)get_proc_address_fn("glUniform3i");
        glUniform4i                 = (PFNGLUNIFORM4IPROC)get_proc_address_fn("glUniform4i");
        glUniform1ui                = (PFNGLUNIFORM1UIPROC)get_proc_address_fn("glUniform1ui");
        glUniform2ui                = (PFNGLUNIFORM2UIPROC)get_proc_address_fn("glUniform2ui");
        glUniform3ui                = (PFNGLUNIFORM3UIPROC)get_proc_address_fn("glUniform3ui");
        glUniform4ui                = (PFNGLUNIFORM4UIPROC)get_proc_address_fn("glUniform4ui");
        glGenVertexArrays           = (PFNGLGENVERTEXARRAYSPROC)get_proc_address_fn("glGenVertexArrays");
        glBindVertexArray           = (PFNGLBINDVERTEXARRAYPROC)get_proc_address_fn("glBindVertexArray");
        glGenBuffers                = (PFNGLGENBUFFERSPROC)get_proc_address_fn("glGenBuffers");
        glBindBuffer                = (PFNGLBINDBUFFERPROC)get_proc_address_fn("glBindBuffer");
        glBufferData                = (PFNGLBUFFERDATAPROC)get_proc_address_fn("glBufferData");
        glVertexAttribPointer       = (PFNGLVERTEXATTRIBPOINTERPROC)get_proc_address_fn("glVertexAttribPointer");
        glEnableVertexAttribArray   = (PFNGLENABLEVERTEXATTRIBARRAYPROC)get_proc_address_fn("glEnableVertexAttribArray");
        glGenFramebuffers           = (PFNGLGENFRAMEBUFFERSPROC)get_proc_address_fn("glGenFramebuffers");
        glBindFramebuffer           = (PFNGLBINDFRAMEBUFFERPROC)get_proc_address_fn("glBindFramebuffer");
        glFramebufferTexture        = (PFNGLFRAMEBUFFERTEXTUREPROC)get_proc_address_fn("glFramebufferTexture");
        glFramebufferTexture2D      = (PFNGLFRAMEBUFFERTEXTURE2DPROC)get_proc_address_fn("glFramebufferTexture2D");
        glDrawBuffers               = (PFNGLDRAWBUFFERSPROC)get_proc_address_fn("glDrawBuffers");
        glCheckFramebufferStatus    = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)get_proc_address_fn("glCheckFramebufferStatus");
        //glGetTextureImage           = (PFNGLGETTEXTUREIMAGEEXTPROC)get_proc_address_fn("glGetTextureImage");
        glGenTextures               = (PFNGLGENTEXTURESPROC)get_proc_address_fn("glGenTextures");
        glBindTexture               = (PFNGLBINDTEXTUREPROC)get_proc_address_fn("glBindTexture");
        glTexParameteri             = (PFNGLTEXPARAMETERIPROC)get_proc_address_fn("glTexParameteri");
        glTexParameterf             = (PFNGLTEXPARAMETERFPROC)get_proc_address_fn("glTexParameterf");
        glTexImage2D                = (PFNGLTEXIMAGE2DPROC)get_proc_address_fn("glTexImage2D");
        glTexSubImage2D             = (PFNGLTEXSUBIMAGE2DPROC)get_proc_address_fn("glTexSubImage2D");
        glDrawArrays                = (PFNGLDRAWARRAYSPROC)get_proc_address_fn("glDrawArrays");
        //glClearColor                = (PFNGLCLEARCOLORPROC)get_proc_address_fn("glClearColor");
        //glClear                     = (PFNGLCLEARPROC)get_proc_address_fn("glClear");
        glReadPixels                = (PFNGLREADPIXELSPROC)get_proc_address_fn("glReadPixels");
        glActiveTexture             = (PFNGLACTIVETEXTUREPROC)get_proc_address_fn("glActiveTexture");
#endif
        _log::init("glass");
    }

    std::string m_base_frag_header =
        "#version 130\n"
        "in vec2 frag_coord;\n"
        "out vec4 frag_color;\n";
    
    std::string m_base_vert_header =
        "#version 130\n"
        "out vec2 frag_coord;\n";

    // std::string default_vert_shader =
    //     "void main() {\n"
    //     "    gl_Position = gl_Vertex;\n"
    //     "    vec2 factor = resolution / target_resolution;\n"
    //     "    vec2 normalized = ((gl_Position.xy) + vec2(1.0)) / 2.0;\n"
    //     "    frag_coord = normalized * (resolution * factor);\n"
    //     "}";

    std::string default_vert_shader =
        "void main() {\n"
        "    gl_Position = gl_Vertex;\n"
        "    vec2 normalized = (gl_Position.xy + vec2(1.0)) / 2.0;\n"
        "    frag_coord = normalized * resolution.xy;\n"
        "}\n";
    
    std::string scaler_frag_shader =
        "void main() {\n"
        "    vec2 flipped = vec2(frag_coord.x, resolution.y - frag_coord.y) / resolution.xy;\n"
        "    vec2 scaled = flipped * (input_resolution.xy / resolution.xy);\n"
        "    frag_color = texture(input_texture, scaled);\n"
        "}\n";

    enum uniform_type_t {
        ut_1f,
        ut_1i,
        ut_1ui,
        ut_2f,
        ut_2i,
        ut_2ui,
        ut_3f,
        ut_3i,
        ut_3ui,
        ut_4f,
        ut_4i,
        ut_4ui,
        ut_sampler2d
    };

    std::string uniform_type_names[] = {
        "float",
        "int",
        "uint",
        "vec2",
        "ivec2",
        "uvec2",
        "vec3",
        "ivec3",
        "uvec3",
        "vec4",
        "ivec4",
        "uvec4",
        "sampler2D"
    };

    /** Helper struct for dealing with uniforms.
     *  Automatically selects the correct glUniformXX function
     *  given arguments passed to uniform_t::update()
     */
    struct uniform_t {
        int id;
        bool on_source = false;

        uniform_type_t type;

        GLint location;

        std::string name;

        template <class T> void update(const std::initializer_list<T>& value) {
            const T* d = std::data(value);

            // Uniform not found or optimized away (how annoying)
            if (location == -1) return;

            if (value.size() == 1) {
                if constexpr (std::is_signed_v<T>        ) { glUniform1i (location, d[0]); }
                if constexpr (std::is_unsigned_v<T>      ) { glUniform1ui(location, d[0]); }
                if constexpr (std::is_floating_point_v<T>) { glUniform1f (location, d[0]); }
            }

            if (value.size() == 2) {
                if constexpr (std::is_signed_v<T>        ) { glUniform2i (location, d[0], d[1]); }
                if constexpr (std::is_unsigned_v<T>      ) { glUniform2ui(location, d[0], d[1]); }
                if constexpr (std::is_floating_point_v<T>) { glUniform2f (location, d[0], d[1]); }
            }

            if (value.size() == 3) {
                if constexpr (std::is_signed_v<T>        ) { glUniform3i (location, d[0], d[1], d[2]); }
                if constexpr (std::is_unsigned_v<T>      ) { glUniform3ui(location, d[0], d[1], d[2]); }
                if constexpr (std::is_floating_point_v<T>) { glUniform3f (location, d[0], d[1], d[2]); }
            }

            if (value.size() == 4) {
                if constexpr (std::is_signed_v<T>        ) { glUniform4i (location, d[0], d[1], d[2], d[3]); }
                if constexpr (std::is_unsigned_v<T>      ) { glUniform4ui(location, d[0], d[1], d[2], d[3]); }
                if constexpr (std::is_floating_point_v<T>) { glUniform4f (location, d[0], d[1], d[2], d[3]); }
            }
        }
    };

    static inline std::string get_uniform_definition(const uniform_t& u) {
        return "uniform " + uniform_type_names[(int)u.type] + " " + u.name + ";\n";
    }

    namespace internal {
        static bool compile_shader(GLuint shader, const char* source, GLint* log_size) {
            GLint result;

            glShaderSource(shader, 1, &source, NULL);
            glCompileShader(shader);

            glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

            if (log_size) {
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, log_size);
            }

            return result;
        }

        std::string get_line(std::string s, int line) {
            int l = 1, i = 0;

            std::string ls;

            while (l < line) {
                if (s[i++] == '\n') l++;
            }

            while (s[i] != '\n')
                ls.append(std::string(1, s[i++]));
            
            return ls;
        }

        int parse_error_line_number(const char* buf) {
            std::string ln;

            int i = 0;

            while (std::isdigit(buf[2 + i]))
                ln.append(std::string(1, buf[2 + i++]));
            
            return std::stoi(ln);
        }
    }

    /** This class contains all the necessary data for
     *  representing and updating a shader with input(s)
     *  and an output
     */
    class shader_t {
        std::string m_name = "";
        std::string m_vert_src = "";
        std::string m_frag_src = "";

        GLuint m_program = 0,
               m_vert_shader = 0,
               m_frag_shader = 0;

        // Input texture
        bool m_use_input_texture = false;
        bool m_input_texture_allocated = false;
        GLuint m_texture = 0;
        uint32_t* m_buf = nullptr;
        float m_input_width = 0, m_input_height = 0;
        float m_output_width = 0, m_output_height = 0;
        float m_scale = 0;

        // Framebuffer
        bool m_framebuffer_created = false;
        GLuint m_framebuffer = 0, m_framebuffer_texture = 0;

        bool m_framebuffer_buf_allocated = false;
        uint32_t* m_framebuffer_buf = nullptr;

        // VAO, VBO
        GLuint m_vao = 0, m_vbo = 0;
        bool m_vao_vbo_created = false;

        std::vector <uniform_t> m_uniforms;

        int m_time = 0;
        int m_input_resolution = 0;
        int m_resolution = 0;
        int m_frame = 0;
        int m_input_texture = 0;

        int m_mouse_x = 0, m_mouse_y = 0;
        int m_mouse = 0;

        int m_frames_rendered = 0;

        /**
         *  \brief Compile the shader sources stored on this shader.
         *         This function should be called after calling shader_t::init()
         *         (either manually or by constructing).
         *         If there are any errors during compilation, they will be pretty printed to
         *         your console.
         *  
         *  \return Whether compilation was successful
         */
        bool compile() {
            GLint log_size;

            std::string frag_header, vert_header;

            frag_header = m_base_frag_header;
            vert_header = m_base_vert_header;

            // Append input uniforms as definitions to source
            for (uniform_t& u : m_uniforms) {
                if (!u.on_source) {
                    frag_header.append(get_uniform_definition(u));
                    vert_header.append(get_uniform_definition(u));
                }
            }

            // Append sources to final headers
            std::string frag_src, vert_src;

            frag_src = frag_header + m_frag_src;
            vert_src = vert_header + m_vert_src;

            if (!internal::compile_shader(m_vert_shader, vert_src.c_str(), &log_size)) {
                // Failed compiling vertex shader
                // Print error log
                char buf[0x200];

                glGetShaderInfoLog(m_vert_shader, 0x200, NULL, buf);

                int ln = internal::parse_error_line_number(buf);

                _log(error, ESCAPE(37) "Vertex" ESCAPE(0) " shader compilation failed!\n%s", buf);

                _log(info, "here -> %s", internal::get_line(vert_src, ln).c_str());

                return false;
            }

            if (!internal::compile_shader(m_frag_shader, frag_src.c_str(), &log_size)) {
                // Failed compiling fragment shader
                // Print error log
                char buf[0x200];

                glGetShaderInfoLog(m_frag_shader, 0x200, NULL, buf);

                int ln = internal::parse_error_line_number(buf);

                _log(error, ESCAPE(37) "Fragment" ESCAPE(0) " shader compilation failed!\n%s", buf);

                _log(info, "here -> %s", internal::get_line(frag_src, ln).c_str());

                return false;
            }

            return true;
        }

        /**
         *  \brief Link the shaders to the GPU program. This function
         *         should be called after compiling. If there are any errors
         *         during linkage, they will be pretty printed to your console.
         *  
         *  \return Whether linkage was successful
         */
        bool link() {
            m_program = glCreateProgram();

            glAttachShader(m_program, m_vert_shader);
            glAttachShader(m_program, m_frag_shader);
            glLinkProgram(m_program);

            glDeleteShader(m_vert_shader);
            glDeleteShader(m_frag_shader);

            // Get uniform locations
            for (uniform_t& u : m_uniforms) {
                u.location = glGetUniformLocation(m_program, u.name.c_str());
            }

            GLint result, log_size;

            glValidateProgram(m_program);
            glGetProgramiv(m_program, GL_LINK_STATUS, &result);

            if (!result) {
                // Link failed
                // Print error log
                glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &log_size);

                char buf[0x200];

                int size = 0;

                glGetProgramInfoLog(m_program, 0x200, &size, buf);

                _log(warning, "Shader link failed!\n%s", buf);

                return false;
            }

            return true;
        }

        /**
         *  \brief Generate Vertex Array and Vertex Buffer objects
         *         for this shader
         */
        void generate_vao_vbo() {
            // Generate and bind VAO
            glGenVertexArrays(1, &m_vao);
            glBindVertexArray(m_vao);

            // Generate VBO
            glGenBuffers(1, &m_vbo);

            static GLfloat const quad[12] = {
                -1.f, -1.f, 0.f,
                -1.f, +1.f, 0.f,
                +1.f, -1.f, 0.f,
                +1.f, +1.f, 0.f,
            };

            // Bind VBO
            glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(0);
        }

        bool generate_framebuffer() {
            glGenFramebuffers(1, &m_framebuffer);
            glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);

            glGenTextures(1, &m_framebuffer_texture);
            glBindTexture(GL_TEXTURE_2D, m_framebuffer_texture);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

            // Give an empty image to OpenGL
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RGBA,
                (int)(m_output_width), (int)(m_output_height),
                0,
                GL_RGBA,
                GL_UNSIGNED_BYTE,
                0
            );

            glBindTexture(GL_TEXTURE_2D, 0);

            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_framebuffer_texture, 0);

            // Set the list of draw buffers.
            GLenum draw_buffers[1] = { GL_COLOR_ATTACHMENT0 };

            glDrawBuffers(1, draw_buffers);

            GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

            if (status != GL_FRAMEBUFFER_COMPLETE) {
                // Framebuffer creation failed
                // Print error
                _log(error, "Framebuffer creation failed with status %u", status);

                return false;
            }

            // Restore main framebuffer (screen)
            glBindFramebuffer(GL_FRAMEBUFFER, 0);

            m_framebuffer_created = true;

            return true;
        }
    
    public:
        /**
         *  \brief Get a pointer to the array of uniforms
         *         for this shader
         * 
         *  \return A pointer to an std::vector of uniform_t
         */
        std::vector <uniform_t>* get_uniforms() {
            return &m_uniforms;
        }

        /**
         *  \brief Update the values of the mouse uniform
         * 
         *  \param x New X coord
         *  \param y New Y coord
         */
        void update_mouse_position(int x, int y) {
            m_mouse_x = x;
            m_mouse_y = y;
        }

        /**
         *  \brief Specify the size of the input texture
         * 
         *  \param width Width of the input texture
         *  \param height Height of the input texture
         */
        void set_input_size(int width, int height) {
            m_input_width = width;
            m_input_height = height;
        }

        /**
         *  \brief Set the size and scale of the output buffer
         * 
         *  \param width Width of the output buffer
         *  \param height Height of the output buffer
         *  \param scale Scale of the output buffer
         */
        void set_output_size(float width, float height, float scale = 1.0) {
            m_output_width = width;
            m_output_height = height;
            m_scale = scale;
        }

        /**
         *  \brief Add a uniform to the array of uniforms.
         *         If the uniform isn't present on source beforehand
         *         you'll have to call this function before compiling
         * 
         *  \param type Type of the uniform
         *  \param name Name of the uniform
         *  \param on_source Is the uniform already present on source?
         * 
         *  \return Index of the newly added uniform on the array of uniforms
         */
        int add_uniform(uniform_type_t type, const std::string& name, bool on_source = false) {
            uniform_t uniform;

            uniform.id        = (int)m_uniforms.size();
            uniform.on_source = on_source;
            uniform.type      = type;
            uniform.name      = name;
            uniform.location  = 0;

            m_uniforms.push_back(uniform);

            return uniform.id;
        }

        /**
         *  \brief Update the uniform on index
         * 
         *  \param index Index of the uniform to update
         *  \param value New value
         */
        template <class T> void update_uniform(int index, std::initializer_list<T> value) {
            m_uniforms[index].update(value);
        }

        /**
         *  \brief Get a pointer to the uniform on index
         * 
         *  \param index Index on the array of uniforms
         */
        uniform_t* get_uniform(int index) {
            return &m_uniforms[index];
        }

        /**
         *  \brief Bind a texture for usage as an input texture for the
         *         shader
         * 
         *  \param buf Pointer to an array containing texture data
         *  \param width Width of the texture
         *  \param height Height of the texture
         */
        void bind_input_texture(uint32_t* buf, int width, int height) {
            if (!m_vao_vbo_created) {
                generate_vao_vbo();

                m_vao_vbo_created = true;
            }

            if (!m_input_texture_allocated) {
                glGenTextures(1, &m_texture);

                glBindTexture(GL_TEXTURE_2D, m_texture);

                // set the texture wrapping/filtering options (on the currently bound texture object)
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width * m_scale, height * m_scale, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

                m_input_texture_allocated = true;
            }

            m_use_input_texture = true;
            m_input_width = width;
            m_input_height = height;
            m_buf = buf;
        }

        /**
         *  \brief Bind a buffer for usage as an output buffer for
         *         the shader
         * 
         *  \param buf Pointer to an array for filling in output data
         */
        bool bind_output_buf(uint32_t* buf) {
            if (!m_framebuffer_created) {
                if (!generate_framebuffer()) {
                    // Couldn't generate framebuffer
                    // Print error
                    _log(error, "Couldn't create framebuffer");

                    return false;
                }
            }

            m_framebuffer_buf = buf;

            return true;
        }

        /**
         *  \brief This function is deleted because we don't allocate
         *         output buffers ourselves anymore
         */
        void free_output_buf() = delete; /* {
            if (m_framebuffer_buf_allocated) {
                delete[] m_framebuffer_buf;
            }
        } */

        /**
         *  \brief Bind this shader.
         *         This makes the GPU use this shader next time render() is called
         */
        void bind() {
            if (m_use_input_texture) {
                glActiveTexture(GL_TEXTURE0);

                glBindTexture(GL_TEXTURE_2D, m_texture);

                glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_input_width * m_scale, m_input_height * m_scale, GL_RGBA, GL_UNSIGNED_BYTE, m_buf);
            }

            glUseProgram(m_program);

            update_uniform(m_input_resolution, { m_input_width, m_input_height });
            update_uniform(m_resolution, { m_output_width, m_output_height });
            update_uniform(m_frame, { m_frames_rendered++ });
            update_uniform(m_mouse, { (float)m_mouse_x, (float)m_mouse_y });
            // m_time: To-do
        }

        /**
         *  \brief Initialize this shader. This is the first thing you should call
         *         after default-constructing a shader
         */
        void init() {
            if (m_vert_shader) {
                glDeleteShader(m_vert_shader);
            }

            if (m_frag_shader) {
                glDeleteShader(m_frag_shader);
            }

            m_vert_shader = glCreateShader(GL_VERTEX_SHADER);
            m_frag_shader = glCreateShader(GL_FRAGMENT_SHADER);

            // Append basic uniforms
            m_mouse             = add_uniform(ut_2f       , "mouse");
            m_input_resolution  = add_uniform(ut_2f       , "input_resolution");
            m_resolution        = add_uniform(ut_2f       , "resolution");
            m_frame             = add_uniform(ut_1i       , "frame");
            m_time              = add_uniform(ut_1f       , "time");
            m_input_texture     = add_uniform(ut_sampler2d, "input_texture");
        }

        /**
         *  \brief Main constructor
         * 
         *  \param vert_src String containing the source of the vertex shader
         *  \param frag_src String containing the source of the fragment shader
         */
        shader_t(const std::string& vert_src, const std::string& frag_src, std::string name = "") {
            m_name = name;
            m_vert_src = vert_src;
            m_frag_src = frag_src;

            init();
        }

        ~shader_t() = default;

        /**
         *  \brief Compile, link, and create VAOs and VBOs
         * 
         *  \return Whether any of the steps described above failed
         */
        bool compile_and_link() {
            if (!compile()) {
                // Shader compilation failed
                // Print error
                _log(error, "Shader compilation failed\n");

                return false;
            }

            if (!link()) {
                // Shader link failed
                // Print error
                _log(error, "Shader link failed\n");

                return false;
            }

            if (!m_vao_vbo_created) {
                generate_vao_vbo();

                m_vao_vbo_created = true;
            }

            return true;
        }

        /**
         *  \brief Get the GL framebuffer for this shader
         * 
         *  \return GLuint for this shader's framebuffer
         */
        GLuint get_framebuffer() {
            return m_framebuffer;
        }

        /**
         *  \brief Get the width of the output buffer for this shader
         * 
         *  \return Output buffer width
         */
        float get_output_width() {
            return m_output_width;
        }

        /**
         *  \brief Get the height of the output buffer for this shader
         * 
         *  \return Output buffer height
         */
        float get_output_height() {
            return m_output_height;
        }

        /**
         *  \brief Get a pointer to this shader's framebuffer output buffer
         * 
         *  \return Pointer to this shader's framebuffer output buffer
         */
        uint32_t* get_framebuffer_buf() {
            return m_framebuffer_buf;
        }
    };

    /**
     *  \brief Bind a shader for the GPU to use next time render() is called
     * 
     *  \param shader Shader to bind
     */
    void bind(shader_t& shader) {
        shader.bind();
    }

    /**
     *  \brief This function actually renders the scene to this shader's
     *         framebuffer
     */
    void render_impl() {
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }

    /**
     *  \brief Render the scene using a shader to an arbitrary buffer
     */
    void render_to_framebuffer(shader_t& shader, uint32_t* buf = nullptr) {
        if (buf) shader.bind_output_buf(buf);

        glBindFramebuffer(GL_FRAMEBUFFER, shader.get_framebuffer());

        shader.bind();

        render_impl();

        glReadPixels(0, 0, shader.get_output_width(), shader.get_output_height(), GL_RGBA, GL_UNSIGNED_BYTE, buf);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    // -----------------------------------------------------------
    //                     Simple interface
    // -----------------------------------------------------------
    std::vector <shader_t> m_shaders;

    int m_output_width = 0, m_output_height = 0;
    int m_input_width = 0, m_input_height = 0;
    float m_scale = 1.0f;
    uint32_t* m_scaled;
    uint32_t* m_input;

    /**
     *  \brief Push a shader to the shader stack given vertex and fragment shader
     *         sources, use this function if you already have sources loaded in memory
     * 
     *  \param vert_src String containing the vertex shader's source
     *  \param frag_src String containing the fragment shader's source
     */
    int push_shader_impl(std::string vert_src, std::string frag_src) {
        glass::shader_t shader(vert_src, frag_src);

        shader.set_output_size(m_output_width, m_output_height);
        shader.compile_and_link();

        int current = m_shaders.size();
        int prev = current - 1;

        m_shaders.push_back(shader);

        if (m_shaders.size() > 1) {
            uint32_t* buf = new uint32_t[m_output_width * m_output_height];

            m_shaders[prev].bind_output_buf(buf);
            m_shaders[current].bind_input_texture(buf, m_output_width, m_output_height);
        }

        return current;
    }

    /**
     *  \brief Push a shader to the shader stack getting its sources from files
     * 
     *  \param vert_src_path String containing a file path to the vertex shader's source 
     *  \param frag_src_path String containing a file path to the fragment shader's source
     */
    int push_shader(std::string vert_src_path, std::string frag_src_path) {
        std::string vert_src;
        std::ifstream vert_file(vert_src_path, std::ios::binary);

        if (!(vert_file.is_open() && vert_file.good())) {
            _log(warning, "Couldn't open " ESCAPE(37) "vertex" ESCAPE(0) " shader source file \"%s\"", vert_src_path.c_str());

            return 0;
        }

        std::getline(vert_file, vert_src, '\0');

        std::string frag_src;
        std::ifstream frag_file(frag_src_path, std::ios::binary);

        if (!(frag_file.is_open() && frag_file.good())) {
            _log(warning, "Couldn't open " ESCAPE(37) "fragment" ESCAPE(0) " shader source file \"%s\"", frag_src_path.c_str());

            return 0;
        }
        
        std::getline(frag_file, frag_src, '\0');

        return push_shader_impl(vert_src, frag_src);
    }

    /**
     *  \brief Push a shader to the shader stack given a path to the shader's
     *         fragment shader source file.
     *         The default vertex shader source is used for the vertex shader
     * 
     *  \param frag_src_path String containing a file path to the fragment shader's source
     */
    int push_shader(std::string frag_src_path) {
        std::string frag_src;
        std::ifstream frag_file(frag_src_path, std::ios::binary);

        if (!(frag_file.is_open() && frag_file.good())) {
            _log(warning, "Couldn't open " ESCAPE(37) "fragment" ESCAPE(0) " shader source file \"%s\"", frag_src_path.c_str());

            return 0;
        }

        std::getline(frag_file, frag_src, '\0');

        return push_shader_impl(default_vert_shader, frag_src);
    }

    /**
     *  \brief Specify the size and scale of the output buffer.
     *         This allows arbitrary scaling of the output image
     * 
     *  \param width Width of the output buffer
     *  \param height Height of the output buffer
     *  \param scale Scale of the output buffer
     */
    void set_output_size(int width, int height, float scale = 1.0f) {
        m_output_width = width * scale;
        m_output_height = height * scale;
        m_scale = scale;
    }

    /**
     *  \brief Add a uniform to all shaders on the shader stack
     * 
     *  \param type Type of the newly added uniform
     *  \param name Name of the newly added uniform
     */
    int add_uniform(uniform_type_t type, std::string name) {
        int index = 0;

        for (shader_t& shader : m_shaders) {
            index = shader.add_uniform(type, name);

            shader.compile_and_link();
        }

        return index;
    }

    /**
     *  \brief Update the mouse uniform of all the shaders on the shader stack
     * 
     *  \param x New X coord
     *  \param y New Y coord
     */
    void update_mouse(int x, int y) {
        for (shader_t& shader : m_shaders)
            shader.update_mouse_position(x, y);
    }

    /**
     *  \brief Update a uniform given an index on all shaders on the shader stack
     * 
     *  \param index Index of the uniform to update
     *  \param value New value for the uniform
     */
    template <class T> void update_uniform(int index, std::initializer_list<T> value) {
        for (shader_t& shader : m_shaders)
            shader.update_uniform(index, value);
    }

    /**
     *  \brief Update a uniform given the uniform's name on all shaders on the shader stack
     * 
     *  \param name Name of the uniform to update
     *  \param value New value for the uniform
     */
    template <class T> void update_uniform(std::string name, std::initializer_list<T> value) {
        auto uniforms = m_shaders.front().get_uniforms();

        auto i = std::find_if(
            std::begin(*uniforms),
            std::end(*uniforms),
            [name](uniform_t& u){ return u.name == name; }
        );

        update_uniform((int)std::distance(std::begin(*uniforms), i), value);
    }

    /**
     *  \brief Set the input texture for the first shader in the stack.
     *         This function does not copy the buffer to an internal buffer,
     *         its saved as a pointer so it can be read from every time
     *         render() is called
     * 
     *  \param buf Pointer to a buffer containing texture data
     *  \param width Width of the input texture
     *  \param height Height of the input texture
     */
    void set_input(uint32_t* buf, int width, int height) {
        shader_t& first = m_shaders.front();

        m_input_width = width;
        m_input_height = height;

        if (m_scale != 1.0) {
            m_scaled = new uint32_t[(int)((m_input_width * m_scale) * (m_input_height * m_scale))];
            m_input = buf;
        } else {
            m_scaled = buf;
        }

        first.bind_input_texture(m_scaled, m_input_width, m_input_height);
    }

    /**
     *  \brief Set an output buffer for the shader stack to render to
     * 
     *  \param buf Pointer to a buffer for the shader stack to render to
     */
    void set_output(uint32_t* buf) {
        shader_t& last = m_shaders.back();

        last.bind_output_buf(buf);
    }

    typedef void (*for_each_shader_fn_t)(void*);

    /**
     *  \brief Render using the shader stack, optionally running some code before
     *         each shader on the stack is rendered
     * 
     *  \param for_each_shader Pointer to a function that will be called before each shader is
     *         rendered
     *  \param data Pointer to some data that will be passed to the aforementioned function
     */
    void render(for_each_shader_fn_t for_each_shader = nullptr, void* data = nullptr) {
        if (m_scale != 1.0f) {
            // Copy original image to scaled buffer
            for (int y = 0; y < m_input_height; y++) {
                std::memcpy(
                    &m_scaled[y * m_input_width],
                    &m_input[y * m_input_width],
                    m_input_width * sizeof(uint32_t)
                );
            }
        }

        for (shader_t& shader : m_shaders) {
            uint32_t* buf = shader.get_framebuffer_buf();

            if (buf) {
                render_to_framebuffer(shader, buf);
            } else {
                shader.bind();

                if (for_each_shader) for_each_shader(data);

                render_impl();
            }
        }
    }
}

#ifndef GLASS_USE_GL_LOADER
#undef glCreateShader
#undef glShaderSource
#undef glCompileShader
#undef glGetShaderiv
#undef glGetShaderInfoLog
#undef glDeleteShader
#undef glAttachShader
#undef glCreateProgram
#undef glLinkProgram
#undef glValidateProgram
#undef glGetProgramiv
#undef glGetProgramInfoLog
#undef glUseProgram
//#undef glBindFragDataLocation
#undef glGetUniformLocation
#undef glUniform1f
#undef glUniform2f
#undef glUniform3f
#undef glUniform4f
#undef glUniform1i
#undef glGenVertexArrays
#undef glBindVertexArray
#undef glGenBuffers
#undef glBindBuffer
#undef glBufferData
#undef glVertexAttribPointer
#undef glEnableVertexAttribArray
#undef glActiveTexture
#undef glGenFramebuffers
#undef glBindFramebuffer
#undef glFramebufferTexture
#undef glFramebufferTexture2D
#undef glDrawBuffers
#undef glCheckFramebufferStatus
//#undef glGetTextureImage
#undef glGenTextures
#undef glBindTexture
#undef glTexParameteri
#undef glTexParameterf
#undef glTexImage2D
#undef glTexSubImage2D
#undef glDrawArrays
//#undef glClearColor
//#undef glClear
#undef glReadPixels
#endif