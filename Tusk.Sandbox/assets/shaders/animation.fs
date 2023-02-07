#version 330 core
out vec4 FragColor;

in vec2 texCoords;
in vec3 normal;
in vec3 fragPos;

struct DirLight {
    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
uniform DirLight dirLight;

uniform sampler2D texture_diffuse;

void main() {
    // ambient
    vec3 ambient = dirLight.ambient * texture(texture_diffuse, texCoords).rgb;    
    
     // diffuse 
    vec3 lightDir = normalize(-dirLight.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = dirLight.diffuse * diff * texture(texture_diffuse, texCoords).rgb;
    
    // specular
    vec3 viewDir = normalize(-fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = dirLight.specular * spec * texture(texture_diffuse, texCoords).rgb; 
    
    float alpha = texture(texture_diffuse, texCoords).a;
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, alpha);
}