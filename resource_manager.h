#ifndef RESOURCE_MANAGER_H_
#define RESOURCE_MANAGER_H_

#include <string>
#include <map>
#include <memory>

#include "shader.h"
#include "texture.h"
#include "font.h"

class ResourceManager
{
public:

    ResourceManager()
    {

    }

    std::shared_ptr<Shader> shaders(const std::string& name)
    {
        return _shaders[name];
    }

    void load_shader(const std::string& name, const std::string& vspath, const std::string& fspath) {

        std::shared_ptr<Shader> shader = std::make_shared<Shader>();

        shader->set_vertex_shader_path(vspath);
        shader->set_fragment_shader_path(fspath);

        shader->build();

        _shaders.insert(std::make_pair(name, shader));
    }


    std::shared_ptr<Texture> textures(const std::string& name)
    {
        return _textures[name];
    }

    void load_texture(const std::string& name, const std::string& path)
    {
        std::shared_ptr<Texture> texture = std::shared_ptr<Texture>(Texture::load(path));

        _textures.insert(std::make_pair(name, texture));
    }


    std::shared_ptr<Font> fonts(const std::string& name)
    {
        return _fonts[name];
    }

    void load_font(const std::string& name, const std::string& path)
    {
        Font *font = new Font();

        std::shared_ptr<Font> font_ptr = std::shared_ptr<Font>(font);

        font->load_from_file(path);
        // font->save_texture_to_file("image.tga");

        _fonts.insert(std::make_pair(name, font_ptr) );    
    }

private:

    std::map<std::string, std::shared_ptr<Shader> > _shaders;
    std::map<std::string, std::shared_ptr<Texture> > _textures;
    std::map<std::string, std::shared_ptr<Font> > _fonts;

};

ResourceManager* rm();

#endif // RESOURCE_MANAGER_H_
