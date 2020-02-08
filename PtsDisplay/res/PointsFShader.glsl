varying vec3 v_position;
varying vec3 v_color;
uniform bool isColor;

void main()
{
    if(isColor)
        gl_FragColor = vec4(v_color.r,v_color.g,v_color.b,1.0);
    else
        gl_FragColor = vec4(0.0,0.0,0.0,1.0);
}




