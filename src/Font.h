#pragma once

#include "pch.h"
#include "Utils.h"
#include "Texture.h"
#include "File.h"


extern void DrawTexture(Texture *texture, float x, float y, float w, float h, const Color &color);

extern void DrawTexture(Texture *texture, float x, float y,const Rectangle &clip, const Color &color);
extern void DrawTexture(Texture *texture, float x, float y, float scale,const Rectangle &clip, const Color &color);




struct Font 
{

        Font()
        {
            m_height = 1;
            m_length = 0;
            m_proportion = 1.0f;
        }
        bool Load(const std::string & fileName)
        {
           
            std::ifstream file(fileName);
           
            std::string path = GetFilePath(fileName);
            std::string texture =path +  GetFileNameNoExtension(fileName) + ".tga";
             m_texture.Load(texture);


            m_height =1;

            if (file.is_open()) 
            {
                std::string line;
                while (std::getline(file, line)) 
                {
                    Character data;
                    
                    std::istringstream iss(line);
                // std::cout<<line<<std::endl;

                    data.width= 1;
                    data.height= 1;
                    data.xoffset= 0;
                    data.yoffset= 0;
                    data.x=0;
                    data.y=0;



                    size_t start = line.find('"');
                    size_t end = line.find('"', start + 1);
                    if (start != std::string::npos && end != std::string::npos) 
                    {
                    data.id = line[start + 1];
                    data.c = line[start + 1];
                    }



                    // Verificamos se a linha tem o número esperado de valores separados por delimitadores
                    std::stringstream ss(line.substr(end + 1));
                    char delimiter;
                    if (ss >> delimiter >> 
                    data.x >> delimiter >> 
                    data.y >> delimiter >> 
                    data.width >> delimiter >> 
                    data.height >> delimiter >> data.xoffset >> delimiter >> data.yoffset  )
                    {
                    
                        if (delimiter != ',' || ss.fail()) 
                        {
                            Log(1, "Formato incorreto na linha: %s",line.c_str());
                            return false;
                        }



                        if (data.height > m_height) 
                        {
                            m_height = data.height;
                        }


                    m_letters.push_back(data);
                    m_sizes.push_back(data.width);
                    m_offsets.push_back(Vec2(data.xoffset,data.yoffset));
                    }

                
                
                }
                file.close();
                return true;
            } else 
            {
                Log(2, "Erro ao abrir o arquivo de fonte");
                return false;
            }
            
        }
        void DrawText(const char *text, float x, float y, float scale, const Color &color)
        {
            float fx = x;
            float fy = y;
          
 
            float max_width=1;
            float total =0;


        while (*text) 
        {
            if (*text == '\n') 
            {
            fy += int(m_height * scale);
            fx = x;
            
            } else 
            if (*text == ' ') 
            {
            fx += int(max_width * scale);
            } else
            {
                Uint32 i = static_cast<unsigned char>(*text) - 33;
                fx +=  m_proportion * scale  ;
                Rectangle clip;
                
                Vec2 offset = m_offsets[i];
                clip.x = m_letters[i].x;
                clip.y = m_letters[i].y;
                clip.width = m_letters[i].width;
                clip.height = m_letters[i].height;

                if (max_width < clip.width)
                {
                    max_width = clip.width;
                }
               
                
                total += (clip.width ) * scale * m_proportion;       
                DrawTexture(&m_texture, fx, fy + offset.y, scale, clip, color);
                fx += (clip.width ) * scale * m_proportion +  m_letters[i].xoffset;
            
            }
            text++;
        }

        if (total > m_length)
        {
            m_length = total;
        }

    //    DrawTexture(&m_texture, 10,10,120,120, color);

        }
        
        int GetHeight() const { return m_height; }

        int GetWidth(const char *text,float scale=1.0f)
        {
            Uint16 width =0;
            Uint32 n;
            for(const char* p = text; *p; ++p)
            {
                n = (*p) - 33;
                if ( n > (Uint32)m_sizes.size())
                    n = 0;
                width += (int)m_sizes[n] * scale * m_proportion;
            }
            return width;
        }

        void DrawText(float x, float y,float scale, const Color &color, const char *text, ...)
        {
            char buffer[512];
            va_list args;
            va_start(args, text);
            vsprintf(buffer, text, args);
            va_end(args);
            DrawText(buffer, x, y,scale, color);
        }

        private:
            struct Character
            {
                char c;
                int id;
                Uint16 x;
                Uint16 y;
                Uint16 width;
                Uint16 height;
                Uint16 xoffset;
                Uint16 yoffset;
            };
        std::vector<Character> m_letters;
        std::vector<Uint16> m_sizes;
        std::vector<Vec2> m_offsets;
        Uint16 m_height;
        Uint16 m_length;
        Texture m_texture;
        float m_proportion;
};
