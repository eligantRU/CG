uniform float time;
uniform vec2 resolution;
uniform vec2 aspect;

void DrawSpiral(float time, vec2 resolution, vec2 aspect)
{
    vec2 position = -aspect.xy + 2.0 * gl_FragCoord.xy / resolution.xy * aspect.xy;
    float angle = 0.0;
    float radius = length(position);
    if (position != vec2(0.0, 0.0))
    {
        angle = degrees(atan(position.y, position.x));
    }
    float amod = mod(angle + 30.0 * time - 120.0 * log(radius), 30.0);
    if (amod < 15.0)
    {
        gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
    else
    {
        gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);                    
    }
}

void main()
{
    DrawSpiral(time, resolution, aspect);
}
