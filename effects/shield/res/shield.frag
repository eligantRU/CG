uniform sampler2D colormap;

void main()
{
    gl_FragColor = texture2D(colormap, gl_TexCoord[0].st);
}
