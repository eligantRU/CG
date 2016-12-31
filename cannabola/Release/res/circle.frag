uniform vec2 center;
uniform float radius;
uniform vec4 color;

void main()
{   
    vec2 pos = gl_TexCoord[0].xy;      
    if (distance(pos, center) <= radius)
    {
        gl_FragColor = color;
    }
}
