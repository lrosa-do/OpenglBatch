

#include "Texture.h"
#include "Shader.h"
#include "Utils.h"
#include "Font.h"



 int SCREEN_WIDTH = 1024;
 int SCREEN_HEIGHT = 720;


unsigned int vaoId;         
unsigned int vboId;      
unsigned int iboId;   

Shader shader;



void DrawRectangle(float x, float y, float w, float h, const Color &color)
{
    Vertex vertices[4];
    vertices[0].pos = { x, y, 0 };
    vertices[1].pos = { x + w, y, 0 };
    vertices[2].pos = { x + w, y + h, 0 };
    vertices[3].pos = { x, y + h, 0 };
    vertices[0].color = color;
    vertices[1].color = color;
    vertices[2].color = color;
    vertices[3].color = color;
    vertices[0].uv = { 0, 0 };
    vertices[1].uv = { 1, 0 };
    vertices[2].uv = { 1, 1 };
    vertices[3].uv = { 0, 1 };
    unsigned int indices[6] = { 0, 1, 2, 2, 3, 0 };
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STREAM_DRAW);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void DrawRectangleLines(float x, float y, float w, float h,const Color &color)
{
    Vertex vertices[4];
    vertices[0].pos = { x, y, 0 };
    vertices[1].pos = { x + w, y, 0 };
    vertices[2].pos = { x + w, y + h, 0 };
    vertices[3].pos = { x, y + h, 0 };
    vertices[0].color = color;
    vertices[1].color = color;
    vertices[2].color = color;
    vertices[3].color = color;
    vertices[0].uv = { 0, 0 };
    vertices[1].uv = { 1, 0 };
    vertices[2].uv = { 1, 1 };
    vertices[3].uv = { 0, 1 };
    unsigned int indices[8] = { 0, 1, 1, 2, 2, 3, 3, 0 };
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STREAM_DRAW);
    glDrawElements(GL_LINES, 8, GL_UNSIGNED_INT, 0);
}

void DrawLine(float x1, float y1, float x2, float y2,const Color &color)
{
    Vertex vertices[2];
    vertices[0].pos = { x1, y1, 0 };
    vertices[1].pos = { x2, y2, 0 };
    vertices[0].color = color;
    vertices[1].color = color;
    vertices[0].uv = { 0, 0 };
    vertices[1].uv = { 0, 0 };
    unsigned int indices[2] = { 0, 1 };
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STREAM_DRAW);
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, 0);
}

void DrawCircleLines(float x, float y, float radius,const Color &color)
{
    int segments = 32;
    Vertex vertices[32];
    for (int i = 0; i < segments; i++)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(segments);
        float x1 = radius * cosf(theta);
        float y1 = radius * sinf(theta);
        vertices[i].pos = { x + x1, y + y1, 0 };
        vertices[i].color = color;
        vertices[i].uv = { 0, 0 };
    }
    unsigned int indices[64];
    for (int i = 0; i < segments; i++)
    {
        indices[i * 2] = i;
        indices[i * 2 + 1] = (i + 1) % segments;
    }
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STREAM_DRAW);
    glDrawElements(GL_LINES, segments * 2, GL_UNSIGNED_INT, 0);
}

void DrawCircle(float x, float y, float radius,const Color &color)
{
    int segments = 32;
    Vertex vertices[32];
    for (int i = 0; i < segments; i++)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(segments);
        float x1 = radius * cosf(theta);
        float y1 = radius * sinf(theta);
        vertices[i].pos = { x + x1, y + y1, 0 };
        vertices[i].color = color;
        vertices[i].uv = { 0, 0 };
    }
    unsigned int indices[64];
    for (int i = 0; i < segments; i++)
    {
        indices[i * 2] = i;
        indices[i * 2 + 1] = (i + 1) % segments;
    }
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STREAM_DRAW);
    glDrawElements(GL_TRIANGLE_FAN, segments * 2, GL_UNSIGNED_INT, 0);
}

void DrawTexture(Texture *texture, float x, float y, float w, float h, const Color &color)
{
    Vertex vertices[4];
    vertices[0].pos = { x, y, 0 };
    vertices[1].pos = { x + w, y, 0 };
    vertices[2].pos = { x + w, y + h, 0 };
    vertices[3].pos = { x, y + h, 0 };
    vertices[0].color = color;
    vertices[1].color = color;
    vertices[2].color = color;
    vertices[3].color = color;
    vertices[0].uv = { 0, 0 };
    vertices[1].uv = { 1, 0 };
    vertices[2].uv = { 1, 1 };
    vertices[3].uv = { 0, 1 };
    unsigned int indices[6] = { 0, 1, 2, 2, 3, 0 };
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STREAM_DRAW);
    glBindTexture(GL_TEXTURE_2D, texture->id);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void DrawTexture(Texture *texture, float x, float y, float w, float h,const Rectangle &clip, const Color &color)
{
    Vertex vertices[4];
    vertices[0].pos = { x, y, 0 };
    vertices[1].pos = { x + w, y, 0 };
    vertices[2].pos = { x + w, y + h, 0 };
    vertices[3].pos = { x, y + h, 0 };
    vertices[0].color = color;
    vertices[1].color = color;
    vertices[2].color = color;
    vertices[3].color = color;
    vertices[0].uv = { clip.x / texture->width, clip.y / texture->height };
    vertices[1].uv = { (clip.x + clip.width) / texture->width, clip.y / texture->height };
    vertices[2].uv = { (clip.x + clip.width) / texture->width, (clip.y + clip.height) / texture->height };
    vertices[3].uv = { clip.x / texture->width, (clip.y + clip.height) / texture->height };
    unsigned int indices[6] = { 0, 1, 2, 2, 3, 0 };
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STREAM_DRAW);
    glBindTexture(GL_TEXTURE_2D, texture->id);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void DrawTexture(Texture *texture, float x, float y,const Rectangle &clip, const Color &color)
{
    Vertex vertices[4];
    float w = clip.width;
    float h = clip.height;
    vertices[0].pos = { x, y, 0 };
    vertices[1].pos = { x + w, y, 0 };
    vertices[2].pos = { x + w, y + h, 0 };
    vertices[3].pos = { x, y + h, 0 };
    vertices[0].color = color;
    vertices[1].color = color;
    vertices[2].color = color;
    vertices[3].color = color;
    vertices[0].uv = { clip.x / texture->width, clip.y / texture->height };
    vertices[1].uv = { (clip.x + clip.width) / texture->width, clip.y / texture->height };
    vertices[2].uv = { (clip.x + clip.width) / texture->width, (clip.y + clip.height) / texture->height };
    vertices[3].uv = { clip.x / texture->width, (clip.y + clip.height) / texture->height };
    unsigned int indices[6] = { 0, 1, 2, 2, 3, 0 };
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STREAM_DRAW);
    glBindTexture(GL_TEXTURE_2D, texture->id);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
void DrawTexture(Texture *texture, float x, float y, float scale,const Rectangle &clip, const Color &color)
{
    Vertex vertices[4];
    vertices[0].pos = { x, y, 0 };
    vertices[1].pos = { x + clip.width * scale, y, 0 };
    vertices[2].pos = { x + clip.width * scale, y + clip.height * scale, 0 };
    vertices[3].pos = { x, y + clip.height * scale, 0 };
    vertices[0].color = color;
    vertices[1].color = color;
    vertices[2].color = color;
    vertices[3].color = color;
    vertices[0].uv = { clip.x / texture->width, clip.y / texture->height };
    vertices[1].uv = { (clip.x + clip.width) / texture->width, clip.y / texture->height };
    vertices[2].uv = { (clip.x + clip.width) / texture->width, (clip.y + clip.height) / texture->height };
    vertices[3].uv = { clip.x / texture->width, (clip.y + clip.height) / texture->height };
    unsigned int indices[6] = { 0, 1, 2, 2, 3, 0 };
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STREAM_DRAW);
    glBindTexture(GL_TEXTURE_2D, texture->id);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void DrawTexture(Texture *texture, float x, float y, float center_x,float center_y,float rotate,float hscale,float vscale,const Rectangle &clip, const Color &color)
{
    Vertex vertices[4];
    float tx1 = -center_x * hscale;
    float ty1 = -center_y * vscale;
    float tx2 = (clip.width - center_x) * hscale;
    float ty2 = (clip.height - center_y) * vscale;

    float x1 = tx1 * cosf(rotate) - ty1 * sinf(rotate);
    float y1 = tx1 * sinf(rotate) + ty1 * cosf(rotate);
    float x2 = tx2 * cosf(rotate) - ty1 * sinf(rotate);
    float y2 = tx2 * sinf(rotate) + ty1 * cosf(rotate);
    float x3 = tx2 * cosf(rotate) - ty2 * sinf(rotate);
    float y3 = tx2 * sinf(rotate) + ty2 * cosf(rotate);
    float x4 = tx1 * cosf(rotate) - ty2 * sinf(rotate);
    float y4 = tx1 * sinf(rotate) + ty2 * cosf(rotate);

    vertices[0].pos = { x + x1, y + y1, 0 };
    vertices[1].pos = { x + x2, y + y2, 0 };
    vertices[2].pos = { x + x3, y + y3, 0 };
    vertices[3].pos = { x + x4, y + y4, 0 };

    vertices[0].color = color;
    vertices[1].color = color;
    vertices[2].color = color;
    vertices[3].color = color;

    vertices[0].uv = { clip.x / texture->width, clip.y / texture->height };
    vertices[1].uv = { (clip.x + clip.width) / texture->width, clip.y / texture->height };
    vertices[2].uv = { (clip.x + clip.width) / texture->width, (clip.y + clip.height) / texture->height };
    vertices[3].uv = { clip.x / texture->width, (clip.y + clip.height) / texture->height };

    unsigned int indices[6] = { 0, 1, 2, 2, 3, 0 };

    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STREAM_DRAW);

    glBindTexture(GL_TEXTURE_2D, texture->id);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

   
}

void DrawTexture(Texture *texture, float x, float y, float center_x,float center_y,float rotate,float hscale,float vscale,const Rectangle &clip,bool h_flip,bool v_flip, const Color &color)
{
    Vertex vertices[4];
    float tx1 = -center_x * hscale;
    float ty1 = -center_y * vscale;
    float tx2 = (clip.width - center_x) * hscale;
    float ty2 = (clip.height - center_y) * vscale;

    float x1 = tx1 * cosf(rotate) - ty1 * sinf(rotate);
    float y1 = tx1 * sinf(rotate) + ty1 * cosf(rotate);
    float x2 = tx2 * cosf(rotate) - ty1 * sinf(rotate);
    float y2 = tx2 * sinf(rotate) + ty1 * cosf(rotate);
    float x3 = tx2 * cosf(rotate) - ty2 * sinf(rotate);
    float y3 = tx2 * sinf(rotate) + ty2 * cosf(rotate);
    float x4 = tx1 * cosf(rotate) - ty2 * sinf(rotate);
    float y4 = tx1 * sinf(rotate) + ty2 * cosf(rotate);

    vertices[0].pos = { x + x1, y + y1, 0 };
    vertices[1].pos = { x + x2, y + y2, 0 };
    vertices[2].pos = { x + x3, y + y3, 0 };
    vertices[3].pos = { x + x4, y + y4, 0 };

    vertices[0].color = color;
    vertices[1].color = color;
    vertices[2].color = color;
    vertices[3].color = color;

    float left = clip.x / texture->width;
    float right = (clip.x + clip.width) / texture->width;
    float top = clip.y / texture->height;
    float bottom = (clip.y + clip.height) / texture->height;

    if (h_flip)
    {
        float temp = left;
        left = right;
        right = temp;
    }

    if (v_flip)
    {
        float temp = top;
        top = bottom;
        bottom = temp;
    }

    vertices[0].uv = { left, top };
    vertices[1].uv = { right, top };
    vertices[2].uv = { right, bottom };
    vertices[3].uv = { left, bottom };

    unsigned int indices[6] = { 0, 1, 2, 2, 3, 0 };

    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STREAM_DRAW);

    glBindTexture(GL_TEXTURE_2D, texture->id);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


   
    

}


void DrawTexture(Texture *texture, const std::vector<Vertex> &vertex, const std::vector<unsigned int> &index, int count, int mode)
{
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(Vertex), vertex.data(), GL_STREAM_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(unsigned int), index.data(), GL_STREAM_DRAW);
    glBindTexture(GL_TEXTURE_2D, texture->id);
    glDrawElements(mode, count, GL_UNSIGNED_INT, 0);
}



class Batch
{
    public:
    Batch()
    {
         texture.Load("resources/zazaka.tga");
         max_buffer = 60000;
       //   vertex.resize (max_buffer*4);
        //  indices.resize(max_buffer*6);
         numIndices = 0;
         numVertex = 0;
         offset = 0;
         count = 0;
        int k=0;
         for (int i = 0; i < max_buffer; i++)
         {

            vertex.push_back(Vertex(0, 0, 0, 0, 0, 255, 255, 255, 255));
            vertex.push_back(Vertex(0, 0, 0, 0, 0, 255, 255, 255, 255));
            vertex.push_back(Vertex(0, 0, 0, 0, 0, 255, 255, 255, 255));
            vertex.push_back(Vertex(0, 0, 0, 0, 0, 255, 255, 255, 255));
             
            indices.push_back(k);
            indices.push_back(k + 1);
            indices.push_back(k + 2);
            indices.push_back(k);
            indices.push_back(k + 2);
            indices.push_back(k + 3);
            k+=4;
         }
    }
    void reset()
    {
       
       
       // indices.clear();
       // vertex.clear();
    }
    
    void add(float x, float y, float w, float h, const Color &color)
    {
      
        vertices[0].pos.set( x, y, 0 );
        vertices[1].pos.set( x + w, y, 0 );
        vertices[2].pos.set( x + w, y + h, 0 );
        vertices[3].pos.set( x, y + h, 0 );

        vertices[0].color.set(color.r, color.g, color.b, color.a);
        vertices[1].color.set(color.r, color.g, color.b, color.a);
        vertices[2].color.set(color.r, color.g, color.b, color.a);
        vertices[3].color.set(color.r, color.g, color.b, color.a);
        
        vertices[0].uv.set( 0, 0 );
        vertices[1].uv.set( 1, 0 );
        vertices[2].uv.set( 1, 1 );
        vertices[3].uv.set( 0, 1 );

        add(vertices[0], vertices[1], vertices[2], vertices[3]);

    }

    void add(const Vertex &v1, const Vertex &v2, const Vertex &v3, const Vertex &v4)
    {

        if (count >= max_buffer - 4)
        {
            Log(1, "Buffer Reset");
            reset();
        }
      

        vertex[numVertex++    ] = v1;
        vertex[numVertex++    ] = v2;
        vertex[numVertex++    ] = v3;
        vertex[numVertex++    ] = v4;
        
     

        // indices[numIndices++] = offset;
        // indices[numIndices++] = offset + 1;
        // indices[numIndices++] = offset + 2;
        // indices[numIndices++] = offset;
        // indices[numIndices++] = offset + 2;
        // indices[numIndices++] = offset + 3;
        
        // vertex.push_back(v1);
        // vertex.push_back(v2);
        // vertex.push_back(v3);
        // vertex.push_back(v4);

     

        // indices.push_back(offset);
        // indices.push_back(offset + 1);
        // indices.push_back(offset + 2);
        // indices.push_back(offset);
        // indices.push_back(offset + 2);
        // indices.push_back(offset + 3);

       

        offset+=4;
        count+=1;
    }
        



    void render()
    {

      DrawTexture(&texture, vertex, indices, count * 6 , GL_TRIANGLES);
        offset = 0;
        count = 0;
        numVertex = 0;
        numIndices=0;
 
    }
    private:
     Vertex vertices[4];
     std::vector<Vertex> vertex;
     std::vector<unsigned int> indices;
     Texture texture;
     int offset = 0;
     int numVertex = 0;
     int numIndices =0;
     int count = 0;
     int max_buffer;
};


const int LINES = 0;
const int TRIANGLES = 1;

class Primitives
{
    public:
    Primitives()
    {
        colorr = 255;
        colorg = 255;
        colorb = 255;
        colora = 255;
        texcoordx = 0;
        texcoordy = 0;
        mode = 0;
        linesCout = 0;
        trianglesCount = 0;
        
        elementCount= 10000;
        
        
        texture.createDefault();
        for (int i = 0; i < elementCount; i++)
        {
            lines.push_back(Vertex(0, 0, 0, 0, 0, 255, 255, 255, 255));
            lines.push_back(Vertex(0, 0, 0, 0, 0, 255, 255, 255, 255));
            lines.push_back(Vertex(0, 0, 0, 0, 0, 255, 255, 255, 255));
            lines.push_back(Vertex(0, 0, 0, 0, 0, 255, 255, 255, 255));
            triangles.push_back(Vertex(0, 0, 0, 0, 0, 255, 255, 255, 255));
            triangles.push_back(Vertex(0, 0, 0, 0, 0, 255, 255, 255, 255));
            triangles.push_back(Vertex(0, 0, 0, 0, 0, 255, 255, 255, 255));
            triangles.push_back(Vertex(0, 0, 0, 0, 0, 255, 255, 255, 255));
        }
    }
    void Mode(bool fill)
    {
        
        if (fill)
            mode = TRIANGLES;
        else
            mode = LINES;
     
    }
        
    void Vertex3f(float x, float y, float z)
    {
        if (mode==LINES)
        {
           
            lines[linesCout].pos.set(x,y,z);
            lines[linesCout].uv.set(texcoordx,texcoordy);
            lines[linesCout].color.set(colorr,colorg,colorb,colora);
            linesCout++;
        } 
        else
        if (mode==TRIANGLES)
        {
            triangles[trianglesCount].pos.set(x,y,z);
            triangles[trianglesCount].uv.set(texcoordx,texcoordy);
            triangles[trianglesCount].color.set(colorr,colorg,colorb,colora);
            trianglesCount++;
        }
    }

    void Vertex2f(float x, float y)
    {
        Vertex3f(x, y, 0);
    }

    void Color4(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
    {
        colorr = r;
        colorg = g;
        colorb = b;
        colora = a;
    }
    void Color3(unsigned char r, unsigned char g, unsigned char b)
    {
        Color4(r, g, b, 255);
    }

    void Line(float x1, float y1, float x2, float y2,const Color &c)
    {
        Mode(false);
        Color4(c.r, c.g, c.b, c.a);
        Vertex3f(x1, y1, 0);
        Vertex3f(x2, y2, 0);
    }
    void Rectangle(float x, float y, float w, float h,const Color &c,bool fill)
    {
        if (fill)
        {
            Mode(true);
            Color4(c.r, c.g, c.b, c.a);
           
            Vertex2f(x   , y);
            Vertex2f(x, y + h);
            Vertex2f( x + w  , y);

            Vertex2f( x + w   , y);
            Vertex2f(x , y + h);
            Vertex2f( x + w, y + h);
            
        }
        else
        {
            Mode(false);
            Color4(c.r, c.g, c.b, c.a);
            Vertex2f(x , y );
            Vertex2f(x + w, y );

            Vertex2f(x + w, y );
            Vertex2f(x + w, y + h);

            Vertex2f(x + w, y + h);
            Vertex2f(x , y + h);

            Vertex2f(x , y + h);
            Vertex2f(x , y );
        }
    }
    void Circle(float x,float y, float radius, const Color &c,bool fill)
    {
        if (fill)
        {
            Mode(true);
            Color4(c.r, c.g, c.b, c.a);
            float angle = 0.0f;
            float angleInc = 1.0f / radius;
            for (int i = 0; i < 360; i++)
            {
                Vertex2f(x, y);
                Vertex2f(x + cos(angle) * radius, y + sin(angle) * radius);
                angle += angleInc;
                Vertex2f(x + cos(angle) * radius, y + sin(angle) * radius);
            }

        } else 
        {

         
            Mode(false);
            Color4(c.r, c.g, c.b, c.a);
            float angle = 0.0f;
            float angleInc = 1.0f / radius;
            for (int i = 0; i < 360; i++)
            {
                Vertex2f(x + cos(angle) * radius, y + sin(angle) * radius);
                angle += angleInc;
                Vertex2f(x + cos(angle) * radius, y + sin(angle) * radius);
            }

        }
    }


    void Render()
    {
        glBindTexture(GL_TEXTURE_2D, texture.id);

        if (trianglesCount>0)
        {
            glBindBuffer(GL_ARRAY_BUFFER, vboId);
            glBufferData(GL_ARRAY_BUFFER, trianglesCount * sizeof(Vertex), triangles.data(), GL_STREAM_DRAW);
            glDrawArrays(GL_TRIANGLES, 0, trianglesCount*3);
        }

        if (linesCout > 0)
        {
            glBindBuffer(GL_ARRAY_BUFFER, vboId);
            glBufferData(GL_ARRAY_BUFFER, linesCout * sizeof(Vertex), lines.data(), GL_STREAM_DRAW);
            glDrawArrays(GL_LINES, 0, linesCout*2);
        }


        
        linesCout = 0;
        trianglesCount = 0;
    }
    


private:
    int mode;                 
    
    int linesCout;
    int trianglesCount;
        
    
    int elementCount;

    std::vector<Vertex> lines;
    std::vector<Vertex> triangles;
    float texcoordx, texcoordy;         
    float colorr, colorg, colorb, colora;
    

    Texture texture;
};

 struct Bunny 
 {
    Vec2 position;
    Vec2 speed;
    Color color;
} ;


int GetRandomValue(int min, int max)
{
    return min + rand() % (max - min + 1);
}


void IniVBO()
{
    
    glGenVertexArrays(1,&vaoId);
    glBindVertexArray(vaoId);
    glGenBuffers(1, &vboId);
    glGenBuffers(1, &iboId);
    glBindVertexArray(0);
   
}

void FreeVBO()
{
    glDeleteBuffers(1, &vboId);
    glDeleteBuffers(1, &iboId);
    glDeleteVertexArrays(1, &vaoId);
}

int main()
{
   




    if (SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        SDL_Log( "Erro ao inicializar a SDL %s ", SDL_GetError() );
        return -1;
    }
 

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
       

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    

    SDL_Window* window = SDL_CreateWindow("aka djoker", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,  SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!window) 
    {
        SDL_Log( "Error creating window%s " , SDL_GetError() );
        SDL_Quit();
        return -1;
    }


    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) 
    {
        SDL_Log(  "Erro creating  OpenGL  context %s ",SDL_GetError() );
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    SDL_GL_SetSwapInterval(1);

   SDL_Log("Vendor  :  %s",glGetString(GL_VENDOR));
   SDL_Log("Renderer:  %s",glGetString(GL_RENDERER));
   SDL_Log("Version :  %s",glGetString(GL_VERSION));

    IniVBO();


        const char* vertexShaderSource = R"(
        #version 310 es
        precision highp float;
        layout (location = 0) in vec3 Position;
        layout (location = 1) in vec2 UV;
        layout (location = 2) in vec4 Color;
        uniform mat4 ProjMtx;
        out vec2 Frag_UV;
        out vec4 Frag_Color;
        void main()
        {
            Frag_UV = UV;
            Frag_Color = Color;
            gl_Position = ProjMtx * vec4(Position,1);
        }
        )";

     const char* fragmentShaderSource = R"(
        #version 310 es
        precision mediump float;
        uniform sampler2D texture0;
        in vec2 Frag_UV;
        in vec4 Frag_Color;
        layout (location = 0) out vec4 Out_Color;
        void main()
        {
            Out_Color = Frag_Color * texture(texture0, Frag_UV.st);
        }
        )";

    shader.Create(vertexShaderSource, fragmentShaderSource);
    shader.BindUniform("ProjMtx");
    shader.BindUniform("texture0");
    shader.setInt("texture0", 0);

    Texture defaultTexture;
    defaultTexture.createDefault();

    Font font;
    font.Load("resources/font5.fnt");

    Batch batch;
    Primitives primitives;

    std::vector<Bunny*> bunnies;

    //    int max_buffer = 100000;
    //    for (int i = 0; i < max_buffer; i++)
    //    {
    //        Bunny *bunny = new Bunny();
    //        bunny->position.x = GetRandomValue(0, SCREEN_WIDTH);
    //        bunny->position.y = GetRandomValue(0, SCREEN_HEIGHT);
    //        bunny->speed.x = GetRandomValue(-250, 250) ;
    //        bunny->speed.y = GetRandomValue(-250, 250) ;

    //        bunny->color.r = GetRandomValue(50, 255);
    //        bunny->color.g = GetRandomValue(50, 255);
    //        bunny->color.b = GetRandomValue(50, 255);

    //        bunnies.push_back(bunny);
    //    }

    double lastTime = GetTime();
    int frameCount = 0;
    double fps = 0.0;
    Uint32 lastFrameTime = GetTicks(); 
     bool quit = false;
    while (!quit) 
    {
       
        Uint32 currentFrameTime = GetTicks(); 
        Uint32 deltaTimeUint32 = currentFrameTime - lastFrameTime; 
        double deltaTime = deltaTimeUint32 / 1000; 


        SDL_Event event;
        while (SDL_PollEvent(&event)) 
        {
            switch (event.type)
            {

                case SDL_QUIT:
                {
                     quit = true;
                    break;    
                }
             
                case SDL_WINDOWEVENT:
                {
                    if (event.window.event == SDL_WINDOWEVENT_RESIZED)
                    {
                        int w = event.window.data1;
                        int h = event.window.data2;
                        SCREEN_WIDTH = w;
                        SCREEN_HEIGHT = h;
                        glViewport(0, 0, w, h);
                    
                    }
                    break;  
                }    
                case SDL_MOUSEMOTION:
                {
                                break;
                }
                case SDL_MOUSEBUTTONDOWN:
                {
                  
                             break;
                }
                case SDL_MOUSEBUTTONUP:
                {

                  
                           
                    break;
                }
                case SDL_MOUSEWHEEL:
                {   
                          break;
                }

                
                case SDL_KEYUP:
                {
                         break;
                }
            
                case SDL_KEYDOWN:
                {
                      if (event.key.keysym.sym == SDLK_ESCAPE)      quit = true;
                    
                    break;  
                }

            }

        }

        int mouseX, mouseY;
        int button = SDL_GetMouseState(&mouseX, &mouseY);

        if (button & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            for (int i = 0; i < 100; i++)
            {
                Bunny *bunny = new Bunny();
                bunny->position.x = mouseX;
                bunny->position.y = mouseY;
                bunny->speed.x = GetRandomValue(-250, 250) /60.0f;
                bunny->speed.y = GetRandomValue(-250, 250) /60.0f;

                bunny->color.r = GetRandomValue(50, 255);
                bunny->color.g = GetRandomValue(50, 255);
                bunny->color.b = GetRandomValue(50, 255);

                bunnies.push_back(bunny);
            }
        }


        float L = 0;
        float R = SCREEN_WIDTH;
        float T = 0;
        float B = SCREEN_HEIGHT;

         float ortho_projection[4][4] =
        {
            { 2.0f/(R-L),   0.0f,         0.0f,   0.0f },
            { 0.0f,         2.0f/(T-B),   0.0f,   0.0f },
            { 0.0f,         0.0f,        -1.0f,   0.0f },
            { (R+L)/(L-R),  (T+B)/(B-T),  0.0f,   1.0f },
        };

        glDisable(GL_DEPTH_TEST);    
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        
        glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        
        
        glBindVertexArray(vaoId);
        glBindBuffer(GL_ARRAY_BUFFER, vboId);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(0, 2, GL_FLOAT,         GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, pos));
        glVertexAttribPointer(1, 3, GL_FLOAT,         GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, uv));
        glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE,  sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
        glBindVertexArray(0);
            
        shader.use();
        shader.setMatrix("ProjMtx",  &ortho_projection[0][0]);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, defaultTexture.id);
        glBindVertexArray(vaoId);
      
        // DrawRectangle(20,20,250,250, Color(255,0,0));
   
        // DrawRectangleLines(20,20,250,250, Color(255,255,0));

        // DrawCircleLines(350,150,100, Color(255,0,255));
        // DrawCircle(350,150,100, Color(255,0,255));

   
        // DrawLine(20,20,100,100,Color(255,0,255,255));

     
        batch.add(100, 400, 64, 64, Color(255, 255, 255));

        // batch.add(200, 400, 64, 64, Color(255, 255, 255));

        // batch.add(300, 400, 64, 64, Color(255, 255, 255));
        


        for (int i = 0; i < (int)bunnies.size(); i++)
        {
            Bunny *bunny = bunnies[i];
            bunny->position.x += bunny->speed.x;
            bunny->position.y += bunny->speed.y;

            float width  = 64;
            float height = 64;

             if (((bunny->position.x + width/2) > SCREEN_WIDTH) ||
                (bunny->position.x + width/2) < 0) bunny->speed.x *= -1;

            if (((bunny->position.y + height/2) > SCREEN_HEIGHT) ||
                (bunny->position.y + height/2 - 40) < 0) bunny->speed.y *= -1;
        


            batch.add(bunny->position.x, bunny->position.y, 64, 64, bunny->color);
          //  DrawTexture(&defaultTexture, bunny->position.x, bunny->position.y, 32, 32, bunny->color);
          }

        batch.render();

        primitives.Line(0, 0, mouseX, mouseY, Color(255, 0, 0));
        primitives.Line(SCREEN_WIDTH, SCREEN_HEIGHT, mouseX, mouseY, Color(255, 0, 0));
        primitives.Line(0, SCREEN_HEIGHT, mouseX, mouseY, Color(255, 0, 0));
        primitives.Line(SCREEN_WIDTH, 0, mouseX, mouseY, Color(255, 0, 0));

 
        
        primitives.Rectangle(250, 50, 50, 50, Color(255, 0, 0), true);//1 0 18
        primitives.Rectangle(480, 100, 50, 50, Color(255, 0, 0), true);
        primitives.Rectangle(mouseX, mouseY, 25, 25, Color(255, 0, 0), true);

        primitives.Rectangle(100, 100, 100, 100, Color(255, 0, 0), false);//0 0 16

        primitives.Circle(100, 100, 50, Color(255, 0, 0), false);

        primitives.Circle(180, 100, 50, Color(255, 0, 0), true);

 

        primitives.Render();


        font.DrawText("AKA LUIS", 20, 300,2, Color(255,255,255));  
        font.DrawText("1234567890", 20, 340,2, Color(255,255,255));  

        font.DrawText(10,10,1, Color(255,255,255), "%d", bunnies.size());
 
         
        glBindVertexArray(0); 
     
  
        
         
        SDL_GL_SwapWindow(window);

        double currentTime = GetTime();
        frameCount++;
        if (currentTime - lastTime >= 1.0)
         {
            fps = frameCount / (currentTime - lastTime);
            std::string title = "aka djoker  [" + std::to_string(static_cast<int>(fps)) + ", "+std::to_string(deltaTime)+"ms]" ;
         
            SDL_SetWindowTitle(window, title.c_str()    );
            frameCount = 0;
            lastTime = currentTime;
        }
        lastFrameTime = currentFrameTime;



    }

    for (int i = 0; i < (int)bunnies.size(); i++)
    {
        delete bunnies[i];
    }
 
    FreeVBO();
    Log(0,"Bye");
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();


    return 0;
}

