//Author: Chen Chen
//Date: 11/27/2015
#version 400 core

in vec2 TexCoords;
in vec4 VertColor;

out vec4 FragColor;

uniform sampler2D DiffTex1;
uniform float     gamma; // Gamma correction

subroutine void RenderPassType();
subroutine uniform RenderPassType RenderPass;

// Render Point
subroutine (RenderPassType)
    void renderPoint(){
        vec2 temp = gl_PointCoord - vec2(0.5);
        float f = dot(temp, temp);
        if (f>0.25) discard;
        FragColor = pow(VertColor, vec4(1.0 / gamma));
    }

// Render without texture 
subroutine (RenderPassType)                   
    void renderPlain(){                               
        FragColor = pow(VertColor, vec4(1.0 / gamma));
    }

// Render with texture 
subroutine (RenderPassType)                             
    void renderWithTexture(){                               
        FragColor = pow(texture(DiffTex1, TexCoords), vec4(1.0 / gamma));
    }

void main()
{
    RenderPass();
}
