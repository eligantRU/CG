uniform vec2 center;
uniform vec4 color;

#define M_PI 3.14159265358979

void DrawCannabola(vec2 center, vec4 color)
{
    vec2 pos = gl_TexCoord[0].xy;

    const float eps = M_PI / 2048.0;
    for (float t = 0.0; t < 2.0 * M_PI; t += eps)
    {
        float R = 0.4 * (1.0 + sin(t)) * (1.0 + 0.9 * cos(8.0 * t)) * (1.0 + 0.1 * cos(24.0 * t));
        if (distance(pos, center + vec2(R * cos(t), R * sin(t))) <= 0.01)
        {
            gl_FragColor = color;
        }
    }
}

void main()
{
    DrawCannabola(center, color);
}
