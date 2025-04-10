#ifndef RENDER_H_
#define RENDER_H_

#include <GL/glew.h>

#include "shader.h"
#include "buffer.h"
#include "texture.h"
#include "font.h"
#include "node.h"

#include "camera.h"
#include "render.h"

#include "resource_manager.h"

#include "font_render.h"
#include "line_render.h"
#include "rect_render.h"


class Render
{
public:
    Render()
    {
        init();
    }

    void set_viewport(float width, float height)
    {
        glViewport ( 0, 0, width, height );

        _width =  width;
        _height = height;

        float x1 = -_width*0.5f;
        float x2 = _width*0.5f;
        float y1 = -_height*0.5f;
        float y2 = _height*0.5f;
    
        P = glm::ortho (x1, x2, y1, y2, -1.0f, 5.0f);
    

        // P = glm::ortho(0.0f, (float)_width, 0.0f, (float)_height, -1.0f, 5.0f);
    }

    void blend(bool enable)
    {
        if (enable)
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            //glBlendFunc(GL_ONE, GL_ONE);
        }
        else
            glDisable(GL_BLEND);
    }

    void depth(bool enable)
    {
        if (enable)
        {
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS); 
        }
        else
        {
            glDisable(GL_DEPTH_TEST);
        }

    }

    void clear()
    {
        // Clear the colorbuffer
        glClearColor(0.0, 0.0, 0.0, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    }
    

    void draw_buffer_u(Buffer* buffer, Node* node, Camera* camera, Shader* shader, bool blend);

    void draw_line(float xa, float ya, float xb, float yb)
    {
        Shader* shader = rm()->shaders("line").get();

        shader->use();

        shader->set("P", P*M);

        lineRender.draw(*shader, xa, ya, xb, yb, _color, _line_width);
    }

    void draw_line_strip(std::vector<glm::vec3>& points)
    {
        Shader* shader = rm()->shaders("line").get();

        shader->use();

        shader->set("P", P*M);

        lineRender.draw(*shader, points, _color, _line_width);
    }


    void draw_text(const std::string& text, float x, float y)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        // glBlendFunc(GL_ONE, GL_ONE);

	    Shader* shader = rm()->shaders("text").get();
        
        shader->use();

	    shader->set("P", P*M);

        fontRender.draw(*shader, *_font, text, x, y, 1.0f, _color);

        glDisable(GL_BLEND);
    }

    void draw_poly(std::vector<glm::vec3>& points)
    {
        Shader* shader = rm()->shaders("rect_solid").get();
        		
        shader->use();

        shader->set("M", P*M);
		
        rectRender.draw_poly(*shader, points, _color);
    }

    void draw_rect(float xc, float yc, float width, float height)
    {
        Shader* shader = rm()->shaders("rect_solid").get();
        		
        shader->use();

        shader->set("M", P*M);
		
        rectRender.draw(*shader, xc, yc, width, height, _color);
    }

    void draw_rect_with_texture(float xc, float yc, float width, float height)
    {
        
	    Shader* shader = rm()->shaders("rect_tex").get();
        		
        shader->use();

        glActiveTexture ( GL_TEXTURE0 );    
        glBindTexture ( GL_TEXTURE_2D, _tex1->get_texID() );

        shader->set("ourTexture", 0);

        shader->set("M", P*M);

        glEnable(GL_BLEND);
        // glBlendFunc(GL_ONE, GL_SRC_ALPHA);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        rectRender.draw(*shader, xc, yc, width, height);

        glDisable(GL_BLEND);

    }

    void set_transform(glm::mat4& mat)
    {
        M = mat;
    }

    void set_line_width(float width)
    {
        _line_width = width;
    }

    void set_color(const glm::vec4& color)
    {
        _color = color;
    }

    void set_font(Font* font)
    {
        _font = font;
    }

    void set_texture(int slot, Texture* texture)
    {
        if (slot == 0) {
            _tex1 = texture;
        }

        if (slot == 1) {
            _tex2 = texture;
        }
    }

    void load_resources_all()
    {
        rm()->load_shader("rect_solid", "./resources/simple_one_mat.vs", "./resources/rect_solid.fs");
        rm()->load_shader("rect_tex", "./resources/simple_one_mat.vs", "./resources/rect_texture.fs");

        rm()->load_shader("text", "./resources/text.vs", "./resources/text.fs");
        rm()->load_shader("line", "./resources/line.vs", "./resources/line.fs");

        rm()->load_shader("poly", "./resources/simple_one_mat.vs", "./resources/poly.fs");
        rm()->load_shader("line1", "./resources/simple_one_mat.vs", "./resources/lines.fs");
        
        rm()->load_texture("tex1", "./resources/tex1.jpeg");

        rm()->load_font("font1", "./resources/font.ttf");
    }

 private:

    void init()
    {
        _tex1 = nullptr;
        _tex2 = nullptr;

        M = glm::mat4(1.0f);
        P = glm::mat4(1.0f);

        _line_width = 1.0;
        _color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

        fontRender.init();
        lineRender.init();
        rectRender.init();
    }

    FontRender fontRender;
    LineRender lineRender;
    RectRender rectRender;

    Texture *_tex1;
    Texture *_tex2;

    float _line_width;

    glm::vec4 _color;

    Font *_font;

    int _width;
    int _height;

    glm::mat4 P;
    glm::mat4 M;
};


#endif // RENDER_H_
