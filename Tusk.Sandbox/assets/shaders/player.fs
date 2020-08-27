#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 LightPos;
in vec2 TexCoords;

//in vec3 TangentLightPos;
in vec3 TangentFragPos;

struct DirLight {
    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
uniform DirLight dirLight;

uniform sampler2D texture_diffuse;
uniform sampler2D texture_normal1;
uniform sampler2D texture_specular1;

uniform vec3 lightColor;

void main() {
    //vec3 normal = texture(texture_normal1, TexCoords).rgb;
    //normal = normalize(normal * 2.0 - 1.0); 
    //
    //// ambient
    //vec3 ambient = dirLight.ambient * texture(texture_diffuse1, TexCoords).rgb;    
    //
    // // diffuse 
    ////vec3 lightDir = normalize(TangentLightPos - TangentFragPos);
    //vec3 lightDir = normalize(-dirLight.direction);
    //float diff = max(dot(normal, lightDir), 0.0);
    //vec3 diffuse = dirLight.diffuse * diff * texture(texture_diffuse1, TexCoords).rgb;
    //
    //// specular
    //vec3 viewDir = normalize(-TangentFragPos);
    //vec3 reflectDir = reflect(-lightDir, normal);  
    //float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    //vec3 specular = dirLight.specular * spec * texture(texture_specular1, TexCoords).rgb; 
    //
    //float alpha = texture(texture_diffuse1, TexCoords).a;
    //vec3 result = ambient + diffuse + specular;
    //FragColor = vec4(result, alpha);


    FragColor = texture(texture_diffuse, TexCoords);
    //FragColor = vec4(1.0);
}