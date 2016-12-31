uniform vec2 center;
uniform float radius;
uniform vec4 color;

void main()
{   
    vec2 pos = gl_TexCoord[0].xy;      
    if (distance(pos, center) <= radius)
    {
        gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    }
    
    /*const vec2 p0 = vec2(1.0, 1.0);
    const vec2 p1 = vec2(3.0, 2.0);
    const vec2 p2 = vec2(2.5, 3.5);
    const vec2 d = vec2(-0.5, -0.5);
    if (pow(pos.x + d.x, 2) + pow(pos.y + d.y, 2) <= 0.1)
    {
    	gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    }*/
}
