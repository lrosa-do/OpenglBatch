#pragma once
#include "pch.h"


#define CONSOLE_COLOR_RESET "\033[0m"
#define CONSOLE_COLOR_GREEN "\033[1;32m"
#define CONSOLE_COLOR_RED "\033[1;31m"
#define CONSOLE_COLOR_PURPLE "\033[1;35m"
#define CONSOLE_COLOR_CYAN "\033[0;36m"


enum PixelFormat
{
    GRAYSCALE = 1,     
    GRAY_ALPHA,        
    R8G8B8,            
    R8G8B8A8,          
};

struct Vec3
{
    float x, y, z;
    Vec3() 
    {
        x = 0;
        y = 0;
        z = 0;
    }
    Vec3(float x, float y, float z) 
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    Vec3(const Vec3& other) 
    {
        x = other.x;
        y = other.y;
        z = other.z;
    }
    Vec3& operator=(const Vec3& other) 
    {
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }
    void set(float x, float y, float z) 
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

struct Vec2
{
    float x, y;
    Vec2() 
    {
        x = 0;
        y = 0;
    }
    Vec2(float x, float y) 
    {
        this->x = x;
        this->y = y;
    }
    Vec2(const Vec2& other) 
    {
        x = other.x;
        y = other.y;
    }
    Vec2& operator=(const Vec2& other) 
    {
        x = other.x;
        y = other.y;
        return *this;
    }
    void set(float x, float y) 
    {
        this->x = x;
        this->y = y;
    }
};
struct Rectangle
{
    float x, y, width, height;
    Rectangle() 
    {
        x = 0;
        y = 0;
        width = 0;
        height = 0;
    }
    Rectangle(float x, float y, float width, float height) 
    {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
    }
    Rectangle(const Rectangle& other) 
    {
        x = other.x;
        y = other.y;
        width = other.width;
        height = other.height;
    }
    Rectangle& operator=(const Rectangle& other) 
    {
        x = other.x;
        y = other.y;
        width = other.width;
        height = other.height;
        return *this;
    }
    void set(float x, float y, float width, float height) 
    {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
    }
};

struct Color 
{
    unsigned char r, g, b, a;
    Color() 
    {
        r = 255;
        g = 255;
        b = 255;
        a = 255;
    }
    Color (unsigned char r, unsigned char g, unsigned char b, unsigned char a) 
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }
    Color (unsigned char r, unsigned char g, unsigned char b) 
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = 255;
    }
    Color(const Color& other) 
    {
        r = other.r;
        g = other.g;
        b = other.b;
        a = other.a;
    }
    void set(unsigned char r, unsigned char g, unsigned char b, unsigned char a) 
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }
    Color& operator=(const Color& other) 
    {
        r = other.r;
        g = other.g;
        b = other.b;
        a = other.a;
        return *this;
    } 
};

struct Vertex
{
    Vec3 pos;
    Vec2 uv;
    Color color;

    Vertex() 
    {
        pos.set(0, 0, 0);
        uv.set(0, 0);
        color.set(255, 255, 255, 255);
    }
    Vertex(float x, float y, float z, float u, float v, unsigned char r, unsigned char g, unsigned char b, unsigned char a) 
    {
        pos.set(x, y, z);
        uv.set(u, v);
        color.set(r, g, b, a);
    }
    Vertex(float x, float y, float z, float u, float v, Color color) 
    {
        pos.set(x, y, z);
        uv.set(u, v);
        this->color = color;
    }
    Vertex(float x, float y, float z, float u, float v) 
    {
        pos.set(x, y, z);
        uv.set(u, v);
        color.set(255, 255, 255, 255);
    }

    Vertex(float x, float y, float z) 
    {
        pos.set(x, y, z);
        uv.set(0, 0);
        color.set(255, 255, 255, 255);
    }

    Vertex(const Vertex& other) 
    {
        pos = other.pos;
        uv = other.uv;
        color = other.color;
    }

    Vertex& operator=(const Vertex& other) 
    {
        pos = other.pos;
        uv = other.uv;
        color = other.color;
        return *this;
    }
};



void Log(int severity, const char* fmt, ...);
char *LoadFileText(const char *fileName);

bool FileExists(const std::string& filename) ;

Uint32 LoadShaderProgram(Uint32 vShaderId, Uint32 fShaderId);
Uint32 CompileShader(const char *shaderCode, int type);

Uint32 CreateTexture(const void *data, int width, int height, PixelFormat format);

Uint32 LoadShaderFromFile(const char *vsFileName, const char *fsFileName);
Uint32 LoadShaderFromMemory(const char *vsCode, const char *fsCode);

void UnloadVertexArray(Uint32 vaoId);

void UnloadVertexBuffer(Uint32 vboId);

void UnloadTexture(Uint32 id);

Uint32 GetTicks(void);
double GetTime(void);

std::string GetFileExtension(const std::string& filename) ;
std::string GetFileName(const std::string& filepath) ;
std::string GetFileNameNoExtension(const std::string& filepath) ;
std::string GetFilePath(const std::string& filepath) ;
std::string ToLower(const std::string& str) ;

std::string StringReplace(const std::string& haystack, const std::string& needle, const std::string& replacement);
std::vector<std::string> Split(const std::string &s, char delim);
