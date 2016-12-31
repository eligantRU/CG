uniform vec2 center;
uniform float radius;
uniform float border;
uniform vec4 color;

void DrawRing(vec2 center, float radius, float border, vec4 color)
{   
    vec2 pos = gl_TexCoord[0].xy;
    border *= 0.5;      
    if ((distance(pos, center) <= radius + border) && (distance(pos, center) >= radius - border))
    {
        gl_FragColor = color;
    }
}

void main()
{   
    DrawRing(center, radius, border, color);    
}
