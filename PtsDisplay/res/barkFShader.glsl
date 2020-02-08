#version 120
uniform vec3 viewPos;
uniform bool isLight;
uniform bool isColor;
varying vec3 v_position;
varying vec3 v_normal;
varying vec3 v_color;


vec3 CalLight(vec3 lightPos,vec3 lightColor,float ambient,float specular)
{
    vec3 norm = normalize(v_normal);

    vec3 ambientLight = ambient*lightColor;

    vec3 lightDir = normalize(lightPos - v_position);

    float diffuse = max(dot(norm, lightDir),0.0);

    vec3 diffuseLight = diffuse*lightColor;

    vec3 viewDir = normalize(viewPos - v_position);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    vec3 specularLight = specular * spec * lightColor;

    return (ambientLight+diffuseLight+specularLight);
}

void main()
{
    vec3 objectColor = v_color; // 物体表面的颜色
    if(!isColor)
        objectColor = vec3(0.8,0.8,0.8);

    if(isLight)
    {
        vec3 lColor1 = vec3(1.0,1.0,1.0);                // 光照的颜色

        vec3 lPos1 = viewPos;          // 光源的位置
        vec3 light = CalLight(lPos1,lColor1,0.3,0.1);

        gl_FragColor = vec4(light * objectColor,1.0);
    }
    else
    {
        gl_FragColor = vec4(objectColor,1.0);
    }
}



